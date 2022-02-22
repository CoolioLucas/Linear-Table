#include <iostream>
#include<assert.h> //assert
#include<iomanip> //setw
#include<string> //memmove
#include<Windows.h>
#include"My_SeqList.h"
#include"My_LinkList.h"
using namespace std;

int main(int argc, char* argv[]) {
	LinkList head = InitList();
}

#if 0
//斐波那契数列优化
//long long fib(unsigned int n) {
//	if (n <= 1) return 0;
//	if (n <= 2) return 1;
//	long long* nums = (long long*)malloc(sizeof(long long) * n); //辅助空间（可以不需要，进一步优化）
//	nums[0] = 0;
//	nums[1] = 1;
//	for (unsigned int i = 2; i <= n; ++i) {
//		nums[i] = nums[i - 1] + nums[i - 2];
//	}
//	long long fc = nums[n - 1];
//	free(nums);
//	nums = NULL;
//	return fc;
//}

long long fib(unsigned int n) {
	long long a = 0, b = 1;
	if (n <= 1) return a;
	if (n <= 2) return b;
	long long tmp = 0;
	for (int i = 3; i <= n; ++i) {
		tmp = a + b;
		a = b;
		b = tmp;
	}
	return b;
}

//递归的最优方法
long long fib_1(long long a, long long b, unsigned int n) {
	if (n <= 1)return a;
	if (n <= 2)return b;
	return fib_1(b, a + b, n - 1);
}

long long fib_2(unsigned int n) {
	long long a = 0, b = 1;
	return fib_1(a, b, n);
}

int main() {
	long long f = fib_2(50);
	printf("%lld \n", f);
	getchar();
}


int sum = 0; //统计递归次数

long long fib(unsigned int n) {
	sum += 1;
	if (n <= 1)
		return 0;
	if (n <= 2)
		return 1;
	return fib(n - 1) + fib(n - 2);
}

int main() {
	fib(50);
	printf("%d\n", sum);
	getchar();
}


//Fibonacci sequence
int main() {
	const int n = 50;
	long long fib[n] = { 0,1 };
	for (int i = 2; i < n; ++i) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	for (int i = 3; i < n - 1; ++i) {
		printf("%lld / %lld  ==>  %f \n", fib[i], fib[i + 1], (double)fib[i] / fib[i + 1]);
	}
	getchar();
}


//二分查找
int BinaryFindValue(const int* nums, int n, int val) {
	assert(nums != NULL);
	int pos = -1;
	int left = 0, right = n - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (val < nums[mid]) {
			right = mid - 1;
		}
		else if (val > nums[mid]) {
			left = mid + 1;
		}
		else {
			pos = mid; //返回第一个查找的值的位置 while(mid < left && nums[mid-1]=val) --mid;
			break;     // pos=mid; break;
		}
	}
		return pos;
}

int main() {
	int nums[] = { 12,23,34,45,56,67,78,89,90,100,110,120 };
	int n = sizeof(nums) / sizeof(nums[0]);
	int val = 34;
	int pos = BinaryFindValue(nums, n, val);
	cout << setw(5) << pos << endl;
	getchar();
}


//数组中的重复元素(1-n,只重复一个)
int FindDuplicate_1(const int* nums, int size) {
	assert(nums != NULL);
	int n = size - 1;
	int total = n * (n + 1) / 2;
	int sum = 0;
	for (int i = 0; i < size; ++i) {
		sum = sum + nums[i];
	}
	return sum - total;
}

//穷举(暴力)法
int FindDuplicate_2(const int* nums, int size) {
	assert(nums != NULL);
	int tmp = 0;
	for (int i = 0; i < size; ++i) {
		tmp = nums[i];
		for (int j = i+1; i < size; ++j) {
			if (tmp == nums[j])
				goto end;
		}
	}
	end:
	return tmp;
}

//先排序在判断是否重复
int Compare_ints(const void* a, const void* b) {
	int arg1 = *(const int*)a;
	int arg2 = *(const int*)b;
	if (arg1 < arg2) return -1;
	else if (arg1 > arg2) return 1;
	else return 0;
}

int FindDuplicate_3(int* nums, int size) {
	assert(nums != NULL);
	qsort(nums, size, sizeof(int), Compare_ints);
	int tmp = -1;
	for (int i = 0; i < size - 1; ++i) {
		if (nums[i] == nums[i + 1]) {
			tmp = nums[i];
			break;
		}
	}

	return tmp;
}

//查表法
int FindDuplicate_4(const int* nums, int size) {
	assert(nums != NULL);
	//int* index = (int*)malloc(sizeof(int) * size);//int index[size]错误,只能动态开辟空间!
	//memset(index, 0, sizeof(int) * size); //变为0
	int* index = (int*)calloc(size, sizeof(int));//自动置为0
	int idx = 0;
	for (int i = 0; i < size; ++i) {
		idx = nums[i];
		if (index[idx] == 0) {
			index[idx] += 1;
		}
		else {
			break;
		}
	}
	free(index);
	index = NULL;
	return idx;
}

//双指针法
int FindDuplicate_5(const int* nums, int size) {
	assert(nums != NULL);
	for (int i = 0; i < size; ++i) {
		if (nums[i]<1 || nums[i]>size - 1) {
			return -1;
		}
	}
	int fast = 0;
	int slow = 0;
	do {
		slow = nums[slow];
		//fast = nums[fast];
		//fast = nums[fast];
		fast = nums[nums[fast]];
	} while (slow != fast);
	slow = 0;
	while (slow != fast) {
		slow = nums[slow];
		fast = nums[fast];
	}
	return slow;
}

int main() {
	int n = 40000;
	int size = n + 1;
	int* nums = (int*)calloc(size, sizeof(int));
	for (int i = 0; i < n; ++i) {
		nums[i] = i + 1;
	}
	nums[n] = rand() % 40000;
	int dup;
	unsigned long begin, end;
	begin = GetTickCount();
	dup = FindDuplicate_1(nums, size);
	end = GetTickCount();
	printf("1_dup : %d diff %u \n", dup, end - begin);

	begin = GetTickCount();
	dup = FindDuplicate_2(nums, size);
	end = GetTickCount();
	printf("2_dup : %d diff %u \n", dup, end - begin);

	begin = GetTickCount();
	dup = FindDuplicate_3(nums, size);
	end = GetTickCount();
	printf("3_dup : %d diff %u \n", dup, end - begin);


	begin = GetTickCount();
	dup = FindDuplicate_4(nums, size);
	end = GetTickCount();
	printf("4_dup : %d diff %u \n", dup, end - begin);

	begin = GetTickCount();
	dup = FindDuplicate_5(nums, size);
	end = GetTickCount();
	printf("5_dup : %d diff %u \n", dup, end - begin); 

	getchar();
}


int main() {
	int nums[] = { 1,2,5,4,3,5 };
	int n = sizeof(nums) / sizeof(nums[0]);
	int dup = FindDuplicate_5(nums, n);
	printf("%d\n", dup);
	getchar();
}


//Monotonicity
bool Inc_Nums(int* nums, int n) {
	assert(nums != NULL);
	bool res = true;
	for (int i = 0; i < n - 1; ++i) {
		if (nums[i] > nums[i + 1]) {
			res = false;
			break;
		}
	}
	return res;
}

bool Dec_Nums(int* nums, int n) {
	assert(nums != NULL);
	bool res = true;
	for (int i = 0; i < n - 1; ++i) {
		if (nums[i] < nums[i + 1]) {
			res = false;
			break;
		}
	}
	return res;
}

bool IsMonotoni(int* nums, int n) {
	assert(nums != NULL);

	return Inc_Nums(nums, n) || Dec_Nums(nums, n);
}

int main() {
	int ar[] = { 12,23,34,45,56,67 };
	int n = sizeof(ar) / sizeof(ar[0]);
	printf("%d\n", IsMonotoni(ar, n));
	getchar();
}

//A∪B
void Union(SeqList* pLa, const SeqList* pLb) {
	assert(pLa != NULL && pLb != NULL);
	int n = GetSize(pLb);
	for (int i = 0; i < n; ++i) {
		int val = 0;
		//GetIElem(pLb, i, &val);
		Get_Elem(pLb, i, val);
		if (!LocatElem(pLa, val))
			Push_Back(pLa, val);
	}	 
}

int main() {
	int ar[] = { 2,4,6,8,10 };
	int na = sizeof(ar) / sizeof(ar[0]);
	int br[] = { 1,3,6,8,9,11 };
	int nb = sizeof(br) / sizeof(br[0]);

	SeqList La, Lb;
	InitSeqList(&La);
	InitSeqList(&Lb);

	for (int i = 0; i < na; ++i) {
		Push_Back(&La, ar[i]);
	}
	for (int i = 0; i < nb; ++i) {
		Push_Back(&Lb, br[i]);
	}
	PrintSeqList(&La);
	PrintSeqList(&Lb);
	Union(&La, &Lb);
	PrintSeqList(&La);
	DestorySeqList(&La);
	DestorySeqList(&Lb);
	getchar();
	return 0;
}

//合并数组
void Merge_List(const SeqList* pLa,const SeqList* pLb, SeqList* pLc) {
	ElemType* pa = pLa->data;
	ElemType* pb = pLb->data;
	pLc->capacity = pLc->cursize = pLa->cursize + pLb->cursize;
	pLc->data = (ElemType*)malloc(sizeof(ElemType) * pLc->capacity);  //申请了内存一定要检查
	if (NULL == pLc->data)
		exit(EXIT_FAILURE);
	ElemType* pc = pLc->data;
	ElemType* pa_Last = pLa->data + pLa->cursize - 1;
	ElemType* pb_Last = pLb->data + pLb->cursize - 1;
	while (pa <= pa_Last && pb <= pb_Last) {
		if (*pa <= *pb)
			*pc++ = *pa++;   // *pc=*pa, pc++, pa++
		else
			*pc++ = *pb++;
	}
	while (pa <= pa_Last) { *pc++ = *pa++; }
	while (pb <= pb_Last) { *pc++ = *pb++; }
}

void Merge_1(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
	assert(nums1 != NULL && nums2 != NULL);
	int* newdata = (int*)malloc(sizeof(int) *( m + n));
	if (NULL == newdata) {
		exit(1);
	}
	int i = 0, j = 0;
	int k = 0;
	while (i < m && j < n) {
		newdata[k++] = nums1[i] <= nums2[j] ? nums1[i++] : nums2[j++];
	}
	while (i < m)newdata[k++] = nums1[i++];
	while (j < n)newdata[k++] = nums2[j++];
	nums1 = newdata;
	for (i = 0; i < m + n; ++i) {
		nums1[i] = newdata[i];
	}
	newdata = NULL;
}

void Merge_2(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
	assert(nums1 != NULL && nums2 != NULL);
	int i = m - 1;//s1最后一个下标
	int j = n - 1;//s2最后一个下标
	int k = m + n - 1;//合并后s1最后一个下标
	while (i >= 0 && j >= 0) {
		nums1[k--] = nums2[j] >= nums1[i] ? nums2[j--] : nums1[i--];
	}
	while (j > 0) { nums1[k--] = nums2[j--]; }
}

void MoveArray(int* nums, int n) {
	assert(nums != NULL);
	int tem = nums[n - 1];
	for (int i = n - 1; i < 0; --i) {
		nums[n] = nums[n - 1];
	}
}

//旋转数组
//时间换空间
int Rotate(int* nums, int n, int k) {
	assert(nums != NULL);
	if (k < 0) cout << "Invalid k!" << endl;
	for (int i = 0; i < k; ++i) {
		MoveArray(nums, n);
	}
}

//空间换时间
void Rotate_Right(int* nums, int n, int k) {
	assert(nums != NULL);
	if (k < 0) cout << "Invalid k!" << endl;
	k = k % n; //因为循环旋转,否则k太大会越界
	int* newdata = (int*)calloc(sizeof(int), n);
	if (NULL == newdata) {
		exit(1);
	}
	int j = k;
	for (int i = 0; i <= n - k - 1; ++i) {
		newdata[j] = nums[i];
		j += 1;
	}
	j = 0;
	for (int i = n - k; i <= n - 1; ++i) {
		newdata[j] = nums[i];
		j += 1;
	}
	for (int i = 0; i < n; ++i) {
		nums[i] = newdata[i];
	}
	free(newdata);
	newdata = NULL;
}

void Swap_Int(int* ap, int* bp) {
	int tmp = *ap;
	*ap = *bp;
	*bp = tmp; 
}

void Reverse(int* nums, int left, int right) {
	assert(nums != NULL);
	while (left < right) {
		Swap_Int(&nums[left], &nums[right]);
		left++;
		right--;
	}
}

//逆置
void Rotate_Ar(int* nums, int n, int k) {
	assert(nums != NULL);
	if (k < 0) exit(1);
	k = k % n;
	Reverse(nums, 0, n - 1);
	Reverse(nums, 0, k);
	Reverse(nums, k, n - 1);
}

int main() {
	int ar[] = { 1,2,3,4,5,6,7 };
	int n = sizeof(ar) / sizeof(ar[0]);
	Rotate(ar, n, 3);	
}

int main(){
	int ar[6] = { 1,2,5 };
	int br[3] = { 2,3,8 };
	Merge_2(ar, 6, 3, br, 3, 3);
	for (int i = 0; i < 6; ++i) {
		printf("%d\t", ar[i]);
	}
	getchar();
}


int main() {
	int ar[] = { 1,3,5,7,9,11,20 };
	int an = sizeof(ar) /sizeof( ar[0]);
	int br[] = { 2,4,8,10,15,19,45,89,100 };
	int bn = sizeof(br) / sizeof(br[0]);
	SeqList La, Lb, Lc;
	InitSeqList(&La);
	InitSeqList(&Lb);
	for (int i = 0; i < an; ++i) {
		Push_Back(&La, ar[i]);
	}
	for (int i = 0; i < bn; ++i) {
		Push_Back(&Lb, br[i]);
	}
	PrintSeqList(&La);
	PrintSeqList(&Lb);
	Merge_List(&La, &Lb, &Lc);
	PrintSeqList(&Lc);
	DestorySeqList(&La);
	DestorySeqList(&Lb);
	DestorySeqList(&Lc);
	getchar();
}


int main() {
	int ar[] = { 23,12,12,34,56,78 };
	int n = sizeof(ar) / sizeof(ar[0]);
	SeqList myseq;
	InitSeqList(&myseq);
	for (int i = 0; i < n; ++i) {
		Push_Back(&myseq, ar[i]);
	}
	PrintSeqList(&myseq);
	Remove_All(&myseq, 12);
	PrintSeqList(&myseq);
	//for (int i = 0; i < 20; ++i) {
	//	//Push_Back(&myseq, i);
	//	Push_Front(&myseq, i);
	//	PrintSeqList(&myseq);
	//}
	//Status tag = InsertItem(&myseq, 12, 23);
	//if (tag == INFEASIBLE)
	//{
	//}
	//else if (tag == OVERFLOW)
	//{
	//}
	//else if (tag == OK)
	//{
	//}
	//PrintSeqList(&myseq);
	//DestorySeqList(&myseq);
	cin.get();
}



int main() {
	char ch;
	int in;
	return 0;
}


struct SeqList {
	ElemType data[SEQ_INIT_SIZE];
	int cursize;
};

typedef struct SeqList {
	ElemType data[SEQ_INIT_SIZE];
	int cursize;
}SeqList;

int main() {

}
#endif