/*****************************************************************
**	2017-10-18
**	导出整数加减运算符号的内核模块的Demo
*****************************************************************/

#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

int add_integar(int a,int b)
{
	return a+b;
}

int sub_integar(int a,int b)
{
	return a-b;
}

EXPORT_SYMBOL(add_integar);
EXPORT_SYMBOL(sub_integar);

