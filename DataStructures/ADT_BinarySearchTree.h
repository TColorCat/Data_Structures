#ifndef BinarySearch_h_
#define BinarySearch_h_
#include<iostream>
namespace Data_Structures
{
	template<typename Comparable,typename Comparator=less<Comparable>>
	class BinarySearchTree
	{
	private:
		struct BinaryNode
		{
			Comparable element;
			BinaryNode* left;
			BinaryNode* right;

			BinaryNode(const Comparable &Element, BinaryNode*le, BinaryNode*ri)
				:element(Element), left(le), right(ri){}
			/*BinaryNode(Comparable&& Element, BinaryNode*le, BinaryNode*ri)//应该是不行的
				:element(std::move(Element)), left(le), right(ri){}*/

			~BinaryNode(){ make_empty(); };
		};
		BinaryNode* root;
		Comparator isLess;
	public:
		BinarySearchTree(){};
		BinarySearchTree(const BinarySearchTree& source) :root{ nullptr }
		{
			root = clone(source.root);
		}

		~BinarySearchTree(){};

		const Comparable& findmin()const{ return findmin()->element; }
		const Comparable& findmax()const{ return findmax()->element; }

		bool contains(const Comparable& target)const;
		bool isempty()const{ return root == nullptr; }
		void printTree()const;

		void make_empty();
		void insert(const Comparable& inside);
		void remove(const Comparable& target);


		BinarySearchTree& operator=(const BinarySearchTree& target);

	private:
		void insert(const Comparable &x, BinaryNode*&t);
		void remove(const Comparable &x, BinaryNode*&t);
		BinaryNode* findmin(BinaryNode*t)const;
		BinaryNode* findmax(BinaryNode*t)const;
		bool contains(const Comparable& target, BinaryNode*t)const;
		bool make_empty(BinaryNode*&t);
		void printTree(BinaryNode*t,std::ostream&out)const;
		BinaryNode* clone(BinaryNode*target)const;





	};
}


#endif 