/*******************************************************************************************
**	globalmem虚拟设备实例
**	2017-10-18
*******************************************************************************************/

/*********************************设备结构体和宏*******************************************/
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

#define GLOBALMEM_SIZE	0x1000	/*全局内存大小：4KB*/
#define MEM_CLEAR		0x01	/*清零全局变量*/
#define GLOBALMEM_MAJOR	250		/*预设主设备号*/

static int globalmem_major = GLOBALMEM_MAJOR;

/*********************globalmem设备结构体****************/
struct globalmem_dev{
	struct cdev cdev;	/*cdev结构体*/
	unsigned char mem[GLOBALMEM_SIZE];	/*全局变量*/
};

struct globalmem_dev *globalmem_devp;	/*设备结构体指针实例*/

/**************文件打开函数*********************/
int globalmem_open(struct inode *inode,struct file *filp)
{
	/*struct globalmem_dev *dev;

	dev = container_of(inode->i_cdev,struct globalmem_dev,cdev);*/
	/*将设备结构体指针赋值给文件私有数据指针*/
	filp->private_data = globalmem_devp;
	return 0;
}

/**************文件释放函数*************/
int globalmem_release(struct inode *inode,struct file *filp)
{
	return 0;
}

/******************globalmem设备的ioctl控制函数************************/
static long globalmem_ioctl( struct file *filp, unsigned int cmd,unsigned long arg)
{
	struct globalmem_dev *dev = filp->private_data;	/*获取设备结构体指针*/
	
	switch(cmd){
	case MEM_CLEAR:
		/*清除全局变量*/
		memset(dev->mem,0,GLOBALMEM_SIZE);
		printk("globalmem is set to zero\n");
		break;
	default:
		return -EINVAL;
	}	
	return 0;
}

/**************globalmem设备驱动读函数************************/
static ssize_t globalmem_read(struct file *filp,char __user *buf,size_t size,loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	int ret = 0;
	
	struct globalmem_dev *dev = filp->private_data;	/*获取设备结构体指针*/
	
	/*分析和获取有效读长度*/
	if(p >= GLOBALMEM_SIZE)	/*要读的偏移位置越界*/
		return 0;
	if(count > GLOBALMEM_SIZE - p) /*要读的字节数太大*/
		count = GLOBALMEM_SIZE - p;
	
	/* 内核空间 -- 用户空间 */
	if(copy_to_user(buf,(void*)(dev->mem + p), count))
		ret = -EFAULT;
	else{
		*ppos += count;
		ret = count;

		printk(KERN_INFO "read %u bytes from %lu\n",count,p);
	}

	return ret;
}

/****************globalmem设备驱动写函数*********************/
static ssize_t globalmem_write(struct file *filp,const char __user *buf,size_t size,loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	int ret = 0;

	struct globalmem_dev *dev = filp->private_data;	/*获取设备结构体指针*/

	/*分析和获取有效的写长度*/
	if(p >= GLOBALMEM_SIZE)		/*要写的偏移位置越界*/
		return 0;
	if(count > GLOBALMEM_SIZE - p)	/*要写的字节数太多*/
		count = GLOBALMEM_SIZE -p;
	/*用户空间 -- 内核空间 */
	if(copy_from_user(dev->mem + p,buf,count))
		ret = -EFAULT;
	else {
		*ppos += count;
		ret = count;
		printk(KERN_INFO "written %u bytes from %lu\n",count,p);
	}

	return ret;
}

/***********globalmem设备驱动的seek函数***********/
static loff_t globalmem_llseek(struct file *filp,loff_t offset,int orig)
{
	loff_t ret = 0;
	switch(orig){
	case 0:		/*从文件开头开始偏移*/
		if(offset < 0){
			ret = -EINVAL;
			break;
		}
		if((unsigned int)offset > GLOBALMEM_SIZE){
			ret = -EINVAL;
			break;
		}
		filp->f_pos = (unsigned int)offset;
		ret = filp->f_pos;
		break;
	case 1:		/*从当前位置来是偏移*/
		if((filp->f_pos + offset) > GLOBALMEM_SIZE){
			ret = -EINVAL;
			break;
		}
		if((filp->f_pos + offset) < 0){
			break;
		}
		filp->f_pos += offset;
		ret = filp->f_pos;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}


/*************globalmem设备驱动文件操作结构体******************/
static const struct file_operations globalmem_fops = {
	.owner = THIS_MODULE,
	.llseek = globalmem_llseek,
	.read = globalmem_read,
	.write = globalmem_write,
	.unlocked_ioctl = globalmem_ioctl,
	.open = globalmem_open,
	.release = globalmem_release,
};

/*****************初始化并添加cdev结构体***********************/
static void globalmem_setup_cdev(struct globalmem_dev *dev,int index)
{
	int err,devno = MKDEV(globalmem_major,index);

	cdev_init(&dev->cdev,&globalmem_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev,devno,1);
	if(err){
		printk("Error %d adding globalmem %d\n",err,index);
	}
}
/******************设备驱动模块加载函数*************************/
int globalmem_init(void)
{
	int result;
	dev_t devno = MKDEV(globalmem_major,0);
	
	/*申请字符设备驱动区域*/
	if(globalmem_major){	
		result = register_chrdev_region(devno,1,"globalmem");
	} else {
		result = alloc_chrdev_region(&devno,0,1,"globalmem");
		globalmem_major = MAJOR(devno);
	}
	if(result < 0){
		return result;
	}

	/* 动态申请设备结构体的内存 */
	globalmem_devp = kmalloc(sizeof(struct globalmem_dev),GFP_KERNEL);
	if(!globalmem_devp){
		goto fail_malloc;
	}

	memset(globalmem_devp,0,sizeof(struct globalmem_dev));

	globalmem_setup_cdev(globalmem_devp,0);
	return 0;

fail_malloc:
	unregister_chrdev_region(devno,1);
	return result;
}

/***************设备驱动模块卸载函数*******************/
void globalmem_exit(void)
{
	cdev_del(&globalmem_devp->cdev);	/*删除cdev结构*/
	kfree(globalmem_devp);
	unregister_chrdev_region(MKDEV(globalmem_major,0),1);	/*注销设备区域*/
}

module_param(globalmem_major,int,S_IRUGO);
module_init(globalmem_init);
module_exit(globalmem_exit);
MODULE_LICENSE("GPL");

