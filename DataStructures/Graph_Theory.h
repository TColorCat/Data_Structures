#ifndef Graph_Theory_H_ 
#define Graph_Theory_H_ 
#include<vector>
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
		 
		 MatrixUDG() = default;
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
		 MatrixUDG(const vector<T>& vexs,const char edges[][2]);
		 ~MatrixUDG(){}

		 // ��ӡ�������ͼ
		 void print();

	
	 };

 }
 #endif