/************************************************************
**	2017-10-18
**	带参数的内核模块测试 
*************************************************************/

#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

static char *book_name = "dissecting Linux Device Driver";
static int num = 4000;

static int book_init(void)
{
	printk("book name:%s\n",book_name);
	printk("book num:%d\n",num);
	return 0;
}

static void book_exit(void)
{
	printk("Book module exit\n");
}

module_init(book_init);
module_exit(book_exit);
module_param(num,int,S_IRUGO);
module_param(book_name,charp,S_IRUGO);

