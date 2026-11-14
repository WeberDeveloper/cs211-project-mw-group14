#include <iostream>
#include <limits>
#include <string>

using namespace std;

int main()
{
    char choice;    //lets user continue or quit

    do
    {
        string CN;          //CN is credit card number btw
        bool valid = true;  //assume valid input for now

        cout <<"Enter credit card number: ";
        cin >> CN;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
        
            //output if valid
            if (valid)
            {
                cout <<CN<<" is valid format" << endl;

                //Luhn algorithim

                int sum = 0;                //total of the digits   
                bool doubleDigit = false;   
                //helps ttrack wether a digit should be doubled


                //starts from last digit and moves left
                for (int i = CN.length() - 1; i >= 0; i--)
                {
                    int digit = CN[i] - '0';

                    if (doubleDigit)
                    {
                        digit *= 2;

                        if (digit > 9)
                        {
                        digit -= 9;
                        }
                    }

                    sum = sum + digit;              //Add digits to total
                    doubleDigit = !doubleDigit;     //switch from doubling and not
                }   

            //Everything works from here up

            cout << "Sum = " << sum << endl;
    
        // Check if sum is divisible by 10
            if (sum % 10 == 0)
            {
                cout << "Checksum PASSED" << endl;
            }
            else
            {
                cout << "Checksum FAILED" << endl;
            }
        
            }

            //display if non digit charcters are put
            else
            {
                cout <<CN<< " Contains non-digit characters" << endl;
            }
        //ask if person wants to try another card number
        }
            cout << "\nCheck another card? (y/n): ";
            cin >> choice;

    } while (choice == 'y' || choice == 'Y');
    
    return 0;
}
