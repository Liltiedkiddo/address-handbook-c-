#include<iostream>
#include<conio.h>
#include<fstream>
using namespace std;

class address {
private:
    char fname[50], lname[50], sex[50], address[50], email[50], state[50], occupation[50];
    long long phno;

public:
    void addpeople() {
       cout<< "Enter your  first name"<<endl;
    		cin>>fname;
    		
    		cout<< "Enter your last name"<<endl;
    		cin>>lname;
    		
    		cout<<"Enter your phone number"<<endl;
    		cin>>phno;
    		
    		cout<< "Enter your sex"<<endl;
    		cin>>sex;
    		
    		cout<< "Enter your address"<<endl;
    		cin>>address;
    		
    		cout<< "Enter your email"<<endl;
    		cin>>email;
    		
    		cout<<"Enter your occupation"<<endl;
    		cin>>occupation;
    		
    		cout<< "Enter your state "<<endl;
    		cin>>state;
    }

    void showaddress() {
      cout<<"Name: "<<fname<<" "<<lname<<endl;
			cout<<"phone number: "<<phno<<endl;
			cout<<"Sex: "<<sex<<endl;
			cout<<"Address: "<<address<<endl;
			cout<<"Email: "<<email<<endl;
			cout<<"State: "<<state<<endl;
			cout<<"Occupation: "<<occupation<<endl;
    }

    void saveinfile() {
     	char ch;
			ofstream f1;
			f1.open("AMS.dat", ios::binary | ios::app);
			
		    do{
		    		addpeople();
			        f1.write(reinterpret_cast<char*>(this), sizeof(*this));
			        cout<<"Do you have next data? (y/n)";
			        cin>>ch;
			}while(ch=='y');
			
			cout<<"Adress has been successful added"<<endl;
			f1.close();
    }

    void readfromfile() {
       ifstream f2;
			f2.open("AMS.dat", ios::binary); 
			
			cout<<"\n===========================\n";
			cout<<"LIST OF ADDRESS";
			cout<<"\n===========================\n";
			
			while(!f2.eof()){
				if(f2.read(reinterpret_cast<char*>(this), sizeof(*this))){
					showaddress();
					cout<<"\n===========================\n";
				}
			}
			f2.close();
    }

    void searchonfile() {
       	ifstream f3;
			long long phone;
			cout<<"Enter phone number: ";
			cin>>phone; 
			f3.open("AMS.dat", ios::binary);
			
			while(!f3.eof()){
				if(f3.read(reinterpret_cast<char*>(this), sizeof(*this))){
					if(phone == phno){
						showaddress();
						return;
					}
				}
			}
			cout<<"\n\nNo record found";
			f3.close();
    }

    void deletefromfile() {
       long long phone;
			int flag = 0;
			ofstream f4;
			ifstream f5;
			
			f5.open("AMS.dat", ios::binary);
			f4.open("temp.dat", ios::binary);
			
			cout<<"Enter the phone number for the person you want to delete:";
			cin>>phone;
			
			while(!f5.eof()) {
				if(f5.read(reinterpret_cast<char*>(this), sizeof(*this))){
					if(phone != phno) {
						f4.write(reinterpret_cast<char*>(this), sizeof(*this));
					}
					else flag = 1;
				}
			}
			f5.close();
			f4.close();
			remove("AMS.dat");
			rename("temp.dat", "AMS.dat");
			
			flag == 1 ?
			cout<<"\Address deleted....":
			cout<<"\Address not found....";
				
    }

    void editaddress() {
      	long long phone;
			fstream f6;
			
			cout<<"Edit address";
			cout<<"\n=============================\n";
			cout<<"Enter the phone no of the person to be edited";
			cin>>phone;
			
			f6.open("AMS.dat", ios::binary|ios::out|ios::in);
			while(!f6.eof()) {
				if(f6.read(reinterpret_cast<char*>(this), sizeof(*this))){
					if(phone == phno) {
						cout<<"Enter new record\n";
						addpeople();
						
						int pos = -1*sizeof(*this);
						f6.seekp(pos, ios::cur); 
						f6.write(reinterpret_cast<char*>(this), sizeof(*this));
						cout<<endl<<endl<<"\tAddress successful updated...";
						return; 
					}
				}
			}
			cout<<"\n\nNo Record found";
			f6.close();
			
    }
};

int main() {
    system("cls");
    system("color 7E"); // Background color: nude, Text color: gray

    cout << "\n\n\n\n\n\n\n\t\t\t\t* WELCOME TO THE ADDRESS HANDBOOK *";
    getch();

    address a1;
    int choice;

    do {
        system("cls");
        cout << "\nADDRESS HANDBOOK";
        cout << "\n\nMAIN MENU";
        cout << "\n==========================\n";
        cout << "[1] Add a new Address\n";
        cout << "[2] List the addresses\n";
        cout << "[3] Search address\n";
        cout << "[4] Delete address\n";
        cout << "[5] Edit address\n";
        cout << "[0] Exit\n";
        cout << "\n================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system("cls");
            a1.saveinfile();
            break;

        case 2:
            system("cls");
            a1.readfromfile();
            break;

        case 3:
            system("cls");
            a1.searchonfile();
            break;

        case 4:
            system("cls");
            a1.deletefromfile();
            break;

        case 5:
            system("cls");
            a1.editaddress();
            break;

        case 0:
            system("cls");
            cout << "\n\n\n\t\t thank you for using address handbook." << endl << endl;
            exit(0);
            break;

        default:
            cout << "";
        }

        int opt;
        cout << "\n\n..::Enter the Choice:\n[1] Main Menu\t\t[0] Exit\n";
        cin >> opt;

        if (opt == 0) {
            system("cls");
            cout << "\n\n\n\t\t thank you for using address handbook." << endl << endl;
            exit(0);
        }

    } while (true);

    return 0;
}
