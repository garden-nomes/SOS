/*
 * Lab 8
 * This is the same indexed BST as Lab 5, since the ideal data structure for this lab
 * is an indexed BST.
 *
 * Find is O(logN), and accessing the k'th element is O(logN), it doesn't use the extra
 * space of maintaining a separate list, and it doesn't require the O(n) sequential indexing
 * of a threaded BST.
 * 
 * Noah Weiner
 * March 8, 2016
 */

#include <iostream>
#include <cstdlib>
using namespace std;

template <typename Comparable>
class BinarySearchTree
{
  public:
	BinarySearchTree( ) : root(NULL) { 
	}

	BinarySearchTree( const BinarySearchTree & rhs ) : root(NULL) {
		makeEmpty();
		*this = rhs;
	}

	/**
	 * Destructor for the tree
	 */
	~BinarySearchTree( )
	{
		makeEmpty( );
	}

	const Comparable & findMin( ) const {
		return findMin(root)->element;
	}

	const Comparable & findMax( ) const {
		return findMax(root)->element;
	}

	bool contains( const Comparable & x ) const {
		return contains(x, root);
	}

	bool isEmpty( ) const {
		return root == NULL;
	}

	void printTree( ) const {
		printTree(root);
		cout << endl;
	} 

	void makeEmpty( ) {
		makeEmpty(root);
	}

	void insert( const Comparable & x ) {
		insert(x, root, 0);
	}

	void remove( const Comparable & x ) {
		remove(x, root);
	}

	int size() {
		return findMax( root )->index + 1;
	}

	const Comparable & operator[]( int index )
	{
		return findIndex( index, root );
	}

	/**
	 * Deep copy.
	 */
	const BinarySearchTree & operator=( const BinarySearchTree & rhs )
	{
		if( this != &rhs )
		{
			makeEmpty( );
			root = clone( rhs.root );
		}
		return *this;
	}
	

  private:
	struct BinaryNode
	{
		Comparable element;
		int index;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode( const Comparable & theElement, int theIndex, BinaryNode *lt,
			BinaryNode *rt )
			: element( theElement ), index( theIndex ), left( lt ), right( rt ) { }
	};

	BinaryNode *root;

	/**
	 * Increment a node's index and all sub-tree's indexes
	 */
	void incrementIndex( BinaryNode* t )
	{
		if( t != NULL ) {
			incrementIndex( t->left );
			incrementIndex( t->right );
			++t->index;
		}
	}

	/**
	 * Decrement a node's index and all sub-tree's indexes
	 */
	void decrementIndex( BinaryNode* t )
	{
		if( t != NULL ) {
			decrementIndex( t->left );
			decrementIndex( t->right );
			--t->index;
		}
	}

	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 * (SJS) Note that this is not a const method
	 * (NW) Added a parent parameter
	 */
	bool insert( const Comparable & x, BinaryNode * & t, int index )
	{

		if( t == NULL ) {
			t = new BinaryNode( x, index, NULL, NULL );
			return true;
		} else if( x < t->element ) {
			bool ret = insert( x, t->left, t->index );
			if( ret ) {	// don't increment indexes on
				++t->index;							// duplicate insert
				incrementIndex( t->right );
			}
			return ret;
		} else if( t->element < x )
			return insert( x, t->right,t->index + 1 );
		else
			return false;
	}

	/**
	 * Internal method to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 * (SJS) Note this is not a const method
	 * Book notes this is inefficient because of two
	 * passes. Think about how you would correct this.
	 * (NW) Modified to decrement indexes.
	 */
	bool remove( const Comparable & x, BinaryNode * & t )
	{
		if( t == NULL )
			return false;   // Item not found
		if( x < t->element ) {
			bool ret = remove( x, t->left );
			if( ret ) {	// decrement on successful deletion only
				--t->index;
				decrementIndex( t->right );
			}
			return ret;
		} else if( t->element < x )
			return remove( x, t->right );
		else if( t->left != NULL && t->right != NULL ) // Two children
		{
			t->element = findMin( t->right )->element;
			remove( t->element, t->right );
			return true;
		}
		else
		{
			BinaryNode *oldNode = t;
			t = ( t->left != NULL ) ? t->left : t->right;
			delete oldNode;
			return true;
		}
	}

	/**
	 * Internal method to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 */
	BinaryNode * findMin( BinaryNode *t ) const
	{
		if( t == NULL )
			return NULL;
		if( t->left == NULL )
			return t;
		return findMin( t->left );
	}

	/**
	 * Internal method to find the largest item in a subtree t.
	 * Return node containing the largest item.
	 */
	BinaryNode * findMax( BinaryNode *t ) const
	{
		if( t != NULL )
			while( t->right != NULL )
				t = t->right;
		return t;
	}

	/**
	 * Internal method to test if an item is in a subtree.
	 * x is item to search for.
	 * t is the node that roots the subtree.
	 */
	bool contains( const Comparable & x, BinaryNode *t ) const
	{
		if( t == NULL )
			return false;
		else if( x < t->element )
			return contains( x, t->left );
		else if( t->element < x )
			return contains( x, t->right );
		else
			return true;	// Match
	}

	/**
	 * Internal method to make subtree empty.
	 */
	void makeEmpty( BinaryNode * & t )
	{
		if( t != NULL )
		{
			makeEmpty( t->left );
			makeEmpty( t->right );
			delete t;
		}
		t = NULL;
	}

	void printTree( BinaryNode *t ) const {
		// do an in-order traversal
		if (t == NULL)
			return;
		else {
			printTree(t->left);
			cout << t->element << ", ";
			printTree(t->right);
		}
	} 

	const Comparable & findIndex( int index, const BinaryNode * t ) {
		if( t == NULL )
			throw out_of_range("BST index is out of range!");
		else if( index < t->index )
			return findIndex( index, t->left );
		else if( t->index < index )
			return findIndex( index, t->right );
		else
			return t->element;
	}

	/**
	 * Internal method to clone subtree.
	 */
	BinaryNode * clone( BinaryNode *t ) const
	{
		if( t == NULL )
			return NULL;
 
		return new BinaryNode( t->element, t->index, clone( t->left ), clone( t->right ) );
	}
};

int main() {
	BinarySearchTree<int> t1;
	t1.insert(11);
	t1.insert(5);
	t1.insert(3);
	t1.insert(6);
	cout << "Finding!" << endl;
	cout << "t1.findMin(): " << t1.findMin() << endl;
	cout << "t1.findMax(): " << t1.findMax() << endl;
	cout << "t1: ";
	for( int i = 0; i < t1.size(); i++ )
		cout << t1[i] << " ";
	cout << endl;
	t1.insert(6);
	t1.remove(6);
	if (t1.contains(6))
		cout << "Tree contains 6" << endl;
	else
		cout << "Tree does not contain 6" << endl;
	cout << "t1: ";
	for( int i = 0; i < t1.size(); i++ )
		cout << t1[i] << " ";
	cout << endl;

	t1.printTree();
	cout << endl;

	BinarySearchTree<int> t2(t1);
	t2.printTree();

	cout << "accessing t1[8], should throw out_of_range exception..." << endl;
	try {
		cout << t1[8] << endl;
	} catch( const out_of_range & e ) {
		cout << "Yup!" << endl;
	}
}