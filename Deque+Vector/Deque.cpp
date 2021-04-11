#include <iostream>
#include <iterator>
using namespace std;
const int block_size = 64;//условно говоря любого значение которое вы захотите 
struct Block
{
    int* arr;
    Block();
    ~Block();
};
Block::Block()
{
    arr = new int[block_size];
}
Block::~Block()
{
    delete[] arr;
}
class Deque
{
public:
    class Iterator;
    Deque();
    Deque(const Deque& other);
    ~Deque();
    void push_back(int x);
    void push_front(int x);
    void pop_back();
    void pop_front();
    void clear();
    int size();
    bool empty();
    int operator[](int value);
    Iterator begin();
    Iterator end();
     class Iterator :iterator<random_access_iterator_tag, int >
     {
     public:
         Iterator()
         {
             object=nullptr;
             block=nullptr;
             index=nullptr;
         }
         Iterator(Deque* ob,Block* bl,int* ind)
         {
             ob=object;
             bl=block;
             ind=index;
         } 
         Iterator(const Iterator& other)
         {
             this->object = other.object;
             this->block = other.block;
             this->index = other.index;
         }
         Iterator& operator++()
         {

         }
         Iterator& operator++(int)
         {

         }
         Iterator& operator--(int)
         {

         }
         Iterator& operator--()
         {

         }
         int& operator*()
         {
             return *index;
         }
         int operator*() const
         {
             return *index;
         }
         bool operator==(const Iterator& rhs) const
         {
             return this->index == rhs.index;
         }
         bool operator!=(const Iterator& rhs) const
         {
             return this->index != rhs.index;
         }
         bool operator>(const Iterator& rhs) const
         {
             return this->index > rhs.index;
         }
         bool operator<(const Iterator& rhs) const
         {
             return this->index < rhs.index;
         }
         bool operator<=(const Iterator& rhs) const
         {
             return this->index <= rhs.index;
         }
         bool operator>=(const Iterator& rhs) const
         {
             return this->index >= rhs.index;
         }
     private:
         Deque* object;
         Block* block;
         int* index;
     };
private:
    Block** arr_ptr;
    int block_end, block_begin, myEnd, myBegin;
    int mySize;
    int capacity;
    void resize();
};
Deque::Deque()
{
    mySize = 0;
    capacity = block_size * 4;
    arr_ptr = new Block * [4];
    for (int i = 0; i < 4; i++)
    {
        arr_ptr[i] = new Block();
    }
    myBegin = 0;
    myEnd = 0;
    block_begin = 0;
    block_end = 0;
}
Deque::Deque(const Deque& other)
{
    this->block_begin = other.block_begin;
    this->block_end = other.block_end;
    this->myEnd = other.myEnd;
    this->myBegin = other.myBegin;
    this->mySize=other.mySize;
    this->capacity=other.capacity;
    this->arr_ptr = other.arr_ptr;
}
Deque::~Deque()
{
    for (int i = 0; i < capacity / block_size; i++)
    {
        delete arr_ptr[i];
    }
}
void Deque::resize()
{
    int tmp = capacity;
    capacity = (mySize / block_size) * block_size * 2;
    Block** tmp_arr_ptr = new Block * [capacity];
    int i = 0;
    while (block_begin != block_end)
    {
        tmp_arr_ptr[i] = arr_ptr[block_begin];
        block_begin++;
        i++;
        if (block_begin == tmp / block_size)
        {
            block_begin = 0;
        }
    }
    tmp_arr_ptr[i] = arr_ptr[block_begin];
    i++;
    mySize = i;
    block_begin = 0;
    block_end = mySize - 1;
    while (i != capacity / block_size)
    {
        tmp_arr_ptr[i] = new Block();
        i++;
    }
    arr_ptr = tmp_arr_ptr;
    delete[] tmp_arr_ptr;
}
void Deque::push_back(int value)
{
    (*arr_ptr[block_end]).arr[myEnd] = value;
    if (myEnd == block_size - 1)
    {
        if (block_end == capacity / block_size - 1)
        {
            if (block_begin == 0)
            {
                resize();
            }
            else
            {
                block_end = 0;
            }
        }
        else
        {
            block_end++;
        }
        myEnd = 0;
    }
    else
    {
        myEnd++;
    }
    mySize++;
}
void Deque::push_front(int value)
{
    if (myBegin == 0)
    {
        if (block_begin == 0)
        {
            if (block_end == capacity / block_size - 1)
            {
                resize();
            }
            else
            {
                block_begin = capacity / block_size - 1;
            }
        }
        else
        {
            block_begin--;
        }
        myBegin = capacity / block_size - 1;
    }
    else
    {
        myBegin--;
    }
    mySize++;
    (*arr_ptr[block_begin]).arr[myBegin] = value;
}
void Deque::pop_back()
{
    myEnd--;
    if (myEnd == -1)
    {
        block_end--;
        if (block_end == -1)
        {
            block_end = capacity / block_size - 1;
        }
        myEnd = block_size - 1;
    }
    mySize--;
}
void Deque::pop_front()
{
    myBegin++;
    if (myBegin == block_size)
    {
        block_begin++;
        if (block_begin == capacity / block_size)
        {
            block_begin = 0;
        }
        myBegin = 0;
    }
    mySize--;
}
void Deque::clear()
{
    for (int i = 0; i < capacity / block_size; i++)
    {
        delete arr_ptr[i];
    }

    mySize = 0;
    capacity = block_size * 4;
    arr_ptr = new Block * [4];
    for (int i = 0; i < 4; i++)
    {
        arr_ptr[i] = new Block();
    }
    myBegin = 0;
    myEnd = 0;
    block_begin = 0;
    block_end = 0;
}
int Deque::size()
{
    return mySize;
}
bool Deque::empty()
{
    if (mySize == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int Deque::operator[](int value)
{
    int x = value + myBegin;
    int indexBlock = block_begin;
    while (x >= block_size)
    {
        indexBlock++;
        x -= block_size;
        if (indexBlock == mySize)
        {
            indexBlock = 0;
        }
    }
    return (*arr_ptr[indexBlock]).arr[x];
}
Deque::Iterator Deque::begin()
{
    return Iterator(this, this->arr_ptr[block_begin], &this->arr_ptr[block_begin]->arr[myBegin]);
}
Deque::Iterator Deque::end()
{
    return Iterator(this, this->arr_ptr[block_end], &this->arr_ptr[block_end]->arr[myEnd]);
}

int main()
{
    return 0;
}
