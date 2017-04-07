#ifndef QueueList_H_
#define QueueList_H_
#include<iostream>
#include"Dlink.h"
using namespace std;
namespace Data_structures
{
	template<class T>
	class QueueList :private DLink<T>
	{
	public:

		QueueList() :DLink(){};
		~QueueList(){};

		void add(const T& a)
		{
			append_last(a);
		}
		T pop()
		{
			T temp = get_first();
			delete_first();
			return temp;
		}

		T front()
		{
			return get_first();
		}

		int getSize()
		{
			return size();
		}

		bool  isEmpty()
		{
			return size() == 0;
		}



		
	};


	namespace Test_demo
	{
		void test_queueList()
		{
			int tmp = 0;
			QueueList<int> *astack = new QueueList<int>();

			// ��10, 20, 30 �������������
			astack->add(10);
			astack->add(20);
			astack->add(30);

			// �������п�ͷԪ�ء���ֵ��tmp����ɾ������Ԫ�ء�
			tmp = astack->pop();

			cout << "tmp=" << tmp << endl;

			// ֻ�������п�ͷ��Ԫ�ء���ֵ��tmp����ɾ����Ԫ��.
			tmp = astack->front();
			cout << "tmp=" << tmp << endl;

			astack->add(40);

			cout << "is_empty()=" << astack->isEmpty() << endl;
			cout << "size()=" << astack->getSize() << endl;
			while (!astack->isEmpty())
			{
				tmp = astack->pop();
				cout << tmp << endl;
			}

			return;
		}
	}
}

#endif