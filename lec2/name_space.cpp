#include <iostream>

namespace meow {
    void Meow(int times)
    {
        for (int i = 0; i < times ; i++)
        {
            std::cout << "MEOW \n";
        }
    }
}

int main(int argv, char **args)
{
    int x = 5;
    // can be used like this 
    meow::Meow(x);
    // or like This 
    using namespace meow;
    Meow(x);
}