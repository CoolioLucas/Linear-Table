#ifndef MY_LINKLIST_H
#define MY_LINKLIST_H

typedef int ElemType;
typedef struct ListNode {
	ElemType data; 
	struct ListNode* next;
}ListNode, *LinkList;

ListNode* InitList();
PrintList;
FindValue;

#endif