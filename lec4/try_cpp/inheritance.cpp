#include <iostream>

// Animal name, age, info
class Animal {
protected:
    std::string name;
    int age;

public:
    Animal(const std::string & name, int age): name(name), age(age) {}
    void info()
    {
        std::cout << "Name: " << name << "Age: " << age << std::endl;
    }
};

class Cat : public Animal {
public:
    Cat(const std::string& name, int age): Animal(name, age){}
    void Meow()
    {
        std::cout << name << " is eating" << std::endl;
    }
};