/*
 This program lets you enter the data for a company and 10 employees in it, then writes the data to a file.
 After that it gives you the option to view the data, via single user login, or via employer login that allows
 you to view all of the data.
*/

#include <iostream>
#include <termios.h>
#include <iomanip>
#include <fstream>
#include <string>
#define endl '\n'
/*
overriding endl with the ASCII character '\n' to prevent flushing the stream
every time the program prints a new line
*/

#define emp company1.employee  // To decrease text written and make the code more readable

/*
The functions initTermios, resetTermios, getch_, getch, and getche were added due to the lack of the conio.h
header file on the GNU compiler
*/


//Compiled using GNU C++11
//Written by Ahmed Elmayyah from Section 3 under supervision of Dr.Sally Saad

//Not using the whole std namespace because the following functions only are needed.
using std::cout;
using std::cin;
using std::setprecision;
using std::setw;
using std::fixed;
using std::string;
using std::ofstream;

//struct for an employee
struct Employee
{
	 double nHours = 0;
	 int dependants = 0;

	 string name = "EMP_NAME";
	 string password = "PASSWORD";

	 double socialSec = 0;
	 double fedTax = 0;
	 double stateIncome = 0;
	 double unionDues = 10;
	 double healthInsurance = 0;
	 double totalWithdraws = 0;

	 double netSalary = 0;
	 double grossSalary = 0;
};

//struct for the company
struct Company
{
	 string masterPassword; //Used by the employer to view the data of all of the employees
	 string name = "CMP_NAME";
	 double rate = 16.78;
	 int nEmployees = 10;
	 Employee employee[10];
	 //company1.employee has been defined as "emp"
};

//Check the function definition to see what each function does
void charline(char c, int n);
bool login(string correctpw);
double computeNetSalary(double grossPay, double taxes);


//Functions and struct needed to mimic getch and getche.
static struct termios old, newi;
void initTermios(int echo);
void resetTermios();
char getch_(int echo);
char getch();
char getche();
//////////////////////////


int main()
{
	double highest(-1e6), lowest(1e6); //variables to store the highest and lowest salaries of employees, and their indices
	int highestIndex(0),lowestIndex(0);

	Company company1; //initialising a company variable
	//company1.employee has been defined as "emp"

	////INPUT////

	cout << "Enter the company's name: ";
	cin >> company1.name;

	cout << "Enter tha master password for the employer: ";
	cin >> company1.masterPassword;

	for (int i = 0; i < company1.nEmployees; i++)
	{

		if (i < company1.nEmployees)
			cout << endl << "Entering the data for employee #" << i + 1 << endl;

		cin.ignore();
		//Entering the Employee's name and password
		cout << "Please enter the employee's name: ";
		getline (cin, emp[i].name);

		cout << "Please enter the employee's password (no spaces allowed): ";
		cin >> emp[i].password;

		//Entering the number of hours worked by the employee
		while (true)
		{
			cout << "Please enter the number of hours worked weekly by the employee: ";
			cin >> emp[i].nHours;

			//Checking if the user inputs hours more than the number of hours in a week or a negative value
			if (emp[i].nHours > 7 * 24||emp[i].nHours < 0)
			{
				cout << "The number of hours you have entered is invalid!" << endl;
				continue;
			} else break;
		}

		//Entering the dependants of the employee
		while (true)
		{
			cout << "Please enter the number of dependants of the employee: ";
			cin >> emp[i].dependants;

			//Check if the user inputs a negative value
			if (emp[i].dependants < 0)
			{
				cout << "The number of dependants you have entered is invalid!" << endl;
				continue;
			} else break;
		}
		////END OF INPUT////


		////CALCULATIONS////

		if (emp[i].nHours <= 40) //gross salary if the employee worked 40 hours or less
			emp[i].grossSalary = company1.rate * emp[i].nHours;
		else
		{
			emp[i].grossSalary = company1.rate  * 40;
			emp[i].grossSalary += (company1.rate  * 1.5) * (emp[i].nHours - 40);
			//gross salary if the employee worked more than 40 hours
		}

		//calculating taxes(total withdraws)
		emp[i].socialSec = (0.06) * emp[i].grossSalary;
		emp[i].fedTax = (0.14) * emp[i].grossSalary;
		emp[i].stateIncome = (0.05) * emp[i].grossSalary;

		//Checking the number of dependants and assigning the health insurance based on that
		if (emp[i].dependants >= 3)
			emp[i].healthInsurance = 35;

		emp[i].totalWithdraws = emp[i].socialSec + emp[i].fedTax + emp[i].stateIncome + emp[i].unionDues + emp[i].healthInsurance ;

		cout << endl;


		emp[i].netSalary = computeNetSalary(emp[i].grossSalary, emp[i].totalWithdraws);

	}

	for (int i = 0; i < company1.nEmployees; i ++) //Checking for lowest paid and highest paid employees
	{
		if (emp[i].netSalary > highest)
		{
			highest = emp[i].netSalary;
			highestIndex = i;
		}
		else if (emp[i].netSalary < lowest && emp[i].netSalary >= 0)
		{
			lowest = emp[i].netSalary;
			lowestIndex = i;
		}
	}
	////END OF CALCULATIONS////

	///WRITING TO A FILE///

	//This part of the program writes the raw data to a file in the format of Name*  Password  Hours  Dependants
	//so that it can be read from it in a future update.

	//The '*' "Asterisk" is used to denote that the name has ended, and will be used as a delimiter for input in a future update.

	ofstream companyDataO;
	companyDataO.open(company1.name + ".txt");
	for (int i = 0; i < company1.nEmployees; i++)
	{
		companyDataO <<  emp[i].name << '*' << setw(30 - emp[i].name.size()) << emp[i].password <<
						setw(20 - emp[i].password.size()) << setw(5) << emp[i].nHours << '\t' << emp[i].dependants << '\t' << endl;
	}

	companyDataO.close();

	///END OF WRITING///


	////INTERACTIVE PROGRAM////
	while (true)
	{
		cout << "You have all of the data for the company " << company1.name
			  << ", what would you like to do?" << endl;
		cout << "(1)->Login for a certain user." << endl;
		cout << "(2)->View all of the employees' data." << endl;
		cout << "(3)->Exit the program." << endl;

		cout << "Choice: ";
		char choice;
		cin >> choice;

		switch (choice)
		{
			case '1': //Single user login case
			{
				retryCase1:
				bool userNameCorrect(false);
				int index(0);

				cout << "Name: ";
				string name;
				cin.ignore();
				getline(cin, name);

				//Checking if the username exists, and returns the index if so.
				for (int i = 0; i < company1.nEmployees; i++)
				{
					if (name == emp[i].name)
					{
						userNameCorrect = true;
						index = i;
						break;
					}
				}

				///OUTPUT FOR THE USER///
				if (login(emp[index].password) && userNameCorrect)
				{
					cout << setw(10) << "Login Successful!" << endl;
					charline('-', 10);
					cout << "Name: " << emp[index].name << endl;
					cout << "Hours worked: " << emp[index].nHours << endl;
					cout << "Number of dependants: " << emp[index].dependants << endl;
					cout << "Gross salary: $" << emp[index].grossSalary << endl;
					cout << "Total withdraws: $" << emp[index].totalWithdraws << endl;
					if (emp[index].netSalary >= 0)
						cout << "Net salary: $" << emp[index].netSalary << endl;
					else
						cout << "Net salary: $0\t\tError, the gross salary smaller than the total withdraws!" << endl;
				}
				else
					cout << "The username or password you have entered is wrong." << endl;

				///OUTPUT FOR THE USER///

				cout << "Would you like to try again? (y/n): ";
				char retry;
				cin >> retry;
				if (retry == 'y' || retry == 'Y')
					goto retryCase1;
				else break;
			}

			case '2': //Employer login case
			{
				retryCase2:

				if (login(company1.masterPassword))
				{
					cout << setw(10) << "Login Successful!" << endl;
					charline('-', 10);

					///OUTPUT FOR EMPLOYER///

					cout << endl << "The data available for the " << company1.nEmployees <<
						  " employees at " << company1.name << ": " << endl << endl;

					cout << "#Emp." << setw(8) << "Name" << setw(20) << "#Hours Worked" << setw(20) << "#Dependants" << setw(22)
						  << "Total Taxes" <<  setw(23) << " Net Salary" << endl << endl;

					for (int i = 0; i < company1.nEmployees; i++)
					{
						int width(15);

						cout << i+1; //printing the number of the employee
						cout << setw(width);
						cout << emp[i].name;

						cout << setw(width);
						cout << fixed << setprecision(0) << emp[i].nHours; // printing the number of hours

						cout << setw(width);
						cout << fixed << setprecision(0) << emp[i].dependants; // printing the number of dependants

						cout << setw(width+5);
						cout << '$' << fixed << setprecision(3) << emp[i].totalWithdraws; // printing the total taxes

						//printing the net salary
						if (emp[i].netSalary<0)
						{
							cout << setw(width+2) << '$' << 0;
							cout << "\t\t" << "Error, the gross salary smaller than the total withdraws!";
						}

						else
						{
							cout << setw(width+1);
							cout << '$' << fixed << setprecision(3) << emp[i].netSalary;
						}

						cout << endl << endl;
					}
					charline('-',65);

					//printing the lowest and highest paid employee's data
					cout << "The lowest paid employee is employee #" << lowestIndex+1 << ' ' << emp[lowestIndex].name << " and has a salary of $" << lowest << endl
						  << "The highest paid employee is employee #" << highestIndex+1 << ' ' << emp[highestIndex].name << " and has a salary of $" << highest << endl;

					///END OF OUTPUT FOR EMPLOYER///

					cout << endl << "To return to the menu enter 'r', to exit press 'e': ";

					char _exit;
					cin >> _exit;
					if (_exit == 'r')
						continue;
					else if (_exit == 'e')
					{
						cout << "Okay! Goodbye :)" << endl;
						return 0;
					}

				}


				else
				{
					cout << "The password you have entered is wrong." << endl;
					cout << "Would you like to try again? (y/n): ";
					char retry;
					cin >> retry;
					if (retry == 'y' || retry == 'Y')
						goto retryCase2;
					else break;
				}
			}

			case '3': //Exit case
			{
				cout << "Okay! Goodbye :)" << endl;
				return 0;
			}

			default:
				cout << "Wrong Input!" << endl;

		}
	}
	////END OF INTERACTIVE PROGRAM////
}

void charline(char c, int n)
{
	//function that prints a certain character n times
	for (int i = 0; i < n; i++)
		cout << c;
	cout << endl;
}

bool login(string correctpw)
{
	cout << "Password: ";
	string password;

	while(true)
	{
		char ch;
		ch = getch();
		if (ch != '\n')
		{
			cout << '*';
			password += ch;
		}
		else if (password.size() > 1)
			break;
	}
	cout << endl;
	charline('-',10);

	if (password == correctpw)
		return true;

	return false;
}

double computeNetSalary(double grossPay, double taxes)
{
	return grossPay - taxes;
}

//This part of the code was not written by me,
// but instead was found on stackoverflow to overcome the issue of the missing "conio.h"
// header file on non MS-DOS compatible compilers.

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
	tcgetattr(0, &old); /* grab old terminal i/o settings */
	newi = old; /* make new settings same as old settings */
	newi.c_lflag &= ~ICANON; /* disable buffered i/o */
	if (echo)
	{
		newi.c_lflag |= ECHO; /* set echo mode */
	}

	else
	{
		newi.c_lflag &= ~ECHO; /* set no echo mode */
	}

	tcsetattr(0, TCSANOW, &newi); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios()
{r
	tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
	char ch;
	initTermios(echo);
	ch = getchar();
	resetTermios();
	return ch;
}

/* Read 1 character without echo */
char getch()
{
	return getch_(0);
}

/* Read 1 character with echo */
char getche()
{
	return getch_(1);
}
