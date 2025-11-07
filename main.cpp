#ifdef MAIN

//#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
//#include "LLDQ.hpp"
//#include "LLQ.hpp"
//#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    LinkedList<int> a;
    
    for (int i = 0; i < 100; i++) {
        a.addHead(i);
        a.addTail(i);
    }
    LinkedList<int> b(a);
    LinkedList<int> c = b;
    LinkedList<int> d(c);
    LinkedList<int> e(d);
    LinkedList<int> f(std::move(d));
    LinkedList<int> g = std::move(e);
    a.printForward();
    a.clear();
    a.removeHead();
    a.removeTail();
    a.printForward();
    a.clear();
    b.printForward();
    b.clear();
    c.printForward();
    c.clear();
    d.printForward();
    d.clear();
    e.printForward();
    e.clear();
    f.printForward();
    f.clear();
    g.printForward();
    g.clear();
    return 0;
}


#endif