#ifndef MY_LINKLIST_H
#define MY_LINKLIST_H

typedef int ElemType;

typedef struct ListNode {
	ElemType data; 
	struct ListNode* next;
}ListNode, *LinkList;

ListNode* InitList();	

void ClearList(LinkList head);

void DestroyList(LinkList head);

ListNode* BuyNode();

void FreeNode(ListNode* p);

bool IsEmpty(LinkList head);

int GetSize(LinkList head);

void PrintList(LinkList head);

ListNode* FindValue(LinkList head, ElemType val);

ListNode* FindValue_Prev(LinkList head, ElemType val);

ListNode* FindPos(LinkList head, int pos);

ListNode* FindPos_Prev(LinkList head, int pos);

bool Insert_Next(LinkList head, ListNode* ptr, ElemType val);

void Push_Front(LinkList head, ElemType val);

void Push_Back(LinkList head, ElemType val);

bool InsertPos(LinkList head, int pos, ElemType val);

// delete rear node of ptr
bool Erase_Next(LinkList head, ListNode* ptr);

void Pop_Front(LinkList head);

void Pop_Back(LinkList head);

bool Remove(LinkList head, ElemType val);

void Remove_All(LinkList head, ElemType val);



#endif