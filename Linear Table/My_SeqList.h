#ifndef MY_SEQ_LIST_H
#define MY_SEQ_LIST_H


#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0

#define INFEASIBLE -1 //����ʵ��
#define OVERFLOW   -2 //�ڴ����
#define NULLPTR   -3 //��ָ��

typedef int Status; //״̬

#define SEQ_INIT_SIZE 10
#define SEQ_INC_SIZE 2  //����2�� 
typedef int ElemType;

typedef struct {
	ElemType* data;
	int capacity;
	int cursize;
}SeqList;

//1.��ʼ��
void InitSeqList(SeqList* plist);
//2.����
void DestorySeqList(SeqList* plist);
//3.�ÿ�
void ClearSeqList(SeqList* plist);
//4.��ȡ��ǰԪ������
int GetSize(const SeqList* plist);
//5.��ȡ����
int GetCapacity(const SeqList* plist);
//6.�ж�˳����Ƿ�Ϊ��
bool IsEmpty(const SeqList* plist);
//7.�ж�˳����Ƿ�װ��
bool IsFull(const SeqList* plist);
//8.��ѯֵΪval��Ԫ����˳����е�λ��
int FindValue(const SeqList* plist, ElemType val);
//9.����
bool Inc_Capacity(SeqList* plist);
//10.����
Status InsertItem(SeqList* plist, int pos, ElemType val);
//11.β��
void Push_Back(SeqList* plist, ElemType val);
//12.ͷ��
void Push_Front(SeqList* plist, ElemType val);
//13.ɾ��ָ��λ�õ�Ԫ��
Status EraseItem(SeqList* plist, int pos);
//14.ɾ��β��
void Pop_Back(SeqList* plist);
//15.ɾ��ͷ��
void Pop_Front(SeqList* plist);
//16.�ж�Ԫ���Ƿ��ڱ���
bool LocatElem(const SeqList* plist, ElemType val);
//17.ɾ��ֵΪval�ĺ���
Status Remove(SeqList* plist, int val);
//18.��ӡ˳���
void PrintSeqList(const SeqList* plist);
//19.ɾ������ֵΪval��Ԫ��
void Remove_All(SeqList* plist, ElemType val);
//20.����ָ��λ�õ�Ԫ��
Status GetIElem(const SeqList* plist, int pos, ElemType* plva);
Status Get_Elem(const SeqList* plist, int pos, ElemType& e); //ʹ������
#endif
