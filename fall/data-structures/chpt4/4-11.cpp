/*
 * Problem 4-11
 * Noah Weiner
 *
 * Write an implementation of the set class.
 */

#include <iostream>
#include <cstdlib>
#include <utility>
using namespace std;

/*
 * Based on the BinarySearchTree from the book
 *
 * Modifications:
 * add parent pointer to node
 * internal insert function
 * made a second insert function
 */
template<typename Comparable>
class Set
{
  private:
	struct BinaryNode
    {
       Comparable element;
       BinaryNode *left;
       BinaryNode *right;
	   BinaryNode *parent;

       BinaryNode( const Comparable & theElement, BinaryNode *lt,
			   BinaryNode *rt, BinaryNode* pt )
         : element( theElement ), left( lt ), right( rt ), parent( pt ) { }
    };

  public:
    Set( ) : root(NULL) { 
    }

    Set( const Set & rhs ) : root(NULL) {
		makeEmpty();

		*this = rhs;
    }

    /**
     * Destructor for the tree
     */
    ~Set( )
    {
        makeEmpty( );
    }

	/*
	 * iterator subclass added for Set
	 */
	class iterator {
		public:
			iterator(BinaryNode* n) : b(n) { }
			iterator(const iterator & i) : b(i.b) { }

			iterator & operator++() { b = next(b); }
			iterator operator++(int) {
				iterator tmp = *this;
				operator++();
				return tmp;
			}
			bool operator==(const iterator & rhs) { return rhs.b == b; }
			bool operator!=(const iterator & rhs) { return rhs.b != b; }
			Comparable & operator*() { return b->element; }

		private:
			BinaryNode* b;

			BinaryNode* next(BinaryNode* n) {
				if (n == NULL)
					return NULL;
				else if (n->right == NULL)
					return next(n->parent);
				else
					return findMin(n->right);
			}

			BinaryNode* findMin(BinaryNode* n) {
				if (n->left == NULL)
					return n;
				else
					return findMin(n->left);
			}
	};

	iterator begin() { return iterator(findMin(root)); }
	iterator end() { return iterator(NULL); }

    const Comparable & findMin( ) const {
		return findMin(root)->element;
    }

    const Comparable & findMax( ) const {
		return findMax(root)->element;
    }

    iterator find( const Comparable & x ) const {
		return find(x, root);
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

    pair<bool, iterator> insert( const Comparable & x ) {
		cout << "Entering insert" << endl;
		return insert(x, root);
		cout << "Exiting insert" << endl;
    }
	
	pair<bool, iterator> insert( const iterator & i, const Comparable & x) {
		return insert(x, i);
	}	

	int erase( const Comparable & x ) { return remove(x, root);	}
	iterator erase( iterator itr ) { return remove(*itr, itr.b); }
	iterator erase( iterator start, iterator end) {
		for (; start != end; start++)
			remove(start);
	}

    /**
     * Deep copy.
     */
    const Set & operator=( const Set & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            root = clone( rhs.root );
        }
        return *this;
    }
    
		
  private:
    

    BinaryNode *root;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     * (SJS) Note that this is not a const method
	 *
	 * Modified for Set
     */
    pair<bool, iterator> insert( const Comparable & x, BinaryNode * & t )
    {

        if( x < t->element ) {
			if (t->left == NULL) {
				t->left = new BinaryNode( x, NULL, NULL, t );
				return pair<bool, iterator>(true, iterator(t->left));
			} else
				insert( x, t->left );
		} else if( t->element < x ) {
			if (t->right == NULL) {
				t->right = new BinaryNode( x, NULL, NULL, t );
				return pair<bool, iterator>(true, iterator(t->right));
			} else
				insert( x, t->right );
		} else
			return pair<bool, iterator>(false, iterator(t));
    }

	/*
	 * Added for set
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     * (SJS) Note this is not a const method
     * Book notes this is inefficient because of two
     * passes. Think about how you would correct this.
     */
    int remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == NULL )
            return 0;   // Item not found; do nothing
        if( x < t->element )
            return remove( x, t->left );
        else if( t->element < x )
            return remove( x, t->right );
        else if( t->left != NULL && t->right != NULL ) // Two children
        {
            t->element = findMin( t->right )->element;
            return remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != NULL ) ? t->left : t->right;
            delete oldNode;
			return 1;
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
    iterator find( const Comparable & x, BinaryNode *t ) const
    {
        if( t == NULL )
            return iterator(NULL);
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return iterator(t);    // Match
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

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == NULL )
            return NULL;
 
        return new BinaryNode( t->element, clone( t->left ), clone( t->right ) );
    }
};

int main(int argc, char** argv) {
	Set<int> set;
	for (int i = 1; i <= 10; i++)
		set.insert(i);

	set.printTree();
	auto ret = set.insert(5);
	cout << "Insert 5: " << (ret.first ? "true" : "false") << endl;
	ret = set.insert(15);
	cout << "Insert 15: " << (ret.first ? "true" : "false") << endl;
	auto itr = set.begin();
	for (; itr != set.end(); itr++)
		cout << *itr << " ";
	cout << endl;

	return 0;
}

