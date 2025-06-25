// reverse.cpp
#include <iostream>
#include <string.h>
using namespace std;
void Reverse(char arr[], int size){ // 传入size是因为数组传入之后会退化为指针, 所以需要知道个数
    char *p = arr;
    char *q = arr + size - 1;
    while (p < q){
        char ch = *p;
        *p = *q;
        *q = ch;
        p++;
        q--;
    }
}
int main(){
    char arr[] = "hello world";
    cout << arr << endl;
    Reverse(arr, strlen(arr)); // strlen()需要用<string.h>
    cout << arr << endl;
    return 0;
}