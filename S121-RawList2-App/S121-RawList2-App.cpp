// S121-RawList2-App.cpp 
// Goal     Implement a simple doubly-linked list container
//          using raw pointers
//-----------------------------------------------------------------

#include "RawList2.h"
int main()
{
    //create a list of integers
    RawList2<int> lst1;
    lst1.addLast(40);
    lst1.addLast(15);
    lst1.addLast(50);
    lst1.addFirst(10);
    lst1.showList();

    //Test find using a value
    RawNode2<int>* p = lst1.find(10);
    if (p == nullptr)
        cout << "Sorry - data not found\n";
    else
        cout << "FOUND => " << p->toString() << endl;

    ////test - remove first (40)
    //lst1.remove(40);
    //lst1.showList();

    //Test remove last (50)
    
    ////test - remove node in the middle
    //lst1.remove(10);
    //lst1.showList();

    //Testing addAt - change the value of pos
    int pos = 2;
    bool addFlag = lst1.addAt(pos, 7777);
    cout << endl << "add 7777 at pos: " << pos 
         << ", (addFlag) Value added? " << (addFlag ? "True" : "False") << endl;
    lst1.showList();

    cout << "\nAll done!\n";
}

