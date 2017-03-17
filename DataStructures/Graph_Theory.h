#ifndef Graph_Theory_H__ 
#define Graph_Theory_H__


#include<vector>
#include<iostream>
#include<map>
#include<list>
using namespace std;

namespace Data_structures
 { 

	 //图的基本表示方法:矩阵法与链表法
	 /*输入是各个节点 
	 
	 是从起始点到结束点的路径*/
	 template<typename T>
	 class Graph {
	 private:
		 
		 map<int,T> mVexs;    // 顶点集合
		 int mVexNum;             // 顶点数
		 int mEdgNum;             // 边数
		 vector<vector<int>> mMatrix;   // 邻接矩阵
		 map<T, list<T>> mlist;//链表表示法

	 public:
		 
		 Graph() ;
		 // 创建图(用已提供的矩阵)
		 /*
		 * 创建图(用已提供的矩阵)
		 *
		 * 参数说明：
		 *     vexs  -- 顶点数组
		 *     vlen  -- 顶点数组的长度
		 *     edges -- 边数组
		 *     elen  -- 边数组的长度
		 */
		 Graph(const vector<T>& vexs,const T edges[][2]);
		 ~Graph();

		 // 打印矩阵队列图
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
			mlist[vexs[i]] = list<T>();//添加链表的 节点
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
			//链表记录法 无相图
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

		
		cout << "list Graph:" << endl;//这样才是图链表的正确表示方法。
		for (const pair<T,list<T>> a : mlist)
		{
			for (auto it = a.second.begin(); it != a.second.end(); it++)
				cout << " " << *it;
				
			cout << endl;
		}
	}
}
 #endif