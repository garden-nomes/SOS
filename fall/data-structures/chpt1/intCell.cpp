#include "intCell.h"

/**
 *  * Construct the IntCell with initialValue
 *   */
IntCell::IntCell( int initialValue ) : storedValue( initialValue )
{
}

/**
 *  * Return the stored value.
 *   */
int IntCell::read( ) const
{
    return storedValue;
}

/**
 *  * Store x.
 *   */
void IntCell::write( int x )
{
    storedValue = x;
}


/**
 * * Addition functions
 *  */
IntCell IntCell::add( IntCell a ) {
	return IntCell(storedValue + a.storedValue);
}

IntCell IntCell::add( int a ) {
	return IntCell(storedValue + a);
}

void IntCell::addToThis( int a ) {
	storedValue += a;
}

/**
 * * Subtraction functions
 *  */
IntCell IntCell::subtract( IntCell a ) {
	return IntCell(storedValue - a.storedValue);
}

IntCell IntCell::subtract( int a ) {
	return IntCell(storedValue - a);
}

void IntCell::subtractFromThis( int a ) {
	storedValue -= a;
}

std::ostream& operator<<(std::ostream& os, const IntCell& a) {
	return os << a.storedValue;
}
