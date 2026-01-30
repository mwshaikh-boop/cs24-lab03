#include "intbst.h"
#include <iostream>

using namespace std;

int main() {

    IntBST testbst;

    testbst.insert(10);
    testbst.insert(5);
    testbst.insert(15);
    testbst.insert(7);
    testbst.insert(8);
    testbst.insert(3);
    testbst.insert(20);
    testbst.insert(12);
    testbst.insert(17);
    testbst.insert(15);
    
    testbst.printPreOrder();
    cout << endl;
    testbst.printInOrder();
    cout << endl;
    testbst.printPostOrder();
    cout << endl;

    cout << testbst.sum() << endl;
    cout << testbst.count() << endl;

    cout << "Contains 12? " <<
	    (testbst.contains(12) ? "Y" : "N") << endl;
    cout << "Contains 19? " <<
            (testbst.contains(19) ? "Y" : "N") << endl;
    
    cout << "Predecessor of 10 is: " <<
	    testbst.getPredecessor(10) << endl;
    cout << "Successor of 3 is: " <<
	    testbst.getSuccessor(3) << endl;
    
    testbst.remove(12);
    testbst.remove(8);
    testbst.remove(10);
    testbst.printInOrder();
    cout << endl;

    return 0;
}
