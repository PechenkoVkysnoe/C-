#include <iostream>
#include <utility>
#include <iterator>
using namespace std;

class Tree
{
public:
    struct Node
    {
        int key;
        Node* left, * right;
        Tree* tree;
        Node(int key)
        {
            this->key= key;
            this->left = this->right = nullptr;
        }
    };
    Tree();
    ~Tree();
    void clear();
    int size();
    bool empty();
    void RecursiveDeleteNode(Node* node);
    void insert(int key);
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
        int* operator->()
        {
            return &object->key;
        }
        Iterator& operator++()
        {
            object = object->tree->next(object->key);
            return *this;
        }
        Iterator& operator++(int)
        {
            Iterator tmp = *this;
            object = object->tree->next(object->key);
            return tmp;
        }
        Iterator& operator--()
        {
            object = object->tree->prev(object->key);
            return *this;
        }
        Iterator& operator--(int)
        {
            Iterator tmp = *this;
            object = object->tree->prev(object->key);
            return tmp;
        }
        int& operator*()
        {
            return object->key;
        }
        int operator*() const
        {
            return object->key;
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
    Iterator begin();
    Iterator end();
private:
    int my_size;
    Node* my_root;
    Node* find(Node* node, int key);
    void insert(Node* node, int key);
    void erase(Node* node, int key);
    void erase(Node* node, int key, Node* parent);
};
Tree::Iterator Tree::begin()
{
    Node* tmpNode = my_root;
    while (tmpNode->left != nullptr)
    {
        tmpNode = tmpNode->left;
    }
    return Iterator(tmpNode);
}
Tree::Iterator Tree::end()
{
    Node* tmpNode = my_root;
    while (tmpNode->right != nullptr)
    {
        tmpNode = tmpNode->right;
    }
    return Iterator(tmpNode);
}
Tree::Tree()
{
    my_size = 0;
    my_root = nullptr;
}
Tree::~Tree()
{
    RecursiveDeleteNode(my_root);
}
void Tree::clear()
{
    RecursiveDeleteNode(my_root);
}
int Tree::size()
{
    return my_size;
}
void Tree::RecursiveDeleteNode(Node* node)
{
    if (node)
    {
        RecursiveDeleteNode(node->left);
        RecursiveDeleteNode(node->right);
        delete node;
    }
}
bool Tree::empty()
{
    return (my_size == 0);
}
typename Tree::Node* Tree::find(Node* node, int key)
{
    if (key == node->key)
    {
        return node;
    }
    if (key < node->key)
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
typename Tree::Node* Tree::find(int key)
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
typename Tree::Node* Tree::next(int key)
{
    Node* now = my_root; 
    Node* tmp = nullptr;
    while (now != nullptr)
    {
        if (now->key > key)
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
typename Tree::Node* Tree::prev(int key)
{
    Node* now = my_root;
    Node* tmp = nullptr;
    while (now != nullptr)
    {
        if (now->key < key)
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
void Tree::insert(int key)
{
    if (my_root == nullptr)
    {
        my_root = new Node(key);
        my_root->tree = this;
        my_size++;
    }
    else
    {
        insert(my_root,key);
    }
}
void Tree::insert(Node* node, int key)
{
    if (key < node->key)
    {
        if (node->left == nullptr)
        {
            node->left = new Node(key);
            node->left->tree = this;
        }
        else
        {
            insert(node->left,key);
        }
    }
    else if (key > node->key)
    {
        if (node->right == nullptr)
        {
            node->right = new Node(key);
            node->right->tree = this;
        }
        else
        {
            insert(node->right,key);
        }
    }
}
void Tree::erase(int key)
{
    if (my_root != nullptr)
    {
        erase(my_root, key);
    }
}
void Tree::erase(Node* node, int key)
{
    if (node->key > key)
    {
        erase(my_root->left, key, my_root);
    }
    else if (node->key < key)
    {
        erase(my_root->right, key, my_root);
    }
}
void Tree::erase(Node* node, int key, Node* parent)
{
    if (node->key < key)
    {
        erase(node->right, key, node);
    }
    if (node->key > key)
    {
        erase(node->left, key, node);
    }
    if (node->key == key)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            if (parent->left == node)
            {
                parent->left = nullptr;
                delete node;
                my_size--;
            }
            if (parent->right == node)
            {
                parent->right = nullptr;
                delete node;
                my_size--;
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
            int tmp = tmpNode->key;
            erase(tmpNode, tmp, tmpParent);
            node->key = tmp;
        }
        if ((node->left != nullptr && node->right == nullptr) || (node->left == nullptr && node->right != nullptr))
        {
            if (node->left != nullptr)
            {
                if (parent->left == node)
                {
                    parent->left = node->left;
                    delete node;
                    my_size--;
                }
                if (parent->right == node)
                {
                    parent->right = node->left;
                    delete node;
                    my_size--;
                }
            }
            if (node->right != nullptr)
            {
                if (parent->left == node)
                {
                    parent->left = node->right;
                    delete node;
                    my_size--;
                }
                if (parent->right == node)
                {
                    parent->right = node->right;
                    delete node;
                    my_size--;
                }
            }
        }
    }
}

int main()
{
    return 0;
}