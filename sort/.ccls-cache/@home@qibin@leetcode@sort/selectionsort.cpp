#include <algorithm>
#include <iostream>
//#include <stdlib>
#include <vector>
using namespace std;

void selectionSort(vector<int> &sortArray) {
    for (int i = 0; i < sortArray.size(); ++i) {
        int tmpIdx = i;
        for (int j = i; j < sortArray.size(); ++j) {
            if (sortArray[j] <= sortArray[tmpIdx]) {
                tmpIdx = j;
            }
        }
        swap(sortArray[i],sortArray[tmpIdx]);
    }
}

int main(int argc, char *argv[]) {
    vector<int> s;
    for (int i = 0; i < 10; ++i) {
        s[i] = rand()%10;
    }

    selectionSort(s);

    for (int i = 0; i < 10; ++i) {
        cout << s[i] << " "<<endl;
    }
    return 0;
}
