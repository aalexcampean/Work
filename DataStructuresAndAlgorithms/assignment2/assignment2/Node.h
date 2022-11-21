#include <tuple>

class Node {
private:
    std::tuple<int, int, int> info;
    Node *prev;
    Node *next;

public:

    // Constructors, Destructor

    Node();
    Node(const Node& n);
    ~Node();

    // Getters

    int Value() const;
    int Row() const;
    int Col() const;
    Node *Prev() const;
    Node *Next() const;

    // Setters

    void setValue(int new_value);
    void setRow(int new_row);
    void setColumn(int new_column);
    void setNext(Node *new_next);
    void setPrev(Node *new_prev);
};

