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
    double highest(-100000), lowest(1000000);
    int highestIndex,lowestIndex;
    const int nEmployees(10);
    double employeeData[nEmployees][4]; // 0-Hours, 1-Dependants, 2-Total Withdraws, 3-Net Salary

    for (int i = 0; i < nEmployees; i++)
    {

        if (i < nEmployees)
            cout << endl << "Entering the data for employee #" << i + 1 << endl;

        while (true)
        {
            cout << "Please enter the number of hours worked weekly by the employee: ";
            cin >> employeeData[i][0];
            //Check if the user inputs hours more than the number of hours in a week or a negative value
            if (employeeData[i][0] > 7 * 24||employeeData[i][0] < 0)
            {
                cout << "The number of hours you have entered is invalid!" << endl;
                continue;
            } else break;
        }

        while (true)
        {
            cout << "Please enter the number of dependants of the employee: ";
            cin >> employeeData[i][1];
            //Check if the user inputs a negative value
            if (employeeData[i][1] < 0)
            {
                cout << "The number of dependants you have entered is invalid!" << endl;
                continue;
            } else break;
        }

        double grossSalary;

        if (employeeData[i][0] <= 40)
            grossSalary = rateFirst * employeeData[i][0];
        else
        {
            grossSalary = rateFirst * 40;
            grossSalary += (rateFirst * 1.5) * (employeeData[i][0] - 40);
        }

        double socialSec, fedTax, stateIncome, unionDues(10), healthInsurance(0);
        socialSec = (0.06) * grossSalary;
        fedTax = (0.14) * grossSalary;
        stateIncome = (0.05) * grossSalary;

        if (employeeData[i][1] >= 3)
            healthInsurance = 35;

        employeeData[i][2] = socialSec + fedTax + stateIncome + unionDues + healthInsurance;

        cout << endl;


        employeeData[i][3] = grossSalary - employeeData[i][2];

    }

    for (int i = 0; i < 10; i ++) //Checking for lowest paid and highest paid employees
    {
        if (employeeData[i][3] > highest)
        {
            highest = employeeData[i][3];
            highestIndex = i;
        }
        else if (employeeData[i][3] < lowest && employeeData[i][3] >= 0)
        {
            lowest = employeeData[i][3];
            lowestIndex = i;
        }
    }
    cout << endl << "The data you have entered for the 10 employees: " << endl << endl;
    cout << "#Emp." << '\t' << "#Hours Worked" << '\t' << "#Dependants" << "\t\t\t"
         << "Total Taxes" <<  "\t\t\t" << " Net Salary" << endl << endl;

    for (int i = 0; i < 10; i++)
    {
        cout << i+1;

        for (int j = 0; j < 4; j++)
        {
            if (j==3&&employeeData[i][j]<0)
            {
                cout << setw(15) << '$' << 0;
                cout << "\t\t" << "Error, the gross salary smaller than the total withdraws!";
            }
            else if (j!=0&&j!=1)
            {
                cout << setw(15);
                    cout << '$';
                cout << fixed << setprecision(3) << employeeData[i][j];
            }
            else
            {
                cout << setw(15);
                cout << fixed << setprecision(0) << employeeData[i][j];
            }
        }

        cout << endl << endl;
    }
    charline('-',65);
    cout << "The lowest paid employee is employee #" << lowestIndex+1 << " and has a salary of $" << lowest << endl
         << "The highest paid employee is employee #" << highestIndex+1 << " and has a salary of $" << highest << endl;
}

void charline(char c, int n)
{
    for (int i = 0; i < n; i++)
        cout << c;
    cout << endl;
}