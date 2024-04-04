#pragma once
#include <iostream>
#include <sstream>
using namespace std;


template <class T>
struct RawNode2 {
    T            data;
    RawNode2<T>* prev;
    RawNode2<T>* next;

    RawNode2(T dataValue) {
        data = dataValue;
        prev = next = nullptr;
    }

    string toString() {
        stringstream sout;
        sout << this << " RawNode2 [prev: " << prev
            << ", next: " << next
            << ", data: " << data << "]";
        return sout.str();
    }
};
// ---------------------------------------------------------------

template <class T>
class RawList2 {
private:

    RawNode2<T>* head;
    RawNode2<T>* tail;
    int          size;

public:
    RawList2() {
        head = tail = nullptr;
        size = 0;
    }

    ~RawList2() {
        //TODO -Very important!!!
    }

    void addLast(T newData) {
        RawNode2<T>* pnew = new RawNode2<T>(newData);
        //Case1. Is the list empty?
        if (head == nullptr)
        {
            head = tail = pnew;
            size++;
            return;
        }

        //Case2. There is data already stored in the list
        pnew->prev = tail;
        tail->next = pnew;
        tail = pnew;
        size++;
    }


    void addFirst(T newData) {
        RawNode2<T>* pnew = new RawNode2<T>(newData);
        //Case1. Is the list empty?
        if (head == nullptr)
        {
            head = tail = pnew;
            size++;
            return;
        }

        //Case2. There is data already stored in the list
        pnew->next = head;
        head->prev = pnew;
        head = pnew;
        size++;
    }


    bool addAt(int index, T dataValue) {
        if (index > size) return false;

        if (index == 0) {
            addFirst(dataValue); return true;
        }

        if (index == size) {
            //insertat(tail->prev, dataValue); 
            addLast(dataValue);
            return true;
        }

        int pos = 0;
        auto p = head;
        while (pos < index) { p = p->next; pos++; }
        addAt(p->prev, dataValue);
        return true;
    }

    void addAt(RawNode2<T>* p, T dataValue) {
        //insert new node after p
        auto pnew = new RawNode2<T>(dataValue);
        pnew->next = p->next;
        p->next->prev = pnew;

        p->next = pnew;
        pnew->prev = p;

    }


    void showList() {
        cout << endl;
        cout << "Head: " << head << ", Tail: " << tail << ", Size: " << size << endl;
        RawNode2<T>* p = head;
        while (p != nullptr) {
            cout << p->toString() << endl;
            p = p->next;
        }
    }

    RawNode2<T>* find(T dataValue) {
        RawNode2<T>* p = head;
        while (p != nullptr) {
            if (p->data == dataValue) return p;
            p = p->next;
        }
        return nullptr;
    }

    bool remove(T dataValue) {
        auto p = find(dataValue);
        if (p == nullptr)
            return false;
        else {
            remove(p);
            return true;
        }
    }


    bool remove(RawNode2<T>* p) {
        //Case1. p is nullptr
        if (p == nullptr) return false;

        //Case2. p points to a singleton
        if (p == tail && p == head) {
            head = tail = nullptr;
            size = 0;
            delete p;
            return true;
        }

        //Case3. p points to last
        if (p == tail) {
            //p->prev->next = nullptr;
            //tail = p->prev;

            auto before = p->prev;
            before->next = nullptr;
            tail = before;

            delete p;
            size--;
            return true;
        }

        //Case4. p points to head
        if (p == head) {
            auto after = p->next;
            after->prev = nullptr;
            head = after;

            delete p;
            size--;
            return true;

        }

        //Case5. p points to a node surrounded by two nodes
        auto before = p->prev;
        auto after = p->next;
        before->next = after;
        after->prev = before;

        delete p;
        size--;
        return true;

    }
};