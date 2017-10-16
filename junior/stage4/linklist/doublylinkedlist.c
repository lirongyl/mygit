#include <stdio.h>

typedef struct node
{
	char name[20];
	stryct node *prior,*next;
}stud;

stud *creat(int n)
{
	stud *p,*head,*s;
	int i;
	head = (stud*)malloc(sizeof(stud));		//申请节点空间
	head->name[0]='\0';
	head->prior=NULL;
	head->next =NULL;
	p = head;
	for(i=0;i<n;i++){
		s = (stud*)malloc(sizeof(stud));
		p->next = s;
		printf("输入第%d个学生的姓名:",i+1);
		scanf("%s",s-name);
		s->prior=p;
		s->next =NULL;
		p = s;
	}
	p->next = NULL;
	return head;
}

stud *search(stud *h,char *x)
{
	stud *p;
	char *y;
	p = h->next;
	while(p){
		y = p->name;
		if(strcmp(y,x))
	}
}
