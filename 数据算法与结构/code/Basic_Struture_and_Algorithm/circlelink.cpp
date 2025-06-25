#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;


struct Node{
    Node(int data = 0) : data_(data), next_(nullptr){}
    int data_;
    Node* next_;
};
class CircleLink{
public:
    CircleLink(){
        head_ = new Node();
        // tail指针的信息将在尾插的过程中得到更新!
        tail_ = head_;
        head_->next_ = head_;
    }
    ~CircleLink(){
        Node* p = head_->next_;
        while (p != head_){
            head_->next_ = p->next_;
            delete p;
            p = head_->next_;
        }
        delete head_;
    }

public:
    void InsertTail(int val){
        Node* node = new Node(val);
        node->next_=tail_->next_;
        tail_->next_ = node;
        // 在这里, tail指针的信息得到更新! 
        tail_ = node;
    }

    void InsertHead(int val){
        Node* node = new Node(val);
        node->next_=head_->next_;
        head_->next_ = node;
        // 如果只有头节点, tail和head一样, 那么头插之后, tail指针需要移动
        // 但是对于不止头节点情况, tail指针不需要移动. 所以这里需要分类讨论对tail指针的处理!
        if (node->next_ == head_){
            tail_ = node;
        }
    }

    void Remove(int val){
        Node* q = head_;
        Node* p = head_->next_;
        while (p != head_){ // 注意什么时候退出循环! 除非需要可以寻找尾节点, 循环中尽可能少用->next_判断
            if (p->data_ == val){
                q->next_ = p->next_;
                delete p;
                // 如果删除的是为节点, 那么tail指针需要得到更新! 
                if (q->next_ == head_){
                    tail_ = q;
                }
                return;
            }
            else {
                q = p;
                p = p->next_;
            }
        }
        return;
    }

    bool Find(int val) const{
        Node* p = head_->next_;
        while (p != head_){
            if (p->data_ == val){
                return true;
            }
        }
        return false;
    }

    void Show() const{
        Node* p = head_->next_;
        while (p != head_){
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }

private:
    Node* head_;
    Node* tail_;
 };

void Joseph(Node* head, int k, int m){
    Node* p = head;
    Node* q = head;
    // q指向最后一个节点! 因为在我们测试的时候, 没有头节点.
    while (q->next_ != head){
        q = q->next_;
    }
    // 到第k个人
    for (int i = 1; i < k; i++){
        q = p;
        p = p->next_;
    }
    for (;;){ // 一直循环, 直到p == q
        for (int i = 1; i < m; i++){
            q = p;
            p = p->next_;
        }
        cout << p->data_ << " ";
        if (p == q){
            delete p;
            break;
        }
        q->next_ = p->next_;
        delete p;
        p = q->next_;
    }
    cout << endl;
}

void TestBasic(CircleLink& clink){
    cout << "Testing Basic!" << endl;
    srand(time(NULL));
    for (int i = 0; i < 10; i++){
        clink.InsertTail(rand()%100);
    }
    clink.Show();
    clink.InsertHead(200);
    clink.InsertTail(200);
    clink.Show();
    clink.Remove(200);
    clink.Show();
    cout << endl;
}

void TestJoseph(){
    cout << "Testing Joseph!" << endl;
    Node* head = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);
    Node* n6 = new Node(6);
    Node* n7 = new Node(7);
    Node* n8 = new Node(8);
    head->next_ = n2;
    n2->next_ = n3;
    n3->next_ = n4;
    n4->next_ = n5;
    n5->next_ = n6;
    n6->next_ = n7;
    n7->next_ = n8;
    n8->next_ = head;
    Joseph(head, 1, 1);
}
int main(){
    CircleLink clink;
    TestBasic(clink);
    TestJoseph();
    return 0;
}