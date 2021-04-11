#include <iostream>
#include <utility>
using namespace std;

template < typename T >
class Tree
{
public:
    struct Node
    {
        pair<T,int > data;
        Node* left, * right;
        Node(T value, int key)
        {
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
private:
    int my_size;
    Node* my_root;
    Node* find(Node* node, int key);
    void insert(Node* node, T value, int key);
    void erase(Node* node, int key);
};
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
typename Tree<T>::Node* Tree<T>::find(Node* node,int key)
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
void Tree<T>::insert(T value,int key)
{
    if (my_root==nullptr)
    {
        my_root = new Node(value, key);
        my_size++;
    }
    else
    {
        insert(my_root, value, key);
    }
}
template < typename T >
void Tree<T>::insert(Node* node, T value,int key)
{
    if (key<node->data.second)
    {
        if (node->left==nullptr)
        {
            node->left = new Node(value,key);
        }
        else
        {
            node->left = insert(node->left, value, key);
        }
    }
    else (key > node->data.second)
    {
        if (node->right == nullptr)
        {
            node->right = new Node(value, key);
        }
        else
        {
            node->right = insert(node->right, value, key);
        }
    }
}
template < typename T >
void Tree<T>::erase(int key)
{
    if (my_root!=nullptr)
    {
        erase(my_root, key);
    }
}
template < typename T >
void Tree<T>::erase(Node* node,int key)
{
    if (node->data.second < my_root->key)
    {

    }
}


int main()
{
    return 0;
}