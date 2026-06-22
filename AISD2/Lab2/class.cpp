#include <iostream>
#include <chrono>
#include <random>
#include <cmath>
using namespace std;

template <typename V>
class hashtable
{
private:
    struct Node
    {
        int _key;
        V _value;
        bool _is_deleted;
        Node(const V &value, const int &key) : _value(value), _is_deleted(false), _key(key) {}
        Node() : _key(0), _is_deleted(true) {}
    };
    
    Node* arr;
    size_t _size = 0;
    size_t _capacity;
    double A = 0.6180339887498949;

    size_t hash_funk(const int &key, size_t attempt) const
    {
        size_t hash_value = static_cast<size_t>(std::abs(key));
        double product = hash_value * A;
        double fractional = product - (long long)product;
        size_t main_hash = static_cast<size_t>(_capacity * fractional);
        return (main_hash + attempt) % _capacity;
    }

    void resize()
    {
        size_t old_capacity = _capacity;
        Node* old_arr = arr;
        _capacity = _capacity * 2;
        arr = new Node[_capacity];
        for (size_t i = 0; i < _capacity; i++)
        {
            arr[i]._is_deleted = true;
            arr[i]._key = 0;
        }
        size_t old_size = _size;
        _size = 0;
        for (size_t i = 0; i < old_capacity; i++)
        {
            if (!old_arr[i]._is_deleted)
            {
                insert(old_arr[i]._key, old_arr[i]._value);
            }
        }
        
        delete[] old_arr;
    }

public:
    size_t size() const { return _size; }
    bool empty() const { return _size == 0; }

    hashtable() : _capacity(16)
    {
        arr = new Node[_capacity];
        for (size_t i = 0; i < _capacity; i++)
        {
            arr[i]._is_deleted = true;
            arr[i]._key = 0;
        }
        _size = 0;
    }

    hashtable(size_t size) : _capacity(size)
    {
        arr = new Node[_capacity];
        for (size_t i = 0; i < _capacity; i++)
        {
            arr[i]._is_deleted = true;
            arr[i]._key = 0;
        }
        _size = 0;
    }

    hashtable(size_t size, int num_elements, unsigned int seed, double min_val, double max_val) : _capacity(size)
    {
        mt19937 gen(seed);
        uniform_int_distribution<> key_dist(0, 9999);
        uniform_real_distribution<> val_dist(min_val, max_val);
        
        arr = new Node[_capacity];
        for (size_t i = 0; i < _capacity; i++)
        {
            arr[i]._is_deleted = true;
            arr[i]._key = 0;
        }
        _size = 0;
        
        for (int i = 0; i < num_elements; i++)
        {
            int key = key_dist(gen);
            double value = val_dist(gen);
            insert(key, value);
        }
    }

    hashtable(const hashtable<V> &other)
    {
        A = other.A;
        _size = other._size;
        _capacity = other._capacity;
        
        arr = new Node[_capacity];
        for (size_t i = 0; i < _capacity; i++)
        {
            if (!other.arr[i]._is_deleted)
            {   
                arr[i]._key = other.arr[i]._key;
                arr[i]._value = other.arr[i]._value;
                arr[i]._is_deleted = false;
            }
            else
            {
                arr[i]._is_deleted = true;
                arr[i]._key = 0;
            }
        }
    }

    ~hashtable()
    {
        delete[] arr;
    }

    hashtable<V>& operator=(const hashtable<V> &other)
    {
        if (this != &other)
        {
            delete[] arr;
            
            A = other.A;
            _size = other._size;
            _capacity = other._capacity;
            
            arr = new Node[_capacity];
            for (size_t i = 0; i < _capacity; i++)
            {
                if (!other.arr[i]._is_deleted)
                {
                    arr[i]._key = other.arr[i]._key;
                    arr[i]._value = other.arr[i]._value;
                    arr[i]._is_deleted = false;
                }
                else
                {
                    arr[i]._is_deleted = true;
                    arr[i]._key = 0;
                }
            }
        }
        return *this;
    }

    bool insert(int key, const V &value)
    {
        while (true)
        {
            for (size_t attempt = 0; attempt < _capacity; attempt++)
            {
                size_t index = hash_funk(key, attempt);
                
                if (arr[index]._is_deleted)
                {
                    arr[index]._key = key;
                    arr[index]._value = value;
                    arr[index]._is_deleted = false;
                    _size++;
                    return true;
                }
                
                if (arr[index]._key == key && !arr[index]._is_deleted)
                {
                    return false;
                }
            }
            
            resize();
        }
    }

    bool insert_or_assign(int key, const V &value)
    {
        while (true)
        {
            for (size_t attempt = 0; attempt < _capacity; attempt++)
            {
                size_t index = hash_funk(key, attempt);
                
                if (arr[index]._is_deleted)
                {
                    arr[index]._key = key;
                    arr[index]._value = value;
                    arr[index]._is_deleted = false;
                    _size++;
                    return true;
                }
                
                if (arr[index]._key == key && !arr[index]._is_deleted)
                {
                    arr[index]._value = value;
                    return false;
                }
            }
            
            resize();
        }
    }

    V* search(int key)
    {
        for (size_t attempt = 0; attempt < _capacity; attempt++)
        {
            size_t index = hash_funk(key, attempt);
            
            if (arr[index]._is_deleted)
                continue;
            
            if (arr[index]._key == key)
                return &(arr[index]._value);
        }
        return nullptr;
    }

    bool erase(int key)
    {
        for (size_t attempt = 0; attempt < _capacity; attempt++)
        {
            size_t index = hash_funk(key, attempt);
            
            if (arr[index]._is_deleted)
                continue;
            
            if (arr[index]._key == key)
            {
                arr[index]._is_deleted = true;
                _size--;
                return true;
            }
        }
        return false;
    }

    bool contain(const V &value) const
    {
        for (size_t i = 0; i < _capacity; i++)
        {
            if (!arr[i]._is_deleted && arr[i]._value == value)
                return true;
        }
        return false;
    }

    int count(int key) const
    {
    size_t target_hash = hash_funk(key, 0);
    int counter = 0;
    for (size_t i = 0; i < _capacity; i++)
    {
        if (!arr[i]._is_deleted)
        {
            if (hash_funk(arr[i]._key, 0) == target_hash)
                counter++;
        }
    }
    return counter;
    }

    void print() const
    {
        for (size_t i = 0; i < _capacity; i++)
        {
            cout << "  [" << i << "] ";
            if (arr[i]._is_deleted)
                cout << "deleted\n";
            else
                cout << "key=" << arr[i]._key << ", value=" << arr[i]._value << "\n";
        }
    }
};