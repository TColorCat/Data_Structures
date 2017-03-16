#ifndef Binary_Heap_H_ 
#define Binary_Heap_H_ 
#include<iostream>
using namespace std;
namespace Data_structures
 { 
	 template <class T>//���ѵ�ʵ��
	 class MaxHeap{
	 private:
		 T *mHeap;        // ����
		 int mCapacity;    // �ܵ�����
		 int mSize;        // ʵ������

	 private:
		 // ���ѵ����µ����㷨
		 void filterdown(int start, int end);
		 // ���ѵ����ϵ����㷨(��start��ʼ����ֱ��0��������)
		 void filterup(int start);
	 public:
		 MaxHeap();
		 MaxHeap(int capacity);
		 ~MaxHeap();

		 // ����data�ڶ�����е�����
		 int getIndex(T data);
		 // ɾ�������е�data
		 int remove(T data);
		 // ��data���뵽�������
		 int insert(T data);
		 // ��ӡ�����
		 void print();
	 };
 
	 namespace  Test_demo
	 {
		 void test_heap_bianry()
		 {
			 int a[] = { 80, 40, 30, 60, 90, 70, 10, 50, 20 };
			 int i, len = (sizeof(a)) / (sizeof(a[0]));
			 MaxHeap<int>* tree = new MaxHeap<int>();

			 cout << "== �������: ";
			 for (i = 0; i<len; i++)
			 {
				 cout << a[i] << " ";
				 tree->insert(a[i]);
			 }

			 cout << "\n== �� С ��: ";
			 tree->print();

			 i = 15;
			 tree->insert(i);
			 cout << "\n== ���Ԫ��: " << i;
			 cout << "\n== �� С ��: ";
			 tree->print();

			 i = 10;
			 tree->remove(i);
			 cout << "\n== ɾ��Ԫ��: " << i;
			 cout << "\n== �� С ��: ";
			 tree->print();
			 cout << endl;

			 return;
		 }
	 }

}
 #endif