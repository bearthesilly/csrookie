#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct Node{
    Node(int data = 0): data_(data), next_(nullptr){}
    int data_;
    Node* next_;
};

class Clink{
public:
    Clink(){
        // 初始化的时候, 指向头节点; new Node()在开辟的时候, 同时也会调用构造函数进行初始化
        head_ = new Node();
    }
    ~Clink(){ // 一定不是简简单单的释放头指针就完了! 理解为什么需要p head_两个指针完成操作!
        Node *p = head_;
        while (p != nullptr){
            head_ = head_->next_;
            delete p;
            p = head_;
        }
        head_ = nullptr;
    }

    void InsertTail(int val){ // 链表尾插法
        // 先找到当前链表的末尾节点, 然后生成新节点; 如何找到尾节点呢? 判断地址域是不是空指针!
        Node *p = head_;
        while (p->next_ != nullptr){
            p = p->next_;
        }
        Node *node = new Node(val);
        p->next_ = node;        
    }


    void InsertHead(int val){ // 链表头插法; 注意修改的顺序!!
        Node *node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
    }

    void Remove(int val){ // 删除节点; 理解为什么p q要两个结构体指针来操作!
        Node *p = head_->next_;
        Node *q = head_;
        while (p != nullptr){
            if (p->data_ == val){
                q->next_ = p->next_;
                delete p; // 释放p对应的node
                return;
            }
            else{
                q = p;
                p = p->next_;
            }
        }
    }

    bool Find(int val){
        Node *p = head_->next_;
        while (p != nullptr){
            if (p->data_ == val){
                return true;
            }
            else{
                p = p->next_;
            }
        }
        return false;
    }

    void RemoveAll(int val){
        Node *p = head_->next_;
        Node *q = head_;
        while (p != nullptr){
            if (p->data_ == val){
                q->next_ = p->next_;
                delete p;
                p = q->next_;
            }
            else{
                q = p;
                p = p->next_;
            }
        }
    }

    void Show(){
        // 注意这里指针的设计! 这样可以防止尾节点的数据忘记被打印! 
        Node *p = head_->next_;
        while (p != nullptr){
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }
private:
    Node *head_;
    friend void ReverseLink(Clink &link);
    friend bool MergeLink(Clink& link1, Clink& link2);
    friend bool GetLastKNode(Clink &link, int k, int &val);
};



void ReverseLink(Clink &link){
    Node *p = link.head_->next_;
    if (p == nullptr){return;}
    link.head_->next_ = nullptr;
    while (p != nullptr){
        Node *q = p->next_;
        p->next_ = link.head_->next_;
        link.head_->next_ = p;
        p = q;
    }
}

bool GetLastKNode(Clink &link, int k, int &val){
    // 注意是引用传递, 这样就可以将值赋给val
    Node* head = link.head_;
    Node* q = head;
    Node* p = head;
    // 好习惯: 判断参数有效性!! 为什么小心k=0? 因为p最后开始走0步, 然后和q一起到空指针
    // 悲剧就是: 访问了空指针. 
    if (k < 1){return false;} 
    for (int i = 0; i < k; i++){
        p = p->next_;
        if (p == nullptr){
            return false;
        }
    }
    while (p != nullptr){
        q = q->next_;
        p = p->next_;
    }
    val = q->data_;
    return true;
}

bool MergeLink(Clink& link1, Clink& link2){
    Node* p = link1.head_->next_;
    Node* q = link2.head_->next_;
    Node* last = link1.head_;
    link2.head_->next_ = nullptr;
    while (p != nullptr && q != nullptr){
        if (p->data_ < q->data_){
            last->next_ = p;
            p = p->next_;
            last = last->next_;
        }
        else{
            last->next_ = q;
            q = q->next_;
            last = last->next_;
        }
    }
    if (p != nullptr){
        last->next_ = p;
    }
    else{
        last->next_ = q;
    }
    return true;
}

bool IsLinkHasCircle(Node* head, int& val){
    Node* fast = head;
    Node* slow = head;
    while (fast != nullptr && fast->next_ != nullptr){ // fast走两步, 所以判断两个是不是nullptr, 防止访问空指针
        slow = slow->next_;
        fast = fast->next_->next_;
        if (fast == slow){
            fast = head;
            while (fast != slow){
                slow = slow->next_;
                fast = fast->next_;
            }
            val = slow->data_;
            return true;
        }
    }
    return false;
}

bool IsLinkHasMerge(Node* head1, Node* head2, int& val){
    int cnt1 = 0, cnt2 = 0;
    Node* p = head1->next_;
    Node* q = head2->next_;
    while (p != nullptr){
        cnt1++;
        p = p->next_;
    }
    while (q != nullptr){
        cnt1++;
        q = q->next_;
    }
    p = head1->next_;
    q = head2->next_;
    if (cnt1 > cnt2){
        int offset = cnt1 - cnt2;
        while (offset-- > 0){
            p = p->next_;
        }
        while (p != nullptr && q != nullptr){
            if (p == q){
                val = p->data_;
                return true;
            }
            p = p->next_;
            q = q->next_;
        }
        return false;
    }
    else {
        int offset = cnt2 - cnt1;
        while (offset-- > 0){
            q = q->next_;
        }
        while (p != nullptr && q != nullptr){
            if (p == q){
                val = p->data_;
                return true;
            }
            p = p->next_;
            q = q->next_;
        }
        return false;
    }
}

void TestBasic(){
    cout << "Testing Basic" << endl;
    Clink link;
    srand(time(0));
    for (int i = 0; i < 10; i++){
        int val = rand()%100;
        link.InsertTail(val);
        cout << val << " ";
    }
    cout << endl;
    link.InsertTail(200);
    link.Show();
    link.Remove(200);
    link.Show();
    link.InsertHead(233);
    link.InsertHead(233);
    link.InsertTail(233);
    link.Show();
    link.RemoveAll(233);
    link.Show();
    ReverseLink(link);
    link.Show();
}

void TestGetLastKNode(int k){
    cout << "Testing GetLastKNode" << endl;
    Clink link;
    srand(time(0));
    for (int i = 0; i < 10; i++){
        int val = rand()%100;
        link.InsertTail(val);
        cout << val << " ";
    }
    cout << endl;
    int val;
    GetLastKNode(link, k, val);
    cout << "The last " << k << " node is: " << val << endl;
}

void TestReverse(){
    cout << "Testing Reverse" << endl;
    Clink link;
    srand(time(0));
    for (int i = 0; i < 10; i++){
        int val = rand()%100;
        link.InsertTail(val);
        cout << val << " ";
    }
    cout << endl;
    ReverseLink(link);
    link.Show();
}

void TestMerging(){
    cout << "Testing MergingLink" << endl;
    Clink link1, link2;
    for (int i = 0; i < 10; i++){
        int val = 2*i;
        link1.InsertTail(val);
    }
    for (int i = 0; i < 10; i++){
        int val = 2*i+1;
        link2.InsertTail(val);
    }
    link1.Show();
    link2.Show();
    MergeLink(link1, link2);
    link1.Show();
}

void TestCircle(){
    cout << "Testing IsLinkHasCircle" << endl;
    Node head;
    Node n1(25), n2(67), n3(32), n4(18);
    head.next_ = &n1;
    n1.next_ = &n2;
    n2.next_ = &n3;
    n3.next_ = &n4;
    n4.next_ = &n2;
    int val;
    if (IsLinkHasCircle(&head, val)){
        cout << "Link has a circle and the entrance data is: " << val << endl;
    }
    else {
        cout << "Link has no circle" << endl;
    }
}

void TestIsHasMerge(){
    cout << "Testing IsLinkHasMerge" << endl;
    Node head1, head2;
    Node n1(25), n2(67), n3(32), n4(18);
    Node m1(23), m2(65);
    head1.next_ = &n1;
    n1.next_ = &n2;
    n2.next_ = &n3;
    n3.next_ = &n4;
    head2.next_ = &m1;
    m1.next_ = &m2; 
    m2.next_ = &n2;
    int val;
    if (IsLinkHasMerge(&head1, &head2, val)){
        cout << "The two links has intersection node and its value is: " << val << endl;
    }
    else{
        cout << "Those two links don't have intersction!" << endl;
    }
}

int main(){
    TestBasic();
    TestReverse();
    TestGetLastKNode(3);
    TestMerging();
    TestCircle();
    TestIsHasMerge();
    return 0;
}