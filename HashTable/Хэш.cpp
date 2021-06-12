#include <iostream>
#include <vector>
#include <string>
#include <forward_list>
using namespace std;

template <typename Key, typename Value, typename Hasher = std::hash<Key>>
class HashTable
{
public:
	HashTable(int Size, const int SizeBatch);
	~HashTable();
	void insert(const Key key, Value value);
	void erase(Key key);
	bool contains(Key key);
	void clear();
	void rehash(int n);
	HashTable& operator=(const HashTable& x)
	{
		Size = x.Size;
		arr = new std::forward_list<std::pair<const Key, Value>>[Size];
		for (int i = 0; i < Size; i++)
		{
			for (auto it : x.arr[i])
			{
				insert(it.first, it.second);
			}
		}
		return *this;
	}
private:
	Hasher Hash;
	int Size;
	const int SizeBatch;
	std::forward_list<std::pair<const Key, Value>>* arr;
};
template <typename Key, typename Value, typename Hasher >
HashTable<Key, Value, Hasher>::HashTable(int Size, const int SizeBatch)
{
	this->Size = Size;
	this->SizeBatch = SizeBatch;
	arr = new std::forward_list<std::pair<const Key, Value>>[Size];
}
template <typename Key, typename Value, typename Hasher >
HashTable<Key, Value, Hasher>::~HashTable()
{
	delete[] arr;
}
template <typename Key, typename Value, typename Hasher >
void HashTable<Key, Value, Hasher>::clear()
{
	delete[] arr;
	Size = 1;
	arr = new std::forward_list<std::pair<const Key, Value>>[Size];
}
template <typename Key, typename Value, typename Hasher >
void HashTable<Key, Value, Hasher>::insert(const Key key,Value value)
{
	int pos = Hash(key) % Size;
	int n = 0;
	for(auto it: arr[pos])
	{
		if (it.first==key)
		{
			throw std::runtume_error("There can be no two identical keys");
		}
		n++;
	}
	if (n>=SizeBatch)
	{
		rehash(2 * Size);
	}
	arr[pos].push_front(std::pair<const Key, Value>(key,value));
}
template <typename Key, typename Value, typename Hasher >
void HashTable<Key, Value, Hasher>::rehash(int n)
{
	std::forward_list<std::pair<const Key, Value>>* tmpArr=arr;
	arr = new std::forward_list<std::pair<const Key, Value>>[n];
	int tmpSize = Size;
	Size = n;
	for (int i = 0; i < tmpSize; i++)
	{
		for (auto it: tmpArr[i])
		{
			insert(it.first, it.second);
		}
	}
	delete[] tmpArr;
}
template <typename Key, typename Value, typename Hasher >
bool HashTable<Key, Value, Hasher>::contains(const Key key)
{
	bool tr = false;
	int pos = Hash(key) % Size;
	for (auto it : arr[pos])
	{
		if (it.first==key)
		{
			tr = true;
		}
	}
	return tr;
}

int main()
{
    
    return 0;
}