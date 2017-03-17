#ifndef Graph_Theory_H__ 
#define Graph_Theory_H__


#include<vector>
#include<iostream>

using namespace std;

namespace Data_structures
 { 

	 //ͼ�Ļ�����ʾ����:����������
	 /*�����Ǹ����ڵ� 
	 
	 �Ǵ���ʼ�㵽�������·��*/
	 template<typename T>
	 class MatrixUDG {
	 private:
		 
		 vector<T> mVexs;    // ���㼯��
		 int mVexNum;             // ������
		 int mEdgNum;             // ����
		 vector<vector<T>> mMatrix;   // �ڽӾ���

	 public:
		 
		 MatrixUDG() ;
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
		 MatrixUDG(const vector<T>& vexs,const T edges[][2]);
		 ~MatrixUDG();

		 // ��ӡ�������ͼ
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