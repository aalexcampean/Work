#include "Da.h"

typedef int TKey;
typedef int TValue;

class Node {
private:
    TKey key;
    DynamicArray<TValue> da;
    Node* next;

public:

    // Constructors, Destructor

    Node();
    Node(const Node& n);
    ~Node();
    void resize();

    // Operators Overload
    Node& operator=(const Node* n);
    TValue operator[](int index);

    // Getters

    TKey Key() const;
    int DALength();
    int DACapacity();
    DynamicArray<TValue>& DA();
    int DAGetIndex(TValue elem);
//    TValue DAElement(int index);
    Node* Next() const;

    // Setters

    void setKey(TKey new_key);
    void setNext(Node *new_next);

    // Add, Delete

    void addElement(TValue elem);
    void removeElement(TValue elem);
};

