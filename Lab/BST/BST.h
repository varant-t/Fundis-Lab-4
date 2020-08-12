#ifndef BST_H
#define BST_H

#include <iostream>
#include <queue>
#include <list>

using namespace std;

template <class Key, class Value>
class BST
{
	public:
		//Node
		//Contains: Key, Value, Left Link, Right Link
		class Node
		{
			friend class BST;

			private:

				Key key;
				Value value;
				Node *left, *right;

				Node(const Key& key, const Value& value) : key(key), value(value), left(NULL), right(NULL)
				{ }

				~Node()
				{
					// delete children
					if(left)
					{
						delete left;
						left = NULL;
					}
					if(right)
					{
						delete right;
						right = NULL;
					}
				}

			public:

				const Key& getKey() const
				{
					return key;
				}

				const Value& getValue() const
				{
					return value;
				}

				Value& getValue()
				{
					return value;
				}
		};

		//Constructor initializes root to NULL
		BST() : root(NULL)
		{ }

		//Destructor removes all node in tree
		~BST()
		{
			clear();
		}

		//Delete all node in tree
		void clear()
		{
			delete root;
			
			root = NULL;
		}

		//Insert calls private helper member function
		void insert(const Key &key, const Value &value)
		{
			insert(root, new Node(key, value));
		}

		//Find call private helper member function
		Node* find(const Key &key)
		{
			return find(key, root);
		}

		//Remove is recursive
		void remove(const Key &key)
		{
			//Search for the node to remove
			Node *node = find(key);
			//Search for the parent of the node to remove
			Node *parent = predecessor(key);

			//If the root node is being removed
			//Assign root to the new subtree
			if(node == parent)
			{
				remove(node);
				root = node;
			}
			else
			{
				//Remove the branch or leaf
				remove(node);

				//If the node is a subtree
				if(node)
				{	
					//Check if subtree is to the left or right
					//Link parent to the subtree
					if(node->key < parent->key)
						parent->left = node;
					else if(node->key > parent->key)
						parent->right = node;
				}
				//Check if node is NULL
				//Link parent to NULL
				else
				{
					if(parent->left)
						parent->left = node;
					else
						parent->right = node;
				}
			}
		}

		//Remove is non-recursive
		/*void remove(const Key &key)
		{
			//If tree is empty return NULL
			if(root == NULL)
				return;

			//Node tracks item for removal
			//Parent is the predecessor of node
			Node *parent = root;
			Node *node = root;

			//Determine whether left or right branch
			bool isLeftNode = false;

			//Node traverses tree until finds key
			//Parent remains one level ahead
			while(node->key != key)
			{
				parent = node;

				if(key < node->key)
				{
					 node = node->left;
					 isLeftNode = true;
				}
				else
				{
					node = node->right;
					isLeftNode = false;
				}

				//If node not found exit
				if(node == NULL)
					return;
			}

			//If node ia a leaf
			if(node->left == NULL && node->right == NULL)
			{
				//If deleting root not set to NULL
				if(node == root)
					root = NULL;
				//If deleting parent left node set to left link to NULL
				else if(isLeftNode == true)
					parent->left = NULL;
				//If deleting parent right node set to left link to NULL
				else
					parent->right = NULL;
			}

			//If node is a right branch
			else if(node->left == NULL)
			{
				//Move right branch to root
				if(node == root)
					root = node->right;
				//Move right node to parent
				else if(isLeftNode == true)
					parent->left = node->right;
				//Move left node to parent
				else
					parent->right = node->right;
			}

			//If node is a left branch
			else if(node->right == NULL)
			{
				//Move left branch to root
				if(node == root)
					root = node->left;
				//Move left node to parent
				else if(isLeftNode == true)
					parent->left = node->left;
				//Move right node to parent
				else
					parent->right = node->left;
			}

			//Determine leftmost node of right branch
			else
			{
				//Set to right branch
				Node *tempNode = node->right;
				Node *successor = node;
				Node *successorParent = node;

				//Iterate through node until leftmost node is found
				while(tempNode != NULL)
				{
					successorParent = successor;
					successor = tempNode;
					tempNode = tempNode->left;
				}

				//Move leftmost node to successor
				if(successor != node->right)
				{
					successorParent->left = successor->right;
					successor->right = node->right;
				}

				if(node == root)
					root = successor;
				else if(isLeftNode)
				{
					node = parent->left;
					parent->left = successor;
				}
				else
				{
					node = parent->right;
					parent->right = successor;
				}

				successor->left = node->left;
			}

			//Prepare node for deletion
			node->left = NULL;
			node->right = NULL;
			delete node;
		}*/

		//Predecessor call private helper member function
		Node* predecessor(const Key &key)
		{
			return predecessor(root, find(key, root));
		}

		//Redifine functor name
		typedef void (*VisitFunction)(Value&);

		//In Order traversal call private helper member function
		void traverseInOrder(VisitFunction f)
		{
			visitInOrder(root, f);
		}

		//Pre Order traversal call private helper member function
		void traversePreOrder(VisitFunction f)
		{
			visitPreOrder(root, f);
		}

		//Post Order traversal call private helper member function
		void traversePostOrder(VisitFunction f)
		{
			visitPostOrder(root, f);
		}

		//Level Order traversal call private helper member function
		void traverseLevelOrder(VisitFunction f)
		{
			visitLevelOrder(root, f);
		}

	private:

		//Root node
		Node *root;

		//Insert recursively
		void insert(Node *&treeNode, Node *newNode)
		{
			//Insert if leaf found 
			if(treeNode == NULL)
				treeNode = newNode;
			//Recurse to left
			else if(newNode->key < treeNode->key)
				insert(treeNode->left, newNode);
			//Recurse to right
			else
				insert(treeNode->right, newNode);
		}

		//Search recursively
		Node* find(const Key &key, Node *node)
		{
			//If key found return node
			//If key is not found return NULL
			if(node == NULL || node->key == key)
				return node;
			//Recurse to left
			else if(key < node->key)
				return find(key, node->left);
			//Recurse to right
			else if(key > node->key)
				return find(key, node->right);
		}

		//Find predecessor recursively
		Node* predecessor(Node *parent, Node *node)
		{
			//Return NULL if no predecessor
			if(node == NULL)
				return NULL;
			//Return parent of node
			else if(parent->key == node->key)
				return node;
			//Return leaf node
			else if(parent->left == node || parent->right == node)
				return parent;
			//Recurse to left
			else if(node->key < parent->key)
				return predecessor(parent->left, node);
			//Recurse to right
			else
				return predecessor(parent->right, node);
		}

		//Remove is recursive
		void remove(Node *& node) 
		{
			//If node is a leaf
			//Delete and set to NULL
			if(node->left == NULL && node->right == NULL)
			{
				Node *temp = node;
				delete temp;
				node = NULL;
			}
			//If node is a right branch
			//Delete node and return right subtree
			else if (node->left == NULL) 
			{ 
				Node *temp = node;
				Node *child = node->right;

				temp->left = NULL;
				temp->right = NULL;
				
				delete temp;
				temp = NULL;

				node = child;
			} 
			//If node is a left branch
			//Delete node and return left subtree
			else if (node->right == NULL) 
			{
				Node *temp = node;
				Node *child = node->left;

				temp->left = NULL;
				temp->right = NULL;

				delete temp;
				temp = NULL;

				node = child;
			} 
			//If node is a tree
			//Copy leftmost child of right subtree and delete node recursively 
			else 
			{
				// In-order predecessor (leftmost child of right subtree) 
				// Node has two children - get max of right subtree
				Node **temp = &node->right; // get right node of the original node

				// find the lefttmost child of the subtree of the right node
				while ((*temp)->left != NULL) 
					temp = &(*temp)->left;

				// copy the contents from the in-order predecessor to the original node
				node->key = (*temp)->key;
				node->value = (*temp)->value;

				// then delete the predecessor
				remove(*temp);
			}
		}

		//Traverse in order and use functor
		void visitInOrder(Node *node, VisitFunction f)
		{
			//If empty tree return NULL
			if (node == NULL)
				return;

			//Visit left
			visitInOrder(node->left, f);

			//Return
			f(node->value);

			//Visit right
			visitInOrder(node->right, f);
		}

		//Traverse pre order and use functor
		void visitPreOrder(Node *node, VisitFunction f)
		{
			//If empty tree return NULL
			if (node == NULL)
				return;

	
			//Return
			f(node->value);

			//Visit left
			visitPreOrder(node->left, f);

			//Visit right
			visitPreOrder(node->right, f);
		}

		//Traverse post order and use functor
		void visitPostOrder(Node *node, VisitFunction f)
		{
			//If empty tree return NULL
			if (node == NULL)
				return;

			//Visit left
			visitPostOrder(node->left, f);

			//Visit right
			visitPostOrder(node->right, f);

			//Return
			f(node->value);
		}

		//Traverse level order and use functor
		void visitLevelOrder(Node *node, VisitFunction f)
		{   
			//Declare queue of nodes
			queue<Node*> nodes;
			nodes.push(node);
				//Purpose: store node sequence

				//Declare current node to keep track of the node position
				Node* current = nodes.front();
				nodes.pop();
				

			//Iterate until the current node is NULL
				while (current != NULL)
				{ 
					//Call functor
					f(current->getValue());

					//Check if left branch exists and visit it
					if (current->left != NULL)
					{
					//Enqueue node from the left branch
						nodes.push(current->left);
					}

					//Check if right branch exists and visit it
					if (current->right != NULL)
					{
					//Enqueue node from the right branch
						nodes.push(current->right);
					}
					
					//Check if queue is not empty
					if (nodes.empty())
					{ 
						current = NULL;
					
					}
					//Else, you are at end of queue.  Set current node to NULL
					else
					{
						//Get head of queue and make it current node
						current = nodes.front();
						//Dequeue
						nodes.pop();	
					}
				}
		}
};

#endif