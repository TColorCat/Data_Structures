#ifndef Binary_Heap_H_ 
#define Binary_Heap_H_ 
#include<iostream>
using namespace std;
namespace Data_structures
 { 
	 template <class T>//最大堆的实现
	 class MaxHeap{
	 private:
		 T *mHeap;        // 数据
		 int mCapacity;    // 总的容量
		 int mSize;        // 实际容量

	 private:
		 // 最大堆的向下调整算法
		 void filterdown(int start, int end);
		 // 最大堆的向上调整算法(从start开始向上直到0，调整堆)
		 void filterup(int start);
	 public:
		 MaxHeap();
		 MaxHeap(int capacity);
		 ~MaxHeap();

		 // 返回data在二叉堆中的索引
		 int getIndex(T data);
		 // 删除最大堆中的data
		 int remove(T data);
		 // 将data插入到二叉堆中
		 int insert(T data);
		 // 打印二叉堆
		 void print();
	 };
 
	 namespace  Test_demo
	 {
		 void test_heap_bianry()
		 {
			 int a[] = { 80, 40, 30, 60, 90, 70, 10, 50, 20 };
			 int i, len = (sizeof(a)) / (sizeof(a[0]));
			 MaxHeap<int>* tree = new MaxHeap<int>();

			 cout << "== 依次添加: ";
			 for (i = 0; i<len; i++)
			 {
				 cout << a[i] << " ";
				 tree->insert(a[i]);
			 }

			 cout << "\n== 最 小 堆: ";
			 tree->print();

			 i = 15;
			 tree->insert(i);
			 cout << "\n== 添加元素: " << i;
			 cout << "\n== 最 小 堆: ";
			 tree->print();

			 i = 10;
			 tree->remove(i);
			 cout << "\n== 删除元素: " << i;
			 cout << "\n== 最 小 堆: ";
			 tree->print();
			 cout << endl;

			 return;
		 }
	 }

}
 #endif