#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h> //for system 'cls'
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;



void credits();				//opening splash screen (clone Professor Flores)
void menu();				//menu options including exit option
bool validateUserResponse(string); //catching user input
void checkUserAnswer(int, int, int&, int&, double&); // given a math problem, this function is used to check if the answer the user entered is correct/ incorrect
void updateStats(int&, double&); // used to keep a running total of game statistics
void updateStatsIncorrect(int&, double&);
void displayStats(string, int&, int&, double&); // display statistics on screen
void retireveStats(ifstream&, string&, int&, int&, double&); // retrieve player statistics from external txt file
void saveStats(ofstream&, string, int, int, double); // save player statistics on external txt file
void generateAddition(int&, int&, double&);
void generateSubtraction(int&, int&, double&);
void generateMultiplication(int&, int&, double&);
void generateDivision(int&, int&, double&);
void validateInt(int&);
void floresValidate(string str1, int& userip);
int main(string&, int&)
{
	bool flag = true;
	ofstream file;
	ifstream infile;
	string name;
	int correct = 0;
	int incorrect = 0;
	double earning = 0;
	string choice;
	credits();
	cout << "y/Y To Continue, Any Other Char To Exit: " << endl;

	char ch;
	cin >> ch;
	if (ch != 'y' && ch != 'Y')
	{
		exit(0);
	}
	else
	{
		system("cls");

		cin.ignore();
		do
		{
			cout << "Enter your name and press <ENTER>" << endl;
			do
			{
				getline(cin, name);
				if (name.empty())
					cout << "This is not a valid Name" << endl;
			} while (name.empty());

			flag = validateUserResponse(name);
		} while (flag == false);

		retireveStats(infile, name, correct, incorrect, earning);
		system("cls");

		while (true)
		{
			menu();

			getline(cin, choice);
			while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "n" && choice != "N")
			{
				cout << "That Is Not A Valid Menu Choice\n";
				getline(cin, choice);
			}
			switch (choice[0])
			{
			case '1':
				system("cls");
				generateAddition(correct, incorrect, earning);
				saveStats(file, name, correct, incorrect, earning);
				break;
			case '2':
				system("cls");
				generateSubtraction(correct, incorrect, earning);
				saveStats(file, name, correct, incorrect, earning);
				break;
			case '3':
				system("cls");
				generateMultiplication(correct, incorrect, earning);
				saveStats(file, name, correct, incorrect, earning);
				break;
			case '4':
				system("cls");
				generateDivision(correct, incorrect, earning);
				saveStats(file, name, correct, incorrect, earning);
				break;
			case '5':
				char ch;
				system("cls");
				displayStats(name, correct, incorrect, earning);
				system("pause");
				system("cls");
				break;
			case 'n':
			case 'N':
				exit(0);
				break;
			default:
				cout << "That is not a vallid Menu Option";
				cin.ignore();
				break;
			}
		}
	}


}

void credits()
{

	cout << "***********************" << endl;
	cout << "***********************" << endl;
	cout << "***********************" << endl;
	cout << "******           ******" << endl;
	cout << "******TheMathGame******" << endl;
	cout << "******By Karishma  ****" << endl;
	cout << "******  Mehta    ******" << endl;
	cout << "***********************" << endl;
	cout << "***********************" << endl;
	cout << "***********************" << endl;
	cout << "***********************" << endl << endl;

}


void menu()
{
	cout << endl;
	cout << "******CHOOSE A PROBLEM******" << endl;
	cout << "****************************" << endl;
	cout << "****************************" << endl;
	cout << "******                ******" << endl;
	cout << "****** 1. ADD         ******" << endl;
	cout << "****** 2. SUBTRACT    ******" << endl;
	cout << "****** 3. MULTIPLY    ******" << endl;
	cout << "****** 4. DIVIDE      ******" << endl;
	cout << "****** 5. STATS       ******" << endl;
	cout << "****** n/N to QUIT    ******" << endl;
	cout << "******                ******" << endl;
	cout << "****************************" << endl;
	cout << "****************************" << endl;
}

void generateAddition(int &correct, int &incorrect, double &earning)
{
	srand(time(NULL));
	string userEntry;
	int userip = 0;
	int result;
	int num1 = rand() % 19 + 1;
	int num2 = rand() % 19 + 1;
	cout << "******ADDITION******" << endl;
	cout << "********************" << endl;
	cout << "********************" << endl;
	cout << "***** " << num1 << " + " << num2 << "=? *****" << endl;
	cout << "********************" << endl;
	cout << "********************" << endl;
	result = num1 + num2;
	//cin.ignore();
	getline(cin, userEntry);
	floresValidate(userEntry, userip);
	checkUserAnswer(result, userip, correct, incorrect, earning);
}

void generateSubtraction(int &correct, int &incorrect, double &earning)
{
	srand(time(NULL));
	int result, num1, num2;
	int userip = 0;
	string userEntry;
recalc: num1 = rand() % 20;
	num2 = rand() % 20;
	if (num1<num2) //checks to make sure no negative answers aloud.
	{
		goto recalc;
	}
	cout << "****SUBTRACTION*****" << endl;
	cout << "********************" << endl;
	cout << "********************" << endl;
	cout << "***** " << num1 << " - " << num2 << "=? *****" << endl;
	cout << "********************" << endl;
	cout << "********************" << endl;
	result = num1 - num2;
	/*cin.ignore();*/
	getline(cin, userEntry);
	floresValidate(userEntry, userip);
	checkUserAnswer(result, userip, correct, incorrect, earning);
}

void generateMultiplication(int &correct, int &incorrect, double &earning)
{
	srand(time(NULL));
	int result, userip = 0;
	string userEntry;
	int num1 = rand() % 20;
	int num2 = rand() % 20;
	cout << "**MULTIPLICATION****" << endl;
	cout << "********************" << endl;
	cout << "********************" << endl;
	cout << "***** " << num1 << " * " << num2 << "=? *****" << endl;
	cout << "********************" << endl;
	cout << "********************" << endl;
	result = num1*num2;
	/*cin.ignore();*/
	getline(cin, userEntry);
	floresValidate(userEntry, userip);
	checkUserAnswer(result, userip, correct, incorrect, earning);
}

void generateDivision(int &correct, int &incorrect, double &earning)
{
	srand(time(NULL));
	int result, userip = 0, num1, num2;
	string userEntry;
recalc: num1 = rand() % 20;
	num2 = rand() % 10 + 1;
	if (num1<num2 || !(num1 % num2 == 0)) //makes sure first number larger than second || first num IS divisible by second
	{
		goto recalc;
	}
	cout << "******DIVISION******" << endl;
	cout << "********************" << endl;
	cout << "********************" << endl;
	cout << "***** " << num1 << " / " << num2 << "=? *****" << endl;
	cout << "********************" << endl;
	cout << "********************" << endl;

	result = num1 / num2;
	/*cin.ignore();*/
	getline(cin, userEntry);
	floresValidate(userEntry, userip);
	checkUserAnswer(result, userip, correct, incorrect, earning);
}

void checkUserAnswer(int correctans, int userans, int &correct, int &incorrect, double &earning)

{
	system("cls");
	if (userans == correctans)
	{
		cout << "***********RIGHT!***********" << endl;
		updateStats(correct, earning);
	}
	else
	{
		cout << "***********WRONG!***********" << endl;
		updateStatsIncorrect(incorrect, earning);
	}

}


void updateStats(int &correct, double &earning)
{
	correct++;
	earning += 0.05;
}


void updateStatsIncorrect(int &incorrect, double &earning)
{
	incorrect++;
	earning -= 0.03;
}

void displayStats(string name, int &correct, int &incorrect, double &earning)
{
	cout << "********************************************" << endl;
	cout << "********************************************" << endl;
	cout << "********************************************" << endl;
	cout << "******                                ******" << endl;
	cout << "******" << setw(32) << left << name << "******" << endl;
	cout << "******" << setw(17) << left << "Total Earnings $" << setw(15) << left << earning << "******" << endl;
	cout << "******" << setw(17) << left << "Total Correct " << setw(15) << left << correct << "******" << endl;
	cout << "******" << setw(17) << left << "Total Incorrect " << setw(15) << left << incorrect << "******" << endl;
	cout << "******                                ******" << endl;
	cout << "********************************************" << endl;
	cout << "********************************************" << endl;
	cout << "********************************************" << endl;

}
void saveStats(ofstream &file, string name, int correct, int incorrect, double earning)
{
	string str;
	str = name + ".txt";
	file.open(str.c_str());

	file << name << endl;
	file << earning << endl;
	file << correct << endl;
	file << incorrect << endl;

	file.close();
}
void retireveStats(ifstream &infile, string &name, int &correct, int &incorrect, double &earning)
{
	string fileName, fileVal, str;
	str = name + ".txt";
	infile.open(str.c_str());

	if (infile)
	{
		infile >> fileName;
		name = fileName;
		infile >> fileVal;
		earning = atof(fileVal.c_str());
		infile >> fileVal;
		correct = atoi(fileVal.c_str());
		infile >> fileVal;
		incorrect = atoi(fileVal.c_str());
	}
	infile.close();
}
bool validateUserResponse(string name)
{
	bool secflag = true;
	int i = 0;
	while (name[i] != NULL)
	{
		if (!isalpha(name[i]))
		{

			cout << "Not a valid name" << endl;
			secflag = false;
			break;
		}

		++i;
	}
	return secflag;
}
void validateInt(int &userip)
{
	while (!cin)
	{
		cout << "That was not an integer!\nPlease Enter a number " << endl;

		cin.clear();
		cin.ignore();
		cin >> userip;
	}

}

void floresValidate(string str1, int& userip)
{
	char nextChar;
	int strLength = str1.length();
	int counter = 0;
	userip = 0;
	while (counter < strLength || strLength == 0)
	{
		if (!isdigit(str1[counter]))
		{
			cout << "that is not a number > 0, try again\n";
			getline(cin, str1);
			strLength = str1.length();
			counter = 0;
		}
		else
		{
			counter++;
		}
	}


	counter = 0;
	while (counter < strLength)
	{
		nextChar = str1[counter];
		if (isdigit(nextChar))
		{
			userip = userip * 10 + (nextChar - '0');
		}
		counter++;
	}
}
