#include <iostream>
#include <openssl/md5.h>
#include "md5.h"
#include <sstream>
#include <iomanip>
using namespace std;
string calc(const string& input )
{
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((const unsigned char*)input.c_str(), input.size(), digest);
    stringstream ss;
    for (int i = 0 ; i < MD5_DIGEST_LENGTH;i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)digest[i] ;

    }
    return ss.str();
}
int main() {
    string data = "Hello world" ;
    string md5Hash = calc(data);

    cout << "INput " << data << "\n";
    cout << "out" << md5Hash << "\n";
    return 0;
}