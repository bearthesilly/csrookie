#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std; // 建议之后放弃这一行, 命名空间都带上std
class Array
{
public:
    // 如果没有传, 默认capacity是10
    Array(int size = 10): mCur(0), mCap(size)
    {
        mpArr = new int[mCap]();
    }
    ~Array()
    {
    	delete []mpArr; // 仅仅是堆上面的数据释放了
        // 没必要判断mpArr原来是不是空指针, 因为不知道是野指针还是指向的内存被释放
        // 即使原本就是空指针, 那么delete就相当于是空操作
        mpArr = nullptr; // 防止野指针的出现
    }
    
	// 末尾增加元素
    void push_back(int val){
        // 如果数组满了, 需要扩容
        if (mCur == mCap){
            expand(2 * mCap);
        }
        mpArr[mCur] = val;
        mCur++;
    }
    // 末尾删除元素
    void pop_back(){
        if (mCur == 0){
            return;
        }
        mCur--;
    }
    // 按位置增加元素
    void insert(int pos, int val){
        // 好习惯: 判断传入参数的有效性
        if (pos < 0 || pos > mCur){
            return; // invalid position
        }
        // 如果数组满了, 需要扩容
        if (mCur == mCap){
            expand(2 * mCap);
        }
        for (int i = mCur - 1; i >= pos; i--){
            mpArr[i+1] = mpArr[i];
        }
        mpArr[pos] = val;
    }
    // 按位置删除
    void erase(int pos){
        if (pos < 0 || pos >= mCur){
            return; // invalid operation
        }
        for (int i = pos + 1; i < mCur; i++){
            mpArr[i-1] = mpArr[i];
        }
        mCur--; // 代表数组少了一个元素
    }
    // 元素查询
    int find(int val){
        for (int i = 0; i < mCur; i++){
            if (mpArr[i] == val){
                return i;
            }
        }
        return -1;
    }
    void show() const{
        for (int i = 0; i < mCur; i++){
            cout << mpArr[i] << " ";
        }
        cout << endl;
    }
private: // 一定要先理清哪些是私有成员那些事公开成员
    int *mpArr; // 指向可扩容的数组内存
    int mCur; // 数组有效元素的个数, 这里有妙用
    int mCap; // 数组的容量
    // 内部数组扩容接口
    void expand(int size){
        // 开辟更长内存, 复制数据, 然后释放原来的数据
        int *p = new int[size];
        memcpy(p, mpArr, sizeof(int) * mCap);
        delete[]mpArr; 
        mpArr = p;
        mCap = size;
    }
};

int main(){
    Array arr;
    srand(time(0));
    for (int i = 0; i < 10; i++){
        arr.push_back(rand() % 100);
    }
    arr.show();
    arr.pop_back();
    arr.show();
    arr.insert(0, 100);
    arr.show();
    arr.insert(10, 200);
    arr.show();
    int pos = arr.find(100);
    if (pos != -1){
        arr.erase(pos);
        arr.show();
    }
    return 0;
}