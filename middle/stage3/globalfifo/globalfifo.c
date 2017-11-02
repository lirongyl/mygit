/******************************************************************
**	globalfifo虚拟设备实例
**	支持堵塞操作的globalfifo驱动
**	2017-11-02
******************************************************************/

/*********************设备结构体和宏*****************************/
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
#include <linux/mutex.h>

#define GLOBALFIFO_SIZE	0x1000	/*全局内存大小：4KB*/
#define MEM_CLEAR		0x01	/*清零全局变量*/
#define GLOBALFIFO_MAJOR	250		/*预设主设备号*/

static int globalfifo_major = GLOBALFIFO_MAJOR;

/*********************globalfifo设备结构体****************/
struct globalfifo_dev{
	struct cdev cdev;	/*cdev结构体*/
	unsigned int current_len;	/*fifo有效数据长度*/
	unsigned char mem[GLOBALFIFO_SIZE];	/*全局变量*/
	struct semaphore sem;	/*并发控制用的信号量*/
	wait_queue_head_t r_wait;	/*阻塞读用的等待队列头*/
	wait_queue_head_t w_wait;	/*阻塞写用的等待队列头*/
};

struct globalfifo_dev *globalfifo_devp;	/*设备结构体指针实例*/

/**************文件打开函数*********************/
int globalfifo_open(struct inode *inode,struct file *filp)
{
	/*struct globalmem_dev *dev;

	dev = container_of(inode->i_cdev,struct globalmem_dev,cdev);*/
	/*将设备结构体指针赋值给文件私有数据指针*/
	filp->private_data = globalfifo_devp;
	return 0;
}

/**************文件释放函数*************/
int globalfifo_release(struct inode *inode,struct file *filp)
{
	return 0;
}

/******************globalfifo设备的ioctl控制函数************************/
static long globalfifo_ioctl( struct file *filp, unsigned int cmd,unsigned long arg)
{
	struct globalfifo_dev *dev = filp->private_data;	/*获取设备结构体指针*/
	
	switch(cmd){
	case MEM_CLEAR:

		if(down_interruptible(&dev->sem))
			return -ERESTARTSYS;
		/*清除全局变量*/
		memset(dev->mem,0,GLOBALFIFO_SIZE);
		up(&dev->sem);	//释放信号量
		printk("globalfifo is set to zero\n");
		break;
	default:
		return -EINVAL;
	}	
	return 0;
}

/**************globalfifo设备驱动读函数************************/
static ssize_t globalfifo_read(struct file *filp,char __user *buf,size_t size,loff_t *ppos)
{
	//unsigned long p = *ppos;
	unsigned int count = size;
	int ret = 0;
	
	struct globalfifo_dev *dev = filp->private_data;	/*获取设备结构体指针*/
	DECLARE_WAITQUEUE(wait,current);	//定义等待队列
	down(&dev->sem);
	add_wait_queue(&dev->r_wait,&wait);	//进入等待队列头
	/*等待FIFO非空*/
	while(dev->current_len == 0){
		if(filp->f_flags & O_NONBLOCK){
			ret = -EAGAIN;
			goto out;
		}
		__set_current_state(TASK_INTERRUPTIBLE);	//改变进程状态为睡眠
		up(&dev->sem);

		schedule();		//调度其他进程执行

		if(signal_pending(current)){
			ret = -ERESTARTSYS;
			goto out2;
		}
		down(&dev->sem);
	}
	//分析和获取有效读长度
	/*if(p >= GLOBALFIFO_SIZE)	//要读的偏移位置越界
		return 0;
	if(count > GLOBALFIFO_SIZE - p) //要读的字节数太大
		count = GLOBALFIFO_SIZE - p;

	if(down_interruptible(&dev->sem)){	//获取信号量
		return -ERESTARTSYS;
	}*/

	if(count > dev->current_len)
		count =  dev->current_len;

	/* 内核空间 -- 用户空间 */
	if(copy_to_user(buf,dev->mem, count)){
		ret = -EFAULT;
		goto out;
	} else {
		memcpy(dev->mem,dev->mem+count,dev->current_len-count);//fifo数据前移
		dev->current_len -= count;	//有效长度减少
		printk(KERN_INFO "read %u bytes from %u\n",count,dev->current_len);
		wake_up_interruptible(&dev->w_wait);	//唤醒写等待队列
		ret =  count;
	}
out:up(&dev->sem);	//释放信号量
out2:remove_wait_queue(&dev->w_wait,&wait);	//移除等待队列
	 set_current_state(TASK_RUNNING);
	return ret;
}

/****************globalfifo设备驱动写函数*********************/
static ssize_t globalfifo_write(struct file *filp,const char __user *buf,size_t size,loff_t *ppos)
{
	unsigned int count = size;
	int ret = 0;

	struct globalfifo_dev *dev = filp->private_data;	/*获取设备结构体指针*/

	DECLARE_WAITQUEUE(wait,current);	//定义等待队列
	down(&dev->sem);	//获取信号量
	add_wait_queue(&dev->w_wait,&wait);	//进入写等待队列头

	/*等待FIFO非满*/
	while(dev->current_len == GLOBALFIFO_SIZE){
		if(filp->f_flags & O_NONBLOCK){
			goto out;
		}
		__set_current_state(TASK_INTERRUPTIBLE);	//改变进程状态为睡眠
		up(&dev->sem);

		schedule();		//调度其他进程执行
		if(signal_pending(current)){
			ret = -ERESTARTSYS;
			goto out2;
		}
		down(&dev->sem);
	}

	if(count > GLOBALFIFO_SIZE - dev->current_len)
		count = GLOBALFIFO_SIZE - dev->current_len;
	/*用户空间 -- 内核空间 */
	if(copy_from_user(dev->mem + dev->current_len,buf,count)){
		ret = -EFAULT;
		goto out;
	} else {
		dev->current_len += count;
		printk(KERN_INFO "written %u bytes from %u\n",count,dev->current_len);
		wake_up_interruptible(&dev->r_wait);
		ret = count;
	}
out: up(&dev->sem);	//释放信号量
out2:remove_wait_queue(&dev->w_wait,&wait);
	 set_current_state(TASK_RUNNING);

	 return ret;
}

/***********globalfifo设备驱动的seek函数***********/
static loff_t globalfifo_llseek(struct file *filp,loff_t offset,int orig)
{
	loff_t ret = 0;
	switch(orig){
	case 0:		/*从文件开头开始偏移*/
		if(offset < 0){
			ret = -EINVAL;
			break;
		}
		if((unsigned int)offset > GLOBALFIFO_SIZE){
			ret = -EINVAL;
			break;
		}
		filp->f_pos = (unsigned int)offset;
		ret = filp->f_pos;
		break;
	case 1:		/*从当前位置来是偏移*/
		if((filp->f_pos + offset) > GLOBALFIFO_SIZE){
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


/*************globalfifo设备驱动文件操作结构体******************/
static const struct file_operations globalfifo_fops = {
	.owner = THIS_MODULE,
	.llseek = globalfifo_llseek,
	.read = globalfifo_read,
	.write = globalfifo_write,
	.unlocked_ioctl = globalfifo_ioctl,
	.open = globalfifo_open,
	.release = globalfifo_release,
};

/*****************初始化并添加cdev结构体***********************/
static void globalfifo_setup_cdev(struct globalfifo_dev *dev,int index)
{
	int err,devno = MKDEV(globalfifo_major,index);

	cdev_init(&dev->cdev,&globalfifo_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev,devno,1);
	if(err){
		printk("Error %d adding globalfifo %d\n",err,index);
	}
}
/******************设备驱动模块加载函数*************************/
int globalfifo_init(void)
{
	int result;
	dev_t devno = MKDEV(globalfifo_major,0);
	
	/*申请字符设备驱动区域*/
	if(globalfifo_major){	
		result = register_chrdev_region(devno,1,"globalfifo");
	} else {
		result = alloc_chrdev_region(&devno,0,1,"globalfifo");
		globalfifo_major = MAJOR(devno);
	}
	if(result < 0){
		return result;
	}

	/* 动态申请设备结构体的内存 */
	globalfifo_devp = kmalloc(sizeof(struct globalfifo_dev),GFP_KERNEL);
	if(!globalfifo_devp){	/*申请失败*/
		result = -ENOMEM;
		goto fail_malloc;
	}

	memset(globalfifo_devp,0,sizeof(struct globalfifo_dev));

	globalfifo_setup_cdev(globalfifo_devp,0);

	sema_init(&globalfifo_devp->sem,1);	//初始化信号量
	init_waitqueue_head(&globalfifo_devp->r_wait);
	init_waitqueue_head(&globalfifo_devp->w_wait);
	return 0;

fail_malloc:
	unregister_chrdev_region(devno,1);
	return result;
}

/***************设备驱动模块卸载函数*******************/
void globalfifo_exit(void)
{
	cdev_del(&globalfifo_devp->cdev);	/*删除cdev结构*/
	kfree(globalfifo_devp);
	unregister_chrdev_region(MKDEV(globalfifo_major,0),1);	/*注销设备区域*/
}

module_param(globalfifo_major,int,S_IRUGO);
module_init(globalfifo_init);
module_exit(globalfifo_exit);
MODULE_LICENSE("GPL");

