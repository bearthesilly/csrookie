#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

class HashTable{
public:
    HashTable(int size = primes_[0], double loadFactor=0.75)
        : useBucketNum_(0)
        , loadFactor_(loadFactor)
        , primeIdx_(0)
    {
        if (size != primes_[0]){
            for (; primeIdx_ < PRIME_SIZE; primeIdx_++){
                if (primes_[primeIdx_] > size){
                    break;
                }
            }
            // 用户传入的size值过大,已经超过最后一个素数,则调整到最后一个素数
            if (primeIdx_ == PRIME_SIZE){
                primeIdx_--;
            }
        }
        table_.resize(primes_[primeIdx_]);
    }
public:
    // 增加元素 且不能重复插入
    void insert(int key){
        // 判断是否扩容
        double factor = useBucketNum_ * 1.0 / table_.size();
        cout << "factor:" << factor << endl;
        if (factor > loadFactor_){
            expand();
        }
        // 通过哈希函数得到idx
        int idx = key % table_.size();
        if (table_[idx].empty()){
            useBucketNum_++;
            table_[idx].emplace_front(key);
        }
        else{
            // 使用全局的::find泛型算法,而不是调用自己的成员方法find
            auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
            if (it == table_[idx].end()){
                // 说明没找到,可以插入
                table_[idx].emplace_front(key);
            } else{
                cout << "This key has been inserted in the hash table!" << endl;
            }
        }
    }
    void erase(int key){
        int idx = key % table_.size();
        auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
        if (it != table_[idx].end()){
            table_[idx].erase(it);
            if (table_[idx].empty()){
                useBucketNum_--;
            }
        }
    }
    bool find(int key){
        int idx = key % table_.size();
        auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
        return it != table_[idx].end();
    }
private:
    void expand(){
        if (primeIdx_ + 1 == PRIME_SIZE){
            throw "HashTable is too large! Can not expand anymore";
        }
        primeIdx_++;
        vector<list<int>> oldTable;
        // swap仅仅是叫交换了两个容器的成员变量,因此这里swap其实是很高效的
        table_.swap(oldTable);
        table_.resize(primes_[primeIdx_]);
        for (auto list : oldTable){
            for (auto key : list){
                int idx = key % table_.size();
                if (table_[idx].empty()){
                    useBucketNum_++;
                }
                table_[idx].emplace_front(key);
            }
        }
    }
private:
    vector<list<int>> table_; //哈希表的数据结构
    int useBucketNum_; // 记录桶的个数
    double loadFactor_; // 哈希表装载因子
    static const int PRIME_SIZE = 10; // 素数表的大小
    static int primes_[PRIME_SIZE]; // 素数表
    int primeIdx_; // 当前使用的素数的下标
};

int HashTable::primes_[HashTable::PRIME_SIZE] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

int main(){
    HashTable htable;
    htable.insert(14);
    cout << htable.find(14) << endl;
    htable.insert(32);
    htable.insert(21);
    htable.insert(15);
    htable.insert(560);
    cout << htable.find(14) << endl;
    htable.erase(14);
    cout << htable.find(14) << endl;
}