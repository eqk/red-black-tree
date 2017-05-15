#ifndef MY_SET_H
#define MY_SET_H

//#define nullptr 0

#include <iterator>

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
			friend class RBTree;
			static const bool red = true;
			static const bool black = false;
			RBNode(RBNode * parent, T data = T(), bool color = red, RBNode * left = nullptr, RBNode * right = nullptr):
			parent(parent), data(data), color(color), left(left), right(right){};
			~RBNode()
			{
			if (left)
				delete left;
			if (right)
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
			RBNode * uncle()
			{
				RBNode * g = grandparent();
				if (!g)
				{
					return nullptr;
				}
				if (parent == g->left)
				{
					g->right;
				}
				else
				{
					return g->left;
				}
			}
			bool is_leaf() const { return color == black && left == nullptr && right == nullptr; }
		};
		class RBLeaf : public RBNode
		{
		public:
			RBLeaf(RBNode * parent) : RBNode(parent, T(), black, nullptr, nullptr){}
		};
		class RBTIterator : public std::iterator<std::bidirectional_iterator_tag, T>
		{
			friend class RBNode;
			RBNode * p;
		public:
			RBTIterator(RBNode * p) : p(p) {};
			RBTIterator(const RBTIterator & other) : p(other.p) {};
			bool operator!=(const RBTIterator & other) const
			{
				return p != other.p;
			}
			bool operator==(const RBTIterator & other) const
			{
				return p == other.p;
			}
			RBTIterator & operator++()
			{

			}
			RBTIterator & operator--()
			{

			}
			T & operator*()
			{
				return p->data;
			}
		};
		friend class RBNode;
		RBNode * root;
		RBTree(const RBTree & other){};
		void rotate_left(RBNode * n)
		{
			RBNode * pivot = n->right;
			pivot->parent = n->parent;
			if (n->parent != nullptr)
			{
				if (n->parent->left == n)
					n->parent->left = pivot;
				else
					n->parent->right = pivot;
			}
			n->right = pivot->left;
			if (pivot->left != nullptr)
				pivot->left->parent = n;
			n->parent = pivot;
			pivot->left = n;
		}
		void rotate_right(RBNode * n)
		{
			RBNode * pivot = n->left;
			pivot->parent = n->parent;
			if (n->parent != nullptr)
			{
				if (n->parent->left == n)
					n->parent->left = pivot;
				else
					n->parent->right = pivot;
			}
			n->left = pivot->right;
			if (pivot->right != nullptr)
				pivot->right->parent = n;

			n->parent = pivot;
			pivot->right = n;
		}
		void push_(RBNode * & r, T & x, RBNode * par = nullptr)
		{
			if (!r || r->is_leaf())
			{
				r = new RBNode(par, x, RBNode::red);
			}
			else if (x < r->data)
			{
				push_(r->left, x, r->parent);
			}
			else
			{
				push_(r->right, x, r->parent);
			}
			r->left = new RBLeaf(r);
			r->right = new RBLeaf(r);
			insert_case1(r);
		}
		void insert_case1(RBNode * n) // добавленный узел - корень
		{
			if (n->parent == nullptr)
				n->color = RBNode::black;
			else
				insert_case2(n);
		}
		void insert_case2(RBNode * n)
		{
			if (n->parent->color == RBNode::black)
				return;
			else
				insert_case3(n);
		}
		void insert_case3(RBNode * n)
		{
			RBNode * u = n->grandparent(), * g;

			if ((u != nullptr) && (u->color == RBNode::red) && (n->parent->color == RBNode::red)) {
				n->parent->color = RBNode::black;
				u->color = RBNode::black;
				g = n->grandparent();
				g->color = RBNode::red;
				insert_case1(g);
			}
			else {
				insert_case4(n);
			}
		}
		void insert_case4(RBNode * n)
		{
			RBNode * g = n->grandparent();

			if ((n == n->parent->right) && (n->parent == g->left)) {
				rotate_left(n->parent);
				n = n->left;
			}
			else if ((n == n->parent->left) && (n->parent == g->right)) {
				rotate_right(n->parent);
				n = n->right;
			}
			insert_case5(n);
		}
		void insert_case5(RBNode * n)
		{
			RBNode * g = n->grandparent();
			n->parent->color = RBNode::black;
			g->color = RBNode::red;
			if ((n == n->parent->left) && (n->parent == g->left)) {
				rotate_right(g);
			}
			else {
				rotate_left(g);
			}
		}

		int _size = 0;
		RBNode * left()
		{
			RBNode * p = root;
			while (p->left && !p->left->is_leaf()) {
				p = p->left;
			}
			return p;
		}
		RBNode * right()
		{
			RBNode * p = root;
			while (p->right && !p->right->is_leaf()) {
				p = p->right;
			}
			return p;
		}
	public:
		typedef RBTIterator iterator;
		iterator begin()
		{
			return RBTIterator(left());
		}
		iterator end()
		{
			return RBTIterator(right());
		}
		RBTree(): root(nullptr){};
		~RBTree()
		{
			delete root;
		}
		bool empty() const { return root == nullptr;	}
		void insert(T x) //TODO: return iter
		{
			push_(root, x);
			++_size;
		}
		int size() const
		{
			return _size;
		}
	};
//};

#endif