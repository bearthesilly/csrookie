#include <iostream>
using namespace std;

class LinkQueue{
public:
    LinkQueue(){
        head_ = new Node();
        head_->next_ = head_;
        head_->pre_ = head_;
    }

    ~LinkQueue(){
        Node* p = head_->next_;
        while (p != head_){
            head_->next_ = p->next_;
            p->next_->pre_ = head_;
            delete p;
            p = head_->next_;
        }
        delete head_;
        head_ = nullptr;
    }

public:
    void push(int val){
        Node* p = head_->pre_;
        Node* node = new Node(val);
        node->next_ = head_;
        node->pre_ = p;
        head_->pre_->next_ = node;
        head_->pre_ = node;
    }

    void pop(){
        if (head_->next_ == head_){
            throw "queue is empty!";
        }
        Node* p = head_->next_;
        head_->next_ = p->next_;
        p->next_->pre_ = head_;
        delete p;
    }

    int front() const{
        if (head_->next_ == head_){
            throw "queue is empty!";
        }
        return head_->next_->data_;
    }

    int back() const{
        if (head_->next_ == head_){
            throw "queue is empty!";
        }
        return head_->pre_->data_;
    }
    
    bool empty() const{
        return head_->next_ == head_;
    }
private:
    struct  Node{
        Node(int data = 0) 
        : data_(data)
        , next_(nullptr)
        , pre_(nullptr)
        {}
        int data_;
        Node* next_;
        Node* pre_;
    };
    Node* head_;
};

int main(){
    int arr[] = {11, 45, 14, 19, 19, 8, 1, 0};
    LinkQueue que;
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