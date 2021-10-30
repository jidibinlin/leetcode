#include <algorithm>
#include <iostream>
using namespace std;

void quickSort(int *sortArray, int len) {
    if (len <= 1) {
        return;
    }
    int pivot = sortArray[0];
    int left = 1;
    int right = len - 1;
    while (left != right) {
        while (sortArray[right] > pivot && left != right) {
            right--;
        }
        while (sortArray[left] < pivot && left != right) {
            left++;
        }
        swap(sortArray[left], sortArray[right]);
    }

    if (sortArray[0] >= sortArray[left]) {
        swap(sortArray[0], sortArray[left]);
    }
    quickSort(&sortArray[0], left);
    quickSort(&sortArray[left + 1], len - (left + 1));
}

int main(int argc, char *argv[]) {
    int sortArray[10] = {2, 1};
    quickSort(sortArray, 2);
    for (int i = 0; i < 2; ++i) {
        cout << sortArray[i] << " ";
    }
    return 0;
}
