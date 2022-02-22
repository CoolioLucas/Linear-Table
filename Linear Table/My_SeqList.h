#ifndef MY_SEQ_LIST_H
#define MY_SEQ_LIST_H


#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0

#define INFEASIBLE -1 //不能实行
#define OVERFLOW   -2 //内存溢出
#define NULLPTR   -3 //空指针

typedef int Status; //状态

#define SEQ_INIT_SIZE 10
#define SEQ_INC_SIZE 2  //增容2倍 
typedef int ElemType;

typedef struct {
	ElemType* data;
	int capacity;
	int cursize;
}SeqList;

//1.初始化
void InitSeqList(SeqList* plist);
//2.销毁
void DestorySeqList(SeqList* plist);
//3.置空
void ClearSeqList(SeqList* plist);
//4.获取当前元素数量
int GetSize(const SeqList* plist);
//5.获取容量
int GetCapacity(const SeqList* plist);
//6.判断顺序表是否为空
bool IsEmpty(const SeqList* plist);
//7.判断顺序表是否装满
bool IsFull(const SeqList* plist);
//8.查询值为val的元素在顺序表中的位置
int FindValue(const SeqList* plist, ElemType val);
//9.扩容
bool Inc_Capacity(SeqList* plist);
//10.插入
Status InsertItem(SeqList* plist, int pos, ElemType val);
//11.尾插
void Push_Back(SeqList* plist, ElemType val);
//12.头插
void Push_Front(SeqList* plist, ElemType val);
//13.删除指定位置的元素
Status EraseItem(SeqList* plist, int pos);
//14.删除尾部
void Pop_Back(SeqList* plist);
//15.删除头部
void Pop_Front(SeqList* plist);
//16.判断元素是否在表中
bool LocatElem(const SeqList* plist, ElemType val);
//17.删除值为val的函数
Status Remove(SeqList* plist, int val);
//18.打印顺序表
void PrintSeqList(const SeqList* plist);
//19.删除所有值为val的元素
void Remove_All(SeqList* plist, ElemType val);
//20.返回指定位置的元素
Status GetIElem(const SeqList* plist, int pos, ElemType* plva);
Status Get_Elem(const SeqList* plist, int pos, ElemType& e); //使用引用
#endif
