#ifndef Graph_Theory_H__ 
#define Graph_Theory_H__


#include<vector>
#include<iostream>
#include<map>
#include<list>
using namespace std;

namespace Data_structures
 { 

	 //ͼ�Ļ�����ʾ����:����������
	 /*�����Ǹ����ڵ� 
	 
	 �Ǵ���ʼ�㵽�������·��*/
	 template<typename T>
	 class Graph {
	 private:
		 
		 map<int,T> mVexs;    // ���㼯��
		 int mVexNum;             // ������
		 int mEdgNum;             // ����
		 vector<vector<int>> mMatrix;   // �ڽӾ���
		 map<T, list<T>> mlist;//�����ʾ��

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
		 Graph(const vector<T>& vexs,const T edges[][2]);
		 ~Graph();

		 // ��ӡ�������ͼ
		 void printt();

		 

	
	 };

	 

	


	 namespace Test_demo
	 {
		 void test_graph_martix()
		 {
			 vector<char> points = { 'a', 'b', 'c', 'd', 'e', 'f' };
			 char edges[][2] = { { 'a', 'b' }, { 'c', 'd' } };

			 Graph<char>test(points, edges);

			 test.printt();
		 }
	 }
 }


namespace Data_structures
{
	template<class T>
	Graph<T>::Graph(){}
	template<class T>
	Graph<T>::~Graph(){}
	template<class T>
	Graph<T>::Graph(const vector<T>& vexs, const T edges[][2])
		: mVexNum(vexs.size())

	{

		for (int i = 0; i < mVexNum; i++)
		{
			mVexs[vexs[i]] = i;
			mlist[vexs[i]] = list<T>();//�������� �ڵ�
		}

		if (sizeof(edges) == 0)
			mEdgNum = 0;
		else
			mEdgNum = sizeof(edges) / sizeof(edges[0]); //([edges]()->int{return   })



		mMatrix = vector<vector<int>>(mVexNum, vector<int>(mVexNum, 0));

		for (int i = 0; i < mEdgNum; i++)
		{
			mMatrix[mVexs[edges[i][0]]][mVexs[edges[i][1]]] = 1;
			mMatrix[mVexs[edges[i][1]]][mVexs[edges[i][0]]] = 1;
			//�����¼�� ����ͼ
			mlist[edges[i][0]].push_back(edges[i][1]);


		}



	}

	template<class T>
	void Graph<T>::printt()
	{
		

		cout << "Martix Graph:" << endl;
		for (int i = 0; i < mVexNum; i++)
		{
			for (int j = 0; j < mVexNum; j++)
				cout << mMatrix[i][j] << " ";
			cout << endl;
		}

		
		cout << "list Graph:" << endl;//��������ͼ�������ȷ��ʾ������
		for (const pair<T,list<T>> a : mlist)
		{
			for (auto it = a.second.begin(); it != a.second.end(); it++)
				cout << " " << *it;
				
			cout << endl;
		}
	}
}
 #endif