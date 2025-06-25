#include <iostream>
using namespace std;

struct Node{
    Node(int data = 0) 
        : data_(data)
        , next_(nullptr)
        , pre_(nullptr) 
        {} // 规范化的初始化构造列表,一行一个
    int data_;
    Node *next_;
    Node *pre_;
};

class DoubleLink{
public:
    DoubleLink(){
        head_ = new Node();
    }
    ~DoubleLink(){
        Node* p = head_;
        while (p != nullptr){
            head_ = head_->next_;
            delete p;
            p = head_;
        }
    }

private:
    Node* head_;

public:
    void InsertHead(int val){
        Node* node = new Node(val);
        node->next_ = head_->next_;
        node->pre_ = head_;
        if (head_->next_ != nullptr){
            head_->next_->pre_ = node;
        }
        head_->next_ = node;
    }

    void InsertTail(int val){
        Node* p = head_;
        while (p->next_ != nullptr){
            p = p->next_;
        }
        Node* node = new Node(val);
        node->pre_ = p;
        p->next_ = node;
    }

    bool Find(int val){
        Node* p = head_->next_;
        while (p != nullptr){
            if (p->data_ == val){
                return true;
            }
            else{
                p = p->next_;
            }
        }
    }

    void Remove(int val){
        Node* p = head_->next_;
        while (p != nullptr){
            if (p->data_ == val){
                p->pre_->next_ = p->next_;
                if (p->next_ != nullptr){
                    p->next_->pre_ = p->pre_;
                }
                Node* next = p->next_;
                delete p;
                p = next; // 有了这一行,说明是删除全部值为val的节点
            }
            else{
                p = p->next_;
            }
        }
    }

    void Show(){
        Node* p = head_->next_;
        while (p != nullptr){
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
     }
};

void TestBasic(DoubleLink& dlink){
    cout << "Testing Basics!" << endl;
    dlink.InsertHead(11);
    dlink.InsertHead(45);
    dlink.InsertHead(14);
    dlink.Show();
    dlink.InsertTail(19);
    dlink.InsertTail(19);
    dlink.InsertTail(810);
    dlink.Show();
}

void TestRemoval(DoubleLink& dlink){
    dlink.Remove(19);
    dlink.Show();
}

int main(){
    DoubleLink dlink;
    TestBasic(dlink);
    TestRemoval(dlink);
}