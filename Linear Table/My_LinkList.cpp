#include<stdlib.h>
#include<stdio.h>
#include<string>
#include"My_LinkList.h"

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