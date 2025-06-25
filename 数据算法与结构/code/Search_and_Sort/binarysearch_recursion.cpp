#include <iostream>
using namespace std;

int BinarySearch(int arr[], int i, int j, int val){
    if (i > j){return -1;}
    int mid = (i+j)/2;
    if (arr[mid] == val){
        return mid;
    }
    else if (arr[mid] > val){
        return BinarySearch(arr, i, mid - 1, val);
    }
    else{
        return BinarySearch(arr, mid + 1, j, val);
    }
}