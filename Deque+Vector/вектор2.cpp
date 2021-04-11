#include <iostream>
#include <iterator>
#include <string>

using namespace std;
class vector 
{
public:
    class Iterator;
    vector(int size);
    ~vector();
    vector(const vector& other);
    void input();
    void output();
    int size();
    int capasity();
    void push_back(int value);
    void insert(int index, int value);
    void erase(int index);
    void clear();
    void pop_back();
    int index_off(int value);
    bool empty();
    void resize(int n);
    Iterator begin();
    Iterator end();
    vector& operator = (const vector& other) 
    {
        this->Size = other.Size;
        if (this->vec != nullptr)
        {
            delete this->vec;
        }
        this->vec = new int[other.Size];
        for (int i = 0; i < other.Size; i++)
        {
            this->vec[i] = other.vec[i];
        }
        return *this;
    }
    class Iterator :iterator<random_access_iterator_tag, int>
    {
    private:
        int* object;
    public:
        Iterator() : object(nullptr)
        {
        }
        Iterator(const Iterator& other) : object(other.object) 
        {
        }
        explicit Iterator(int* value) : object(value)
        {
        }
        int* operator->()
        {
            return object;
        }
        Iterator& operator++()
        {
            object++;
            return *this;
        }
        Iterator& operator++(int)
        {
            object++;
            return *this;
        }
        Iterator& operator--(int)
        {
            object--;
            return *this;
        }
        Iterator& operator--()
        {
            object--;
            return *this;
        }
        int& operator*()
        {
            return *object;
        }
        int operator*() const
        {
            return *object;
        }
        bool operator==(const Iterator& rhs) const
        {
            return object == rhs.object;
        }
        bool operator!=(const Iterator& rhs) const
        {
            return object != rhs.object;
        }
        bool operator>(const Iterator& rhs) const
        {
            return object > rhs.object;
        }
        bool operator<(const Iterator& rhs) const
        {
            return object < rhs.object;
        }
        bool operator<=(const Iterator& rhs) const
        {
            return object <= rhs.object;
        }
        bool operator>=(const Iterator& rhs) const
        {
            return object >= rhs.object;
        }
        Iterator& operator+=(const int& rhs)
        {
            object += rhs;
            return *this;
        }
        Iterator& operator-=(const int& rhs)
        {
            object -= rhs;
            return *this;
        }
        Iterator& operator-(const int& rhs)
        {
            object -= rhs;
            return *this;
        }
        friend Iterator operator+(const int& n, const Iterator& rhs)
        {
            return Iterator(rhs.object + n);
        }
        friend Iterator operator+(const Iterator& rhs, const int& n)
        {
            return Iterator(rhs.object + n);
        }
    };
private:
    int* vec;
    int Size;
    int Capacity;
};
vector::Iterator vector::begin()
{
    return Iterator(vec);
}
vector::Iterator vector::end()
{
    return Iterator(vec+Size);
}
void vector:: resize(int n)
{
    if (Capacity<n)
    {
        Size = n;
        Capacity = n * 2;
        int* tmp = new int[Capacity];
        for (int i = 0; i < Size; i++)
        {
            tmp[i] = vec[i];
        }
        delete[] vec;
        vec = tmp;
    }
}
bool vector:: empty()
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
int vector:: index_off(int value)
{
    for (int i = 0; i < Size; i++)
    {
        if (vec[i] == value)
        {
            return i;
        }
    }
    return -1;
}
void vector:: pop_back()
{
    if (Size)
    {
        Size--;
    }
    else
    {
        cout << "error";
        return;
    }
}
vector:: vector(int size)
{
    this->vec = new int[size];
    this->Size = size;
    Capacity = size;
    input();
}
vector:: ~vector()
{
    delete[] vec;
}
vector:: vector(const vector& other)
{
    this->Size = other.Size;
    this->Capacity = other.Capacity;
    this->vec = new int[other.Size];
    for (int i = 0; i < other.Size; i++)
    {
        this->vec[i] = other.vec[i];
    }
}
void vector:: input()
{
    for (int i = 0; i < Size; i++)
    {
        cin >> vec[i];
    }
}
void vector:: output()
{
    for (int i = 0; i < Size; i++)
    {
        cout << vec[i];
    }
}
int vector:: size()
{
    return Size;
}
int vector:: capasity()
{
    return Capacity;
}
void vector:: push_back(int value)
{
    if (Capacity == Size)
    {
        Capacity *= 2;
        int* tmp = new int[Capacity];
        for (int i = 0; i < Size; i++)
        {
            tmp[i] = vec[i];
        }
        delete[] vec;
        vec = tmp;
    }
    vec[Size] = value;
    Size++;
}
void vector:: insert(int index, int value)
{
    if (index >= Size || index < 0)
    {
        cout << "error";
        return;
    }
    else
    {
        if (Capacity == Size)
        {
            Capacity *= 2;
            int* tmp = new int[Capacity];
            for (int i = 0; i < Size; i++)
            {
                tmp[i] = vec[i];
            }
            delete[] vec;
            vec = tmp;
        }
        for (int i = Size; i > index; i--)
        {
            vec[i] = vec[i - 1];
        }
        vec[index] = value;
        Size++;
    }
}
void vector:: erase(int index)
{
    if (index >= Size || index < 0)
    {
        cout << "error";
        return;
    }
    else
    {
        for (int i = index; i < Size - 1; i++)
        {
            vec[i] = vec[i + 1];
        }
        pop_back();
    }
}
void vector:: clear()
{
    while (Size)
    {
        pop_back();
    }
}

int main()
{
    return 0;
}