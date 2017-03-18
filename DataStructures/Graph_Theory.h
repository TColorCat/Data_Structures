#ifndef Graph_Theory_H__ 
#define Graph_Theory_H__


#include<vector>
#include<iostream>
#include<map>
#include<list>
#include<queue>
//#include<unordered_map>
using namespace std;

namespace Data_structures
 { 

	 //ͼ�Ļ�����ʾ����:����������
	 /*�����Ǹ����ڵ� 
	 
	 �Ǵ���ʼ�㵽�������·��*/
	 template<typename T>
	 class Graph {
	 private:
		 
		 map<T,int> mVexs;    // ���㼯��
		 int mVexNum;             // ������
		 int mEdgNum;            // ����

		 map<T, bool>visted_log;//���ʼ�¼��
		 /*��ʹ��unordered-map��ԭ�� unordered_map��Ҫ�洢�����Լ���һ��hash��������stl�����������ṩ��hash����*/
		 vector<vector<int>> mMatrix;   // �ڽӾ���
		 map<T, list<T>> mlist;//�����ʾ��  ��������ͼ������ͼ������
		 


		 list<T> get_next_pointes(const T& root);//�õ���������һ����

		 void reset();//���÷���ͼ
		 bool all_visted(T& next_point);//�����Ƿ����еĵ㶼�����ˣ����ڷ���ͨͼ�������û�з��ʵ��ģ��ͷ�������㡣
	 public:
		 
		 Graph() ;
		 // ����ͼ(�����ṩ�ľ���)
		 /*
		 * ����ͼ(�����ṩ�ľ���)
		 *
		 * ����˵����
		 *     vexs  -- ��������
		 *     vlen  -- ��������ĳ���
		 *     edges -- ������
		 *     elen  -- ������ĳ���
		 */
		 Graph(const vector<T>& vexs,const T edges[][2],const bool& direction);
		 ~Graph();



		 //ͼ�Ĺ�����ȱ���
		 void BFS();
		 //ͼ��������ȱ���
		 void DFS();
		 // ��ӡ�������ͼ
		 void printt();

		 

	
	 };

	 

	


	 namespace Test_demo
	 {
		 void test_graph_martix()
		 {
			 vector<char> points = { 'a', 'b', 'c', 'd', 'e', 'f' };
			 char edges[][2] = { { 'a', 'b' }, { 'c', 'd' }, {'e','f'} };

			 Graph<char>test(points, edges,false);

			 test.printt();

			 cout << endl;
			 test.BFS();
			 cout << endl;
			 test.DFS();

		 }
	 }
 }

//implentments 
namespace Data_structures
{
	template<class T>
	Graph<T>::Graph(){}
	template<class T>
	Graph<T>::~Graph(){}
	template<class T>
	Graph<T>::Graph(const vector<T>& vexs, const T edges[][2],const bool& direction)
		: mVexNum(vexs.size())

	{

		for (int i = 0; i < mVexNum; i++)
		{
			mVexs[vexs[i]] =i ;
			mlist[vexs[i]] = list<T>();//�������� �ڵ�
			visted_log[vexs[i]] = false;
		}

		if (sizeof(edges) == 0)
			mEdgNum = 0;
		else
			mEdgNum = sizeof(edges) / sizeof(edges[0]); //([edges]()->int{return   })



		mMatrix = vector<vector<int>>(mVexNum, vector<int>(mVexNum, 0));

		for (int i = 0; i < mEdgNum; i++)
		{
			//�����¼��
			mMatrix[mVexs[edges[i][0]]][mVexs[edges[i][1]]] = 1;

			//�����¼�� ����ͼ
			mlist[edges[i][0]].push_back(edges[i][1]);
			if (!direction)//����ͼ
			{
				mMatrix[mVexs[edges[i][1]]][mVexs[edges[i][0]]] = 1;
				mlist[edges[i][1]].push_back(edges[i][0]);
			}
				
			


		}



	}
	template<class T>
	void Graph<T>::reset()
	{
		for (map<T, bool>::iterator it = visted_log.begin(); it != visted_log.end(); ++it)
			it->second = false;

	}

	template <class T>
	list<T> Graph<T>::get_next_pointes(const T& root)
	{
		list<T> result;
		const auto roots = mlist.find(root);
		if (roots == mlist.end())
			return result;
		else
		{
			result = mlist[root];
			
		}
		return result;
	}

	template<class T>
	bool Graph<T>::all_visted(T& next_point)
	{
		
		/*for (pair<T, bool>a : visted_log)
			{
				if (a.second == false)
				{
					next_point = a.first;
					return false;
				}
			}*/
		for (auto a = visted_log.begin(); a != visted_log.end(); ++a)
		{
			if (a->second == false)
			{
				next_point = a->first;
				return false;
			}
		}
			
		
		return true;
		
	}
	template<class T>
	void Graph<T>::BFS()//ʹ��mlist��ʾ��
	{
		queue<T>room_next;
		
		reset();//����
		T begin;
		while(!all_visted(begin))//����Ϊ�˱������ͨͼ��Ӱ�졣
		{
			
			room_next.push(begin);
			while (!room_next.empty())
			{
				T temp = room_next.front();
				visted_log.at(temp) = true;
				room_next.pop();
				list<T>name = get_next_pointes(temp);

				for (auto a = name.begin(); a != name.end(); ++a)
				{
					if (!visted_log.at(*a))
					{
						room_next.push(*a);
						visted_log.at(*a) = true;
					}
				}

				//�����Ǹ��½׶�
				//�����Ǵ���׶� Ҫ�봦�������뵽�ķ����� room.find(temp),
				//��ȻҲ���԰� T����һ��ָ�����ͣ���ָ�����������Ӵ�Ľڵ㣬����Ҳ�Ͳ���Ҫ����ʲô���ƻ������õķ�Χ��
				//������������unique_ptr�ǲ������ġ��������������������ʱ�򣬿��Դ���һ��������ָ������
				//��������� ʱ��϶������������ð��ţ�����������õ��ġ�
				cout << temp << "-->";
			}
		} 

	}

	template<class T>
	void Graph<T>::DFS()//ʹ��ջ��ģ��
	{

		reset();
		stack<T>room_next;
		T begin;
		while (!all_visted(begin))//����Ϊ�˱������ͨͼ��Ӱ�졣
		{

			room_next.push(begin);
			while (!room_next.empty())
			{
				T temp = room_next.top();
				visted_log.at(temp) = true;
				room_next.pop();
				list<T>name = get_next_pointes(temp);
				for (auto a = name.begin(); a != name.end(); ++a)
				{
					if (!visted_log.at(*a))
					{
						room_next.push(*a);
						visted_log.at(*a) = true;
					}
				}
				/*for (auto a : name)
				{
					if (!visted_log.at(a))
					{
						room_next.push(a);
						visted_log.at(a) = true;
					}
				}Ҳһ������*/
				cout << temp << "->";
				//�����Ǹ��½׶�

			}
		} 

	}
	template<class T>
	void Graph<T>::printt()
	{
		
		
		cout << "Martix Graph:" << endl;
		int i = 0;
		for (const pair<T, int> a : mVexs)
		{
			
			cout << a.first << "|  ";
			for (int j = 0; j < mVexNum; j++)
				cout << mMatrix[i][j] << " ";
			cout << endl;
			++i;
		}
		
		cout << "list Graph:" << endl;//��������ͼ�������ȷ��ʾ������
		
		for (const pair<T,list<T>> a : mlist)
		{
			cout <<a.first << "->";
			for (auto it = a.second.begin(); it != a.second.end(); it++)
				cout << " " << *it;
				
			cout << endl;
		}
	}
}
 #endif