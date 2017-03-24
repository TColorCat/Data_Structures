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

	 //��Դ�㵽ĳ��������·���Ľ���ṹ
	 //T EndPoint;//�յ㣬Ҳ�Ǳ�־��Դ�㣬�ͷ���list��·�����ˡ�
	 //int PowerValue;//Դ�㵽�յ��Ȩֵ Ĭ��ֵ��-1��˵������Դ����˵����û��
	 //list<T> road;//Դ�㵽�յ��·��������Դ����յ�
	 //bool finally;//��־�Ƿ��Ѿ������˴�Դ�㵽�յ�Ĺ��̣�������ԭ�طָ�U,S����������
	 template<typename T>
	 struct ShortestRoad
	 {
		 T EndPoint;//�յ㣬Ҳ�Ǳ�־��Դ�㣬�ͷ���list��·�����ˡ�
		 int PowerValue;//Դ�㵽�յ��Ȩֵ Ĭ��ֵ��-1��˵������Դ����˵����û��
		 list<T> road;//Դ�㵽�յ��·��������Դ����յ�
		 bool finall;//��־�Ƿ��Ѿ������˴�Դ�㵽�յ�Ĺ��̣�������ԭ�طָ�U,S����������
		 ShortestRoad(const T& begin, const T&end, const int&power = INT_MAX)
			 :EndPoint(end), PowerValue(power), finall(begin == end)
		 {
			 if (begin == end)
			 {
				 road.push_back(begin);

				 PowerValue = 0;
			 }
		 }

		 ~ShortestRoad(){}
	 };
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

		 /*���ж������ߵĵ���յ��Ƿ���ͬ�������ͬ˵�����ṹ�ɻ�·���յ���ǵ�ֵ���*/
		 bool Kruskal_loop(vector<graph_edges<T, int>>&find, graph_edges<T, int>&now_edge);
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
		 Graph(const vector<T>& vexs, const T edges[][2], const int &number_edge,const bool& direction);
		 /*ȨֵvalueҪ��������0 ��������Ϊ��ͨ*/
		 Graph(const vector<T>& vexs, const vector<graph_edges<T,int>>&edges, const bool& direction);
		 //��һ �ֽ�����Ҫ�ߵļ��ϵ�Ȩֵͼ
		 Graph(const vector<graph_edges<T, int>>&edges, const bool& direction=false);

		 //=����  ��ʹ��swap����� map�ĸ�������
		 Graph<T> operator=(Graph<T>);

		 ~Graph();
		 //����˼�壬����ר������Ӷ���ı�
		 bool addedge(const graph_edges<T,int>& edge,const bool& direction = false);



		 //ͼ�Ĺ�����ȱ���
		 vector<vector<T>> BFS();
		 //ͼ��������ȱ���
		 void DFS();
		 //��������
		 void Toposort();

		 //��С������ prim��
		 Graph<T> prim();
			//	Kruskal��
		 Graph<T>Kruskal(vector<graph_edges<T, int>>&edge);


		 //��Դ���·���㷨
		 //Dijkstra��
		 map<T,ShortestRoad<T>> Dijkstra(const T& begin);
	 
		 // function<int(Graph<T>&, list<T>)>extendroad;
		// template<class T>
		 int FFsonExtend(list<T>&, const T &, const T & );
		
	 public:
		 //������㷨 ����ֵΪint,�β�������Ѱ������·���ĺ���,�����ҵ�������·��������������Ϊ0��˵��û���ҵ�
		 int FordFulkerson(const T&input, const T&output);
	
			 
	


		 
		 // ��ӡ���󣬶���ͼ
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
			 //��Ϊ����������Ǹ�ָ�룬������ôҲ�䲻��ԭ�������飬����ֻ�ܳ����²�
			

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

		 void ShortestValue()
		 {
			 vector<char> points = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
			 vector<graph_edges<char, int>>edge = { { 'a', 'b', 12 }, { 'b', 'c', 10 }, { 'd', 'e', 4 }
				 , { 'c', 'd', 3 }, { 'c', 'e', 5 }, { 'c', 'f', 6 }, { 'a', 'g', 14 }
				 , { 'a', 'f', 16 }, { 'b', 'f', 7 }, { 'g', 'f', 9 }, { 'e', 'f', 2 }
			 , { 'e', 'g', 8 } };
			 Graph<char>test(points, edge, true);
			
			 test.printt();
			 
			// auto result=test.Dijkstra('a');

			 test.FordFulkerson('a', 'g');
			// int a = 0;
		 }
		 void MaxFlow()
		 {
			 vector<graph_edges<char, int>>edge = { { 's', 'a', 16 }, { 's', 'b', 13 }, { 'a', 'c', 12 }
				 , { 'c', 'b', 9 }, { 'b', 'a', 4 }, { 'b', 'd', 14 }, { 'd', 'c', 7 }
				 , { 'c', 't', 20 }, { 'd', 't', 4 } };
			 Graph<char>test(edge, true);

			 test.printt();

			 // auto result=test.Dijkstra('a');

			 cout << test.FordFulkerson('s', 't') << endl;
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
			mlist[vexs[i]] = list<T>();//�������� �ڵ�
			visted_log[vexs[i]] = false;
		}

		



		mMatrix = vector<vector<int>>(mVexNum, vector<int>(mVexNum, 0));

		for (int i = 0; i < mEdgNum; i++)
		{
			//�����¼��
			mMatrix[mVexs[edges[i][0]]][mVexs[edges[i][1]]] = 1;

			//�����¼�� ����ͼ
			mlist[edges[i][0]].push_back(edges[i][1]);
			if(!direction)//����ͼ
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
			mlist[vexs[i]] = list<T>();//�������� �ڵ�
			visted_log[vexs[i]] = false;
		}





		mMatrix = vector<vector<int>>(mVexNum, vector<int>(mVexNum, 0));

		for (int i = 0; i < mEdgNum; i++)
		{
			//�����¼��
			graph_edges<T, int>temp = edge[i];
			if (temp.value == 0)
			{
				cout << "wrong has zero " << endl;
				break;
			}

			

			//�����¼�� ����ͼ
			mlist[temp.begin].push_back(temp.end);
			if (!direction)//����ͼ
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
					mlist[temp.begin] = list<T>();
					++point_count;
				}
				if (mVexs.find(temp.end) == mVexs.end())
				{
					mVexs[temp.end] = point_count;
					visted_log[temp.end] = false;
					mlist[temp.end] = list<T>();
					++point_count;
				}

				//�����¼�� ����ͼ
				mlist[temp.begin].push_back(temp.end);
				if (!direction)//����ͼ
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


			//�����¼��
			mMatrix[mVexs.at(temp.begin)][mVexs.at(temp.end)] = temp.value;
		
			if (!direction)//����ͼ
			{
				mMatrix[mVexs.at(temp.end)][mVexs.at(temp.begin)] = temp.value;
				
			}
			
		}

	}
	template<class T>
	bool Graph<T>::addedge(const graph_edges<T,int>&edge,const bool& direction)
	{
		//�Ȳ�ǰ�������Ƿ��Ѿ���map��
		//���ڶ���map�е����
		auto be = mVexs.find(edge.begin);
		auto ed = mVexs.find(edge.end);
	
		if (
			(be != mVexs.end()) && 
			(ed!= mVexs.end())
			)
		{
			if (mMatrix[mVexs.at(edge.begin)][mVexs.at(edge.end)] != 0)
			{
				cout << "had the edge" << endl;
				return false;
			}
			else
			{
				mMatrix[mVexs.at(edge.begin)][mVexs.at(edge.end)] = edge.value;
				return true;
			}

		}
		else
		{
			if (be == mVexs.end())
			{
				mVexs.insert(make_pair(edge.begin, mVexNum++));
				//����listĿ¼
				mlist.insert(make_pair(edge.begin, list<T>()));
				
			
				//���ľ����С
				for (auto it = mMatrix.begin(); it != mMatrix.end(); ++it)
				{
					
					it->push_back(0);

				}
				vector<int>temp(mVexNum, 0);
				mMatrix.push_back(temp);


			}
			if (ed == mVexs.end())
			{
				mVexs.insert(make_pair(edge.end, mVexNum++));
				//����liistĿ¼
				mlist.insert(make_pair(edge.end, list<T>()));
				

				//���ľ����С
				for (auto it = mMatrix.begin(); it != mMatrix.end(); ++it)
				{

					it->push_back(0);

				}
				vector<int>temp(mVexNum, 0);
				mMatrix.push_back(temp);


			}


			//���¾������б�Ŀ¼
			mMatrix[mVexs.at(edge.begin)][mVexs.at(edge.end)] = edge.value;
			mlist[edge.begin].push_back(edge.end);
			if (!direction)
			{
				mMatrix[mVexs.at(edge.end)][mVexs.at(edge.begin)] = edge.value;
				mlist[edge.end].push_back(edge.begin);
			}
			//��������ӱߵ���Ŀ������Ŀ
			++mEdgNum;
			return true;
		}


		
	}

	template<class T>
	Graph<T> Graph<T>::operator=(Graph<T>rhs)
	{
		 mVexs=rhs.mVexs;    // ���㼯��
		mVexNum=rhs.mVexNum;             // ������
		mEdgNum=rhs.mEdgNum;            // ����

		visted_log.swap(rhs.visted_log);//���ʼ�¼��
		/*��ʹ��unordered-map��ԭ�� unordered_map��Ҫ�洢�����Լ���һ��hash��������stl�����������ṩ��hash����*/
		mMatrix.swap(rhs.mMatrix);   // �ڽӾ���
		mlist.swap(rhs.mlist);//�����ʾ��  ��������ͼ������ͼ������


		return *this;
	}
	template<class T>
	void Graph<T>::reset()
	{
		for (map<T, bool>::iterator it = visted_log.begin(); it != visted_log.end(); ++it)
		{
			it->second = false;
			
		}

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
	int Graph<T>::FFsonExtend(list<T>&result, const T &input, const T &output)
	{
		map<T, ShortestRoad<T>> name = Dijkstra(input);



		result = name.at(output).road;
		int power = INT_MAX;
		if (result.size() == 0)return 0;
		T be = *(result.begin());
		T ed;
		for (auto it = ++result.begin(); it != result.end(); it++)
		{
			
			ed = *(it);
			if (mMatrix[mVexs.at(be)][mVexs.at(ed)] < power)
			{
				power = mMatrix[mVexs.at(be)][mVexs.at(ed)];
			}
			be = ed;

		}
		return power;
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
	vector<vector<T>> Graph<T>::BFS()//ʹ��mlist��ʾ���������������
	{
		queue<T>room_next;
		vector<vector<T>>forest;
		
		reset();//����
		T begin;
		while(!all_visted(begin))//����Ϊ�˱������ͨͼ��Ӱ�졣
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

				//�����Ǹ��½׶�
				//�����Ǵ���׶� Ҫ�봦�������뵽�ķ����� room.find(temp),
				//��ȻҲ���԰� T����һ��ָ�����ͣ���ָ�����������Ӵ�Ľڵ㣬����Ҳ�Ͳ���Ҫ����ʲô���ƻ������õķ�Χ��
				//������������unique_ptr�ǲ������ġ��������������������ʱ�򣬿��Դ���һ��������ָ������
				//��������� ʱ��϶������������ð��ţ�����������õ��ġ�
				tree.push_back(temp);

				//cout << temp << "-->";
			}

			forest.push_back(tree);
		} 
		return forest;
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
			input_number[a.second] = number;//��ʼ����ͼ��
			if (number==0)
				room.push(a.first);

			++i;
			
		}//����Դ��

		while (!room.empty())
		{
			T node = room.front();
			room.pop();
			result.push_back(node);

			list<T>nodes = mlist.at(node);
			for (const T neb : nodes)
			{
				--input_number[mVexs.at(neb)];
				if (input_number[mVexs.at(neb)]==0)//������ĵط��������Ǳ����Ժ������жϣ����ж�ʽд�������ֲ���ռ��ʲô�����ߵ���ɽ׶�����֮���ٰ��ж���仯��
					room.push(neb);
			}
		}

		//��� �׶�
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
		//����׼��
		
		
		/*

		��ͼG���㼯��ΪU����������ѡ��ͼG�е�һ����Ϊ��ʼ��a�����õ���뼯��V��
		�ٴӼ���U-V���ҵ���һ��bʹ�õ�b��V������һ���Ȩֵ��С����ʱ��b��Ҳ���뼯��V��

		�����жϵ�ʱ�򣬾�Ҫ�ȽϺܶ���С�
		Ȼ��Ų������һ����
		ֱ��Ѱ�ҵ�ȫ���ĵ�Ϊֹ
		�������Ļ���ʵ���ϲ���Ҫ����ıߵ����ݣ�ֻ��Ҫ����������ʾ���Ϳ����ˡ���������Ȼ�����������õ�ԭ���������ʾ������û�м�Ȩ*/

		const pair<T, int>ntemp =*(mVexs.begin());

		finded_point.insert(ntemp.first);//������һ����
		points.push_back(ntemp.first);

		while (finded_point.size()!=mVexNum)//��Ϊsize()���޷�����
		{
			//�����׸���ĸ�Ѿ��ɹ�������,�������ʹ��mMartix������Ǹ��㵽�������С
			T begin_point=0;//�������Ϊ�����׼�¼��
			T next_point=0;
			int power = 0;
			for (const pair<T,int> finding:mVexs)
			{
			
				if (finded_point.find(finding.first) == finded_point.end())//ֻ�л�û�з��ʵ��ĵ�����жϣ�����Ϊ�˷�ֹ�ظ����ң����ҽ�Լ��ʱ��
				{
					for (T a : finded_point)//�Ѿ��ҵ��ĵ㣬�����ĵ�finding��Ҫ���Ѿ��ҵ��ĵ��������������С�ıߣ����Ӧ�ĵ������һ���㡣
					{
						int temp_power = mMatrix[finding.second][mVexs.at(a)];
						if (temp_power != 0)//��Ҫ����ͬ�ı�
						{
							if (power == 0)
							{
								power = temp_power;
								next_point = finding.first;
								begin_point = a;
								//����Ĵ������룬û�п��ǵ����һ��ʼ�������Ž���������ʱ����ʶ�ų��������Ž��ǵ�һ���Ŀ����ԡ�
								//�����Ժ��ǵ�ʱ�򣬵�һ��Ҳ�ǻ������Ž�ġ�
							}
							else
							{
								if (temp_power<power)//������Ȩ��С�ı�
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

			if (power != 0)//����Ϊ�˷�ֹ������ʱ����power=0�����˵���й�����Ĵ���
			{//��������forѭ��֮�󣬵õ���next_point��power������һ���㣬�Լ�����֮��ıߵ�Ȩֵ��
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
		/*���ж������ߵĵ���յ��Ƿ���ͬ�������ͬ˵�����ṹ�ɻ�·���յ���ǵ�ֵ���*/

		if (find_edges.empty())
			return false;
		else
		{
			T nbegin = now_edge.begin;
			T nend = now_edge.end;
			Graph<T> temp_g(find_edges, false);

			vector<vector<T>>forest=temp_g.BFS();//ʹ��BFS������һ��������
			
			for (auto a : forest)//����Ƿ���һ����֧��
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

		/*��Ҫ��һ����ʱ�����ȼ������ߵ��������Ƿ���������ͬ�����㣬����ǣ���˵���ǻ�·*/
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
	map<T,ShortestRoad<T>> Graph<T>::Dijkstra(const T& sbegin)
	{
		map<T,ShortestRoad<T>> result;
		map<T,ShortestRoad<T>> U_table;//�洢û�б�ǵ�ļ���
		//priority_queue<T> U_table_lable;
		T begin = sbegin;
		//�ȳ�ʼ��U����
		for (const pair<T, int> point : mVexs)
		{
			ShortestRoad<T> temp(begin, point.first);
			U_table.insert(make_pair(point.first, temp));
		//	U_table_lable.push(point.first);
			
		
		}


	
		T NextPoint;


		while (result.size() != mVexNum)
		{
			//������ʼ�����һ���㣬�ҵ���begin��ͬ�ĵ�󣬸��¸õ��Ȩֵ��
			//���¸õ��rode��·������Դ���road���ƹ�����Ȼ������Լ�����㣩Ϊ��˳Ӧ���˼�룬ֻ����ʼ���roadдֵ
			//�ҵ���begin��ͨ�ĵ��У�Ȩֵ��С�ĵ㵱����һ��begin��
			//�������begin�㵽end����Ӿ�begin�㵽end��ȣ�·�����̣��͸���end��Ȩֵ������end��·����������begin���list�������ɵģ�Ȼ������Լ��ģ�

			
				auto itb = U_table.find(begin);
			
			//�ж�Դ��Ĵ��ڣ�Ȼ���Դ����������С�
			if (itb == U_table.end())return result;//��û�������
			itb->second.finall = true;
			ShortestRoad<T> temp = U_table.at(begin);
			result.insert(*itb);//�Ȳ���Դ�㵽�����
			/////////////////////////////////////////////////
			//���� ���Ǳ����Ĺ��̣���������Ҫά��һ����С��


			
			int rule=INT_MAX;
			for (T nextp : mlist.at(begin))
			{
				if (!U_table.at(nextp).finall)//����ȷ��������Ƿ��Ѿ����ʲ������˽�㼯�С���Ϊ������ͼ��
				{
					//������û�з��ʹ����Լ������е���ʼ�㵽Ŀ�� ��ľ���Ҫ����
					if ( U_table.at(nextp).PowerValue > (mMatrix[mVexs.at(begin)][mVexs.at(nextp)] + temp.PowerValue))
					{
						//�������Ȩֵ
						U_table.at(nextp).PowerValue = mMatrix[mVexs.at(begin)][mVexs.at(nextp)] + temp.PowerValue;

						//����begin��·��
						list<T>().swap(U_table.at(nextp).road);
						for (T begin_road : result.at(begin).road)
							U_table.at(nextp).road.push_back(begin_road);
				
						U_table.at(nextp).road.push_back(nextp);

					}



					if (U_table.at(nextp).PowerValue < rule)
					{
						NextPoint = nextp;
						rule = U_table.at(nextp).PowerValue;

					}

					
				}
				

			}
			

			//�������ƣ���Ϊ����һ��֧���ߵ���ͷʱ������ʣ�µĵ㣨finallΪFALSE�ĵ㣩Ȼ���ҵ� Ŀǰ��powervalueֵΪ��С�ĵ㣬������һ����
			if (rule == INT_MAX)//��ʱ�����֧�ߵ�ͷ�ˡ���Ҫ������һ����С��Ȩֵ�ĵ㿪ʼ,��Ϊ���ų����������
			{
				int ruler = INT_MAX;
				for (const auto findnext : U_table)
				{
					if (findnext.second.PowerValue < ruler && (!findnext.second.finall))
					{
						ruler = findnext.second.PowerValue;
						NextPoint = findnext.first;
					}
				}

			//������ǵ�û���ҵ���֮����˳����ã�Ȼ����Ƿ���ͨͼ��Ԥ����ʩ���� ʣ�µĵ��ӽ�ȥ��
				if (ruler == INT_MAX)
				{
					for (const auto findnext : U_table)
						if (!findnext.second.finall)
							result.insert(findnext);
					break;
				}

			}
			begin = NextPoint;
		}

		return result;
	}

	template<typename T>
	int Graph<T>::FordFulkerson(const T&input,const T&output)
	{
		//typedef  Rlist  list < T >;

		
		Graph<T>LeftGraph = *this; 
		list<T> extendR;
		
		int bigestFlow = 0;
		//auto a=extendR.begin();
		int temp = 0;
		temp= LeftGraph.FFsonExtend(extendR, input, output);
		while (temp > 0)
		{
			bigestFlow += temp;
			//�޸Ĳв�ͼ
			T be = *(extendR.begin());
			T ed;
			for (auto it = ++extendR.begin(); it != extendR.end(); it++)
			{

				ed = *(it);
				//�����Դ�ݽ��ˣ�����Ҫɾ��·
				//��Ϊ�϶���begin->end���·��������ֻ��Ҫ����a->b��ɾ������b->a�����
				if ((LeftGraph.mMatrix[LeftGraph.mVexs.at(be)][LeftGraph.mVexs.at(ed)] -= temp) == 0)
				{
					auto beit = LeftGraph.mlist[be].begin();

					while (*beit != ed)
						beit++;


					LeftGraph.mlist[be].erase(beit);

				}

				if (LeftGraph.mMatrix[LeftGraph.mVexs.at(ed)][LeftGraph.mVexs.at(be)] == 0)
					LeftGraph.mlist[ed].push_back(be);

				LeftGraph.mMatrix[LeftGraph.mVexs.at(ed)][LeftGraph.mVexs.at(be)] += temp;

				be = ed;

			}
			

		//	LeftGraph.printt();
			temp = LeftGraph.FFsonExtend(extendR, input, output);

		//	LeftGraph.printt();
		}

			
		
		return bigestFlow;
		
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