#ifndef Graph_Theory_H__ 
#define Graph_Theory_H__


#include<vector>
#include<iostream>
#include<map>
#include<list>
#include<queue>
#include<set>
#include<functional>
//#include<algorithm>
//#include<unordered_map>
using namespace std;

namespace Data_structures
 { 
	 template<typename P,typename Q>
	 struct graph_edges
	 {
		 P begin;
		 P end;
		 Q value;

		 graph_edges(P be, P ed, Q val=1) :begin(be), end(ed), value(val){}

	 };
	 //图的基本表示方法:矩阵法与链表法
	 /*输入是各个节点 
	 
	 是从起始点到结束点的路径*/
	 template<typename T>
	 class Graph {
	 private:
		 
		 map<T,int> mVexs;    // 顶点集合
		 int mVexNum;             // 顶点数
		 int mEdgNum;            // 边数

		 map<T, bool>visted_log;//访问记录表
		 /*不使用unordered-map的原因： unordered_map需要存储的类自己有一个hash函数，而stl给基本类型提供了hash函数*/
		 vector<vector<int>> mMatrix;   // 邻接矩阵
		 map<T, list<T>> mlist;//链表表示法  还有有向图与无向图的区别
		 


		 list<T> get_next_pointes(const T& root);//得到这个点的下一个点

		 void reset();//重置访问图
		 bool all_visted(T& next_point);//看看是否所有的点都访问了，用于非连通图，如果有没有访问到的，就返回这个点。

		 bool Kruskal_loop(vector<graph_edges<T, int>>&find, graph_edges<T, int>&now_edge);
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
		 Graph(const vector<T>& vexs, const T edges[][2], const int &number_edge,const bool& direction);
		 /*权值value要求必须大于0 ，否则视为不通*/
		 Graph(const vector<T>& vexs, const vector<graph_edges<T,int>>&edges, const bool& direction);
		 //另一 种仅仅需要边的集合的权值图
		 Graph(const vector<graph_edges<T, int>>&edges, const bool& direction=false);


		 ~Graph();



		 //图的广度优先遍历
		 vector<vector<T>> BFS();
		 //图的深度优先遍历
		 void DFS();
		 //拓扑排序
		 void Toposort();

		 //最小生成树 prim法
		 Graph<T> prim();

		 Graph<T>Kruskal(vector<graph_edges<T, int>>&edge);
		 // 打印矩阵队列图
		 void printt();

		 

	
	 };

	 

	


	 namespace Test_demo
	 {
		 void test_graph_martix()
		 {
			 vector<char> points = { 'a', 'b', 'c', 'd', 'e', 'f','g' };
			 char edges[][2] = { { 'b', 'a' }, { 'b', 'd' }, {'d','e'}
			 , { 'd', 'f' }, { 'a', 'g' }, { 'c', 'g' }, {'c','f'} };
			 int length;
			 if (sizeof(edges) == 0)
				length = 0;
			 else
				 length = sizeof(edges)/sizeof(edges[0]); //([edges]()->int{return   })
			 //因为传入的数组是个指针，而且怎么也变不回原来的数组，所以只能出此下策
			

			 Graph<char>test(points, edges,length,true);

			 test.printt();

			 cout << endl;
			 vector<vector<char>>forest;
			 test.BFS();
			 cout << endl;
			 test.DFS();
			 cout << endl;
			 test.Toposort();
		 }

		 void test_value_graph()
		 {
			 vector<char> points = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
			 vector<graph_edges<char, int>>edge = { { 'a', 'b' ,12}, { 'b', 'c',10 }, { 'd', 'e' ,4}
			 , { 'c', 'd',3 }, { 'c', 'e' ,5}, { 'c', 'f' ,6}, { 'a', 'g' ,14}
			 , { 'a', 'f', 16 }, { 'b', 'f', 7 }, { 'g', 'f', 9 }, { 'e', 'f', 2 }
			 , { 'e', 'g', 8 } };
			 Graph<char>test(points, edge,  false);

			 test.printt();
			 cout << "prim" << endl;
			 Graph<char>name = test.prim();
			 name.printt();



			 cout << "kruskal" << endl;
			 Graph<char>namet = test.Kruskal(edge);
			 namet.printt();
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
	Graph<T>::Graph(const vector<T>& vexs, const T edges[][2], const int &number_edge, const bool& direction)
		: mVexNum(vexs.size()), mEdgNum(number_edge)

	{

		for (int i = 0; i < mVexNum; i++)
		{
			mVexs[vexs[i]] =i ;
			mlist[vexs[i]] = list<T>();//添加链表的 节点
			visted_log[vexs[i]] = false;
		}

		



		mMatrix = vector<vector<int>>(mVexNum, vector<int>(mVexNum, 0));

		for (int i = 0; i < mEdgNum; i++)
		{
			//矩阵记录法
			mMatrix[mVexs[edges[i][0]]][mVexs[edges[i][1]]] = 1;

			//链表记录法 有相图
			mlist[edges[i][0]].push_back(edges[i][1]);
			if(!direction)//无相图
			{
				mMatrix[mVexs[edges[i][1]]][mVexs[edges[i][0]]] = 1;
				mlist[edges[i][1]].push_back(edges[i][0]);
			}
				
		}



	}
	template<class T>
	Graph<T>::Graph(const vector<T>& vexs, const vector<graph_edges<T, int>>&edge,const bool& direction)
		:mVexNum(vexs.size()), mEdgNum(edge.size())
	{

		for (int i = 0; i < mVexNum; i++)
		{
			mVexs[vexs[i]] = i;
			mlist[vexs[i]] = list<T>();//添加链表的 节点
			visted_log[vexs[i]] = false;
		}





		mMatrix = vector<vector<int>>(mVexNum, vector<int>(mVexNum, 0));

		for (int i = 0; i < mEdgNum; i++)
		{
			//矩阵记录法
			graph_edges<T, int>temp = edge[i];
			if (temp.value == 0)
			{
				cout << "wrong has zero " << endl;
				break;
			}

			

			//链表记录法 有相图
			mlist[temp.begin].push_back(temp.end);
			if (!direction)//无相图
			{
				mMatrix[mVexs.at(temp.end)][mVexs.at(temp.begin)] = temp.value;
				mlist[temp.end].push_back(temp.begin);
			}
			mMatrix[mVexs.at(temp.begin)][mVexs.at(temp.end)] = temp.value;
		}

	}
	template<class T>
	Graph<T>::Graph(const vector<graph_edges<T, int>>&edge, const bool& direction)
		: mEdgNum(edge.size())
	{
		//mvexnum MVEX
		int point_count=0;
		for (int i = 0; i < mEdgNum; i++)
		{

			graph_edges<T, int>temp = edge[i];
			if (temp.value == 0)
			{
				cout << "wrong has zero " << endl;
				break;
			}
			else
			{
				if (mVexs.find(temp.begin) == mVexs.end())
				{
					mVexs[temp.begin] = point_count;
					visted_log[temp.begin] = false;
					++point_count;
				}
				if (mVexs.find(temp.end) == mVexs.end())
				{
					mVexs[temp.end] = point_count;
					visted_log[temp.end] = false;
					++point_count;
				}

				//链表记录法 有相图
				mlist[temp.begin].push_back(temp.end);
				if (!direction)//无相图
				{

					mlist[temp.end].push_back(temp.begin);
				}

			}

		}
		mVexNum = point_count;
		mMatrix = vector<vector<int>>(mVexNum, vector<int>(mVexNum, 0));

		for (int i = 0; i < mEdgNum; i++)
		{
			
			graph_edges<T, int>temp = edge[i];
			if (temp.value == 0)
			{
				cout << "wrong has zero " << endl;
				break;
			}


			//矩阵记录法
			mMatrix[mVexs.at(temp.begin)][mVexs.at(temp.end)] = temp.value;
		
			if (!direction)//无相图
			{
				mMatrix[mVexs.at(temp.end)][mVexs.at(temp.begin)] = temp.value;
				
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
	vector<vector<T>> Graph<T>::BFS()//使用mlist表示法来完成整个函数
	{
		queue<T>room_next;
		vector<vector<T>>forest;
		
		reset();//重置
		T begin;
		while(!all_visted(begin))//这是为了避免非连通图的影响。
		{
			vector<T>tree;
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

				//以上是更新阶段
				//以下是处理阶段 要想处理现在想到的方法是 room.find(temp),
				//当然也可以把 T当做一个指针类型，其指向其他数据庞大的节点，这样也就不需要考虑什么复制或者引用的范围了
				//但是这样对于unique_ptr是不成立的。就算是这样，在输入的时候，可以创建一个两级的指针索引
				//不过输入的 时候肯定是我们先做好安排，所以这个不用担心。
				tree.push_back(temp);

				//cout << temp << "-->";
			}

			forest.push_back(tree);
		} 
		return forest;
	}

	template<class T>
	void Graph<T>::DFS()//使用栈来模拟
	{

		reset();
		stack<T>room_next;
		T begin;
		while (!all_visted(begin))//这是为了避免非连通图的影响。
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
				}也一样可行*/
				cout << temp << "->";
				//以上是更新阶段

			}
		} 

	}

	template<class T>
	void Graph<T>::Toposort()
	{
		queue<T>room;
		vector<T>result;
		vector<int>input_number(mVexNum, 0);


		int i = 0;
		for (const pair<T, int> a : mVexs)
		{

			
			int number = 0;
			for (int j = 0; j < mVexNum; j++)
			{
				if (mMatrix[j][i] != 0)
					++number;
				
			}
			input_number[a.second] = number;//初始化入图。
			if (number==0)
				room.push(a.first);

			++i;
			
		}//更新源点

		while (!room.empty())
		{
			T node = room.front();
			room.pop();
			result.push_back(node);

			list<T>nodes = mlist.at(node);
			for (const T neb : nodes)
			{
				--input_number[mVexs.at(neb)];
				if (input_number[mVexs.at(neb)]==0)//出问题的地方；粗心是表象，以后遇到判断，把判断式写出来，又不会占用什么，或者到完成阶段任务之后，再把判断语句化简
					room.push(neb);
			}
		}

		//输出 阶段
		for (auto a : result)
			cout << a << "->";

		cout << endl;
		
	}

	template<class T>
	Graph<T> Graph<T>::prim()
	{
		vector<graph_edges<T, int>>result;

		//avoide no edge
		if (mEdgNum==0)
			return Graph<T>();//

	

	
		set<T>finded_point;
		vector<T>points;
		//先期准备
		
		
		/*

		设图G顶点集合为U，首先任意选择图G中的一点作为起始点a，将该点加入集合V，
		再从集合U-V中找到另一点b使得点b到V中任意一点的权值最小，此时将b点也加入集合V；

		所以判断的时候，就要比较很多才行。
		然后挪动到下一个点
		直到寻找到全部的点为止
		那这样的话，实际上不需要输入的边的数据，只需要链表与矩阵表示法就可以了。在这里虽然两个方法都用的原因是链表表示法里面没有加权*/

		const pair<T, int>ntemp =*(mVexs.begin());

		finded_point.insert(ntemp.first);//塞进第一个点
		points.push_back(ntemp.first);

		while (finded_point.size()!=mVexNum)//因为size()是无符号数
		{
			//假设首个字母已经成功加入了,下面就是使用mMartix来检查那个点到这个点最小
			T begin_point=0;//这个就是为了容易记录边
			T next_point=0;
			int power = 0;
			for (const pair<T,int> finding:mVexs)
			{
			
				if (finded_point.find(finding.first) == finded_point.end())//只有还没有访问到的点才能判断，这样为了防止重复查找，而且节约了时间
				{
					for (T a : finded_point)//已经找到的点，其他的点finding需要对已经找到的点进行搜索，找最小的边，相对应的点就是下一个点。
					{
						int temp_power = mMatrix[finding.second][mVexs.at(a)];
						if (temp_power != 0)//需要是连同的边
						{
							if (power == 0)
							{
								power = temp_power;
								next_point = finding.first;
								begin_point = a;
								//这里的错误在与，没有考虑到如果一开始就是最优解的情况，当时下意识排除掉了最优解是第一个的可能性。
								//所以以后考虑的时候，第一个也是会有最优解的。
							}
							else
							{
								if (temp_power<power)//发现了权更小的边
								{
									power = temp_power;
									next_point = finding.first;
									begin_point = a;
								}
							}
						}

					}
				}

			}

			if (power != 0)//这是为了防止错误。这时出现power=0的情况说明有孤立点的存在
			{//以上两个for循环之后，得到的next_point与power就是下一个点，以及两点之间的边的权值。
				finded_point.insert(next_point);
				points.push_back(next_point);
				result.push_back(graph_edges<T,int>(begin_point, next_point, power));
			}
			else
			{
				cout << "has single point" << endl;
				break;
			}

		}
		

		Graph<T>name(points, result, false);
		
		return name;
		
		
	}
	template<class T>
	bool Graph<T>::Kruskal_loop(vector<graph_edges<T, int>>&find_edges,graph_edges<T,int>&now_edge)
	{
		/*是判断两个边的点的终点是否相同，如果不同说明不会构成回路，终点就是点值最大*/

		if (find_edges.empty())
			return false;
		else
		{
			T nbegin = now_edge.begin;
			T nend = now_edge.end;
			Graph<T> temp_g(find_edges, false);

			vector<vector<T>>forest=temp_g.BFS();//使用BFS来产生一个搜索树
			
			for (auto a : forest)//检查是否在一个旁支上
			{
				bool be = false;
				bool ed = false;
				for (auto b : a)
				{
					if (nbegin == b)
						be = true;
					if (nend == b)
						ed = true;
				}

				if (be&&ed)
					return true;
			}
			return false;

		}
	}
	template<class T>
	Graph<T> Graph<T>::Kruskal(vector<graph_edges<T, int>>&edge)
	{
		if (edge.empty())return Graph<T>();

		/*想要加一个边时，首先检测这个边的两个点是否是有着相同的最大点，如果是，则说明是回路*/
		sort(edge.begin(), edge.end(),
			[](const graph_edges<T, int>&a, const graph_edges<T, int>&b){return a.value < b.value; });
		//vector<T>finded_point;
		vector<graph_edges<T, int>>result;
		//int count = 0;

		for (int i = 0; i < mEdgNum; i++)
		{
			

			if (!Kruskal_loop(result,edge[i]) )
			{
				//count++;
				result.push_back(edge[i]);
			}
		}

		Graph<T> name(result);
		return name;
	}
	template<class T>
	void Graph<T>::printt()
	{
		
		
		cout << "Martix Graph:" << endl;
		cout << "	";
		for (int i = 0; i < mVexNum; i++)
		{
			for (const pair<T, int> a : mVexs)
				if (a.second == i)
					cout << a.first << "	";

		

		
		}
		cout << endl;
		for (int i = 0; i < mVexNum;i++)
		{
			for (const pair<T, int> a : mVexs)
				if (a.second == i)
					cout << a.first << "	";
		
			for (int j = 0; j < mVexNum; j++)
				cout << mMatrix[i][j] <<"	";
			cout << endl;
	
		}
		
		cout << "list Graph:" << endl;//这样才是图链表的正确表示方法。
		
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