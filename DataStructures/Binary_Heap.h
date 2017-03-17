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

namespace Data_structures
{
	/*
	* ���캯��
	*/
	template <class T>
	MaxHeap<T>::MaxHeap()
	{
		new (this)MaxHeap(30);
	}

	template <class T>
	MaxHeap<T>::MaxHeap(int capacity)
	{
		mSize = 0;
		mCapacity = capacity;
		mHeap = new T[mCapacity];
	}
	/*
	* ��������
	*/
	template <class T>
	MaxHeap<T>::~MaxHeap()
	{
		mSize = 0;
		mCapacity = 0;
		delete[] mHeap;
	}

	/*
	* ����data�ڶ�����е�����
	*
	* ����ֵ��
	*     ���� -- ����data�������е�����
	*     ������ -- -1
	*/
	template <class T>
	int MaxHeap<T>::getIndex(T data)
	{
		for (int i = 0; i<mSize; i++)
			if (data == mHeap[i])
				return i;

		return -1;
	}

	/*
	* ���ѵ����µ����㷨
	*
	* ע������ʵ�ֵĶ��У���N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
	*
	* ����˵����
	*     start -- ���µ��ڵ����ʼλ��(һ��Ϊ0����ʾ�ӵ�1����ʼ)
	*     end   -- ������Χ(һ��Ϊ���������һ��Ԫ�ص�����)
	*/
	template <class T>
	void MaxHeap<T>::filterdown(int start, int end)
	{
		int c = start;          // ��ǰ(current)�ڵ��λ��
		int l = 2 * c + 1;     // ��(left)���ӵ�λ��
		T tmp = mHeap[c];    // ��ǰ(current)�ڵ�Ĵ�С

		while (l <= end)
		{
			// "l"�����ӣ�"l+1"���Һ���
			if (l < end && mHeap[l] < mHeap[l + 1])
				l++;        // ������������ѡ��ϴ��ߣ���mHeap[l+1]
			if (tmp >= mHeap[l])
				break;        //��������
			else
			{
				mHeap[c] = mHeap[l];
				c = l;
				l = 2 * l + 1;
			}
		}
		mHeap[c] = tmp;
	}

	/*
	* ɾ�������е�data
	*
	* ����ֵ��
	*      0���ɹ�
	*     -1��ʧ��
	*/
	template <class T>
	int MaxHeap<T>::remove(T data)
	{
		int index;
		// ���"��"�ѿգ��򷵻�-1
		if (mSize == 0)
			return -1;

		// ��ȡdata�������е�����
		index = getIndex(data);
		if (index == -1)
			return -1;

		mHeap[index] = mHeap[--mSize];    // �����Ԫ���
		filterdown(index, mSize - 1);        // ��indexλ�ÿ�ʼ�������µ���Ϊ����

		return 0;
	}

	/*
	* ���ѵ����ϵ����㷨(��start��ʼ����ֱ��0��������)
	*
	* ע������ʵ�ֵĶ��У���N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
	*
	* ����˵����
	*     start -- ���ϵ��ڵ����ʼλ��(һ��Ϊ���������һ��Ԫ�ص�����)
	*/
	template <class T>
	void MaxHeap<T>::filterup(int start)
	{
		int c = start;            // ��ǰ�ڵ�(current)��λ��
		int p = (c - 1) / 2;        // ��(parent)����λ�� 
		T tmp = mHeap[c];        // ��ǰ�ڵ�(current)�Ĵ�С

		while (c > 0)
		{
			if (mHeap[p] >= tmp)
				break;
			else
			{
				mHeap[c] = mHeap[p];
				c = p;
				p = (p - 1) / 2;
			}
		}
		mHeap[c] = tmp;
	}

	/*
	* ��data���뵽�������
	*
	* ����ֵ��
	*     0����ʾ�ɹ�
	*    -1����ʾʧ��
	*/
	template <class T>
	int MaxHeap<T>::insert(T data)
	{
		// ���"��"�������򷵻�
		if (mSize == mCapacity)
			return -1;

		mHeap[mSize] = data;        // ��"����"���ڱ�β
		filterup(mSize);    // ���ϵ�����
		mSize++;                    // �ѵ�ʵ������+1

		return 0;
	}

	/*
	* ��ӡ�����
	*
	* ����ֵ��
	*     0����ʾ�ɹ�
	*    -1����ʾʧ��
	*/
	template <class T>
	void MaxHeap<T>::print()
	{
		for (int i = 0; i<mSize; i++)
			cout << mHeap[i] << " ";
	}
}

 #endif