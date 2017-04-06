#ifndef SortMethod_H_ 
#define SortMethod_H_ 
 

#include<vector>
#include<iostream>
#include<map>
using namespace std;
namespace Data_structures
 { 

	 namespace Sort_Method
	 {
		 /*最基础的判断函数*/
		 
		 /*冒泡排序，依次循环安置好一个最大的数字到最后*/
		template<class T>
		void bubble_sort(vector<T>&source,
			function<bool(T&, T&)>comp = [](T&a, T&b)->bool{return a < b; })
		{
			int size = source.size();
			for (int i = 0; i < size; ++i)
				for (int j = i+1; j < size; ++j)
				{
					if (comp(source[j] ,source[i]))
					{
						auto temp = source[j];
						source[j] = source[i];
						source[i] = temp;
						//如果i更大，就交换位置。
					}
				}
		}

		/*插入排序
		O(n2)*/
		template<class T>
		void insert_sort(vector<T>&source,
			function<bool(T&, T&)>comp = [](T&a, T&b)->bool{return a < b; })
		{
			int i, j, k;
			int n = source.size();

			for (i = 1; i < n; ++i)
			{
				//为source[i]在前面的source[0...i-1]有序区间中找一个合适的位置
				for (j = i - 1; j >= 0; j--)
					if (comp(source[j], source[i]))
						break;

				//如找到了一个合适的位置
				if (j != i - 1)
				{
					//将比source[i]大的数据向后移
					int temp = source[i];
					for (k = i - 1; k > j; k--)
						source[k + 1] = source[k];
					//将source[i]放到正确位置上
					source[k + 1] = temp;
				}
			}
		}

		/*希尔排序
		分组插入排序
		对于gap步数的选择，会影响运转效率*/
		template<class T>
		void shell_sort(vector<T>&source,
			function<bool(T&, T&)>comp = [](T&a, T&b)->bool{return a < b; })
		{
			int n = source.size();
			int gap = n;
			for (gap /= 2; gap > 0; gap /= 2)
			{
				//分组
				for (int i = 0; i < gap; ++i)
				{
					//分组排序
					for (int j = i+gap; j < n; j += gap)
					{
						if (comp(source[j], source[j - gap]))//找到需要交换的位置，就把后面的值
						{
							int temp = source[j];
							int k = j - gap;
							while (k >= 0 && source[k] > temp)
							{
								source[k + gap] = source[k];
								k -= gap;
							}
							source[k + gap] = temp;

						}

					}
				}
			}
		}

		/*堆排序 使用二叉堆的内部操作代码*/
#define LeftSon(i) (2*i+1);
#define RightSon(i) (2*i+2);
#define Father(i) ((i-1)/2);
		/*
		* (最大)堆的向下调整算法
		*
		* 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
		*     其中，N为数组下标索引值，如数组中第1个数对应的N为0。
		*
		* 参数说明：
		*     a -- 待排序的数组
		*     start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
		*     end   -- 截至范围(一般为数组中最后一个元素的索引)
		*/
		template<class T>
		void maxheap_down(vector<T>&source, int start, int end)
		{
			int c = start;            // 当前(current)节点的位置
			int l = 2 * c + 1;        // 左(left)孩子的位置
			int tmp = source[c];            // 当前(current)节点的大小
			for (; l <= end; c = l, l = 2 * l + 1)
			{
				// "l"是左孩子，"l+1"是右孩子
				if (l < end && source[l] < source[l + 1])
					l++;        // 左右两孩子中选择较大者，即m_heap[l+1]
				if (tmp >= source[l])
					break;        // 调整结束
				else            // 交换值
				{
					source[c] = source[l];
					source[l] = tmp;
				}
			}
		}

		template<class T>
		void heap_sort(vector<T>&source)
		{
			int n = source.size();
			for (int i = n / 2 - 1; i >= 0; i--)
				maxheap_down(source, i, n - 1);

			for (int end = n - 1; end >= 0; --end)
			{
				maxheap_down(source, 0, end);
				//exchange source[0] and source[end]  

				auto temp = source[0];
				 
				source[0] = source[end];
				source[end] = temp;

			}

		}

		//归并排序

		/*这是归并排序的merge步骤，糅合begin middle end分隔出的两个数组到一个新的临时数组内，然后排序之后再重新赋值到source中*/
		template<class T>
		void merge(vector<T>&source,int begin,int middle,int end
			, function<bool(T&, T&)>comp = [](T&a, T&b)->bool{return a < b; })
		{
			vector<T>temp(end - begin+1, 0);//加1很重要
			//下面开始两个数组相比较
			int before = begin;
			int after = middle+1;
			int index_temp = 0;
			while (before <= middle&&after <= end)
			{
				if (comp(source[before] , source[after]))
				{
					temp[index_temp++] = source[before++];//这个 还是 要检测一下

				}
				else
				{
					temp[index_temp++] = source[after++];
				}
			}
			while (before<=middle)
				temp[index_temp++] = source[before++];
			while (after <= end)
				temp[index_temp++] = source[after++];

			//最后复制

			for (unsigned int i = 0; i < temp.size(); ++i)
			{
				source[i+begin] = temp[i];

			}

		}
		template<class T>
		void sort(vector<T>&source, int begin, int end)
		{
			if (begin >= end)return;//退出条件

			int middle = (begin + end) / 2;
			sort(source, begin, middle);
			sort(source, middle + 1, end);

			merge(source, begin, middle,end);
		}
		template<class T>
		void merge_sort(vector<T>&source)
		{
			if (source.empty())return;
			int begin = 0;
			int end = source.size()-1;
			//int middle = (begin + end) / 2;

			sort(source, begin, end);
		}



		//基数排序与桶排序  基本上是对正整数计数排序的方法，就是我使用过的，使用下标来表示大小的方式
		//在这里 使用map,因为map使用红黑树实现，所以其操作时间都是O(lgn)所以排序时间就是O(nlgn)
		template<class T>
		struct comp
		{

			bool operator()(const T&a, const T&b)
			{
				return a < b;
			}
		};
		template<class T>
		void buck_sort(vector<T>&source)
		{
			map<T, int, comp<T>>bucks;
			//初始化
			/*for (auto a : source)
				bucks[a] = 0;*/
			for (auto a : source)
				bucks[a]++;


			vector<T>().swap(source);
			for (const pair<T,int> a : bucks)
			{
				for (int i = 0; i < a.second; ++i)
					source.push_back(a.first);
			}
			
		}


		//简单的输出 功能。
		template<class T>
		void TestPrint(const vector<T>&source)
		{
			for (auto a : source)
				cout << a << " ";
			cout << endl;
		}
		//测试
		void TestSoreMethod()
		{
			vector<int>target = { 1, 4, 2, 5, 7, 4, 3, 8, 9, 10, 44, 6, 3 };
			cout << "冒泡排序，最大值在后" << endl;
			bubble_sort(target);
			TestPrint(target);

			target = { 1, 4, 2, 5, 7, 4, 3, 8, 9, 10, 44, 6, 3 };
			cout << "插入排序" << endl;
			insert_sort(target);
			TestPrint(target);
			target = { 1, 4, 2, 5, 7, 4, 3, 8, 9, 10, 44, 6, 3 };
			cout << "希尔排序" << endl;
			shell_sort(target);
			TestPrint(target);

			target = { 1, 4, 2, 5, 7, 4, 3, 8, 9, 10, 44, 6, 3 };
			cout << "堆排序" << endl;
			heap_sort(target);
			TestPrint(target);

			target = { 1, 4, 2, 5, 7, 4, 3, 8, 9, 10, 44, 6, 3 };
			cout << "归并排序" << endl;
			merge_sort(target);
			TestPrint(target);


			target = { 1, 4, 2, 5, 7, 4, 3, 8, 9, 10, 44, 6, 3 };
			cout << "基于map的桶排序" << endl;
			buck_sort(target);
			TestPrint(target);

		}
	 }

 }
 #endif