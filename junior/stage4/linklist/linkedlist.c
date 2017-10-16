#include <stdio.h>
#include <malloc.h>

struct LNode
{
	int data;
	struct LNode *next;
};

struct LNode *Create(int n)			//创建链表函数
{
	int i;
	struct LNode *head, *p1, *p2;
	int a;
	head = NULL;
	for(i = 0; i < n; i++){
		p1 = (struct LNode *)malloc(sizeof(struct LNode));	//分配空间
		printf("请输入第%d个数据:",i+1);
		scanf("%d",&a);
		p1->data = a;
		if(head == NULL){
			head = p1;
			p2 = p1;
		} else {
			p2->next = p1;
			p2 = p1;
		}
	}
	p2->next = NULL;
	return head;
}

//求单链表中节点的个数
unsigned int GetListLength(struct LNode * pHead)
{
	if(pHead == NULL)
		return 0;
	unsigned int len = 0;
	struct LNode * pCurrent = pHead;
	while(pCurrent != NULL){
		len++;
		pCurrent = pCurrent->next;
	}
	return len;
}

//将单链表反转
struct LNode *ReverseList(struct LNode * pHead)
{
	if(pHead == NULL || pHead->next == NULL)
		return 0;
	struct LNode *pReversedHead = NULL;	//反转后的新链表头指针，初始为NULL
	struct LNode *pCurrent = pHead;
	while(pCurrent != NULL){
		struct LNode *pTemp = pCurrent;
		pCurrent = pCurrent->next;
		pTemp->next = pReversedHead;
		pReversedHead = pTemp;
	}
	return pReversedHead;
}

//查找单链表中倒数第k个节点
struct LNode *RGetKthNode(struct LNode *pHead,unsigned int k)
{
	if(k == 0 || pHead == NULL){
		return NULL;
	}
	struct LNode *pAhead = pHead;
	struct LNode *pBehind = pHead;
	while(k > 1 && pAhead != NULL){
		pAhead = pAhead->next;
		k--;
	}
	if(k>1)
		return NULL;
	while(pAhead->next != NULL){
		pBehind = pBehind->next;
		pAhead = pAhead->next;
	}
	return pBehind;
}

//查找单链表的中间节点
struct LNode *GetMiddleNode(struct LNode *pHead)
{
	if(pHead == NULL || pHead->next == NULL)	//链表为空或只有一个节点
		return pHead;
	struct LNode *pAhead = pHead;
	struct LNode *pBehind = pHead;
	while(pAhead->next != NULL){
		pAhead = pAhead->next;
		pBehind = pBehind->next;
		if(pAhead->next!=NULL)
			pAhead=pAhead->next;
	}
	return pBehind;
}

//从尾到头打印单链表
void RPrintList(struct LNode *pHead)
{
	if(pHead == NULL)
		return;
	else{
		RPrintList(pHead->next);
		printf("%d\t",pHead->data);
	}
	//printf("\n");
}

//删除指定节点
/*struct LNode *Delete(struct LNode *pHead,int data)
{
	struct LNode *pCurrent;
	struct LNode *pTemp;
	if(pHead==NULL){
		printf("List is null!\n");
	}

	pCurrent = pHead;
	while(pCurrent->data != data && pCurrent != NULL){
		pTemp = pCurrent;
		pCurrent = pCurrent->next;
	}
	if(pCurrent->data == data){
		if(pCurrent  == pHead){
			pHead = pCurrent->next;
		} else {
			pTemp->next = pCurrent->next;
		}
		pCurrent = NULL;
		printf("Delete %d success!\n",data)
	}
	return pHead;
}*/

int main(void)
{
	int n;
	struct LNode *q,*h;
	printf("请输入你想创建的节点个数:");
	scanf("%d",&n);
	h = Create(n);
	q = h;
	printf("##############################################\n");
	n = 0;
	while(q){
		n++;
		printf("节点%d的数据为%d\n",n,q->data);
		q = q->next;
	};

	printf("####RUN GetListLength(struct LNode *pHead)####\n");
	printf("查询到的链表长度Len = %d\n",GetListLength(h));

	printf("#RUN RGetKthNode(struct LNode *pHead,unsigned int k)#\n");
	q = RGetKthNode(h,2);
		printf("倒数第2个节点的数据为:%d\n",q->data);

	printf("####RUN GetMiddleNode(struct LNode *pHead)####\n");
	q = GetMiddleNode(h);
		printf("中间节点的数据为:%d\n",q->data);

	printf("####RUN RPrintList(struct LNode *pHead)####\n");
	printf("从尾到头打印单链表数据:\n");
	RPrintList(h);
	printf("\n");
	

	printf("#####RUN ReverseList(struct LNode *pHead)#####\n");
	q = ReverseList(h);
	n = 0;
	while(q){
		n++;
		printf("反转后节点%d的数据为%d\n",n,q->data);
		q = q->next;
	}

	/*printf("#RUN RGetKthNode(struct LNode *pHead,unsigned int k)#\n");
	q = RGetKthNode(h,2);
	if(q)
		printf("倒数第2个节点的数据为:%d\n",q->data);*/

	return 0;
}

