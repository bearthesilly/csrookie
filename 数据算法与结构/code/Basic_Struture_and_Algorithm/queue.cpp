#include <iostream>
using namespace std;

class Queue{
public:
    Queue(int size = 10)
    : cap_(size)
    , front_(0)
    , rear_(0)
    , size_(0){
        pQue_ = new int[cap_];
    }
    ~Queue(){
        delete[] pQue_;
        pQue_ = nullptr;
    }

public:
    void push(int val){
        if ((rear_ + 1) % cap_ == front_){
            expand(2 * cap_);
        }
        pQue_[rear_] = val;
        rear_ = (rear_ + 1) % cap_;
        size_++;
    }

    void pop(){
        if (front_ == rear_){
            throw "The Queue is empty!";
        }
        front_ = (front_ + 1) % cap_;
        size_--;
    }

    int front() const{
        if (front_ == rear_){
            throw "The Queue is empty!";
        }
        return pQue_[front_];
    }

    int back() const{
        if (front_ == rear_){
            throw "The Queue is empty!";
        }
        return pQue_[(rear_ - 1 + cap_) % cap_];
        // 上面这个式子的设计是为了包括rear为0的情况
    }

    bool empty() const{
        return front_ == rear_;
    }

    int size() const{
        return size_;
    }
private:
    void expand(int size){
        int* p = new int[size];
        int i = 0;
        int j = front_;
        for (;j != rear_; i++,j = (j+1) % cap_){
            p[i] = pQue_[j];
        }
        delete[] pQue_;
        pQue_ = p;
        cap_ = size_;
        front_ = 0;
        rear_ = i;
    }
private:
    int* pQue_;
    int cap_; // 空间容量
    int front_; // 队头
    int rear_; //队尾
    int size_;
};

int main(){
    int arr[] = {11, 45, 14, 19, 19, 8, 1, 0};
    Queue que;
    for (int v : arr){
        que.push(v);
    }
    cout << que.front() << endl;
    cout << que.back() << endl;
    que.push(100);
    que.push(200);
    que.push(300);
    cout << que.front() << endl;
    cout << que.back() << endl;
    while (!que.empty()){
        cout << que.front() << " " << que.back() << endl;
        que.pop();
    }
}