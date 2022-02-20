using namespace std;

template <typename Key, typename Value>
class SequentialSearchST {
private:
    class Node {
    public:
        Key key;
        Value value;
        Node *next;
        Node(Key key, Value value, Node *next) {
            this->key = key;
            this->value = value;
            this->next = next;
        }
    };

    Node *first;
public:

    Value get(Key key){
        for(Node x = first; x!=NULL;x=x->next){
            if(key->equals(x->key)){
                return x->val;
            }
            return NULL;
        }
    }

    void put(Key key, Value val){
        for (Node *x = first; x != NULL; x=x->next) {
            if(key->equals(x->key)){
                x->val = val;
                return;
            }
        }
        first = new Node(key,val,first);
    }
};
