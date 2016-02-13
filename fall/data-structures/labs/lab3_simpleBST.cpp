/*
 * Little BST
 * 12/3/15
 * Noah Weiner
 */

#include <iostream>
#include <list>
#include <stack>
#include <queue>
using namespace std;

template<typename Comparable>
class BST {
	private:
		struct node {
			Comparable value;
			node* left; node* right;
			node(Comparable element, node* leftChild = NULL,
					node* rightChild = NULL)
				: value(element), left(leftChild), right(rightChild) { }
		};
		node* root;

	public:
		BST(node* tree = NULL) {
			root = tree;
		}

		bool empty() {
			return root == NULL;
		}

		void insert(const Comparable& value) {
			node* n = root;
			
			if (root == NULL)
				root = new node(value);
			else {
				while (true) {
					if (value < n->value) {	
						if (n->left == NULL) {
							n->left = new node(value);
							break;
						} else {
							n = n->left;
						}
					} else if (n->value < value) {
						if (n->right == NULL) {
							n->right = new node(value);
							break;
						} else {
							n = n->right;
						}
					} else {
						break;
					}
				}

			}
		}

		bool find(const Comparable& value) const {
			node* n = root;
			while (n != NULL) {
				if (value < n->value)
					n = n->left;
				else if (n->value < value)
					n = n->right;
				else
					return true;
			}

			return false;
		}

		Comparable findMin() const {
			node* n = root;
			if (n == NULL)
				return Comparable();

			while (n->left != NULL)	
				n = n->left;
			return n->value;
		}

		Comparable findMax() const {
			node* n = root;
			if (n == NULL)
				return Comparable();

			while (n->right != NULL)	
				n = n->right;
			return n->value;
		}

		list<Comparable> inOrder() const {
			list<Comparable> ret;
			stack<node*> nodes;
			node* n = root;

			while (!(nodes.empty() && n == NULL)) {
				if (n == NULL) {
					n = nodes.top(); nodes.pop();
					ret.push_back(n->value);
					n = n->right;
				} else {
					nodes.push(n);
					n = n->left;
				}
			}

			return ret;
		}

		void remove(const Comparable& value) {
			node** n = &root;

			while (true) {
				if (*n == NULL)
					break;
				else if (value < (*n)->value) {
					n = &((*n)->left);
				} else if ((*n)->value < value) {
					n = &((*n)->right);
				} else {
					if ((*n)->left != NULL && (*n)->right != NULL) {
						node** min = &((*n)->right);
						while ((*min)->left != NULL) {
							min = &((*min)->left);
						}

						(*n)->value = (*min)->value;
						node* doomed = *min;
						*min = (*min)->right;
						delete doomed;
					} else {
						node* doomed = *n;
						*n = ((*n)->left != NULL) ? (*n)->left : (*n)->right;
						delete doomed;
					}
				}
			}
		}

		int height() const {
			if (root == NULL)
				return 0;

			queue<node*> nodes;
			int height = 0;
			nodes.push(root);

			while (!nodes.empty()) {
				height++;
				node* n;
				for (int i = nodes.size(); i > 0; i--) {
					n = nodes.front();
					nodes.pop();
					if (n->left != NULL)
						nodes.push(n->left);
					if (n->right != NULL)
						nodes.push(n->right);
				}
			}

			return --height;
		}

		class const_iterator {
			public:
				const_iterator(node* n, node* root) : current(n) {
					if (root != NULL) {
						while (root != current) {
							path.push(root);
							if (current->value < root->value)
								root = root->left;
							else if (root->value < current->value)
								root = root->right;
						}
					}
				}

				const_iterator & operator++() {
					current = current->right;
					while (current != NULL) {
						path.push(current);
						current = current->left;
					}
					
					if (!(path.empty() && current == NULL)) {
						current = path.top();
						path.pop();
					} else
						current = NULL;
				}

				const_iterator operator++(int) {
					const_iterator old = *this;
					++(*this);
					return old;
				}

				const Comparable & operator*() const {
					return current->value;
				}

				bool operator==(const const_iterator & rhs) const {
					return current == rhs.current;
				}

				bool operator!=(const const_iterator & rhs) const {
					return current != rhs.current;
				}

			protected:
				node* current;
				stack<node*> path;
		};

		const_iterator begin() {
			node* n = root;
			while (n->left != NULL)
				n = n->left;
			return const_iterator(n, root);
		}

		const_iterator end() {
			return const_iterator(NULL, NULL);
		}
};

int main(int argc, char** argv) {
	// create BST
	BST<int> bst;
	cout << "bst is " << (bst.empty() ? "empty" : "not empty") << endl << endl;
	
	// test insert
	cout << "inserting elements 5, 3, 7, 4, 10, 9, 6" << endl;
	bst.insert(5); bst.insert(3); bst.insert(7); bst.insert(4);
	bst.insert(10); bst.insert(9); bst.insert(6);
	cout << "bst is " << (bst.empty() ? "empty" : "not empty") << endl << endl;

	// test find
	cout << "tree " << (bst.find(3) ? "contains" : "does not contain")
		<< " 3" << endl;
	cout << "tree " << (bst.find(4) ? "contains" : "does not contain")
		<< " 4" << endl;
	cout << "tree " << (bst.find(2) ? "contains" : "does not contain")
		<< " 2" << endl << endl;

	// test findMin and findMax
	cout << "min is " << bst.findMin() << ", max is " << bst.findMax()
		<< endl << endl;

	// test inOrder
	cout << "inOrder traversal: ";
	list<int> inOrder = bst.inOrder();
	for (auto itr = inOrder.begin(); itr != inOrder.end(); ++itr)
		cout << *itr << " ";
	cout << endl << endl;

	// test iterator
	cout << "Iterator traversal: ";
	for (auto itr = bst.begin(); itr != bst.end(); ++itr)
		cout << *itr << " ";
	cout << endl << endl;

	// test height
	cout << "Tree height: " << bst.height() << endl << endl;

	// delete elements
	cout << "Delete 5: ";
	bst.remove(5);
	for (auto itr = bst.begin(); itr != bst.end(); ++itr)
		cout << *itr << " ";
	cout << endl;

	cout << "Delete 3: ";
	bst.remove(3);
	for (auto itr = bst.begin(); itr != bst.end(); ++itr)
		cout << *itr << " ";
	cout << endl << endl;

	return 0;
}
