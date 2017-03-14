#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include<iostream>
#include<vector>
#include<stack>
using namespace std;       
namespace Data_structures
{
	// BinarySearchTree class
	//
	// CONSTRUCTION: zero parameter
	//
	// ******************PUBLIC OPERATIONS*********************
	// void insert( x )       --> Insert x
	// void remove( x )       --> Remove x
	// bool contains( x )     --> Return true if x is present
	// Comparable findMin( )  --> Return smallest item
	// Comparable findMax( )  --> Return largest item
	// boolean isEmpty( )     --> Return true if empty; else false
	// void makeEmpty( )      --> Remove all items
	// void printTree( )      --> Print tree in sorted order
	// ******************ERRORS********************************
	// Throws UnderflowException as warranted
	//template <typename Comparable>
	

	template <typename Comparable>
	class BinarySearchTree
	{
		struct BinaryNode
		{
			Comparable element;
			BinaryNode *left;
			BinaryNode *right;

			BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
				: element{ theElement }, left{ lt }, right{ rt } { }

			BinaryNode(Comparable && theElement, BinaryNode *lt, BinaryNode *rt)
				: element{ std::move(theElement) }, left{ lt }, right{ rt } { }

			~BinaryNode(){};
		};
	public:
		BinarySearchTree() : root{ nullptr }
		{
		}

		/**
		* Copy constructor
		*/
		BinarySearchTree(const BinarySearchTree & rhs) : root{ nullptr }
		{
			root = clone(rhs.root);
		}

		/**
		* Move constructor
		*/
		BinarySearchTree(BinarySearchTree && rhs) : root{ rhs.root }
		{
			rhs.root = nullptr;
		}

		/**
		* Destructor for the tree
		*/
		~BinarySearchTree()
		{
			makeEmpty();
		}

		/**
		* Copy assignment
		*/
		BinarySearchTree & operator=(const BinarySearchTree & rhs)
		{
			BinarySearchTree copy = rhs;
			std::swap(*this, copy);
			return *this;
		}

		/**
		* Move assignment
		*/
		BinarySearchTree & operator=(BinarySearchTree && rhs)
		{
			std::swap(root, rhs.root);
			return *this;
		}


		/**
		* Find the smallest item in the tree.
		* Throw UnderflowException if empty.
		*/
		const Comparable & findMin() const
		{
			if (isEmpty())
				throw UnderflowException{};
			return findMin(root)->element;
		}

		/**
		* Find the largest item in the tree.
		* Throw UnderflowException if empty.
		*/
		const Comparable & findMax() const
		{
			if (isEmpty())
				throw UnderflowException{};
			return findMax(root)->element;
		}

		/**
		* Returns true if x is found in the tree.
		*/
		bool contains(const Comparable & x) const
		{
			return contains(x, root);
		}

		/**
		* Test if the tree is logically empty.
		* Return true if empty, false otherwise.
		*/
		bool isEmpty() const
		{
			return root == nullptr;
		}

		/**
		* Print the tree contents in sorted order.
		*/
		void printTree(ostream & out = cout) const
		{
			if (isEmpty())
				out << "Empty tree" << endl;
			else
				printTree(root, out);
		}

		/**
		* Make the tree logically empty.
		*/
		void makeEmpty()
		{
			makeEmpty(root);
		}

		/**
		* Insert x into the tree; duplicates are ignored.
		*/
		void insert(const Comparable & x)
		{
			insert(x, root);
		}

		/**
		* Insert x into the tree; duplicates are ignored.
		*/
		void insert(Comparable && x)
		{
			insert(std::move(x), root);
		}

		void insert_loop(const Comparable&t)
		{
			insert_loop(t, root);
		}
		/**
		* Remove x from the tree. Nothing is done if x is not found.
		*/
		void remove(const Comparable & x)
		{
			remove(x, root);
		}

		/*遍历的方式*/
		void prorder()
		{
			prorder(root);
		}
		void miorder_loop()
		{
			miorder_loop(root);
		}
		void miorder(){ miorder(root); }
		void posorder(){ posorder(root); }
		void posorder_loop(){ posorder_loop(root); }
	private:


		BinaryNode *root;
		/*前序遍历*/
		void prorder(BinaryNode*tree)const
		{
			if (tree != nullptr)
			{
				cout << tree->element << " ";
				prorder(tree->left);
				prorder(tree->right);
			}
		}
		/*中序遍历*/
		void miorder(BinaryNode*tree)const
		{
			if (tree != nullptr)
			{

				miorder(tree->left);
				cout << tree->element << " ";
				miorder(tree->right);
			}
		}
		/*中序遍历-循环方式
		主要是模拟了进栈出栈的行为*/
		void miorder_loop(BinaryNode*root)const
		{
			stack<BinaryNode*>room;
			BinaryNode* pcurrent=root;
			//room.push(pcurrent);
			while (!room.empty()||pcurrent)
			{
				if (pcurrent)
				{
					room.push(pcurrent);
					pcurrent = pcurrent->left;

				}
				else
				{
					BinaryNode* temp = room.top();
					cout << temp->element << " ";
					room.pop();
					pcurrent = temp->right;//重要
				}
			}
			
		}
		/*后序遍历*/
		void posorder(BinaryNode*tree)const
		{
			if (tree != nullptr)
			{

				posorder(tree->left);

				posorder(tree->right);
				cout << tree->element << " ";
			}
		}
		/*需要更多信息来确定是否有右子树*/
		struct Node_r
		{
			BinaryNode*node;
			bool revisted_right;
			Node_r(BinaryNode* right, bool r) :node(right), revisted_right(r){};
			~Node_r(){};
		};
		void posorder_loop(BinaryNode*root)const
		{
			BinaryNode* pcurrent = root;
			stack<Node_r>room;

			while (pcurrent!=nullptr)
			{
				room.push(Node_r(pcurrent, false));
				pcurrent = pcurrent->left;
			}

			while (!room.empty() )
			{
				Node_r temp = room.top();
				//注意，任意一个结点N，只要他有左孩子，则在N入栈之后，N的左孩子必然也跟着入栈了(这个体现在算法的后半部分)，
				//所以当我们拿到栈顶元素的时候，可以确信这个元素要么没有左孩子，要么其左孩子已经被访问过，
				//所以此时我们就不关心它的左孩子了，我们只关心其右孩子。
				//若其右孩子已经被访问过，或是该元素没有右孩子，则由后序遍历的定义，此时可以visit这个结点了
				if (temp.node->right == nullptr || temp.revisted_right)
				{
					cout << temp.node->element << " ";
					room.pop();
				}
				else
				{
					room.pop();
					temp.revisted_right = true;//修改右子树访问
					room.push(temp);


					BinaryNode*pcurren = temp.node->right;
					while (pcurren!=nullptr)
					{
						room.push(Node_r(pcurren, false));
						pcurren = pcurren->left;
					}
				}
				

			}
		}
		
		/**
		* Internal method to insert into a subtree.
		* x is the item to insert.
		* t is the node that roots the subtree.
		* Set the new root of the subtree.
		*/
		void insert(const Comparable & x, BinaryNode * & t)
		{
			if (t == nullptr)
				t = new BinaryNode{ x, nullptr, nullptr };
			else if (x < t->element)
				insert(x, t->left);
			else if (t->element < x)
				insert(x, t->right);
			else
				return;  // Duplicate; do nothing
		}

		/**
		* Internal method to insert into a subtree.
		* x is the item to insert.
		* t is the node that roots the subtree.
		* Set the new root of the subtree.
		*/
		void insert(Comparable && x, BinaryNode * & t)
		{
			if (t == nullptr)
				t = new BinaryNode{ std::move(x), nullptr, nullptr };
			else if (x < t->element)
				insert(std::move(x), t->left);
			else if (t->element < x)
				insert(std::move(x), t->right);
			else
				return;  // Duplicate; do nothing
		}
		/*循环版本的insert*/
		void insert_loop(const Comparable& value, BinaryNode* &node)//这里是指针的引用，不是指针的指针
		{
			if (!node)
				node = new BinaryNode{ value, nullptr, nullptr };
			else
			{
				while (node->left&& node->right)
				{
					if (value < node->element)
						node = node->right;
					else if (value>node->element)
						node = node->left;
					else
						return;//禁止相同的值
				}
				insert(value, node);


			}

		}
		/**
		* Internal method to remove from a subtree.
		* x is the item to remove.
		* t is the node that roots the subtree.
		* Set the new root of the subtree.
		*/
		void remove(const Comparable & x, BinaryNode * & t)
		{
			if (t == nullptr)
				return;   // Item not found; do nothing
			if (x < t->element)
				remove(x, t->left);
			else if (t->element < x)
				remove(x, t->right);
			else if (t->left != nullptr && t->right != nullptr) // Two children
			{
				t->element = findMin(t->right)->element;
				remove(t->element, t->right);
			}
			else
			{
				BinaryNode *oldNode = t;
				t = (t->left != nullptr) ? t->left : t->right;
				delete oldNode;
			}
		}

		/**
		* Internal method to find the smallest item in a subtree t.
		* Return node containing the smallest item.
		*/
		BinaryNode * findMin(BinaryNode *t) const
		{
			if (t == nullptr)
				return nullptr;
			if (t->left == nullptr)
				return t;
			return findMin(t->left);
		}

		/**
		* Internal method to find the largest item in a subtree t.
		* Return node containing the largest item.
		*/
		BinaryNode * findMax(BinaryNode *t) const
		{
			if (t != nullptr)
				while (t->right != nullptr)
					t = t->right;
			return t;
		}


		/**
		* Internal method to test if an item is in a subtree.
		* x is item to search for.
		* t is the node that roots the subtree.
		*/
		bool contains(const Comparable & x, BinaryNode *t) const
		{
			if (t == nullptr)
				return false;
			else if (x < t->element)
				return contains(x, t->left);
			else if (t->element < x)
				return contains(x, t->right);
			else
				return true;    // Match
		}
		/****** NONRECURSIVE VERSION*************************
		bool contains( const Comparable & x, BinaryNode *t ) const
		{
		while( t != nullptr )
		if( x < t->element )
		t = t->left;
		else if( t->element < x )
		t = t->right;
		else
		return true;    // Match

		return false;   // No match
		}
		*****************************************************/

		/**
		* Internal method to make subtree empty.
		*/
		void makeEmpty(BinaryNode * & t)
		{
			if (t != nullptr)
			{
				makeEmpty(t->left);
				makeEmpty(t->right);
				delete t;
			}
			t = nullptr;
		}

		/**
		* Internal method to print a subtree rooted at t in sorted order.
		*/
		void printTree(BinaryNode *t, ostream & out) const
		{
			if (t != nullptr)
			{
				printTree(t->left, out);
				out << t->element << endl;
				printTree(t->right, out);
			}
		}
		/*前驱：左子树中的最大节点
		后驱：右子树中的最小节点
		*/
		BinaryNode* predecessor(BinaryNode*root)
		{
			if (!root)
				return nullptr;
			else
			{
				if (root->left)
					return findMax(root);
				else
				{

				}
			}

			// 如果x没有左孩子。则x有以下两种可能：
			// (01) x是"一个右孩子"，则"x的前驱结点"为 "它的父结点"。
			// (01) x是"一个左孩子"，则查找"x的最低的父结点，并且该父结点要具有右孩子"，找到的这个"最低的父结点"就是"x的前驱结点"。
		}

		/**
		* Internal method to clone subtree.
		*/
		BinaryNode * clone(BinaryNode *t) const
		{
			if (t == nullptr)
				return nullptr;
			else
				return new BinaryNode{ t->element, clone(t->left), clone(t->right) };
		}
	};



	namespace Test_demo
	{
	

		void test_BinarySearch()
		{
			BinarySearchTree<int>tree;
			std::vector<int>input = { 12,41, 62, 3, 94, 75, 6, 7, 8, 9, 10 };


			for (auto in : input)
				tree.insert_loop (in);
			

			tree.posorder_loop();
			cout << endl;
			tree.posorder();

			
		}
	}
}

#endif
