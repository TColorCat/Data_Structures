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

		// 获取第index位置的节点的值
		T getValue(int index)
		{
			return get_node(index)->val;
		}
		T get_first(){ return get_node(0)->val; }
		T get_last(){ return get_node(count)->val; }

		// 将节点插入到第index位置之前
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
			//插入在第一个后面
			LinkNode<T>* pnode = new LinkNode<T>(head->before, head, t);
			head->before->next = pnode;
			head->before = pnode;
			count++;

			return true;
		}

		// 将节点追加到链表的末尾
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
			//判断对错
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
		// 删除所有的节点

		while (temp != head)
		{
			store = temp;
			temp = store->next;
			delete store;
		}

		// 删除"表头"
		delete temp;
		head = NULL;

	}

	namespace Test_demo
	{
		void test_DLink()
		{
			int iarr[4] = { 10, 20, 30, 40 };

			cout << "\n----int_test----" << endl;
			// 创建双向链表
			DLink<int>* pdlink = new DLink<int>();

			pdlink->insert(0, 20);        // 将 20 插入到第一个位置
			
			

			pdlink->insert_first(10);

			pdlink->append_last(30);
			
			
			// 双向链表的大小
			cout << "size()=" << pdlink->size() << endl;

			// 打印双向链表中的全部数据
			int sz = pdlink->size();
			for (int i = 0; i<sz; i++)
				cout << "pdlink(" << i << ")=" << pdlink->getValue(i) << endl;


		

		}
	}

	
}



#endif