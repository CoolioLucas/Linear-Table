#include <iostream>
#include<assert.h> //assert
#include<iomanip> //setw
#include<string> //memmove
using namespace std;

#include"My_SeqList.h"

//1.˳����ʼ��
void InitSeqList(SeqList* plist) {
	assert(plist != NULL);     //����ָ�����Ҫ��assert
	plist->capacity = SEQ_INIT_SIZE;
	plist->cursize = 0;
	plist->data = (ElemType*)malloc(sizeof(ElemType) * plist->capacity);
	if (plist == NULL) {
		cout << "Error" << endl;
		exit(EXIT_FAILURE);
	}
}

int GetSize(const SeqList* plist) {
	assert(plist != NULL);
	return plist->cursize;
}

bool IsEmpty(const SeqList* plist) {
	return GetSize(plist) == 0; //����д�����ٴ�һ���ȺŻᱨ��
	//return plist->cursize == 0; //����д�ٴ�һ���Ȼ᲻�ᱨ��
}

int GetCapacity(const SeqList* plist) {
	assert(plist != NULL);
	return plist->capacity;
}

bool IsFull(const SeqList* plist) {
	assert(plist != NULL);
	return GetSize(plist) == GetCapacity(plist);
	//return plist->cursie==plist->capacity;
}

//2.���˳���
void PrintSeqList(const SeqList* plist) {
	assert(plist != NULL);
	cout << "Capacity: " << plist->capacity << endl;
	cout << "Cursize: " << plist->cursize << endl;
	for (int i = 0; i < plist->cursize; i++) {
		cout << setw(5) << plist->data[i];
	}
	cout << endl;
}

//3.��˳����в�ѯ
int FindValue(const SeqList* plist, ElemType val) {
	assert(plist != NULL);
	int pos = -1;
	for (int i = 0; i < plist->cursize; ++i) {
		if (val == plist->data[i]) {
			pos = i;
			break;
		}
	}
	return pos;
	/*assert(plist != NULL);
	int i = 0;
	while (plist->data[i] != val) {
		assert(plist != NULL);
		if (i < plist->cursize) {
			i++;
		}
		else {
			cout << "No corresponding value found!" << endl;
			break;
		}
	} cout << i << endl;*/
	/*int i = 0;
	for (i; i < plist->cursize; i++) {
		if (plist->data[i] == val) {
			cout << i << endl;
		}
	}
	if (i == plist->cursize)
		cout << "No corresponding value found!" << endl;*/
}

//4.˳�������(�ѿռ����ʱ������relloc����)
//bool Inc_Capacity(SeqList* plist) {
//	assert(plist != NULL);
//	int total = plist->capacity * SEQ_INC_SIZE;
//	plist->data = (ElemType*)realloc(plist->data, sizeof(ElemType) * total); ����һ������Ϊtotal�Ŀռ�newdata����data����ת�Ƶ�newdata��free��data�����ٽ�plist->dataָ��newdata
//	if (NULL == plist->data)
//		return false;
//	plist->capacity = total;
//	return true;
//}
//���ѿռ䲻��(�������ݿռ��ر��ʱ)����realloc����NULL,������plist->data��Ϊ��,�����ڴ�й©
//�Ľ�����
//bool Inc_Capacity(SeqList* plist) {
//	assert(plist != NULL);
//	int total = plist->capacity * SEQ_INC_SIZE;
//	ElemType *newdata = (ElemType*)realloc(plist->data, sizeof(ElemType) * total); ����һ������Ϊtotal�Ŀռ�newdata����data����ת�Ƶ�newdata��free��data�����ٽ�plist->dataָ��newdata
//	if (NULL == newdata)
//		return false;
//  plist->data = newdata;
//	plist->capacity = total;
//	return true;
//}
bool Inc_Capacity(SeqList* plist) {
	assert(plist != NULL);
	ElemType* newdata = NULL; //(ElemType*)malloc(sizeof(ElemType)*SEQ_INIT_SIZE * SEQ_INC_SIZE) ����,����ÿ�ζ��ǳ�ʼcapacity��2��
	int total = plist->capacity * SEQ_INC_SIZE;
	newdata = (ElemType*)malloc(sizeof(ElemType) * total);
	if (NULL == newdata) //NULLдǰ���ֹ����
		return false;
	memmove(newdata, plist->data, sizeof(ElemType) * plist->capacity); //�Ż�����for����
	//for (int i = 0; i < plist->cursize; i++) {
	//	newdata[i] = plist->data[i];
	//}
	free(plist->data);
	plist->data = newdata;
	plist->capacity = total;
	return true;
}

//5.˳������Ԫ��
Status InsertItem(SeqList* plist, int pos, ElemType val) {
	assert(plist != NULL);
	if (pos<0 || pos>plist->cursize)
		return INFEASIBLE;
	if (IsFull(plist) && !Inc_Capacity(plist))
		return OVERFLOW;
	for (int i = plist->cursize; i > pos; i--) {
		plist->data[i] = plist->data[i - 1];
	}
	/*for (int i = plist->cursize; i > pos; i--) {
		plist->data[i] = plist->data[i - 1];
	}*/
	plist->data[pos] = val;
	plist->cursize += 1;
	return OK;
}

//6.��˳���β��(����Ԫ�ص�β��,�������һ���ռ����)����
void Push_Back(SeqList* plist, ElemType val) {
	InsertItem(plist, plist->cursize, val);
	//assert(plist != NULL);
	//plist->data[plist->cursize] = val;
	//plist->cursize += 1;
}

//7.��˳���ͷ������
void Push_Front(SeqList* plist, ElemType val) {
	InsertItem(plist, 0, val);
	/*assert(plist != NULL);
	for (int i = plist->cursize; i > 0; i--) {
		plist->data[i] = plist->data[i-1];
	}
	plist->data[0] = val;
	plist->cursize += 1;*/
}

//8.ɾ��˳����е�Ԫ��
Status EraseItem(SeqList* plist, int pos) {
	assert(plist != NULL);
	if (pos<0 || pos>plist->cursize - 1)
		return INFEASIBLE;
	for (int i = pos; i < plist->cursize - 1; ++i) {
		plist->data[i] = plist->data[i + 1];
	}
	plist->cursize -= 1;
	return OK;
}

//9.ɾ��˳�����ֵΪval��Ԫ��
Status Remove(SeqList* plist, int val) {
	assert(plist != NULL);
	return EraseItem(plist, FindValue(plist, val));
}

//10.ɾ��β��Ԫ��
void Pop_Back(SeqList* plist) {
	assert(plist != NULL);
	EraseItem(plist, plist->cursize - 1);
}

//11.ɾ����һ��Ԫ��
void Pop_Front(SeqList* plist) {
	assert(plist != NULL);
	EraseItem(plist, 0);
}

//12.�ж�Ԫ���Ƿ��ڱ���
bool LocatElem(const SeqList* plist, ElemType val) {
	assert(plist != NULL);
	return FindValue(plist, val) != -1;
}

//13.����
void DestorySeqList(SeqList* plist) {
	assert(plist != NULL);
	plist->capacity = 0;
	plist->cursize = 0;
	free(plist->data);
}

//14.�ÿ�
void ClearSeqList(SeqList* plist) {
	assert(plist != NULL);
	plist->cursize = 0;
}

//15.ɾ������ֵΪval��Ԫ��
// Ч�ʵ�
//void Remove_All(SeqList* plist, ElemType val) {
//	assert(plist != NULL);
//	int pos;
//	while ((pos = FindValue(plist, val))!=-1) {
//		EraseItem(plist, pos);
//	}
//}
// ��val���±�Ϊ0�ǲ���ɾ��
//void Remove_All(SeqList* plist, ElemType val) {
//	int j = 0;
//	for (int i = 1; i < plist->cursize; ++i) {
//		if (plist->data[i] != val) {
//			j += 1;
//			plist->data[j] = i;
//		}
//	}
//	plist->cursize = j + 1;
//}
// j=-1, i=0,��+1�ٸ�ֵ
//void Remove_All(SeqList* plist, ElemType val) {
//	int j = -1;
//	for (int i = 0; i < plist->cursize; ++i) {
//		if (plist->data[i] != val) {
//			j += 1;
//			plist->data[j] = i;
//		}
//	}
//	plist->cursize = j + 1;
//}
//j=0,i=0,�ȸ�ֵ��+1
void Remove_All(SeqList* plist, ElemType val) {
	int j = 0;
	for (int i = 0; i < plist->cursize; ++i) {
		if (plist->data[i] != val) {
			plist->data[j] = i;
			j += 1;
		}
	}
	plist->cursize = j;
}

//16.����ָ��λ�õ�Ԫ��
Status GetIElem(const SeqList* plist, int pos, ElemType* pval) {
	assert(plist != NULL);
	if (pos < 0 || pos >= plist->cursize) return INFEASIBLE;
	if (NULL == pval) return NULLPTR;
	*pval = plist->data[pos];
	return OK;
}

Status Get_Elem(const SeqList* plist, int pos, ElemType& e) //ʹ������
{
	assert(plist != NULL);
	if (pos < 0 || pos >= plist->cursize) return INFEASIBLE;
	e = plist->data[pos]; //���ñ�ָ�����ȫ�������ж�ָ���Ƿ�Ϊ�գ�
	return OK;
}