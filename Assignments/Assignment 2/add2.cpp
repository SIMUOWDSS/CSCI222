#include "aes.h"
#include "hex.h"
#include "modes.h"
#include "osrng.h"
#include "pwdbased.h"
#include <fstream>
#include <iostream>
#include <string>
#include "sha256.h"
#include <sstream>

using namespace std;

class user {
	public:
	string user1;
	string pass;
};

int adduser()
{
	string username, salt;
	cout << "Please enter a username.";
	cin >> username;
    cout << "Username: \"" << username << "\"\n";
	
	string password1; 
	cout << "Please enter your password.";
	cin >> password1;
    string password2 ;
	cout << "Please re-enter your password.";
	cin >> password2;
   
   while (password1 != password2) {
       cout << "Error! Passwords do not match." "\n";
        cout << "Please enter your password.";
		cin >> password1;
		cout << "Please re-enter your password.";
		cin >> password2;
    }
	
	salt = username + password1;
	string output1 = sha256(salt);
	
	ofstream	myFile;
	myFile.open("pass.txt", fstream::app);
	myFile << username << ":" << output1 << endl;
	myFile.close();
	
	return 0;
}



void login()
{	
	string username, salt, password;
	
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
cout << "Please enter a username.1";
	getline(cin, username);
	cout << "Please enter your password.1";
	getline(cin, password);
	salt = username + password;
	string output = sha256(salt);
	
			string tempUser2;
		 while (getline(open3,aline2))	
	
	 {	
	 
			
		stringstream linestream2(aline2);
		
		getline(linestream2, tempUser2, ':');
		array2[g].user1 = tempUser2;
		if(username == array2[g].user1)
		{
			account2.user1 = array2[g].user1;
			i++;
		}
		g++;
	 }
		 if (account2.user1 == username && i>0)
		{
			cout << "account is locked !"<< endl;
			exit(1);
		}
	
	 
		while (getline(open1,aline))
		{
			
		 string tempUser, tempPass;
		 stringstream linestream(aline);
		
		getline(linestream, tempUser, ':');
		getline(linestream, tempPass);
		array[f].user1 = tempUser;
		array[f].pass = tempPass;
		if (username == array[f].user1)
		{
		account.user1 = array[f].user1;
		account.pass = array[f].pass;
		i++;
		}
		f++;
		
		
		
		}
	
		
	   
		while(username == account.user1 )
	   {
		   // string username1, password1, salt1;
   // salt1 = username + password;
	// string output1 = sha256(salt);
		   if ( username == account.user1 && output == account.pass && i> 0)
	   {
		   cout << output << endl;
		   cout << account.pass << endl;
			cout << "Login successfully." << endl;
		  exit(1);
	   }
	   else
	   {
		   cerr << "Wrong username or password!" << "?" << endl;
		   
	   }
	   
	   while (output != account.pass && i> 0)
	   {
	    string username1, password1, salt1;
  
	    
		cout << "Please enter a username.2";
	getline(cin, username1);
	cout << "Please enter your password.2";
	getline(cin, password1);
	salt1 = username1 + password1;
	string output1 = sha256(salt1);
	  if ( output1 != account.pass && i> 0)
	  {				
		  
			count++;
	 }else if (output1 == account.pass && i>0)
	 {
		 cout << output1 << endl;
		   cout << account.pass << endl;
			cout << "Login successfully." << endl;
		  exit(1);
	 }	 
	   }
	 
	 
	
		   
	   
	   if (open2.is_open() && count == 3 && i>0 )
		   // else
	   {
		   
		   cout << "account is lock";
		   open2 << account.user1 << ":" << account.pass << endl;
			exit(1);
	   
	   }
	   }
		  
	   
	    
	  
		
	
	cout << "---infile closing---\n";
	 open1.close();
	 open2.close();
	  open3.close(); 
	  
	
		
}


	


 int main ()
 {
	 
	 // adduser();
	 login();
 }