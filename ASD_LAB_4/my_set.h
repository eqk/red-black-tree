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
			friend class RBTree;
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
		class RBLeaf : private RBNode
		{
		public:
			RBLeaf(RBNode * parent) : RBNode(parent, T(), black, nullptr, nullptr){}
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
			struct node * pivot = n->left;
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
			if (r->parent == nullptr) // добавленный - корень
			{
				r->color = RBNode::black;
				return;
			}
			if (n->parent->color == RBNode::black) // предок добавленного - черный, всё норм
			{
				return;
			}
			
		}
	public:
		RBTree(): root(nullptr){};
		~RBTree()
		{
			delete root;
		}
		bool empty() const { return root == nullptr;	}
		void insert(T x) //TODO: return iter
		{

		}
	};
//};

#endif