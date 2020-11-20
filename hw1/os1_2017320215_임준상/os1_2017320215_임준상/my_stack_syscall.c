#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/linkage.h> 
#include <linux/slab.h>//kmalloc, kfree

struct stackNode {
	int data;
	struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

StackNodePtr stackPtr = NULL;

SYSCALL_DEFINE1(oslab_push, int, a)
{
	StackNodePtr printPtr = NULL;
	StackNodePtr newPtr;

	int flag = 1;
	
	//分配内存 메모리 분배
	newPtr = (struct stackNode*)kmalloc(sizeof(StackNode), GFP_KERNEL);	
	if (newPtr == NULL)
	{
		return -1;
	}
	else
	{	
		printPtr = stackPtr;
		
		if (printPtr != NULL)//같은 데이터가 있다면 flag가 0이 될 것이다.
		{//历遍stack 有相同的则flag = 0 不push
			while (printPtr != NULL)
			{//전체 stack를 살펴본다.
				if(a == printPtr->data) flag = 0;
				printPtr = printPtr->nextPtr;
			}
		}

		if(flag)//push value------------
		{
			newPtr->data = a;
			newPtr->nextPtr = stackPtr;
			stackPtr = newPtr;
		}
		else
		{//duplicate
			printk("Duplicate!");
		}
	}
	
	printPtr = stackPtr;

	printk("Stack Top----------");
	
	if (printPtr != NULL)//历遍打印
	{
		while (printPtr != NULL)
		{
			printk(KERN_INFO"%d", printPtr->data);
			printPtr = printPtr->nextPtr;
		}
	}

	printk("Stack Bottom-------");
	if(flag)	return 1;
	else	return 0;
}

SYSCALL_DEFINE0(oslab_pop){
	
	StackNodePtr tempPtr = NULL;
	int popValue;
	
	tempPtr = stackPtr;
	popValue = stackPtr->data;
	stackPtr = stackPtr->nextPtr;
	kfree(tempPtr);//메머리 free
	return popValue;
}