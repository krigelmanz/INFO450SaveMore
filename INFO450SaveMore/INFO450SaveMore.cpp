// Zachary Krigelman Assignment 3
#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

// Create base class
class Account
{
// private variables
	static int IDGenerator;
// Protected variables
protected:
	double rate;
	double balance;
	double deposit = 0;
	double withdraw = 0;
	char transaction;
	double amount = 0;
	double withdcount = 0;
// Public variables
public:
	int ID;
// Empty constructor
	Account()
	{
		ID = IDGenerator++;
		rate = 0;
		balance = 0;

	};
// Constructor with balance variable
	Account(double b)
	{
		ID = IDGenerator++;
		rate = 0; balance = b;
	};
	int getID();
// Pure virtual function
	virtual void Display() = 0;
	void transactions();
};
// Instantiate ID Generator
int Account::IDGenerator = 1;

/*int Account::getID()
{
	return ID;
}*/
// Create transactions for account
void Account::transactions()
{
	do
	{
		cout << "Would you like to add a transaction?" << endl <<
			"Enter (D)eposit (W)ithdraw (Q)uit" << endl;
		cin >> transaction;
		if (transaction == 'd' || transaction == 'D')
		{
			cout << "Amount?" << endl;
			cin >> amount;
			deposit += amount;
		}
		else if (transaction == 'w' || transaction == 'W')
		{
			cout << "Amount?" << endl;
			cin >> amount;
			if (amount > balance + deposit - withdraw)
			{
				cout << "Insufficient funds" << endl;
			}
			else
			{
				withdraw += amount;
				withdcount++;
			}
		}
		else if (transaction != 'q' && transaction != 'Q')
		{
			cout << "Invalid entry." << endl;
		}
	} while (transaction != 'q' && transaction != 'Q');
}
// Create savings account inheriting base class
class Savings : public Account
{
public:
	Savings(double b) : Account(b)
	{
		balance = b;
		transactions();
	}
	void Display();
};
// Create checking account inheriting base class
class Checking : public Account
{
	char checkOrder;
public:
	Checking(double b) : Account(b)
	{
		balance = b;
		cout << "Would you like to order checks? Enter Y or N." << endl;
		cin >> checkOrder;
		if ((checkOrder == 'y' || checkOrder == 'Y') && balance > 15)
		{
			balance -= 15;
		}
		else if ((checkOrder == 'y' || checkOrder == 'Y') && balance < 15)
		{
			cout << "Insufficient funds." << endl;
		}
		transactions();
	}
	void Display();
};
// Create certificate of deposit inheriting base class
class Deposit : public Account
{
public:
	Deposit(double b, int t) : Account(b)
	{
		int CDTerm = t;
		if (CDTerm >= 5)
		{
			rate = 10;
		}
		else
		{
			rate = 5;
		}
		transactions();
	}
	void Display();
};
// Display savings account
void Savings::Display()
{
	cout << "Account Number: " << ID << endl;
	cout.precision(2);
	cout << "Starting balance: " << fixed << balance << endl;
	cout << "Total deposits: " << deposit << endl;
	cout << "Total withdraws: " << withdraw << endl;
	if ((balance + deposit - withdraw - (2 * withdcount)) >= 10000)
		rate = 2;
	else
		rate = 1;
	cout << "APR: " << rate / 100 << endl;
	cout << "Interest earned: " << (balance + deposit - withdraw) * rate / 1200 << endl;
	cout << "Withdraw fees: " << (2 * withdcount) << endl;
	cout << "Ending balance: " << (balance + deposit - withdraw - (2 * withdcount)) * (1 + (rate / 1200)) << endl << endl;
}
// Display Checking account
void Checking::Display()
{
	string checks;
	double lowBalanceFee = 0;
	cout << "Account Number: " << ID << endl;
	cout.precision(2);
	cout << "Starting balance: " << fixed << balance << endl;
	if (checkOrder == 'n' || checkOrder == 'N')
	{
		checks = "No";
	}
	else
	{
		checks = "Yes";
	}
	if ((balance + deposit - withdraw) < 500)
	{
		lowBalanceFee += 5;
	}
	else
	{
		lowBalanceFee += 0;
	}
	cout << "Total deposits: " << deposit << endl;
	cout << "Total withdraws: " << withdraw << endl;
	cout << "Ordered checks? " << checks << endl;
	cout << "Fees accrued: " << lowBalanceFee << endl;
	cout << "Ending balance: " << balance - lowBalanceFee + deposit - withdraw << endl << endl;
}
// Display certificate of deposit
void Deposit::Display()
{
	cout << "Account Number: " << ID << endl;
	cout.precision(2);
	cout << "Starting balance: " << fixed << balance << endl;
	cout << "Total deposits: " << deposit << endl;
	cout << "Total withdraws: " << withdraw << endl;
	cout << "APR: " << rate / 100 << endl;
	cout << "Interest earned: " << (balance + deposit - withdraw - (withdraw / 10)) * rate / 1200 << endl;
	cout << "Withdraw fees: " << (withdraw / 10) << endl;
	cout << "Ending balance: " << (balance + deposit - withdraw - (withdraw / 10)) * (1 + (rate / 1200)) << endl << endl;

}

int main()
{
	int count = 100;
	int AccountNum = 0;
	char AType = 'r';
	double b;
	int t;
	Account **Alist = new Account*[count];

	for (int i = 0; i < count; i++)
	{
		while (AType != 'q' && AType != 'Q')
		{
			cout << "Type of account? (C)hecking, (S)avings, C(D) or (Q)uit" << endl;
			cin >> AType;
			if (AType == 'C' || AType == 'c')
			{
				cout << "Starting Balance?" << endl;
				cin >> b;
				cin.ignore();
				cin.clear();
				Alist[i] = new Checking(b);
				AccountNum++;
				break;
			}
			else if (AType == 'S' || AType == 's')
			{
				cout << "Starting Balance?" << endl;
				cin >> b;
				cin.ignore();
				cin.clear();
				Alist[i] = new Savings(b);
				AccountNum++;
				break;
			}
			else if (AType == 'D' || AType == 'd')
			{
				cout << "Starting Balance?" << endl;
				cin >> b;
				cout << "Length of CD in years?" << endl;
				cin >> t;
				cin.ignore();
				cin.clear();
				Alist[i] = new Deposit(b, t);
				AccountNum++;
				break;
			}
			else if (AType != 'Q' && AType != 'q')
			{
				cout << "Invalid choice." << endl;
				break;
			}
		}
	}
// Display all accounts
	for (int i = 0; i < AccountNum; i++)
	{
		Alist[i]->Display();
	}
// Delete array to redeem memory
	for (int i = 0; i < AccountNum; i++)
	{
		delete Alist[i];
	}
	return 0;
}