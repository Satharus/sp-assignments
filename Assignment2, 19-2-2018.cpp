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

    int nEmployees;

    cout << "Please enter the number of employees: ";
    cin >> nEmployees;

    for (int i = 0; i < nEmployees; i++)
    {

        double employeeData[2] = {}; // 0-Hours, 1-Dependants
        double employeeWithdraws[6] = {0, 0, 0, 10, 0, 0}; //0-Social Security, 1-Federal Tax, 2- State Income, 3- Union Dues, 4- Health Insurance(0),5- Total Withdraws;
        double employeeSalary[2] = {}; // 0 - Gross Salary, 1- Net Salary

        if (i < nEmployees)
            cout << endl << "Entering the data for employee #" << i + 1 << endl;

        while (true)
        {
            cout << "Please enter the number of hours worked weekly by the employee: ";
            cin >> employeeData[0];
            //Check if the user inputs hours more than the number of hours in a week or a negative value
            if (employeeData[0] > 7 * 24||employeeData[0] < 0)
            {
                cout << "The number of hours you have entered is invalid!" << endl;
                continue;
            } else break;
        }

        while (true)
        {
            cout << "Please enter the number of dependants of the employee: ";
            cin >> employeeData[1];
            //Check if the user inputs a negative value
            if (employeeData[1] < 0)
            {
                cout << "The number of dependants you have entered is invalid!" << endl;
                continue;
            } else break;
        }


        if (employeeData[0] <= 40)
            employeeSalary[0] = rateFirst * employeeData[0];
        else
        {
            employeeSalary[0] = rateFirst * 40;
            employeeSalary[0] += (rateFirst * 1.5) * (employeeData[0] - 40);
        }

        employeeWithdraws[0] = (0.06) * employeeSalary[0];
        employeeWithdraws[1] = (0.14) * employeeSalary[0];
        employeeWithdraws[2] = (0.05) * employeeSalary[0];

        if (employeeData[1] >= 3)
            employeeWithdraws[4] = 35;

        for (int k = 0; k < 5; k++)
        {
            employeeWithdraws[5] += employeeWithdraws[k];
        }

        cout << endl;
        cout << "The data of employee #" << i + 1 << ": " << endl;
        cout << "Withdraws: " << endl;
        charline('*', 33);

        cout << setprecision(2) << fixed;

        cout << ' ' << "Gross salary: " << setw(9) << '$' << employeeSalary[0] <<
             endl <<
             endl << ' ' << "Social security: " << setw(6) << '$' << employeeWithdraws[0] <<
             endl << ' ' << "Federal tax: " << setw(10) << '$' << employeeWithdraws[1] <<
             endl << ' ' << "State income: " << setw(9) << '$' << employeeWithdraws[2] <<
             endl << ' ' << "Union dues: " << setw(11) << '$' << employeeWithdraws[3] <<
             endl << ' ' << "Health insurance: " << setw(5) << '$' << employeeWithdraws[4] << endl;
        charline('*', 33);

        cout << ' ' << "Total withdraws: " << setw(6) << '$' << employeeWithdraws[5] << endl;

        charline('-', 33);

        employeeSalary[1] = employeeSalary[0] - employeeWithdraws[5];

        if (employeeSalary[1] >= 0)
            cout << ' ' << "Gross salary: " << setw(9) << '$' << employeeSalary[0] <<
            endl << ' ' << "Net salary: " << setw(11) << '$' << employeeSalary[1] << endl;
        else
        {
            cout << ' ' << "Gross salary: " << setw(9) << '$' << employeeSalary[0] <<
            endl << ' ' << "Net salary: " << setw(11) << '$' << 0 << endl;
            cout << "Error, the gross salary smaller than the total withdraws" << endl;

        }
    }
}

void charline(char c, int n)
{
    for (int i = 0; i < n; i++)
        cout << c;
    cout << endl;
}
