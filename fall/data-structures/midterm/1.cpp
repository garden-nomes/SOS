/*
 * Midterm Problem 1
 * Noah Weiner
 *
 * Write a function to reverse a list using the linked list implementation. Your algoritm should
 * not allocate any additional space to store the list (ie you should not use malloc or new.) Do
 * this in 2 ways: one as a "member" function and one as a "non-member" function. In the non-member
 * version you can only use the interface functions specified in the template for list.
 *
 * Both functions are O(n) and require constant space.
 */

/*
 * List.h from the syllabus
 */

#include <iostream>
#include <cstdlib>
using namespace std;

template <typename Object>
class List {
   private:
	struct Node {
		/* See Figure 3.13 */
        Object  data;
        Node   *prev;
        Node   *next;

        Node( const Object & d = Object( ), Node *p = NULL, Node *n = NULL )
          : data( d ), prev( p ), next( n ) { }
	};

   public:
	class const_iterator {
      public:
        const_iterator( ) : current( NULL )
          { }

        const Object & operator* ( ) const
          { return this->retrieve( ); }
            
        const_iterator & operator++ ( )
        {
            current = current->next;
            return *this;
        }
    
        const_iterator operator++ ( int )
        {
            const_iterator old = *this;
            ++( *this );
            return old;
        }

		/*
		 * -- operators added
		 */
		const_iterator & operator-- ( )
        {
            current = current->prev;
            return *this;
        }
    
        const_iterator operator-- ( int )
        {
            const_iterator old = *this;
            --( *this );
            return old;
        }
    
        bool operator== ( const const_iterator & rhs ) const
          { return current == rhs.current; }
        bool operator!= ( const const_iterator & rhs ) const
          { return !( *this == rhs ); }
    
      protected:
        Node *current;
    
        Object & retrieve( ) const
          { return current->data; }
    
        const_iterator( Node *p ) : current( p )
          { }
            
        friend class List<Object>;
	};

	class iterator : public const_iterator {

      public:
        iterator( )
          { }
    
        Object & operator* ( )
          { return this->retrieve( ); }

        const Object & operator* ( ) const
          { return const_iterator::operator*( ); }
            
        iterator & operator++ ( )
        {
            this->current = this->current->next;
            return *this;
        }
    
        iterator operator++ ( int )
        {
            iterator old = *this;
            ++( *this );
            return old;
        }
		
		iterator & operator-- ( )
        {
            this->current = this->current->prev;
            return *this;
        }
    
        iterator operator-- ( int )
        {
            iterator old = *this;
            --( *this );
            return old;
        }
    
      protected:
        iterator( Node *p ) : const_iterator( p )
          { }
    
        friend class List<Object>;
    };

   public:
	List() { init( ); }
    
    ~List( )
    {
        clear( );
        delete head;
        delete tail;
    }
    
    List( const List & rhs )
    {
        init( );
        *this = rhs;
    }
    
    const List & operator= ( const List & rhs )
    {
        if( this == &rhs )
            return *this;
        clear( );
        for( const_iterator itr = rhs.begin( ); itr != rhs.end( ); ++itr )
            push_back( *itr );
        return *this;
    }
    
    void init( )
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
	}

	iterator begin() {
		return iterator( head->next);
	}

	const_iterator begin() const {
		return const_iterator( head->next);
	}

	iterator end() {
		return iterator(tail);
	}

	const_iterator end() const {
		return const_iterator(tail);
	}

	int size() const {
		return theSize;
	}

	bool empty() const {
		return size() == 0;
	}

	void clear() {
		while (!empty())
			pop_front();
	}

		
    Object & front( )
      { return *begin( ); }
    const Object & front( ) const
      { return *begin( ); }
    Object & back( )
      { return *--end( ); }
    const Object & back( ) const
      { return *--end( ); }
    void push_front( const Object & x )
      { insert( begin( ), x ); }
    void push_back( const Object & x )
      { insert( end( ), x ); }
    void pop_front( )
      { erase( begin( ) ); }
    void pop_back( )
      { erase( --end( ) ); }

    iterator insert( iterator itr, const Object & x )
    {
        Node *p = itr.current;
        theSize++;
        return iterator( p->prev = p->prev->next = new Node( x, p->prev, p ) );
    }

    iterator erase( iterator itr )
    {
        Node *p = itr.current;
        iterator retVal( p->next );
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        theSize--;
 
        return retVal;
    }
 
    iterator erase( iterator from, iterator to )
    {
        for( iterator itr = from; itr != to; )
            itr = erase( itr );
 
        return to;
    }

/*
 * Additional function needed for non-member reverse
 */

	void swap(iterator& a, iterator& b) {
		Object data = a.current->data;
		a.current->data = b.current->data;
		b.current->data = data;
	}

/*
 * Member reverse function
 */

	void reverse() {
		Node* n = head;
		Node* tmp;

		while (n != NULL) {
			tmp = n->next;	
			n->next = n->prev;
			n->prev = tmp;

			n = n->prev;
		}

		tmp = head;
		head = tail;
		tail = tmp;
	}

  private:
    int   theSize;
    Node *head;
    Node *tail;

/* This should either be private or public but not both. 
    void init( )
      { }
*/
};

/*
 * Non-member reverse function
 */
template <typename Object>
void reverse(List<Object>& list) {
	auto a = list.begin();
	auto b = list.end();

	while (a != b && a != b--) {
		list.swap(a, b);
		a++;
	}
}


/*
 * Test functions
 */

int main(int argc, char** argv) {
	List<int> list;
	for (int i = 1; i <= 10; i++)
		list.push_back(i);

	for (auto i = list.begin(); i != list.end(); i++)
		cout << *i << " ";
	cout << endl;

	list.reverse();

	for (auto i = list.begin(); i != list.end(); i++)
		cout << *i << " ";
	cout << endl;

	reverse(list);

	for (auto i = list.begin(); i != list.end(); i++)
		cout << *i << " ";
	cout << endl;
	
	return 0;
}
