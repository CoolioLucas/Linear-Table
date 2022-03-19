#include <iostream>
#include<assert.h> //assert
#include<iomanip> //setw
#include<string> //memmove
using namespace std;

#include"My_SeqList.h"

//1.顺序表初始化
void InitSeqList(SeqList* plist) {
	assert(plist != NULL);     //创建指针必须要用assert
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
	return GetSize(plist) == 0; //这样写可以少打一个等号会报错
	//return plist->cursize == 0; //这样写少打一个等会不会报错
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

//2.输出顺序表
void PrintSeqList(const SeqList* plist) {
	assert(plist != NULL);
	cout << "Capacity: " << plist->capacity << endl;
	cout << "Cursize: " << plist->cursize << endl;
	for (int i = 0; i < plist->cursize; i++) {
		cout << setw(5) << plist->data[i];
	}
	cout << endl;
}

//3.在顺序表中查询
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

//4.顺序表扩容(堆空间充足时可以用relloc代替)
//bool Inc_Capacity(SeqList* plist) {
//	assert(plist != NULL);
//	int total = plist->capacity * SEQ_INC_SIZE;
//	plist->data = (ElemType*)realloc(plist->data, sizeof(ElemType) * total); 创建一个容量为total的空间newdata，将data数据转移到newdata并free（data），再将plist->data指向newdata
//	if (NULL == plist->data)
//		return false;
//	plist->capacity = total;
//	return true;
//}
//若堆空间不足(申请数据空间特别大时)，则realloc返回NULL,将导致plist->data变为空,导致内存泄漏
//改进方法
//bool Inc_Capacity(SeqList* plist) {
//	assert(plist != NULL);
//	int total = plist->capacity * SEQ_INC_SIZE;
//	ElemType *newdata = (ElemType*)realloc(plist->data, sizeof(ElemType) * total); 创建一个容量为total的空间newdata，将data数据转移到newdata并free（data），再将plist->data指向newdata
//	if (NULL == newdata)
//		return false;
//  plist->data = newdata;
//	plist->capacity = total;
//	return true;
//}
bool Inc_Capacity(SeqList* plist) {
	assert(plist != NULL);
	ElemType* newdata = NULL; //(ElemType*)malloc(sizeof(ElemType)*SEQ_INIT_SIZE * SEQ_INC_SIZE) 错误,这样每次都是初始capacity的2倍
	int total = plist->capacity * SEQ_INC_SIZE;
	newdata = (ElemType*)malloc(sizeof(ElemType) * total);
	if (NULL == newdata) //NULL写前面防止出错
		return false;
	memmove(newdata, plist->data, sizeof(ElemType) * plist->capacity); //优化：比for更好
	//for (int i = 0; i < plist->cursize; i++) {
	//	newdata[i] = plist->data[i];
	//}
	free(plist->data);
	plist->data = newdata;
	plist->capacity = total;
	return true;
}

//5.顺序表插入元素
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

//6.在顺序表尾部(数据元素的尾部,不是最后一个空间插入)插入
void Push_Back(SeqList* plist, ElemType val) {
	InsertItem(plist, plist->cursize, val);
	//assert(plist != NULL);
	//plist->data[plist->cursize] = val;
	//plist->cursize += 1;
}

//7.在顺序表头部插入
void Push_Front(SeqList* plist, ElemType val) {
	InsertItem(plist, 0, val);
	/*assert(plist != NULL);
	for (int i = plist->cursize; i > 0; i--) {
		plist->data[i] = plist->data[i-1];
	}
	plist->data[0] = val;
	plist->cursize += 1;*/
}

//8.删除顺序表中的元素
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

//9.删除顺序表中值为val的元素
Status Remove(SeqList* plist, int val) {
	assert(plist != NULL);
	return EraseItem(plist, FindValue(plist, val));
}

//10.删除尾部元素
void Pop_Back(SeqList* plist) {
	assert(plist != NULL);
	EraseItem(plist, plist->cursize - 1);
}

//11.删除第一个元素
void Pop_Front(SeqList* plist) {
	assert(plist != NULL);
	EraseItem(plist, 0);
}

//12.判断元素是否在表中
bool LocatElem(const SeqList* plist, ElemType val) {
	assert(plist != NULL);
	return FindValue(plist, val) != -1;
}

//13.销毁
void DestorySeqList(SeqList* plist) {
	assert(plist != NULL);
	plist->capacity = 0;
	plist->cursize = 0;
	free(plist->data);
}

//14.置空
void ClearSeqList(SeqList* plist) {
	assert(plist != NULL);
	plist->cursize = 0;
}

//15.删除所有值为val的元素
// 效率低
//void Remove_All(SeqList* plist, ElemType val) {
//	assert(plist != NULL);
//	int pos;
//	while ((pos = FindValue(plist, val))!=-1) {
//		EraseItem(plist, pos);
//	}
//}
// 当val在下标为0是不能删除
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
// j=-1, i=0,先+1再赋值
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
//j=0,i=0,先赋值再+1
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

//16.返回指定位置的元素
Status GetIElem(const SeqList* plist, int pos, ElemType* pval) {
	assert(plist != NULL);
	if (pos < 0 || pos >= plist->cursize) return INFEASIBLE;
	if (NULL == pval) return NULLPTR;
	*pval = plist->data[pos];
	return OK;
}

Status Get_Elem(const SeqList* plist, int pos, ElemType& e) //使用引用
{
	assert(plist != NULL);
	if (pos < 0 || pos >= plist->cursize) return INFEASIBLE;
	e = plist->data[pos]; //引用比指针更安全，不用判断指针是否为空；
	return OK;
}