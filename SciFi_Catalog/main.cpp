#include"interface.h"

int main()
{
	int choice = 0;
	cout<<"Welcome to the Sci-Fi cataloging program."<<endl;
	cout<<endl;
	enter_password();
	cout<<"\nPlease press enter to view cataloging mode..."<<endl;
	cin.get();
	while(true)
	{
		Show_catalog();
		if(!Accept_Input()) return false;
	}
	return 0;
}

void Show_catalog()
{
	Clear_screen();
	cout<<"--Catalog Menu--"<<endl;
	cout<<"    1. Search\n" 
		<<"    2. View all\n" 
		<<"    3. Add to catalog\n" 
		<<"    4. Remove from catalog\n" 
		<<"    5. Help (If first time navigate here)\n"
		<<"    6. Quit\n" <<endl;
}
	
bool Accept_Input()
{
	Book obj;
	Cat_Search obj2;
	Cat_View obj3;
	Cat_Add_To obj4;
	Cat_Remove obj5;
	int choice = 0;
	cout<<"Navigate to: ";
	if(!(cin>>choice)) Return_Error("\nUnknown option");
	switch(choice)
	{
	case 1:
		obj.nav_catalog(obj2);
		return true;
		break;
	case 2:
		obj.nav_catalog(obj3);
		return true;
		break;
	case 3:
		obj.nav_catalog(obj4);
		return true;
		break;
	case 4:
		obj.nav_catalog(obj5);
		return true;
		break;
	case 5:
		Cat_help();
		return true;
		break;
	case 6:
		cout<<"\nThank you for using our program, Goodbye."<<endl;
		cout<<endl;
		cin.ignore();
		cin.get();
		return false;
		break;
	default:
		Return_Error("\nUnknown option");
		return true;
	}
}
