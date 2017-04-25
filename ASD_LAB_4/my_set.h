#ifndef MY_SET_H
#define MY_SET_H

//#define nullptr 0

template <typename T>
//class MySet
//{
	class RBTree
	{
		class RBNode
		{
			RBNode * parent, * left, * right;
			T data;
			bool color;
		public:
			static const bool red = true;
			static const bool black = false;
			RBNode(RBNode * parent, T data = T(), bool color = red, RBNode * left = nullptr, RBNode * right = nullptr):
			parent(parent), data(data), color(color), left(left), right(right){};
			~RBNode()
			{
			while (left)
				delete left;
			while (right)
				delete right;
			}
			RBNode * grandparent()
			{
				if (parent)
				{
					return parent->parent;
				}
				else
				{
					return nullptr;
				}
			}
		};

		class RBLeaf : private RBNode
		{
		public:
			RBLeaf(RBNode * parent): parent(parent), color(black), left(nullptr), right(nullptr){};
		};
		RBNode * root;
		RBTree(const RBTree & other){};
	public:
		RBTree(): root(nullptr){};
		~RBTree()
		{
			delete root;
		}
	};
//};

#endif