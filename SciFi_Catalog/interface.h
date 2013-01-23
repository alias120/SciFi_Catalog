#ifndef INTERFACE_H
#define INTERFACE_H
#include"includes.h"

class Node
{
	string author;
	string title;
	string date;
	friend class Cat_Search;
	friend class Cat_Remove;
};

class Book
{
protected:
	string t_search;
	string c_space;
	string title;
	string author;
	string file_read;
	int date;
	virtual void init()
	{
		return;
	}
public:
	Book(){}
	~Book(){}
	void nav_catalog(Book &obj)
	{
		obj.init();
	}
};

class Cat_Search : public Book
{
private:
	Node obj;
	int nav_choice;
public:
	Cat_Search(){}
	~Cat_Search(){}
protected:
	void init()
	{
		cin.sync();
		Clear_screen();
		cout<<"--Search--"<<endl;
		cout<<"\nYou can either search by Title, or Author."<<endl;
		cout<<"1. Title \n"
			<<"2. Author "<<endl
			<<"3. Main Menu"<<endl;
		cout<<"\nChoice: "; 
		if(!(cin>>nav_choice)) 
		{
			Return_Error("Incorrect Choice");
			return;
		}
		switch(nav_choice)
		{
		case 1:
			Title_Search(); 
			break;
		case 2:
			Author_Search();
			break;
		case 3:
			return;
			break;
		default:
			Return_Error("Unknown Option");
		}
	}

	void Title_Search()
	{
		Clear_screen();
		cin.sync();
		cout<<"\nPlease enter the Title you are searching for: ";
		getline(cin, t_search);
		ifstream search("SF_Catalog.doc");
		if(!File_Error_Check_in(search)) return;
		while(search.is_open())
		{	
			getline(search, obj.title);
			getline(search, obj.author);
			getline(search, obj.date);
			getline(search, c_space);

			if(obj.title == t_search)
			{
				cout<<"\nFound match: \n\n"
					<< obj.title << endl
					<< obj.author << endl
					<< obj.date << endl
					<< endl;
			}
			if(search.eof()) break;
		}
		cout<<"\nPress any key to return to menu..."<<endl;
		cin.get();
		Clear_screen();
	}

	void Author_Search()
	{
		Clear_screen();
		cin.sync();
		cout<<"\nPlease enter the Author you are searching for: ";
		getline(cin, t_search);
		ifstream search("SF_Catalog.doc");
		if(!File_Error_Check_in(search)) return;
		do
		{	
			getline(search, title);
			if(title.size() == 0) break;
			obj.title = title;
			getline(search, author);
			if(author.size() == 0) break;
			obj.author = author;
			getline(search, obj.date);
			getline(search, c_space);

			if(obj.author == t_search)
			{
				cout<<"\nFound match: \n\n"
					<< obj.title << endl
					<< obj.author << endl
					<< obj.date << endl
					<< endl;
			}
		}while(!(search.eof()));
		cout<<"\nPress any key to return to menu..."<<endl;
		cin.get();
		Clear_screen();
	}
};
	
class Cat_View : public Book
{
public:
	Cat_View(){}
	~Cat_View(){}
protected:
	void init()
	{
		Clear_screen();
		cout<<"--Full Catalog--\n"<<endl;
		ifstream obj("SF_Catalog.doc",ios::out);
		if(!File_Error_Check_in(obj)) return;
		while(obj.is_open())
		{
			getline(obj, file_read);
			cout<< file_read <<endl;
			if(obj.eof()) break;
		}
	
		cout<<"\nPress any key to return to menu..."<<endl;
		cin.ignore();
		cin.get();
	}
};

class Cat_Add_To : public Book
{
private:
	int choice;
public:
	Cat_Add_To(){}
	~Cat_Add_To(){}
protected:
	void init()
	{
		cin.sync();
		Clear_screen();
		cout<<"--Add Entry--"<<endl;
		cout<<"\n1. Add Entry to Catalog \n"
			<<"2. Main Menu "<<endl;
		cout<<"\nChoice: ";
		if(!(cin>>choice)) 
		{
			Return_Error("Invalid Input");
			return;
		}
		switch(choice)
		{
		case 1:
			Add_To();
			break;
		case 2:
			break;
		default:
			Return_Error("Invalid Choice");
		}
	}

	void Add_To()
	{
		cin.sync();
		Clear_screen();
		cout<<"--Add Entry--"<<endl;
		cout<<"\nEnter the Title: ";
		getline(cin,title);
		cout<<"\nEnter the Author: ";
		getline(cin,author);
		cout<<"\nEnter the Publication Date: ";
		if(!(cin>>date)) 
		{
			Return_Error("Invalid Input");
			return;
		}
		ofstream obj("SF_Catalog.doc",::ios::app);     //Change to append or ate file
		if(!File_Error_Check_out(obj)) return;
		obj << title <<endl
			<< author << endl
			<< date << endl
			<< endl;
		cout<<"\nEntry made."<<endl;
		cout<<"\nPress any key to return to menu..."<<endl;
		cin.ignore();
		cin.get();
	}
};

class Cat_Remove : public Book
{
private:
	string r_search;
	string c_space;
	string t_title;
	string t_author;
	char choice;
	int choose;
	Node obj;
public:
	Cat_Remove(){}
	~Cat_Remove(){}
protected:
	
	void init()
	{
		Clear_screen();
		cin.sync();
		cout<<"--Remove from Catalog--\n"<<endl;
		cout<<"Would you like to search for a Title, or "
			<<"an Author to remove?\n"<<endl;
		cout<<"1. Title \n"
			<<"2. Author \n"
			<<"3. Main Menu \n"<<endl;
		cout<<"Choice: ";
		if(!(cin>>choose)) 
		{
			Return_Error("Incorrect Choice");
			return;
		}
		switch(choose)
		{
		case 1:
			Title_Input();
			break;
		case 2:
			Author_Input();
			break;
		case 3:
			break;
		default:
			Return_Error("Invalid Option");
			break;
		}
	}

	void Title_Input()
	{
		cin.sync();
		cout<<"\nTitle to Remove: ";
		getline(cin, r_search);
		Title_Remove(r_search);
	}
	void Author_Input()
	{
		cin.sync();
		cout<<"\nAuthor to search for: ";
		getline(cin, r_search);
		Author_Remove(r_search);
	}

	void Title_Remove(string r_search)
	{
		ifstream search("SF_Catalog.doc");
		if(!File_Error_Check_in(search)) return;
		ofstream temp("Temp.doc", ios::app);
		if(!File_Error_Check_out(temp)) return;
		while(search.is_open())
		{	
			Clear_screen();
			getline(search, obj.title);
			t_title = obj.title;
			if(t_title.size() == 0) break;
			getline(search, obj.author);
			//t_author = obj.author;
			//if(t_author.size() == 0) break;
			getline(search, obj.date);
			getline(search, c_space);

			if(obj.title == r_search)
			{
				cout<<"\nLooking...\n"<<endl;
				cout<<"\nFound match: \n\n"
					<< obj.title << endl
					<< obj.author << endl
					<< obj.date << endl
					<< endl;
				cout<<"\nWas this the Book you wanted to remove?\n"
					<<"(y or n): ";
				cin >> choice;
				switch(choice)
				{
				case 'y':
					Remove_book(obj);
					break;
				case 'n':
					No_Remove(obj, temp);
					break;
				default:
					Error("Invalid Option");
				}
				if(choice != 'y' && choice != 'n') Error("Invalid option");
			}
			else No_Remove(obj, temp);
			if(search.eof()) search.close();
		}
		system("copy Temp.doc SF_Catalog.doc");
		temp.close();
		system("del Temp.doc");
		Clear_screen();
		cout<<"\nComplete."<<endl;
		cout<<"\nPress any key to return to menu..."<<endl;
		cin.get();
	}

	void Author_Remove(string r_search)
	{
		ifstream search("SF_Catalog.doc");
		if(!File_Error_Check_in(search)) return;
		ofstream temp("Temp.doc", ios::app);
		if(!File_Error_Check_out(temp)) return;
		while(search.is_open())
		{	
			Clear_screen();
			getline(search, obj.title);
			t_title = obj.title;
			if(t_title.size() == 0) break;
			getline(search, obj.author);
			t_author = obj.author;
			if(t_author.size() == 0) break;
			getline(search, obj.date);
			getline(search, c_space);

			if(obj.author == r_search)
			{
				cout<<"\nLooking...\n"<<endl;
				cout<<"\nFound match: \n\n"
					<< obj.title << endl
					<< obj.author << endl
					<< obj.date << endl
					<< endl;
				cout<<"\nWas this the Book you wanted to remove?\n"
					<<"(y or n): ";
				cin >> choice;
				switch(choice)
				{
				case 'y':
					Remove_book(obj);
					break;
				case 'n':
					No_Remove(obj, temp);
					break;
				default:
					Error("Invalid Option");
				}
				if(choice != 'y' && choice != 'n') Error("Invalid option");
			}
			else No_Remove(obj, temp);
			if(search.eof()) search.close();
		}
		system("copy Temp.doc SF_Catalog.doc");
		temp.close();
		system("del Temp.doc");
		Clear_screen();
		cout<<"\nComplete."<<endl;
		cout<<"\nPress any key to return to menu..."<<endl;
		cin.get();
	}

	void Remove_book(Node &obj)
	{
		cin.sync();
		cout<<"\n"<< obj.title <<" removed."<<endl;
	}

	void No_Remove(Node &obj, ofstream &temp)
	{
		cin.sync();
		if(temp.is_open())
		{
			temp << obj.title <<endl
			<< obj.author << endl
			<< obj.date << endl
			<< c_space <<endl;
		}
		else Return_Error("Error writing to File.");
	}

};

void Cat_help()
{
	Clear_screen();
	cout<<"--Help--"<<endl;
	cout<<"\nIf this is your first time using this program, \n"
		<<"here are some tips you might find useful: \n"
		<<"\n1. Wherever you have this program saved, \n"
		<<"your catalog will appear in the same location.\n"
		<<"2. Your catalog will appear after you make your \n"
		<<"first entry.\n"
		<<"3. Navigate the menu by the number associated \n"
		<<"with that option.\n"
		<<"4. Entries are made as Title: Author: Date:."
		<<endl;
	cout<<"\nPress any key to return to menu..."<<endl;
	cin.ignore();
	cin.get();
}
#endif
