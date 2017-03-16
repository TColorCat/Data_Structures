#include"stdafx.h"
#include"Graph_Theory.h"

namespace Data_structures
{

	template<class T>
	MatrixUDG<T>::MatrixUDG(const vector<T>& vexs, const T edges[][2])
		:mVexs(vexs), mVexNum(vexs.size())
		, mEdgNum([edges]()->int{return  (sizeof(edges) != 0) ? (sizeof(edges) / sizeof(edges[0])) : 0; })
	{
		mMatrix = vector(mVexNum, vector<T>(mVexNum, 0));

		for (int i = 0; i < elen; i++)
		{
			mMatrix[edges[i][0]][edges[i][1]] = 1;
			mMatrix[edges[i][1]][edges[i][0]] = 1;

		}
	}

	template<class T>
	void MatrixUDG<T>::print()
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