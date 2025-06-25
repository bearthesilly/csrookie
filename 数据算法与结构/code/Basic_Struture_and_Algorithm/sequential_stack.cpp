#include <iostream>
using namespace std;

// 顺序栈 C++容器适配器 stack
class SeqStack{
public:
    SeqStack(int size = 10)
        : mtop(0)
        , mcap(size)
        {
            mpStack = new int[mcap];
        }
    ~SeqStack(){
        delete[] mpStack;
        mpStack = nullptr; // 防止野指针
    }

public:
    // 入栈
    void push(int val){
        if (mtop == mcap){
            // 扩容
            expand(2*mcap);
        }
        mpStack[mtop++] = val; // 赋值后,top++
    }

    void pop(){
        if (mtop == 0){
            // 抛异常也是一种return
            throw "Stack is empty";
        }
        mtop--;
    }

    int top() const{ // 加const是因为,这个方法是只读的
        if (mtop == 0){
            throw "Stack is empty";
        }
        return mpStack[mtop-1];
    }

    bool empty(){
        return mtop == 0;
    }

    int size() const{
        return mtop;
    }

private:
    int* mpStack;
    int mtop; // 栈顶位置
    int mcap; // 栈空间大小

private:
    void expand(int size){
        int* p = new int[size];
        memcpy(p, mpStack, mtop*sizeof(int));
        delete[] mpStack;
        mpStack = p;
        mcap = size;
    }
};

int main(){
    int arr[] = {12, 4, 56, 7, 89, 31, 53, 75};
    SeqStack s;
    for (int v : arr){
        s.push(v);
    }
    while (!s.empty()){
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
    return 0;
}