#include <iostream>
#include <vector>
#include <functional>
using namespace std;

template <typename T>
struct node
{
    T data;
    node<T> *next;
    node<T>(T x) : data{x}, next{} {}
    node<T>(T x, node<T> *n) : data{x}, next{n} {}
};

template <typename T>
class linked_list
{
    node<T> *head, *tail;
    int length;

public:
    linked_list<T>() : head{}, tail{}, length{} {}
    linked_list<T>(int x) : length{1} { head = tail = new node<T>(x); }
    ~linked_list<T>()
    {
        node<T> *temp{head};
        while (head)
        {
            head = head->next;
            delete temp;
            temp = head;
        }
    }
    void display() const
    {
        node<T> *temp{head};
        while (temp)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
    void get_head() const { cout << "head = " << head->data << endl; }
    void get_tail() const { cout << "tail = " << tail->data << endl; }
    void get_length() const { cout << "length = " << length << endl; }
    vector<int> find_all(T x) const
    {
        vector<int> vt;
        node<T> *temp{head};
        for (int i{}; temp != nullptr; temp = temp->next, ++i)
            if (temp->data == x)
                vt.push_back(i);
        return vt;
    }
    int find(T x) const // find first node
    {
        if (length == 0 || find_all(x).empty())
            return -1;
        else
            return find_all(x)[0];
    }
    linked_list<T> &append(T x)
    {
        if (length == 0)
            head = tail = new node<T>(x);
        else
        {
            tail->next = new node<T>(x);
            tail = tail->next;
        }
        ++length;
        return *this;
    }
    linked_list<T> &prepend(T x)
    {
        if (length == 0)
            head = tail = new node<T>(x);
        else
        {
            node<T> *temp{new node<T>(x)};
            temp->next = head;
            head = temp;
        }
        ++length;
        return *this;
    }
    linked_list<T> &insert(T x, int index)
    {
        if (index < 0 || index >= length)
            return *this;
        if (index == 0)
            return prepend(x);
        node<T> *temp{head};
        for (int i{1}; i < index; ++i)
            temp = temp->next;
        node<T> *n{new node<T>{x, temp->next}};
        temp->next = n;
        length++;
        return *this;
    }
    linked_list<T> &remove(T x) // remove 1st node only
    {
        if (length == 0)
            return *this;
        if (length == 1)
        {
            length = 0;
            delete head;
            head = tail = nullptr;
            return *this;
        }
        node<T> *temp{head};
        while (temp->next->data != x)
            temp = temp->next;
        node<T> *n{temp->next};
        temp->next = temp->next->next;
        delete n;
        length--;
        return *this;
    }
    linked_list<T> &remove_all(T x)
    {
        while (!find_all(x).empty())
        {
            if (length == 0)
                return *this;
            if (length == 1)
            {
                length = 0;
                delete head;
                head = tail = nullptr;
                return *this;
            }
            node<T> *temp{head};
            while (temp->next->data != x)
                temp = temp->next;
            node<T> *n{temp->next};
            temp->next = temp->next->next;
            delete n;
            length--;
        }
        return *this;
    }
    linked_list<T> &remove_last()
    {
        if (length == 0)
            return *this;
        if (length == 1)
        {
            length = 0;
            delete head;
            head = tail = nullptr;
            return *this;
        }
        node<T> *temp{head};
        while (temp->next != tail)
            temp = temp->next;
        delete tail;
        tail = temp;
        tail->next = nullptr;
        length--;
        return *this;
    }
    linked_list<T> &remove_first()
    {
        if (length == 0)
            return *this;
        if (length == 1)
        {
            length = 0;
            delete head;
            head = tail = nullptr;
            return *this;
        }
        node<T> *temp{head};
        head = head->next;
        delete temp;
        length--;
        return *this;
    }
    linked_list<T> &reverse()
    {
        node<T> *n{head};
        head = tail;
        tail = n;

        node<T> *temp{tail}, *before{}, *after{temp->next};
        while (after)
        {
            after = temp->next;
            temp->next = before;
            before = temp;
            temp = after;
        }
        return *this;
    }
    linked_list<T> &swap(int m, int n)
    {
        if (length < 2 || m == n || m >= length || m < 0 || n >= length || n < 0)
            return *this;

        node<T> *before_a{}, *a{head};
        for (int i{}; i < m; ++i)
        {
            before_a = a;
            a = a->next;
        }
        node<T> *before_b{}, *b{head};
        for (int i{}; i < n; ++i)
        {
            before_b = b;
            b = b->next;
        }

        if (before_a)
            before_a->next = b;
        else
            head = b; // If swapping the head node

        if (before_b)
            before_b->next = a;
        else
            head = a; // If swapping the head node

        node<T> *temp{a->next};
        a->next = b->next;
        b->next = temp;

        return *this;
    }
    node<T> *at(int index) const
    {
        if (index < 0 || index >= length)
            return nullptr;
        node<T> *temp{head};
        for (int i{}; i < index; ++i)
            temp = temp->next;
        return temp;
    }
    linked_list &sort(function<bool(const T &a, const T &b)> predicate)
    {
        for (int i{}; i < length - 1; ++i)
        {
            bool swapped{false};
            for (int j{}; j < length - 1 - i; ++j)
                if (!predicate(at(j)->data, at(j + 1)->data))
                {
                    this->swap(j, j + 1);
                    swapped = true;
                }
            if (!swapped)
                break;
        }
        return *this;
    }
};

int main()
{
    linked_list<char> ll{'a'};
    ll.append('c').append('d').append('e').append('f').append('g').append('h');
    ll.display();
    ll.get_length();
    ll.remove_last();
    ll.display();
    ll.get_length();
    ll.remove_first();
    ll.display();
    ll.get_length();
    ll.prepend('x');
    ll.display();
    ll.get_length();
    ll.at(3)->data = 'q';
    ll.display();
    ll.get_length();
    ll.insert('m', 1).insert('m', 1);
    ll.display();
    ll.get_length();
    ll.remove_all('m');
    ll.display();
    ll.get_length();
    ll.reverse().reverse();
    ll.display();
    ll.swap(4, 1);
    ll.display();
    ll.swap(0, 4).swap(4, 0);
    ll.swap(1, 2);
    ll.display();
    ll.sort(less<char>());
    ll.display();
}
