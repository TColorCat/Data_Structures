#include"stdafx.h"
#include"ADT_BinarySearchTree.h"


using namespace Data_Structures;

template<typename Comparable, typename Comparator = less<Comparable>>
bool BinarySearchTree<Comparable>::contains(const Comparable&target)const
{
	return contains(target, root);
}
template<typename Comparable, typename Comparator = less<Comparable>>
bool BinarySearchTree<Comparable>::contains(const Comparable& target, BinaryNode*t)const
{
	if (t == nullptr)
		return false;
	else if (isLess(target,t->element))
	{
		return contains(target, root->left);
	}
	else if (isLess(target, t->right))
	{
		return contains(target, root->right)
	}
	else
		return true;
}
template<typename Comparable, typename Comparator = less<Comparable>>
BinaryNode* BinarySearchTree<Comparable>::findmin(BinaryNode*t)
{
	if (t == nullptr)
		return nullptr;
	else if (t->left == nullptr)
	{
		return t;
	}
	else
	{
		return findmin(t->left);
	}
}

template<typename Comparable, typename Comparator = less<Comparable>>
BinaryNode*
BinarySearchTree<Comparable>::findmax(BinaryNode*t)
{
	if (t!=nullptr)
		while (t->right!=nullptr)
		{
			t = t->right;
		}
	return t;
}


template<typename Comparable, typename Comparator = less<Comparable>>
void BinarySearchTree<Comparable>::remove(const Comparable &x, BinaryNode*&t)
{
	if (!t)
		return;
	if (x < t->element)
	{
		remove(x, t->left);
	}
	else if (t->element < x)
		remove(x, t->right);
	else if ((!t->left) && (!t->right))
	{
		t->element = findmin(t->right)->element;
		remove(t->element, t->right);
	}
	else
	{
		BinaryNode* oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;

		delete oldNode;
	}

}

template<typename Comparable, typename Comparator = less<Comparable>>
void BinarySearchTree<Comparable>::make_empty(BinaryNode*&t)
{
	if (t != nullptr)
	{
		make_empty(t->left);
		make_empty(t->right);
		delete t;
	}
	t = nullptr;
}
template<typename Comparable, typename Comparator = less<Comparable>>
BinaryNode* BinarySearchTree<Comparable>::clone(BinaryNode*target)const
{
	if (!t)
		return nullptr;
	else
	{
		return new BinaryNode{ t->element, clone(t->left), clone(t->right) };
	}
}

template<typename Comparable, typename Comparator = less<Comparable>>
void BinarySearchTree<Comparable>::insert(const Comparable & x, BinaryNode*& t)
{
	//找到最低点的叶子

	if (!t)
		t = new BinaryNode{ x, nullptr, nullptr };
	else if (x < t->element)
		insert(x, t->left);
	else if (t->element < x)
		insert(x, t->right);
	else
		return;


}
;
