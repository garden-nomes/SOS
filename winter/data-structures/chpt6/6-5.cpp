/*
 * Problem 6.5
 * Noah Weiner
 *
 * Rewrite the BinaryHeap insert routine by placing a copy of the inserted item in
 * position 0.
 *
 * NOTE: I think the book implementation already uses this method??? The following code
 * is taken straight from figure 6.8 (4th Ed.)
 */

void insert( const Comparable & x )
{
    if( currentSize == array.size( ) - 1 )
        array.resize( array.size( ) * 2 );

    // Percolate up
    int hole = ++currentSize;
	Comparable copy = x;

	array[ 0 ] = std::move( copy );
    for( ; x < array[ hole / 2 ]; hole /= 2 )
        array[ hole ] = std::move( array[ hole / 2 ] );
    array[ hole ] = std::move( array[ 0 ] );
}