#include <iostream>

const int myConstant = 42; // should be "MY_CONSTANT"

class badClass // should be BadClass
{
public:
    void thisisabadfunction() // should be "thisIsABadFunction"
    {
        std::cout << "Bad function" << std::endl;
    }
    void duplicatedFunction() // should be removed
    {
        std::cout << "Bad function" << std::endl;
    }
};


int main()
{
    int MYVARIABLE = 42; // should be "myVariable"
}