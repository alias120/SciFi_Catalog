#ifndef INCLUDES_H
#define INCLUDES_H
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <sys/stat.h>

using namespace std;

string filename = "SF_Catalog.doc";
string password = "asimov";
string passtry = " ";
struct stat statInfo;
extern void Show_catalog();
extern bool Accept_Input();
void enter_password();
bool File_Test();

bool File_Error_Check_in(ifstream &obj)
{
	if(!obj)
	{
		cout<<"No file in directory."<<endl;
		cout<<"\nPress any key to return to main menu..."<<endl;
		cin.ignore();
		cin.get();
		return false;
	}
	else return true;
}

bool File_Error_Check_out(ofstream &obj)
{
	if(!obj)
	{
		cout<<"No file in directory."<<endl;
		cout<<"\nPress any key to return to main menu..."<<endl;
		cin.ignore();
		cin.get();
		return false;
	}
	else return true;
}

int Error(string s)
{
	cout<< s << ", Goodbye.\n" <<endl;
	cin.sync();
	cin.clear();
	cin.get();
	exit(1);
}

void Return_Error(string s)
{
	cout<< s << ", press enter to return to the main menu.\n"<<endl;
	cin.sync();
	cin.clear();
	cin.get();
}

void password_error(int i)
{
	static int time_out = 0;
	if(i == 1)
	{
		cout<<"You did not enter your password correctly, please try again."<<endl;
		enter_password();
	}
	if(i == 2)
	{
		cout<< "\nIncorrect Password.\n"<<endl;
		time_out++;
		if(time_out == 3) Error("You have failed too many password attempts");
		enter_password();
	}
}

bool File_Test()
{
	int statTest = 0;
	statTest = stat(filename.c_str(), &statInfo);
	if(statTest == 0) return true;
	else return false;
}

void Clear_screen()
{
	system("CLS");
}

void enter_password()
{
	if(File_Test()) return;
	cout<<"\nPlease enter your password: ";
	while(!(cin>>passtry))
	{
		password_error(1);
	}
	if(passtry != password) password_error(2);
	else
		cout<<"\nWelcome Sci-fi reader!"<<endl;
		cout<<"Since this is your first time, choose Help from the main menu."<<endl;
		cin.sync();
}
#endif
