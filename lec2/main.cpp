#include <iostream>
#include "student.h"
#include "course.h"
#include <vector>

int main(int argv, char ** args)
{ 	Course cs("CS50");
	cs.LoadFromFile("file.txt");
	cs.print();
	return 0;
}

