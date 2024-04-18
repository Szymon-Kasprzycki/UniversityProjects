#include <iostream>
#include <string>
using namespace std;

void getStringReversed(string& old)
{
    string temp = old;
    for (size_t i = 0; i < old.length(); i++) old[i] = temp[old.length()-i-1];
}

void generatePalindrome(string prefix, int n, int len)
{
    if (n == len) n = (n % 2) ? len/2+1 : len/2;
    if (n == 0)
    {
        cout << prefix;
        getStringReversed(prefix);
        if (len % 2) cout << prefix.substr(1, prefix.length());
        else cout << prefix;
    }
    else
    {
        generatePalindrome(prefix + "1", n - 1, len);
        generatePalindrome(prefix + "0", n - 1, len);
    }
}

int main()
{
    int n;
    
    while(cin >> n)
    {
        generatePalindrome("", n, n);
        cout << endl;
    }
    return 0;
}