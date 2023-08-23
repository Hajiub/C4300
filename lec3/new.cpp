#include <iostream>

class MyClass {

};

int main()
{
    int val = 5; // stack
    int* hval = new int; // heap
    *hval  = 5;
    MyClass c; // Stack
    MyClass *h = new MyClass; // heap
    delete hval;
    delete  h;
}  