#include <iostream>
#include <utility>
#include <iterator>
using namespace std;

template < typename T >
class Tree
{
public:
    struct Node
    {
        pair<T, int > data;
        Node* left, * right,*next,*prev;
        Tree<T>* tree;
        Node(T value, int key)
        {
            this->next = nullptr;
            this->prev = nullptr;
            data.first = value;
            data.second = key;
            this->left = this->right = nullptr;
        }
    };
    Tree();
    ~Tree();
    void clear();
    int size();
    bool empty();
    void RecursiveDeleteNode(Node* node);
    void insert(T value, int key);
    void erase(int key);
    Node* find(int key);
    Node* next(int key);
    Node* prev(int key);
    class Iterator :iterator<bidirectional_iterator_tag, int >
    {
    public:
        Iterator() : object(nullptr)
        {
        }
        Iterator(const Iterator& other) : object(other.object)
        {
        }
        Iterator(Node* value) : object(value)
        {
        }
        Node* operator->()
        {
            return &object->data;
        }
        Iterator& operator++()
        {
            object = object->next;
            return *this;
        }
        Iterator& operator++(int)
        {
            Iterator tmp = *this;
            object = object->next;
            return tmp;
        }
        Iterator& operator--()
        {
            object = object->prev;
            return *this;
        }
        Iterator& operator--(int)
        {
            Iterator tmp = *this;
            object = object->prev;
            return tmp;
        }
        int& operator*()
        {
            return object->data.second;
        }
        int operator*() const
        {
            return object->data.second;
        }
        bool operator==(const Iterator& rhs) const
        {
            return object == rhs.object;
        }
        bool operator!=(const Iterator& rhs) const
        {
            return object != rhs.object;
        }
        template<typename T>
        T& operator[](int key) 
        {
            Node* node = find(my_root, key);
            return node->data.first;
        }
    private:
        Node* object;
    };
    Iterator begin();
    Iterator end();
private:
    int my_size;
    Node* my_root;
    Node* find(Node* node, int key);
    void insert(Node* node, T value, int key);
    void erase(Node* node, int key);
    void erase(Node* node, int key, Node* parent);
};
template < typename T >
typename Tree<T>::Iterator Tree<T>::begin()
{
    Node* tmpNode = my_root;
    while (tmpNode->left != nullptr)
    {
        tmpNode = tmpNode->left;
    }
    return Iterator(tmpNode);
}
template < typename T >
typename Tree<T>::Iterator Tree<T>::end()
{
    Node* tmpNode = my_root;
    while (tmpNode->right != nullptr)
    {
        tmpNode = tmpNode->right;
    }
    return Iterator(tmpNode);
}
template < typename T >
Tree<T>::Tree()
{
    my_size = 0;
    my_root = nullptr;
}
template < typename T >
Tree<T>::~Tree()
{
    RecursiveDeleteNode(my_root);
}
template < typename T >
void Tree<T>::clear()
{
    RecursiveDeleteNode(my_root);
}
template < typename T >
int Tree<T>::size()
{
    return my_size;
}
template < typename T >
void Tree<T>::RecursiveDeleteNode(Node* node)
{
    if (node)
    {
        RecursiveDeleteNode(node->left);
        RecursiveDeleteNode(node->right);
        delete node;
    }
}
template < typename T >
bool Tree<T>::empty()
{
    return (my_size == 0);
}
template < typename T >
typename Tree<T>::Node* Tree<T>::find(Node* node, int key)
{
    if (key == node->data.second)
    {
        return node;
    }
    if (key < node->data.second)
    {
        if (node->left == nullptr)
        {
            return find(node->left, key);
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        if (node->right == nullptr)
        {
            return find(node->right, key);
        }
        else
        {
            return nullptr;
        }
    }
}
template < typename T >
typename Tree<T>::Node* Tree<T>::find(int key)
{
    if (my_root == nullptr || key == my_root->key)
    {
        return my_root;
    }
    if (key < my_root->key)
    {
        return find(my_root->left, key);
    }
    else
    {
        return find(my_root->right, key);
    }
}
template < typename T >
typename Tree<T>::Node* Tree<T>::next(int key)
{
    Node* now = my_root, tmp = nullptr;
    while (now != nullptr)
    {
        if (now->data.second > key)
        {
            tmp = now;
            now = tmp->left;
        }
        else
        {
            now = now->right;
        }
    }
    return tmp;
}
template < typename T >
typename Tree<T>::Node* Tree<T>::prev(int key)
{
    Node* now = my_root, tmp = nullptr;
    while (now != nullptr)
    {
        if (now->data.second < key)
        {
            tmp = now;
            now = tmp->right;
        }
        else
        {
            now = now->left;
        }
    }
    return tmp;
}
template < typename T >
void Tree<T>::insert(T value, int key)
{
    if (my_root == nullptr)
    {
        my_root = new Node(value, key);
        my_root->tree = this;
        my_size++;
    }
    else
    {
        insert(my_root, value, key);
    }
}
template < typename T >
void Tree<T>::insert(Node* node, T value, int key)
{
    if (key < node->data.second)
    {
        if (node->left == nullptr)
        {
            node->left = new Node(value, key);
            node->left->tree = this;
            node->left->next = next(node->left->key);
            node->left->prev = prev(node->left->key);
            node->left->next->prev = node->left;
            node->left->prev->next = node->left;
        }
        else
        {
            insert(node->left, value, key);
        }
    }
    else if (key > node->data.second)
    {
        if (node->right == nullptr)
        {
            node->right = new Node(value, key);
            node->right->tree = this;
            node->right->next = next(node->right->key);
            node->right->prev = prev(node->right->key);
            node->right->next->prev = node->right;
            node->right->prev->next = node->right;
        }
        else
        {
            insert(node->right, value, key);
        }
    }
}
template < typename T >
void Tree<T>::erase(int key)
{
    if (my_root != nullptr)
    {
        erase(my_root, key);
    }
}
template < typename T >
void Tree<T>::erase(Node* node, int key)
{
    if (node->data.second > key)
    {
        erase(my_root->left, key, my_root);
    }
    else if (node->data.second < key)
    {
        erase(my_root->right, key, my_root);
    }
}
template < typename T >
void Tree<T>::erase(Node* node, int key, Node* parent)
{
    if (node->data.second < key)
    {
        erase(node->right, key, node);
    }
    if (node->data.second > key)
    {
        erase(node->left, key, node);
    }
    if (node->data.second == key)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        if (node->left == nullptr && node->right == nullptr)
        {
            if (parent->left == node)
            {
                parent->left = nullptr;
                delete node;
                size--;
            }
            if (parent->right == node)
            {
                parent->right = nullptr;
                delete node;
                size--;
            }
        }
        if (node->left != nullptr && node->right != nullptr)
        {
            Node* tmpNode = node->right;
            Node* tmpParent = node;
            while (tmpNode->left != nullptr)
            {
                tmpNode = tmpNode->left;
                tmpParent = tmpNode;
            }
            int tmp = tmpNode->data.second;
            erase(tmpNode, tmp, tmpParent);
            node->data.second = tmp;
        }
        if ((node->left != nullptr && node->right == nullptr) || (node->left == nullptr && node->right != nullptr))
        {
            if (node->left != nullptr)
            {
                if (parent->left == node)
                {
                    parent->left = node->left;
                    delete node;
                    size--;
                }
                if (parent->right == node)
                {
                    parent->right = node->left;
                    delete node;
                    size--;
                }
            }
            if (node->right != nullptr)
            {
                if (parent->left == node)
                {
                    parent->left = node->right;
                    delete node;
                    size--;
                }
                if (parent->right == node)
                {
                    parent->right = node->right;
                    delete node;
                    size--;
                }
            }
        }
    }
}

int main()
{
    return 0;
}