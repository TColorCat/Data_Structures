#include"stdafx.h"
#include"ADT_BinarySearchTree.h"


using namespace Data_Structures;
template<typename Comparable>
bool Data_Structures::BinarySearchTree::contains(const Comparable&target)const
{
	return contains(target, root);
}
template<typename Comparable>
bool Data_Structures::BinarySearchTree::contains(const Comparable& target, BinaryNode*t)const
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