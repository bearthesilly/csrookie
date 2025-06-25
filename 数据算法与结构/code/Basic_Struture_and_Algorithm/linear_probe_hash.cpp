#include <iostream>
using namespace std;

enum State{
    STATE_UNUSE, // 从未使用过的桶
    STATE_USING, // 正在使用的桶
    STATE_DEL, // 元素被删除了的桶
};

struct Bucket{
    Bucket(int key = 0, State state = STATE_UNUSE)
        : key_(key)
        , state_(state)
    {}
    int key_; // 存储的数据
    State state_; // 桶当前的状态
};

class HashTable{
public:
    HashTable(int size = primes_[0], double loadFactor = 0.75)
        : useBucketNum_(0)
        , loadFactor_(loadFactor)
        , primeIdx_(0)
    {
        // 用户传入的size调整到最近的比较大的素数上
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
        tableSize_ = primes_[primeIdx_];
        table_ = new Bucket[tableSize_];
    }

    ~HashTable(){
        delete[] table_;
        table_ = nullptr;
    }
public:
    // 插入元素
    bool insert(int key){
        // 考虑扩容
        double factor = useBucketNum_*1.0 / tableSize_; 
        // 两个int相除得到int, 但是其中一个可以通过*1.0变成浮点数
        cout << "factor: " << factor << endl;
        if (factor > loadFactor_){
            // 哈希表扩容
            expand();
        }
        // 此处的哈希函数
        int idx = key % tableSize_;
        if (table_[idx].state_ != STATE_USING){
            table_[idx].state_ = STATE_USING;
            table_[idx].key_ = key;
            useBucketNum_++;
            return true;
        }
        // Linear Probe
        for (int i = (idx+1) % tableSize_; i != idx; i = (i+1) % tableSize_){
            if (table_[i].state_ != STATE_USING){
                table_[i].state_ = STATE_USING;
                table_[i].key_ = key;
                useBucketNum_++;
                return true;
            }
        }
        return false;
    }

    // 删除元素
    bool erase(int key){
        int idx = key % tableSize_;
        int i = idx;
        do{
            if (table_[i].state_ == STATE_USING && table_[i].key_ == key){
                table_[i].state_ = STATE_DEL;
                useBucketNum_--;
            }
            i = (i + 1) % tableSize_;
        } while(table_[i].state_ != STATE_DEL && i != idx);
        return true;
    }

    // 查询 
    bool find(int key){
        int idx = key % tableSize_;
        int i = idx;
        do{
            if (table_[i].state_ == STATE_USING && table_[i].key_ == key){
                return true;
            }
            i = (i + 1) % tableSize_;
        } while(table_[i].state_ != STATE_UNUSE && i != idx);
        return false;
    }
private:
    void expand(){
        ++primeIdx_;
        if (primeIdx_ == PRIME_SIZE){
            throw "HashTable is too large! Can not expand anymore";
        }
        Bucket *newTable = new Bucket[primes_[primeIdx_]];
        for (int i = 0; i < tableSize_; i++){
            if (table_[i].state_ == STATE_USING){
                // 旧表有效的数据,重新哈希放在扩容后的新表
                int idx = table_[i].key_ % primes_[primeIdx_];
                int k = idx;
                // 放进新表的时候, 依然要考虑哈希冲突的问题!
                do{
                    if (newTable[k].state_ != STATE_USING){
                        newTable[k].state_ = STATE_USING;
                        newTable[k].key_ = table_[i].key_;
                        break;
                    }
                    k++;
                } while(k != idx);
            }
        }
        delete[] table_;
        table_ = newTable;
        tableSize_ = primes_[primeIdx_];
    }
private:
    Bucket *table_; // 指向动态开辟的哈希表
    int tableSize_; // 哈希表当前的长度
    int useBucketNum_; // 已经使用的桶的个数
    double loadFactor_; // 哈希表的装载因子
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