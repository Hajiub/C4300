#include <iostream>

void pp(int & a)
{
	std::cout << &a << " " << a << " " << sizeof(a) << std::endl;
}
int main(int argc, char *  argv[])
{
	int   a = 10;
	int   b = 25;
	int* pa = &a;
	int* pb = &b;
	*(pb - 1) = 17;
	*(pa + 1) =  34;
	pp(a);
	pp(b);
	return 0;
}
