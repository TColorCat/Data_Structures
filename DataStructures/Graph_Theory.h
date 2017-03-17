#ifndef Graph_Theory_H_ 
#define Graph_Theory_H_ 
#include<vector>
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
		 
		 MatrixUDG() = default;
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
		 MatrixUDG(const vector<T>& vexs,const char edges[][2]);
		 ~MatrixUDG(){}

		 // 打印矩阵队列图
		 void print();

	
	 };

 }
 #endif