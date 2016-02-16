/* 
 * Lab 5: Heap implementation
 * Noah Weiner
 */

#include <vector>
#include <exception>
using namespace std;

struct UnderflowException : public exception {
	const char* what() const throw() {
		return "Empty heap";
	}
};

template <typename Comparable>
class BinaryHeap
{
public:
	explicit BinaryHeap( int capacity = 100 );
	explicit BinaryHeap( const vector<Comparable> & items );

	bool isEmpty( ) const;
	const Comparable & findMin( ) const;

	void insert( const Comparable & x );
	void deleteMin( );
	void deleteMin( Comparable & minItem );
	void makeEmpty( );

private:
	int				currentSize;  // Number of elements in heap
	vector<Comparable> array;		// The heap array

	void buildHeap( );
	void percolateDown( int hole );
};

template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap( int capacity ) : array( capacity ), currentSize( 0 )
{ }

template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap( const vector<Comparable> & items ) :
	array( items.size() + 10 ), currentSize( items.size() )
{
	for (int i = 0; i < items.size(); i++)
		array[ i + 1 ] = items [ i ];
	buildHeap();
}

template <typename Comparable>
bool BinaryHeap<Comparable>::isEmpty() const
{ return currentSize == 0; }

template <typename Comparable>
void BinaryHeap<Comparable>::insert( const Comparable & x )
{
	if( currentSize == array.size( ) - 1 )
		array.resize( array.size( ) * 2 );

	// Percolate up
	int hole = ++currentSize;
	for( ; hole > 1 && x < array[ hole / 2 ]; hole /= 2 )
		array[ hole ] = array[ hole / 2 ];
	array[ hole ] = x;
}

template <typename Comparable>
const Comparable & BinaryHeap<Comparable>::findMin() const
{
	return array[ 1 ];
}

template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin()
{
	if( isEmpty( ) )
		throw UnderflowException( );

	array[ 1 ] = array[ currentSize-- ];
	percolateDown( 1 );
}

template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin( Comparable & minItem )
{
	if( isEmpty( ) )
		throw UnderflowException( );

	minItem = array[ 1 ];
	array[ 1 ] = array[ currentSize-- ];
	percolateDown( 1 );
}

template <typename Comparable>
void BinaryHeap<Comparable>::makeEmpty()
{
	array = vector<Comparable>( currentSize );
	currentSize = 0;
}

template <typename Comparable>
void BinaryHeap<Comparable>::buildHeap()
{
	for( int i = currentSize / 2; i > 0; --i )
		percolateDown( i );
}

template <typename Comparable>
void BinaryHeap<Comparable>::percolateDown( int hole )
{
	int child;
	Comparable tmp = array[ hole ];

	for( ; hole * 2 <= currentSize; hole = child )
	{
		child = hole * 2;
		if( child != currentSize && array[ child + 1 ] < array[ child ] )
			child++;
		if( array[ child ] < tmp )
			array[ hole ] = array[ child ];
		else
			break;
	}
	array[ hole ] = tmp;
}

#include <iostream>
#include <cstdlib>
int main( int argc, char* argv[] ) {
	vector<int> items( 10 );
	BinaryHeap<int> heap( 10 );
	for( int i = 0; i < 4; ++i ) {
		/* insert and delete a bunch of random numbers */
		vector<int> items( 10 );
		for( int j = 0; j < 10; ++j )
			items[j] = rand() % 100;

		cout << "Vector: [" << items[ 0 ];
		for (auto itr = ++items.begin(); itr != items.end(); ++itr) {
			cout << ", " << *itr;
			if( i > 1 )
				heap.insert( *itr );
		}
		cout << "]" << endl;

		if( i < 2 )
			heap = BinaryHeap<int>( items );

		const char* method = i < 2 ? "insert" : "buildheap";
		cout << "Heapsort (" << method << " method): [" << heap.findMin();
		heap.deleteMin();
		while( !heap.isEmpty() ) {
			cout << ", " << heap.findMin();
			heap.deleteMin();
		}
		cout << endl << endl;

		heap.makeEmpty();
	}
			
	return 0;
}

