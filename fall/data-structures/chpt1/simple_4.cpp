#include <iostream>
using namespace std;

class IntCell
{
  public:
    explicit IntCell( int initialValue = 0 )
      { storedValue = new int( initialValue ); }

    int read( ) const
      { return *storedValue; }
    void write( int x )
      { *storedValue = x; }
  private:
    int *storedValue;
};

int main(int argc, char** argv) {

    // create and print array
    cout << "Array 1:";
    IntCell arr1[10];
    for (int i = 0; i < 10; i++) {
        arr1[i] = IntCell(i + 1);
        cout << " " << arr1[i].read();
    }

    // copy into second array and modify values
    cout << endl << "Copying array..." << endl;
    IntCell *arr1p = arr1;
    IntCell arr2[10];
    for (int i = 0; i < 10; i++) {
        arr2[i] = *arr1p++;
    }

    cout << "Modifying second array..." << endl;
    for (int i = 0; i < 10; i++) { arr2[i].write(arr2[i].read() + 1); }

    // print arrays
    cout << "Array 1:";
    for (int i = 0; i < 10; i++) {
        cout << " " << arr1[i].read();
    }
    cout << endl << "Array 2:";
    for (int i = 0; i < 10; i++) {
        cout << " " << arr2[i].read();
    }
    cout << endl;

    return 0;
}

