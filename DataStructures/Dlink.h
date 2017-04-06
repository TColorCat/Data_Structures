#ifndef DLink_H_
#define DLink_H_
#include<iostream>
using namespace std;
namespace Data_structures
{
	template<class T>
	struct LinkNode
	{
		LinkNode* next;
		LinkNode* before;
		T val;

		LinkNode(){};
		LinkNode(LinkNode* a, LinkNode*b, T v) :before(a), next(b), val(v){};
		
		friend ostream& operator<<(ostream&os,const LinkNode& node)
		{
			os << node.val << " ";
			return os;
		}
		~LinkNode(){};
	};

	template<class T>
	class DLink
	{
	private:
		LinkNode<T>*head;
		int count;
	
	public:
		DLink() :head(nullptr), count(0){}
	
		virtual ~DLink();
		

		int size(){ return count; }
		bool is_empty(){ return count==0; }

		// ��ȡ��indexλ�õĽڵ��ֵ
		T getValue(int index)
		{
			return get_node(index)->val;
		}
		T get_first(){ return get_node(0)->val; }
		T get_last(){ return get_node(count)->val; }

		// ���ڵ���뵽��indexλ��֮ǰ
		bool  insert(int index, T t)
		{
			if (index == 0)
				insert_first(t);
			else
			{
				LinkNode<T>*temp = get_node(index);
				LinkNode<T>* newNode = new LinkNode<T>(temp->before, temp, t);
				temp->before->next = newNode;
				temp->before = newNode;
				++count;
			}
			
			
			return true;
		}
		bool insert_first(T t)
		{
			if (head == nullptr)
			{
				LinkNode<T>* pnode = new LinkNode<T>(nullptr, nullptr, t);
				head = pnode;
				head->before = pnode;
				head->next = pnode;
				count++;
				return true;
			}
			//�����ڵ�һ������
			LinkNode<T>* pnode = new LinkNode<T>(head->before, head, t);
			head->before->next = pnode;
			head->before = pnode;
			count++;

			return true;
		}

		// ���ڵ�׷�ӵ������ĩβ
		bool append_last(T t)
		{
			if (head == nullptr)
			{
				LinkNode<T>* pnode = new LinkNode<T>(nullptr, nullptr, t);
				head = pnode;
				head->before = pnode;
				head->next = pnode;
				count++;
				return true;
			}
			LinkNode<T>* pnode = new LinkNode<T>(head, head->next,t);
			head->before->next = pnode;
			head->before= pnode;
			count++;

			return true;
		}

		bool del(int index)
		{
			LinkNode<T>*temp = get_node(index);
			temp->before->next = temp->next;
			temp->next->before = temp->before;

			delete temp;
			--count;
			return true;
		}
		bool delete_first()
		{
			LinkNode<T>*temp = head;
			head = temp->next;
			temp->before->next = head;
			head->before = temp->before;
			
			delete temp;
			--count;
			return true;
		}
		bool delete_last()
		{
			LinkNode<T>*temp = head->before;
			head->before = temp->before;
			temp->before->next = head;			
			delete temp;

			--count;
			return true;

		}

	
	private:
		LinkNode<T> *get_node(int index)
		{
			//�ж϶Դ�
			if (index<0 || index>count)
			{
				cout << "wrong index" << endl;
				return nullptr;
			}
			int number = 0;
			LinkNode<T>* result=head;
			while (number != index)
			{
				result = result->next;
				++number;
			}

			return result;
			
		}

	};
	template<class T>
	DLink<T>::~DLink()
	{
		LinkNode<T>*temp;
		LinkNode<T>* store;
		temp = head->next;
		// ɾ�����еĽڵ�

		while (temp != head)
		{
			store = temp;
			temp = store->next;
			delete store;
		}

		// ɾ��"��ͷ"
		delete temp;
		head = NULL;

	}

	namespace Test_demo
	{
		void test_DLink()
		{
			int iarr[4] = { 10, 20, 30, 40 };

			cout << "\n----int_test----" << endl;
			// ����˫������
			DLink<int>* pdlink = new DLink<int>();

			pdlink->insert(0, 20);        // �� 20 ���뵽��һ��λ��
			
			

			pdlink->insert_first(10);

			pdlink->append_last(30);
			
			
			// ˫������Ĵ�С
			cout << "size()=" << pdlink->size() << endl;

			// ��ӡ˫�������е�ȫ������
			int sz = pdlink->size();
			for (int i = 0; i<sz; i++)
				cout << "pdlink(" << i << ")=" << pdlink->getValue(i) << endl;


		

		}
	}

	
}



#endif