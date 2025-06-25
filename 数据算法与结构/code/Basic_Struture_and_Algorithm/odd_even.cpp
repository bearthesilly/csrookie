#include <iostream>
#include <time.h>
using namespace std;

void AdjustArray(int arr[], int size){
    int * p = arr;
    int * q = arr + size - 1;
    while (p < q){
        if (*p % 2 == 0){ // p指针对应的是偶数, 那么就右边移动
            p++; // 否则, 那就不会移动
        }
        if (*q % 2 == 1){ // q指针对应的是奇数, 那么就左移动
            q--; // 否则, 那就不会移动
        }
        // 先处理完移动的程序, 然后判断时候交换p q指针的数字
        if ((*p % 2 == 1) && (*q % 2 == 0)){ // 如果p对应奇数而q对应偶数, 交换!
            int temp = *p;
            *p = *q;
            *q = temp;
        }
    }
}
int main(){
    int arr[10] = {0};
    srand(time(0));
    for (int i = 0; i < 10; i++){
        arr[i] = rand()%100;
    }
    // trick : 基于范围的for循环
    for (int v : arr){
        cout << v << " ";
    }
    cout << endl;
    AdjustArray(arr, 10);
    for (int v : arr){
        cout << v << " ";
    }
    return 0;
}