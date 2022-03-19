#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<assert.h>
#include"My_LinkList.h"
#include<iostream>
using namespace std;

void Swap(ElemType& a, ElemType& b) {
	ElemType t = a;
	a = b;
	b = t;
}

ListNode* BuyNode() {
	ListNode* s = (ListNode*)malloc(sizeof(ListNode));
	if (NULL == s) exit(1);
	memset(s, 0, sizeof(ListNode));
	return s;
}

void FreeNode(ListNode* p) {
	free(p);
}

ListNode* InitList() {
	ListNode* s = BuyNode();
	s->next = NULL;
	return s;
	/*ListNode* s = (ListNode*)malloc(sizeof(ListNode));
	if (NULL == s) exit(1);
	s->next = NULL;
	return s;*/
}

void PrintList(LinkList head) {
	assert(head != NULL);
	ListNode* p = head->next;
	while (p != NULL) {
		cout << p->data << "\t";
		p = p->next;
	}
	cout << endl;
}

ListNode* FindValue(LinkList head, ElemType val) {
	assert(head != NULL);
	ListNode* p = FindValue(head, val);
	if (p != NULL ) {
		p = p->next;
	}
	return p;
}

ListNode* FindValue_Prev(LinkList head, ElemType val) {
	assert(head != NULL);
	ListNode* prev = head;
	ListNode* p = head->next;
	while (p != NULL && p->data != val) {
		prev = p;
		p = p->next;
	}
	if (NULL == p)
		prev = NULL;
	return prev;
}

ListNode* FindPos(LinkList head, int pos) {
	assert(head != NULL);
	if (pos < 1) return NULL;
	ListNode* p = FindPos_Prev(head, pos);
	if (p != NULL ) {
		p = p->next;
	}
	return p;
}

ListNode* FindPos_Prev(LinkList head, int pos) {
	assert(head != NULL);
	int i = 1;
	ListNode* prev = head;
	ListNode* p = head->next;
	if (pos < 1) return NULL;
	while (p != NULL && i < pos) {
		prev = p;
		p = p->next;
		i++;
	}
	if (NULL == p)
		prev = NULL;
	return prev;
}

bool Insert_Next(LinkList head, ListNode* ptr, ElemType val) {
	assert(head != NULL);
	if (NULL == ptr) return false;
	ListNode* s = BuyNode();
	if (NULL == s) return false;
	s->data = val;
	s->next = ptr->next;
	ptr->next = s;
	return true;
}

void Push_Front(LinkList head, ElemType val) {
	assert(head != NULL);
	Insert_Next(head, head, val);
}

void Push_Back(LinkList head, ElemType val) {
	assert(head != NULL);
	ListNode* p = head;  //·ÀÖ¹Á´±íÊÇ¿ÕÁ´±í
	while (p->next != NULL) {
		p = p->next;
	}
	Insert_Next(head, p, val);
}

bool InsertPos(LinkList head, int pos, ElemType val) {
	assert(head != NULL);
	if (pos < 1) return false;
	int i = 1;
	ListNode* p = head;
	while (p != NULL && i < pos) {
		p = p->next;
		i++;
	}
	if (pos > i)return false;
	return Insert_Next(head, p, val);
}

bool Erase_Next(LinkList head, ListNode* ptr) {
	assert(head != NULL);
	if (NULL == ptr || NULL == ptr->next) return false;
	ListNode* q = ptr->next;
	ptr->next = q->next;
	FreeNode(q);
	q = NULL;
	return true;
}

void Pop_Front(LinkList head) {
	assert(head != NULL);
	Erase_Next(head, head);
}

void Pop_Back(LinkList head) {
	assert(head != NULL);
	ListNode* prev = head;
	ListNode* p = head->next;
	while (p->next != NULL) {
		prev = p;
		p = p->next;
	}
	Erase_Next(head, prev);
}

bool IsEmpty(LinkList head) {
	assert(head != NULL); 
	return head->next == NULL;
}

int GetSize(LinkList head) {
	assert(head != NULL);
	int i = 0;
	ListNode* p = head->next;
	while (p != NULL) {
		i++;
		p = p->next;
	}
	return i;
}

bool Remove(LinkList head, ElemType val) {
	assert(head != NULL);
	return Erase_Next(head, FindValue_Prev(head, val));
}

//void Remove_All(LinkList head, ElemType val) {
//	assert(head != NULL);
//	ListNode* p = NULL;
//	while (p = FindValue_Prev(head, val)) {
//		Erase_Next(head, p); 
//	}
//} 

void Remove_All(LinkList head, ElemType val) {
	assert(head != NULL);
	ListNode* pre = head;
	ListNode* p = head->next;
	while (p != NULL) {
		if (p->data != val) {
			pre = pre->next;
			Swap(pre->data, p->data);
		}
		p = p->next;
	}
	while (pre->next != NULL) {
		Erase_Next(head, pre);
	}
}

//void ClearList(LinkList head) {
//	assert(head != NULL);
//	while (head->next != NULL) {
//		ListNode* q = head->next;
//		head->next = q->next;
//		FreeNode(q);
//	}
//}

void ClearList(LinkList head) {
	assert(head != NULL);
	while (!IsEmpty(head)) {
		Pop_Front(head);
	}
}

void DestroyList(LinkList head){
	assert(head != NULL);
	ClearList(head);
	FreeNode(head);
}