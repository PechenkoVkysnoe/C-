#include <iostream>
#include <iterator>
using namespace std;

struct Node
{
    int value;
    Node* next, * prev;
};
class DoubleList
{
public:
    class Iterator;
    DoubleList();
    DoubleList(const DoubleList&);
    ~DoubleList();
    void push_back(int x);
    void push_front(int x);
    void pop_back();
    void pop_front();
    int size();
    bool empty();
    Iterator begin();
    Iterator end();
    class Iterator :iterator<bidirectional_iterator_tag, int >
    {
    public:
        Iterator() : object(nullptr)
        {
        }
        Iterator(const Iterator& other) : object(other.object)
        {
        }
        explicit Iterator(Node* value) : object(value)
        {
        }
        Node* operator->()
        {
            return object;
        }
        Iterator& operator++()
        {
            object = object->next;
            return *this;
        }
        Iterator& operator++(int)
        {
            Iterator tmp = *this;
            this->object = this->object->next;
            return tmp;
        }
        Iterator& operator--(int)
        {
            Iterator tmp = *this;
            this->object = this->object->prev;
            return tmp;
        }
        Iterator& operator--()
        {
            object = object->next;
            return *this;
        }
        int& operator*()
        {
            return object->value;
        }
        int operator*() const
        {
            return object->value;
        }
        bool operator==(const Iterator& rhs) const
        {
            return object == rhs.object;
        }
        bool operator!=(const Iterator& rhs) const
        {
            return object != rhs.object;
        }
    private:
        Node* object;
    };
private:
    Node* Head, * Tail;
    int Size;
};
DoubleList::~DoubleList()
{
    while (Size > 0)
    {
        pop_front();
    }
}
DoubleList::DoubleList(const DoubleList& List)
{
    Head = nullptr;
    Tail = nullptr;
    Size = 0;
    int variable = 0;
    Node* tmp = List.Head;
    while (variable != List.Size)
    {
        push_back(tmp->value);
        tmp = tmp->next;
        variable++;
    }
}
DoubleList::Iterator DoubleList::begin()
{
    return Iterator(Head);
}
DoubleList::Iterator DoubleList::end()
{
    return Iterator(Tail->next);
}
bool DoubleList::empty()
{
    if (Size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int DoubleList::size()
{
    return Size;
}
DoubleList::DoubleList()
{
    Size = 0;
    Head = nullptr;
    Tail = nullptr;
}
void DoubleList::push_back(int x)
{
    Node* tmp = new Node;
    Node* last = new Node;
    last->value = 0;
    last->prev = tmp;
    tmp->next = last;
    tmp->prev = Tail;
    tmp->value = x;
    if (Tail != nullptr)
    {
        Tail->next = tmp;
    }
    Tail = tmp;
    if (Size == 0)
    {
        Head = tmp;
    }
    Size++;
}
void DoubleList::push_front(int x)
{
    Node* tmp = new Node;
    tmp->next = Head;
    tmp->prev = nullptr;
    tmp->value = x;
    if (Head != nullptr)
    {
        Head->prev = tmp;
    }
    Head = tmp;
    if (Size == 0)
    {
        Tail = tmp;
    }
    Size++;
}
void DoubleList::pop_front()
{
    Node* tmp = Head->next;

    tmp->prev = nullptr;
    delete Head;
    Head = tmp;

    Size--;
}
void DoubleList::pop_back()
{
    Node* tmp = Tail->prev;
    Node* last = new Node;
    last->value = 0;
    last->prev = tmp;
    tmp->next = last;
    delete Tail;
    Tail = tmp;
    Size--;
}

/*
 * DoubleList arr = {1, 2, 3}; // такое работать не будет, надо доделать...
*/