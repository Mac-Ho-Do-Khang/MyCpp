#include <iostream>
#include <vector>
#include <functional>

using namespace std;

template <typename T>
struct node
{
    T data;
    node<T> *next, *prev;
    node<T>(T x) : data{x}, next{}, prev{} {}
    node<T>(T x, node<T> *n, node<T> *p) : data{x}, next{n}, prev{p} {}
};

template <typename T>
class linked_list
{
    node<T> *head, *tail;
    int length;

public:
    linked_list<T>() : length{}, head{}, tail{} {}
    linked_list<T>(T x) : length{1} { head = tail = new node{x}; }
    ~linked_list()
    {
        node<T> *temp{head};
        while (head)
        {
            head = head->next;
            delete temp;
            temp = head;
        }
    }
    void get_length() const { cout << "length = " << length << endl; }
    void display(bool reverse = false) const
    {
        if (reverse)
        {
            node<T> *temp{tail};
            while (temp)
            {
                cout << temp->data << " -> ";
                temp = temp->prev;
            }
        }
        else
        {
            node<T> *temp{head};
            while (temp)
            {
                cout << temp->data << " -> ";
                temp = temp->next;
            }
        }
        cout << "NULL\n";
    }
    node<T> *operator[](int index)
    {
        if (index < 0 || index >= length)
            return nullptr;
        node<T> *temp{head};
        for (int i{}; i < index; ++i)
            temp = temp->next;
        return temp;
    }
    node<T> *at(int index)
    {
        if (index < 0 || index >= length)
            return nullptr;
        node<T> *temp{head};
        for (int i{}; i < index; ++i)
            temp = temp->next;
        return temp;
    }
    linked_list<T> &append(T x)
    {
        if (length == 0)

            head = tail = new node{x};

        else
        {
            node<T> *temp{new node{x}};
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
        length++;
        return *this;
    }
    linked_list<T> &prepend(T x)
    {
        if (length == 0)

            head = tail = new node{x};

        else
        {
            node<T> *temp{new node{x}};
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
        length++;
        return *this;
    }
    linked_list<T> &insert(T x, int index)
    {
        if (index < 0 || index > length)
            return *this;
        else if (index == 0)
        {
            prepend(x);
            return *this;
        }
        else if (index == length)
        {
            append(x);
            return *this;
        }

        node<T> *b{head};
        for (int i{}; i < index; ++i)
            b = b->next;
        node<T> *a{b->prev}, *temp{new node{x}};
        b->prev = temp;
        temp->next = b;
        a->next = temp;
        temp->prev = a;
        length++;
        return *this;
    }
    vector<int> find_all(T x) const
    {
        vector<int> vt;
        node<T> *temp{head};
        int i{};
        while (temp)
        {
            if (temp->data == x)
                vt.push_back(i);
            ++i;
            temp = temp->next;
        }
        // cout << "<" << x << "> : ";
        // for (int v : vt)
        //     cout << v << ", ";
        // cout << endl;
        return vt;
    }
    int find(T x) const
    {
        if (find_all(x).size() == 0)
            return -1;
        else
            return find_all(x)[0];
    }
    linked_list<T> &remove_first()
    {
        if (length == 0)
            ;
        else if (length == 1)
        {
            delete head;
            head = tail = nullptr;
            length = 0;
        }
        else
        {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
            length--;
        }
        return *this;
    }
    linked_list<T> &remove_last()
    {
        if (length == 0)
            ;
        else if (length == 1)
        {
            delete head;
            head = tail = nullptr;
            length = 0;
        }
        else
        {
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
            length--;
        }
        return *this;
    }
    linked_list<T> &remove_at(int index)
    {
        if (index < 0 || index >= length)
            return *this;
        else if (index == 0)
            return remove_first();
        else if (index == length - 1)
            return remove_last();

        node<T> *temp = head;
        for (int i{}; i < index; ++i)
            temp = temp->next;
        node<T> *before_temp{temp->prev};
        before_temp->next = temp->next;
        temp->next->prev = before_temp;
        delete temp;
        length--;
        return *this;
    }
    linked_list<T> &remove(T x)
    {
        return remove_at(find(x));
    }
    linked_list<T> &remove_all(T x)
    {
        for (int i{find(x)}; i != -1; remove_at(i), i = find(x))
            ;
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
            temp->prev = after;
            before = temp;
            temp = after;
        }
        return *this;
    }
    linked_list<T> &swap(int m, int n)
    {
        if (length < 2 || m < 0 || n < 0 || m >= length || n >= length)
            return *this;

        node<T> *a{head}, *b{head};
        for (int i{}; i < m; ++i)
            a = a->next;
        for (int i{}; i < n; ++i)
            b = b->next;

        if (a->prev)
            a->prev->next = b;
        if (b->prev)
            b->prev->next = a;
        node<T> *temp_prev{a->prev};
        a->prev = b->prev;
        b->prev = temp_prev;

        if (a->next)
            a->next->prev = b;
        if (b->next)
            b->next->prev = a;
        node<T> *temp_next{a->next};
        a->next = b->next;
        b->next = temp_next;

        if (head == a)
            head = b;
        else if (head == b)
            head = a;

        if (tail == a)
            tail = b;
        else if (tail == b)
            tail = a;

        return *this;
    }
    linked_list<T> &sort(function<bool(T a, T b)> predicate = less<T>())
    {
        for (int i{}; i < length; ++i)
        {
            bool swapped{false};
            for (int j{}; j < length - i - 1; ++j)
                if (!predicate(at(j)->data, at(j + 1)->data))
                {
                    swap(j, j + 1);
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
    linked_list<char> ll{};
    ll.append('a').append('c').append('e').append('g').append('k');
    ll.display();
    ll.swap(1, 4).swap(4, 1).swap(0, 1).swap(2, 3);
    ll.display();
    ll.sort(greater<char>());
    ll.display(true);
}