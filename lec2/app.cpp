// The difference between returning a 0 and other number in the main function
#include <iostream>

int main(int argv, char ** args)
{
    using namespace std;
    if(argv == 2){
        cout << "Hello, " << args[1] << endl;
        // returns 0 means that the main function runned smoodly
        return 0;
    }
    cout << "Hello, world" << endl;
    // Something went wrong!
    return 1;

}
