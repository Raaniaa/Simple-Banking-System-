#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;
/*Model, design and develop a banking application. The banking application allows the user, i.e., the
bank employee to create a bank account for a specific client. It allows him to list all the available
bank accounts. For each account, it allows him to display the account details, withdraw money and
deposit money*/

class BankApplication{
public:
    BankApplication();
};

class account
{
protected:
	int account_id;
	char name[50];
	int balance;
	char type;
public:

	void create_account();
	void show_account() const;
	void modify();
	void dep(int);
	void draw(int);
	void report() const;
	int retacno() const;
	int retdeposit() const;
	char rettype() const;
};
class client
{
	protected:
	int account_id;
	char name[50];
	int balance;
	char type;


};
//function to get data from user
void account::create_account()
{
	system("CLS");
	cout<<"\n\t\t\tPlease Enter Account ID =========>";
	cin>>account_id;
	cout<<"\n\n\t\t\tPlease Enter Client Name =========> ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\t\t\tWhat Type of Account Do You Like? (1) Basic (2) Saving – Type 1 or 2 =========> ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\t\t\tPlease Enter the Starting Balance =========>";
	cin>>balance;
	cout<<"\n\n\t\t\tAn account was created with ID "<<account_id<< " and Starting Balance"<<balance<<"L.E";
}
//function to show data on screen
void account::show_account() const
{
	cout<<"\n\t\t\tAccount No. : "<<account_id;
	cout<<"\n\t\t\tAccount Holder Name : ";
	cout<<name;
	cout<<"\n\t\t\tType of Account : "<<type;
	cout<<"\n\t\t\tBalance amount : "<<balance;
}

//function to get new data from user
void account::modify()
{
	cout<<"\n\t\t\tAccount No. : "<<account_id;
	cout<<"\n\t\t\tModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\t\t\tModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\t\t\tModify Balance amount : ";
	cin>>balance;
}

//function to accept amount and add to balance amount
void account::dep(int x)
{
	balance+=x;
}
//function to accept amount and subtract from balance amount
void account::draw(int x)
{
	balance-=x;
}
//function to show data in tabular format
void account::report() const
{
	cout<<account_id<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<balance<<endl;
}
//function to return account number
int account::retacno() const
{
	return account_id;
}
//function to return balance amount
int account::retdeposit() const
{
	return balance;
}
//function to return type of account
char account::rettype() const
{
	return type;
}



void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);

int main()
{ 	// Output options

	char ch;
	int num;
	do
	{
	system("CLS");
	cout<<"\n\n\t\t\t\t=========================================================================\n";
	cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t Welcome to FCI Banking Application";
	cout<<"\n\t\t\t\t===========================================================================\n";
		cout<<"\n\t\t\t\t1. Create a New Account";
		cout<<"\n\t\t\t\t2. Deposit Mone";
		cout<<"\n\t\t\t\t3. Withdraw Money";
		cout<<"\n\t\t\t\t4. Balance details";
		cout<<"\n\t\t\t\t5. List Clients and Accounts";
		cout<<"\n\t\t\t\t6. Close the account";
		cout<<"\n\t\t\t\t7. Modify the account";
		cout<<"\n\t\t\t\t8. Exit";
		cout<<"\n\n\t\t\t\tPlease Enter Choice =========>";
		cin>>ch;

		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			system("CLS");
			cout<<"\n\n\t\t\tPlease Enter Account ID  =========>"; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			system("CLS");
			cout<<"\n\n\t\t\tPlease Enter Account ID  =========>"; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			system("CLS");
			cout<<"\n\n\t\t\tPlease Enter Account ID  =========>"; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			system("CLS");
			cout<<"\n\n\t\t\tPlease Enter Account ID  =========> "; cin>>num;
			delete_account(num);
			break;
		 case '7':
		 	system("CLS");
			cout<<"\n\n\t\t\tPlease Enter Account ID  =========>"; cin>>num;
			modify_account(num);
			break;
		 case '8':
		 	system("CLS");
			cout<<"\n\n\t\t\tBrought To You By code-projects.org";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!='8');
	return 0;
}

//function to write record in binary file
void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}
//function to display account details given by user
void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open ";
		return;
	}
	cout<<"\n\t\t\tBALANCE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\n\t\t\tAccount number does not exist";
}

//function to modify record of file
void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open ";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\n\t\t\tEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur); //fncallat1353
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		    cout<<"\n\n\t\t\tRecord Updated";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found ";
}


//function to delete record of file
void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open ";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\nRecord Deleted ..";
}

//function to display all account details
void display_all()
{
	system("CLS");
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

// function to desposit/withdraw amount for given account
void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\t\t\tTO DEPOSITSS AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be deposited: ";
				cin>>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				cout<<"\n\n\t\t\tTO WITHDRAW AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be withdraw: ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if(bal<0)
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);//fn1353
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t\t\tRecord Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found ";
}
