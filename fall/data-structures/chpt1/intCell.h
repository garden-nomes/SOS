#ifndef IntCell_H
#define IntCell_H

#include <iostream>

/**
 *  * A class for simulating an integer memory cell.
 *   */
class IntCell
{
  public:
    explicit IntCell( int initialValue = 0 );
    int read( ) const;
    void write( int x );

	IntCell add( IntCell a );
	IntCell add( int a );
	void addToThis( int a );

	IntCell subtract( IntCell a );
	IntCell subtract( int a );
	void subtractFromThis( int a );

	friend std::ostream& operator<<(std::ostream& os, const IntCell& a);

  private:
    int storedValue;
};

#endif
