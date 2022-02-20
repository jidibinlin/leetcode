#include <vector>
using namespace std;

template<typename Key,typename Value>
class SequentialSearchSt{
private:
    vector<Key> keys;
    vector<Value> vals;
    int N;
    int end;

public:
    int size(){
        return N;
    }
    Value get(Key key){
        if(isEmpty())
            return ;
        vector<Value>::iterator i = rank(key);
        if (i<N && keys[i]==key)
            return vals[i];
        else
            return NULL;
    }

    int rank(Key key){
        //TODO waiting for write
    }

    void put(Key key,Value val){
        int i= rank(key);
        if (i<N && keys[i]==key){
            vals[i]=val;
            return;
        }
        for (int j = N; j > i; --j) {
            keys[j] = keys[j-1];
            vals[j] = vals[j-1];
        }
        keys[i] = key;
        vals[i] = val;
        N++
    }

    void delete(Key key){
        //TODO waiting for write
    }

}
