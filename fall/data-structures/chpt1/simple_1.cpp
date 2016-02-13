#include <cstdio>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    int arr[3];
    
    cin >> arr[0] >> arr[1] >> arr[2];
    cout << arr[0] << " " << arr[1] << " " << arr[2] << endl;
    cout << arr[2] << " " << arr[1] << " " << arr[0] << endl;

    // find min, max and total
    int total = 0;
    int min = arr[0], max = arr[0];
    for (int i = 0; i < 3; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
        total += arr[i];
    }
    
    cout << "max: " << max << endl;
    cout << "min: " << min << endl;
    cout << "avg: " << (float)total / 3.0 << endl;

    return 0;
}
