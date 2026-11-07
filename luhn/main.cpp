#include <iostream>
#include <string>

using namespace std;

int main()
{
  
    string CN; //CN is credit card number btw
    bool valid = true;

    cout <<"Enter credit card number: ";
    cin >> CN;

    cout <<"Credit card number is: "<<CN<<endl;
    
    //Checking if it has 16 digits
    if (CN.length() != 16)
    {
        cout <<CN<<" contains invalid length" << endl;
    }
    //checking if every character is a digit
    else
    {
        for (int i = 0; i < CN.length(); i++)
        {
            if (CN[i] < '0' || CN[i] > '9')
            {
                valid = false;
            }
        }
        //If credit card number is valid
        if (valid)
        {
            cout <<CN<<" is valid format" << endl;
        }
        else
        {
            cout <<CN<< " Contains non-digit characters" << endl;
        }
    }
    //The Luhn algorithim is lowkey in progress still

    return 0;
}
