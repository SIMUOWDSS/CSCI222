#include <fstream>
#include <iostream>
#include <string>
#include "sha256.h"
#include <sstream>
#include "Stock.h"

using namespace std;

class user {
	public:
	string usernm;
	string role;	// 0 staff, 1 Admin
	string pass;
	string lockStatus; // 0 unlocked, 1 locked
};

//int stockMain();
user globTotalUserArr[100];
string thisUser, thisSaltPass, thisRole;

int adduser(){
	string userinput, salt;
	int newRole;
	cout << "Please enter a username: ";
	cin >> userinput;
    //cout << "Username: \"" << username << "\"\n";
	
	string password1, password2; 
	cout << "Please enter your password: ";
	cin >> password1;
	cout << "Please re-enter your password: ";
	cin >> password2;
   	cout << "Please Enter 0 for Staff or 1 for Admin: ";
	cin >> newRole;
   	while (password1 != password2) {
       	cout << "Error! Passwords do not match." "\n";
        cout << "Please enter your password.";
		cin >> password1;
		cout << "Please re-enter your password.";
		cin >> password2;
    }
	
	salt = userinput + password1;
	string output1 = sha256(salt);
	
	ofstream	myFile;
	myFile.open("user.txt", fstream::app);
	myFile << userinput << ":" << newRole << ":" << output1 << ":" << "0" <<endl;
	myFile.close();
	
	return 0;
}

int getUsers (){
	/*cout << "Enter the name of Product to Add. [Enter: Return]" << endl;
	getline(std::cin, productName);
	if (productName.empty()){
		cout << "No input was detected!\nReturning to menu.\n" << endl;
		return 0;
	}//*/

	ifstream jinFile;
	jinFile.open("user.txt");
    if (!jinFile){
		cerr << "Unable to open file userdatafile";
    	exit(1);   // call system to stop
	}

	string jLine;
	int j = 0;
	while (getline(jinFile, jLine)){
		if (!jLine.empty()){ 					//If line is not empty, feed into uArr
			stringstream linestream(jLine);
			string jUser, jRole, jPass, jLockStat;

			//Get username > uArr
			getline(linestream, jUser, ':');
			globTotalUserArr[j].usernm = jUser;

			//Get role > uArr
			getline(linestream, jRole, ':');
			globTotalUserArr[j].role = jRole;

			//Get passwd > uArr
			getline(linestream, jPass, ':');
			globTotalUserArr[j].pass = jPass;

			//Get lockstat > uArr
			getline(linestream, jLockStat, '\r');
			globTotalUserArr[j].lockStatus = jLockStat;
		}
		j++;
	}

	return 1;
}

int jLogin(){
	cout << "jLogin()" << endl;
	
	string userJnput, passJnput, sJalt;
	int j = 0;
	int joginFail;

	cout << "Kindly enter username:" << endl;
	getline(std::cin, userJnput);
	if (userJnput.empty()){
		cout << "No input was detected!\nReturning to menu.\n" << endl;
		return 0;
	}

	cout << "Kindly enter password:" << endl;
	getline(std::cin, passJnput);
	if (passJnput.empty()){
		cout << "No input was detected!\nReturning to menu.\n" << endl;
		return 0;
	}

	sJalt = sha256(userJnput + passJnput);

	//check for existing users in uArr;
	while (globTotalUserArr[j].usernm != ""){
		if (userJnput == globTotalUserArr[j].usernm && sJalt == globTotalUserArr[j].pass){
			if (globTotalUserArr[j].lockStatus == "1"){
				cout << userJnput << ": Account Locked! Kindly contact admin for further assistance.";
				return 0;
			} else {
				thisUser = userJnput;
				thisSaltPass = sJalt;
				thisRole = globTotalUserArr[j].role;
				cout << userJnput << ": Login Successful!" << endl;

				return 1;
			}
		}
		j++;
	}
}

int jLogout(){
	cout << "jLogout()" << endl;
	thisUser="";
	thisSaltPass="";
	cout << "===================\n Logout Successful!\n===================" << endl;
	return 1;
}

void login(){
	string userinput, salt, password;
	ifstream open1("pass.txt");
	ofstream open2("lock.txt", fstream::app);
	ifstream open3("lock.txt");

	if (!open1){
		cerr << "Unable to open file passdatafile";
    	exit(1);   // call system to stop
	}

	string aline , aline2;
	
    
	int f =0;
	int g = 0;
	int i = 0;
	 
	int count = 0;
	user account;
	user account2;
	user array[100];
	user array2[100];
	cout << "Please enter a username: ";
	getline(cin, userinput);
	cout << "Please enter your password: ";
	getline(cin, password);
	salt = userinput + password;
	string output = sha256(salt);
	
	string tempUser2;
	while (getline(open3,aline2)){	//Read so long as lock.txt has line
		stringstream linestream2(aline2);
		
		getline(linestream2, tempUser2, ':');
		array2[g].usernm = tempUser2;
		if(userinput == array2[g].usernm){
			account2.usernm = array2[g].usernm;
			i++;
		}
		g++;
	}

	if (account2.usernm == userinput && i>0){
			cout << "Account is locked!"<< endl;
			cout << "Please contact Admin"<< endl;
			exit(1);
	}
	
	 
	while (getline(open1,aline)){
			
		string tempUser, tempPass, tempChoice;
		 
		stringstream linestream(aline);
		
		getline(linestream, tempUser, ':');
		getline(linestream, tempChoice, ':');
		getline(linestream, tempPass);
		array[f].usernm = tempUser;
		array[f].role = tempChoice;
		array[f].pass = tempPass;
		if (userinput == array[f].usernm){
			account.usernm = array[f].usernm;
			account.role = array[f].role;
			account.pass = array[f].pass;
			i++;
		}
		f++;
	}
	
	
	  
	while(userinput == account.usernm ){
		if ( account.role == "0" && userinput == account.usernm && output == account.pass && i> 0){
		   	cout << output << endl;
		   	cout << account.pass << endl;
			cout << "Login successfully." << endl;
			cout << "welcome Admin." << endl;
		  	exit(1);
		} else if ( account.role == "1" && userinput == account.usernm && output == account.pass && i> 0){
		   cout << output << endl;
		   cout << account.pass << endl;
			cout << "Login successfully." << endl;
			cout << "welcome Staff." << endl;
		  exit(1);
		} else {
		   cerr << "Wrong username or password!" << "?" << endl;
		}
	   
		while (output != account.pass && i> 0){
		    string username1, password1, salt1;
	  
		    
			cout << "Please enter a username.2";
			getline(cin, username1);
			cout << "Please enter your password.2";
			getline(cin, password1);
			salt1 = username1 + password1;
			string output1 = sha256(salt1);
			if ( output1 != account.pass && i> 0){				
					count++;
			} else if (account.role == "0" && output1 == account.pass && i>0){
				cout << output1 << endl;
				cout << account.pass << endl;
				cout << "Login successfully." << endl;
				cout << "welcome Admin." << endl;
				exit(1);
			} else if (account.role == "1" && output1 == account.pass && i>0){
				cout << output1 << endl;
				cout << account.pass << endl;
				cout << "Login successfully." << endl;
					
				cout << "welcome Staff." << endl;
				exit(1);
			}
	   
		   if (open2.is_open() && count == 2 && i>0 ){
			   
			   cout << "Account is locked, please contact the admin";
			   open2 << account.usernm << ":" << account.pass << endl;
				exit(1);
		   
		   }
		}
	}
	cout << "---Files closing---\n";
	open1.close();
	open2.close();
	open3.close(); 
}

int main (){
	//adduser();
	//login();
	getUsers(); //Put all users into array;
	while (1){
		if (jLogin()){
			//jLogout();
			if (thisRole == "0"){
				//Staff
				jLogout();
			} else if (thisRole == "1"){
				//Admin
				stockMain();
				jLogout();
			}
		}
	}
	
}