#ifndef Graph_Theory_H__ 
#define Graph_Theory_H__


#include<vector>
#include<iostream>

using namespace std;

namespace Data_structures
 { 

	 //图的基本表示方法:矩阵法与链表法
	 /*输入是各个节点 
	 
	 是从起始点到结束点的路径*/
	 template<typename T>
	 class MatrixUDG {
	 private:
		 
		 vector<T> mVexs;    // 顶点集合
		 int mVexNum;             // 顶点数
		 int mEdgNum;             // 边数
		 vector<vector<T>> mMatrix;   // 邻接矩阵

	 public:
		 
		 MatrixUDG() ;
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
		 MatrixUDG(const vector<T>& vexs,const T edges[][2]);
		 ~MatrixUDG();

		 // 打印矩阵队列图
		 void printt();

	
	 };

	 

	 template<class T>
	 MatrixUDG<T>::MatrixUDG(){}
	 template<class T>
	 MatrixUDG<T>::~MatrixUDG(){}
	 template<class T>
	 MatrixUDG<T>::MatrixUDG(const vector<T>& vexs, const T edges[][2])
		 :mVexs(vexs), mVexNum(vexs.size())

	 {
					if(sizeof(edges) == 0 )
						mEdgNum= 0 
					else
						mEdgNum= sizeof(edges) / sizeof(edges[0]); //([edges]()->int{return   })
		 cout << sizeof(edges) << endl;
		 cout <<  sizeof(edges[0]) << endl;

		 cout << mEdgNum << endl;
		 mMatrix = vector<vector<T>>(mVexNum, vector<T>(mVexNum, 0));

		 for (int i = 0; i < mEdgNum; i++)
		 {
			 mMatrix[edges[i][0]][edges[i][1]] = 1;
			 mMatrix[edges[i][1]][edges[i][0]] = 1;

		 }
	 }

	 template<class T>
	 void MatrixUDG<T>::printt()
	 {
		 int i, j;

		 cout << "Martix Graph:" << endl;
		 for (i = 0; i < mVexNum; i++)
		 {
			 for (j = 0; j < mVexNum; j++)
				 cout << mMatrix[i][j] << " ";
			 cout << endl;
		 }
	 }

 }
 #endif