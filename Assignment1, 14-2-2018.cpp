#include <iostream>
#include <iomanip>

//Compiled using GNU C++11
//Written by Ahmed Elmayyah from Section 3 under supervision of Dr.Sally Saad

using std::cout;
using std::cin;
using std::endl;
using std::setprecision;
using std::setw;
using std::fixed;

void charline(char c, int n);

int main()
{
    double rateFirst(16.78);

    while (true)
    {
        double nHours(0);

        while (true)
        {
            cout << "Please enter the number of hours worked weekly by the employee: ";
            cin >> nHours;
            //Check if the user inputs hours more than the number of hours in a week
            if (nHours > 7 * 24)
            {
                cout << "The number of hours you have entered are invalid!" << endl;
                continue;
            }
            else break;
        }

        long long dependants;
        cout << "Please enter the number of dependants of the employee: ";
        cin >> dependants;

        double grossSalary;
        if (nHours <= 40)
            grossSalary = rateFirst * nHours;
        else
        {
            grossSalary = rateFirst * 40;
            grossSalary += (rateFirst*1.5)*(nHours-40);
        }

        double socialSec, fedTax, stateIncome, unionDues(10), healthInsurance(0);
        socialSec = (0.06) * grossSalary;
        fedTax = (0.14) * grossSalary;
        stateIncome = (0.05) * grossSalary;

        if (dependants >=3)
            healthInsurance = 35;

        double totalWithdraws = socialSec + fedTax + stateIncome + unionDues + healthInsurance;

        cout << endl;
        cout << "Withdraws: "<< endl;
        charline('*',33);
        
        cout << setprecision(2) << fixed;

        cout     << ' ' << "Gross salary: "    << setw(9)  << '$' << grossSalary <<
            endl <<
            endl << ' ' << "Social security: " << setw(6)  << '$' << socialSec <<
            endl << ' ' << "Federal tax: "     << setw(10) << '$' << fedTax <<
            endl << ' ' << "State income: "    << setw(9)  << '$' << stateIncome <<
            endl << ' ' << "Union dues: "      << setw(11) << '$' << unionDues <<
            endl << ' ' << "Health insurance: "<< setw(5)  << '$' << healthInsurance << endl;
        charline('*',33);

        cout << ' ' << "Total withdraws: " << setw(6) << '$' << totalWithdraws << endl;

        charline('-',33);

        cout << ' ' << "Gross salary: " << setw(9) << '$' << grossSalary <<
        endl << ' ' << "Net salary: "   << setw(11) << '$' << grossSalary -totalWithdraws << endl;


        cout << endl << "Would you like to enter another employee's data?(y/n)";
        while (true)
        {
            char choice;
            cin >> choice;

            if (choice == 'y' || choice == 'Y')
                break;

            else if (choice == 'n' || choice == 'N')
            {
                cout << "Okay! Have a nice day :)" << endl;
                return 0;
            }

            else
            {
                cout << "Invalid Input! Please enter again: ";
                continue;
            }
        }
    }

}

void charline(char c, int n)
{
    for (int i = 0; i < n; i++)
        cout << c;
    cout << endl;
}