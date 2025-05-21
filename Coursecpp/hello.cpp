#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    int password;
cout << "Put new password" << endl;
cin >> password ;
ofstream outFIle("Hello.txt");
if(outFIle.is_open())
{
outFIle<< "Password New " << password << endl;
cout << "all ok" << endl;
outFIle.close();
}
}