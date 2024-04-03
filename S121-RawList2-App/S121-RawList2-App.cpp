// S121-RawList2-App.cpp 
// Goal     Implement a simple doubly-linked list container
//          using raw pointers

#include <iostream>
#include <sstream>
using namespace std;

// Global data types ---------------------------------------------
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

    void addlast(T newData) {
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


    void addfirst(T newData) {
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


    bool addat(int index, T dataValue) {
        if (index == 0) {
            addfirst(dataValue); return true;
        }

        if (index == size - 1) {
            addlast(dataValue); return true;
        }

        if (index > size) return false;
        int pos = 0;
        auto p = head;
        while (pos < index) { p = p->next; pos++; }
        insertat(p->prev, dataValue);
        return true;
    }

    void insertat(RawNode2<T>* p, T dataValue) {
        //TODO - Test special cases first, last node
        
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

//-----------------------------------------------------------------
int main()
{
    RawList2<int> lst1;
    lst1.addlast(40);
    lst1.addlast(10);
    lst1.addlast(50);
    lst1.showList();

    RawNode2<int>* p = lst1.find(10);
    if (p == nullptr)
        cout << "Sorry - data not found\n";
    else
        cout << "FOUND => " << p->toString() << endl;

    ////test - remove first (40)
    //lst1.remove(40);
    //lst1.showList();


    ////test - remove node in the middle
    //lst1.remove(10);
    //lst1.showList();

    lst1.addat(2, 77);
    lst1.showList();

    cout << "\nAll done!\n";
}

