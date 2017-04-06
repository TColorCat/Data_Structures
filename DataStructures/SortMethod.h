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
		 /*��������жϺ���*/
		 
		 /*ð����������ѭ�����ú�һ���������ֵ����*/
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
						//���i���󣬾ͽ���λ�á�
					}
				}
		}

		/*��������
		O(n2)*/
		template<class T>
		void insert_sort(vector<T>&source,
			function<bool(T&, T&)>comp = [](T&a, T&b)->bool{return a < b; })
		{
			int i, j, k;
			int n = source.size();

			for (i = 1; i < n; ++i)
			{
				//Ϊsource[i]��ǰ���source[0...i-1]������������һ�����ʵ�λ��
				for (j = i - 1; j >= 0; j--)
					if (comp(source[j], source[i]))
						break;

				//���ҵ���һ�����ʵ�λ��
				if (j != i - 1)
				{
					//����source[i]������������
					int temp = source[i];
					for (k = i - 1; k > j; k--)
						source[k + 1] = source[k];
					//��source[i]�ŵ���ȷλ����
					source[k + 1] = temp;
				}
			}
		}

		/*ϣ������
		�����������
		����gap������ѡ�񣬻�Ӱ����תЧ��*/
		template<class T>
		void shell_sort(vector<T>&source,
			function<bool(T&, T&)>comp = [](T&a, T&b)->bool{return a < b; })
		{
			int n = source.size();
			int gap = n;
			for (gap /= 2; gap > 0; gap /= 2)
			{
				//����
				for (int i = 0; i < gap; ++i)
				{
					//��������
					for (int j = i+gap; j < n; j += gap)
					{
						if (comp(source[j], source[j - gap]))//�ҵ���Ҫ������λ�ã��ͰѺ����ֵ
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

		/*������ ʹ�ö���ѵ��ڲ���������*/
#define LeftSon(i) (2*i+1);
#define RightSon(i) (2*i+2);
#define Father(i) ((i-1)/2);
		/*
		* (���)�ѵ����µ����㷨
		*
		* ע������ʵ�ֵĶ��У���N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
		*     ���У�NΪ�����±�����ֵ���������е�1������Ӧ��NΪ0��
		*
		* ����˵����
		*     a -- �����������
		*     start -- ���µ��ڵ����ʼλ��(һ��Ϊ0����ʾ�ӵ�1����ʼ)
		*     end   -- ������Χ(һ��Ϊ���������һ��Ԫ�ص�����)
		*/
		template<class T>
		void maxheap_down(vector<T>&source, int start, int end)
		{
			int c = start;            // ��ǰ(current)�ڵ��λ��
			int l = 2 * c + 1;        // ��(left)���ӵ�λ��
			int tmp = source[c];            // ��ǰ(current)�ڵ�Ĵ�С
			for (; l <= end; c = l, l = 2 * l + 1)
			{
				// "l"�����ӣ�"l+1"���Һ���
				if (l < end && source[l] < source[l + 1])
					l++;        // ������������ѡ��ϴ��ߣ���m_heap[l+1]
				if (tmp >= source[l])
					break;        // ��������
				else            // ����ֵ
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

		//�鲢����

		/*���ǹ鲢�����merge���裬�ۺ�begin middle end�ָ������������鵽һ���µ���ʱ�����ڣ�Ȼ������֮�������¸�ֵ��source��*/
		template<class T>
		void merge(vector<T>&source,int begin,int middle,int end
			, function<bool(T&, T&)>comp = [](T&a, T&b)->bool{return a < b; })
		{
			vector<T>temp(end - begin+1, 0);//��1����Ҫ
			//���濪ʼ����������Ƚ�
			int before = begin;
			int after = middle+1;
			int index_temp = 0;
			while (before <= middle&&after <= end)
			{
				if (comp(source[before] , source[after]))
				{
					temp[index_temp++] = source[before++];//��� ���� Ҫ���һ��

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

			//�����

			for (unsigned int i = 0; i < temp.size(); ++i)
			{
				source[i+begin] = temp[i];

			}

		}
		template<class T>
		void sort(vector<T>&source, int begin, int end)
		{
			if (begin >= end)return;//�˳�����

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



		//����������Ͱ����  �������Ƕ���������������ķ�����������ʹ�ù��ģ�ʹ���±�����ʾ��С�ķ�ʽ
		//������ ʹ��map,��Ϊmapʹ�ú����ʵ�֣����������ʱ�䶼��O(lgn)��������ʱ�����O(nlgn)
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
			//��ʼ��
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


		//�򵥵���� ���ܡ�
		template<class T>
		void TestPrint(const vector<T>&source)
		{
			for (auto a : source)
				cout << a << " ";
			cout << endl;
		}
		//����
		void TestSoreMethod()
		{
			vector<int>target = { 1, 4, 2, 5, 7, 4, 3, 8, 9, 10, 44, 6, 3 };
			cout << "ð���������ֵ�ں�" << endl;
			bubble_sort(target);
			TestPrint(target);

			target = { 1, 4, 2, 5, 7, 4, 3, 8, 9, 10, 44, 6, 3 };
			cout << "��������" << endl;
			insert_sort(target);
			TestPrint(target);
			target = { 1, 4, 2, 5, 7, 4, 3, 8, 9, 10, 44, 6, 3 };
			cout << "ϣ������" << endl;
			shell_sort(target);
			TestPrint(target);

			target = { 1, 4, 2, 5, 7, 4, 3, 8, 9, 10, 44, 6, 3 };
			cout << "������" << endl;
			heap_sort(target);
			TestPrint(target);

			target = { 1, 4, 2, 5, 7, 4, 3, 8, 9, 10, 44, 6, 3 };
			cout << "�鲢����" << endl;
			merge_sort(target);
			TestPrint(target);


			target = { 1, 4, 2, 5, 7, 4, 3, 8, 9, 10, 44, 6, 3 };
			cout << "����map��Ͱ����" << endl;
			buck_sort(target);
			TestPrint(target);

		}
	 }

 }
 #endif