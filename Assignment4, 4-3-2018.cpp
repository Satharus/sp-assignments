#include <iostream>
#include <iomanip>
#define endl '\n' //overriding endl with the ASCII character '\n' to prevent flushing the stream
//every time the program prints a new line

//Compiled using GNU C++11
//Written by Ahmed Elmayyah from Section 3 under supervision of Dr.Sally Saad

//Not using the whole std namespace because I only need the following functions
using std::cout;
using std::cin;
using std::setprecision;
using std::setw;
using std::fixed;

//struct for an employee
struct Employee
{
    double nHours=0;
    int dependants=0;

    double socialSec=0;
    double fedTax=0;
    double stateIncome=0;
    double unionDues = 10;
    double healthInsurance = 0;
    double totalWithdraws=0;

    double netSalary=0;
    double grossSalary=0;
};

//struct for the company
struct Company
{
    double rate = 16.78;
    int nEmployees = 10;
};

//function that prints a certain character n times
void charline(char c, int n);

int main()
{
    double highest(-1e6), lowest(1e6); //variables to store the highest and lowest salaries of employees, and their indices
    int highestIndex(0),lowestIndex(0);

    Company company1; //initialising a company variable
    Employee employee[company1.nEmployees]; //initialising an array of Employees with size nEmployees of company1(10)

    ////INPUT////

    for (int i = 0; i < company1.nEmployees; i++)
    {

        if (i < company1.nEmployees)
            cout << endl << "Entering the data for employee #" << i + 1 << endl;

        //Entering the number of hours worked by the employee
        while (true)
        {
            cout << "Please enter the number of hours worked weekly by the employee: ";
            cin >> employee[i].nHours;

            //Checking if the user inputs hours more than the number of hours in a week or a negative value
            if (employee[i].nHours > 7 * 24||employee[i].nHours < 0)
            {
                cout << "The number of hours you have entered is invalid!" << endl;
                continue;
            } else break;
        }

        //Entering the dependants of the employee
        while (true)
        {
            cout << "Please enter the number of dependants of the employee: ";
            cin >> employee[i].dependants;

            //Check if the user inputs a negative value
            if (employee[i].dependants < 0)
            {
                cout << "The number of dependants you have entered is invalid!" << endl;
                continue;
            } else break;
        }
        ////END OF INTPUT////


        ////CALCULATIONS///

        if (employee[i].nHours <= 40) //gross salary if the employee worked 40 hours or less
            employee[i].grossSalary = company1.rate * employee[i].nHours;
        else
        {
            employee[i].grossSalary = company1.rate  * 40;
            employee[i].grossSalary += (company1.rate  * 1.5) * (employee[i].nHours - 40);
            //gross salary if the employee worked more than 40 hours
        }

        //calculating taxes(total withdraws)
        employee[i].socialSec = (0.06) * employee[i].grossSalary;
        employee[i].fedTax = (0.14) * employee[i].grossSalary;
        employee[i].stateIncome = (0.05) * employee[i].grossSalary;

        //checking the number of dependants and assigning the health insurance based on that
        if (employee[i].dependants >= 3)
            employee[i].healthInsurance = 35;

        employee[i].totalWithdraws = employee[i].socialSec + employee[i].fedTax + employee[i].stateIncome + employee[i].unionDues + employee[i].healthInsurance ;

        cout << endl;


        employee[i].netSalary = employee[i].grossSalary - employee[i].totalWithdraws;

    }

    for (int i = 0; i < company1.nEmployees; i ++) //Checking for lowest paid and highest paid employees
    {
        if (employee[i].netSalary > highest)
        {
            highest = employee[i].netSalary;
            highestIndex = i;
        }
        else if (employee[i].netSalary < lowest && employee[i].netSalary >= 0)
        {
            lowest = employee[i].netSalary;
            lowestIndex = i;
        }
    }

    ////OUTPUT////
    cout << endl << "The data you have entered for the 10 employees: " << endl << endl;
    cout << "#Emp." << setw(17) << "#Hours Worked" << setw(15) << "#Dependants" << setw(22)
         << "Total Taxes" <<  setw(23) << " Net Salary" << endl << endl;

    for (int i = 0; i < 10; i++)
    {
        int width(15);

        cout << i+1; //printing the number of the employee

        cout << setw(width);
        cout << fixed << setprecision(0) << employee[i].nHours; // printing the number of hours

        cout << setw(width);
        cout << fixed << setprecision(0) << employee[i].dependants; // printing the number of dependants

        cout << setw(width+5);
        cout << '$' << fixed << setprecision(3) << employee[i].totalWithdraws; // printing the total taxes

        //printing the net salary
        if (employee[i].netSalary<0)
        {
            cout << setw(width+2) << '$' << 0;
            cout << "\t\t" << "Error, the gross salary smaller than the total withdraws!";
        }

        else
        {
            cout << setw(width+1);
            cout << '$' << fixed << setprecision(3) << employee[i].netSalary;
        }

        cout << endl << endl;
    }
    charline('-',65);

    //printing the lowerst and highest paid employee's data
    cout << "The lowest paid employee is employee #" << lowestIndex+1 << " and has a salary of $" << lowest << endl
         << "The highest paid employee is employee #" << highestIndex+1 << " and has a salary of $" << highest << endl;
    ////END OF OUTPUT////
    return 0;
}

void charline(char c, int n)
{
    //function that prints a certain character n times
    for (int i = 0; i < n; i++)
        cout << c;
    cout << endl;
}
