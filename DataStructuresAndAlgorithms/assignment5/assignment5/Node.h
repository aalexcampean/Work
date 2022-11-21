typedef int TElem;
#define NULLTElem -111111111;

class Node {
private:
    TElem info;
    int leftCounter;
    Node* left;
    Node* right;

public:

    Node();
    Node(const Node& n);
    ~Node();

    TElem getInfo() const;
    int getLeftCounter() const;
    Node* getLeft() const;
    Node* getRight() const;

    void setInfo(TElem new_info);
    void increaseLeftCounter();
    void decreaseLeftCounter();
    void setLeftCounter(int new_value);
    void setLeft(Node* new_prev);
    void setRight(Node* new_next);

    Node& operator=(const Node& given_node);
};


