#include <iostream>
#include <list>
using namespace std;
int main()
{
    //сохраним список в переменной
    char arr[4] = {'black', 'white', 'red', 'orange'};
   
    //организация стека
    list <char> stack;
    stack.push_back('black');
    stack.push_back('white');
    stack.push_back('red');
    stack.push_back('orange');
    
    return 0;
}
