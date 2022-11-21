typedef int TElem;

class Node {
private:
    TElem info;
    int prev;
    int next;

public:

    Node();
    Node(const Node& n);
    ~Node();

    TElem getInfo() const;
    int getPrev() const;
    int getNext() const;

    void setInfo(TElem new_info);
    void setPrev(int new_prev);
    void setNext(int new_next);

    Node& operator=(const Node& given_node);
};


