#include <iostream>
#include <vector>
#include <functional>
using namespace std;

// Generic findMax, with a function object, C++ style.
// Precondition: a.size( ) > 0.
template <typename Object, typename Comparator>
const Object & findMax( const vector<Object> & arr, Comparator isLessThan )
{
    int maxIndex = 0;

    for( int i = 1; i < arr.size( ); ++i )
        if( isLessThan( arr[ maxIndex ], arr[ i ] ) )
            maxIndex = i;

    return arr[ maxIndex ];
}

class Rectangle {

public:
	Rectangle(int h, int w)
		: height(h), width(w) {}
	int getHeight() const
		{ return height; }
	int getWidth() const
		{ return width; }
	ostream& print(ostream& os)
		{ return os << width << "x" << height; }

private:
	int width;
	int height;

};

class AreaCompare {
public:
	bool operator()(const Rectangle& lhs, const Rectangle& rhs)
		{ return lhs.getWidth() * lhs.getHeight() < rhs.getWidth() * rhs.getHeight(); }
};


class PerimeterCompare {
public:
	bool operator()(const Rectangle& lhs, const Rectangle& rhs) const
		{ return lhs.getWidth() * 2 +  lhs.getHeight() * 2 < rhs.getWidth() * 2 + rhs.getHeight() * 2; }
};

int main(int argc, char* argv[]) {
	vector<Rectangle> rects = { Rectangle(1, 10), Rectangle(3, 4), Rectangle(4, 4) };
	cout << "Rectangles:";
	for (int i = 0; i < 3; i++) {
		cout << " " << rects[i];
	}
	cout << "Max area :\t" << findMax(rects, AreaCompare{}) << endl;
	cout << "Max perimeter :\t" << findMax(rects, PerimeterCompare{}) << endl;
	

	return 0;
}
