#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void Merge(int arr[], int left, int mid, int right){
    // 需要额外的内存空间，把两个小段有序的序列，合并成大段有序的序列
    int* p = new int[right-left+1];
    int idx = 0;
    int i = left;
    int j = mid + 1;
    while (i <= mid && j <= right){
        if (arr[i] <= arr[j]){
            p[idx++] = arr[i++];
        }
        else {
            p[idx++] = arr[j++];
        }
    }
    while (i <= mid){
        p[idx++] = arr[i++];
    }
    while (j <= right){
        p[idx++] = arr[j++];
    }
    // 把合并好的大段有序结果拷贝到原始数组[left, right]区间内
    for (i = left, j = 0; i <= right; i++, j++){
        arr[i] = p[j];
    }
    delete[] p;
}

void MergeSort(int arr[], int begin, int end){
    // 递归结束的条件
    if (begin >= end){
        return;
    }
    int mid = (begin + end) / 2;
    // 先递
    MergeSort(arr, begin, mid);
    MergeSort(arr, mid + 1, end);
    // 再归并 [begin, mid] [mid + 1, begin]这两段有序的序列
    Merge(arr, begin, mid, end);
    
}

void MergeSort(int arr[], int size){
    MergeSort(arr, 0, size-1);
}

int main(){
    int arr[10];
    srand(time(NULL));
    for (int i = 0; i < 10; i++){
        arr[i] = rand() % 100 + 1;
    }
    for (int v : arr){
        cout << v << " ";
    }
    cout << endl;
    MergeSort(arr, 10);
    for (int v : arr){
        cout << v << " ";
    }
    cout << endl;
}