#include <iostream>

class IntArray 
{
private:
	int * array;
public:
 	IntArray(size_t size) { array = new int[size]; }
	~IntArray() { delete [] array; }
	int & operator [] (size_t i) { return array[i]; }
};

int main(int args, char * argv[])
{
	IntArray arr(5);
	arr[0] = 15;
	int value  = arr[0];
	std::cout << value << std::endl;
	std::cout << arr[34] << std::endl;
}
