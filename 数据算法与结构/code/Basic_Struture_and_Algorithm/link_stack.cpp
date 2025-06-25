#include <iostream>
using namespace std;

class LinkStack{
public:
    LinkStack() : size_(0){
        head_ = new Node;
    }
    ~LinkStack(){
        Node* p = head_;
        while (p != nullptr){
            head_ = head_->next_;
            delete p;
            p = head_;
        }
    }

public:
    // 入栈 头结点的后面第一个有效节点的位置作为栈顶
    void push(int val){
        Node* node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
        size_++;
    }
    // 出栈
    void pop(){
        if (head_->next_ == nullptr)
            throw "Stack is empty!";
        Node* p = head_->next_;
        head_->next_ = p->next_;
        delete p;
        size_--;
    }

    int top() const{
        if (head_->next_ == nullptr)
            throw "Stack is empty!";
        return head_->next_->data_;
    } 

    bool empty(){
        return head_->next_ == nullptr;
    }

    int size() const{
        // 返回栈元素个数，如果遍历，那么就是O(n)
        // 为了O(1),可以在成员里面加入记录这一参数的设计
        return size_;
    }
private:
    struct Node{
        Node(int data = 0) : data_(data), next_(nullptr){}
        int data_;
        Node* next_;
    };
    Node* head_;
    int size_;
};

int main(){
    int arr[] = {12, 4, 56, 7, 89, 31, 53, 75};
    LinkStack s;
    for (int v : arr){
        s.push(v);
    }
    cout << "The size of the stack is: " << s.size() << endl;
    while (!s.empty()){
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
    return 0;
}