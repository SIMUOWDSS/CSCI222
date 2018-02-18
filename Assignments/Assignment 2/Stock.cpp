#include "Stock.h"
using namespace std;

//CSCI222
//JOSHUA TAN JUN JIE
//Q1 2018

/*class Stock {
public:
	int PID = 0;
	string Name;
	string Category;
	string SubCategory;
	double Price;
	int Quantity;
	string TranscDate;

	bool ProductStatus;
	int ViewType;
	
	int AddProduct();
	int commitFileChange();
	int EditProduct();
	int RemoveProduct();
	int SearchProduct();
	int SummaryReport();
	int RetrieveProduct();
private:

};//*/

StockRecord readStockArray[1000];
string fileName = "SampleData.txt";
ifstream inFile;

string productName;
string productCategory;
string productSubCategory;
double productPrice;
int productQuantity;

bool productProductStatus;
int productViewType;//*/

string returnNowDate(){
	//Returns local date
	time_t now = time(0);
	tm *gmtm = localtime(&now);
   	char *dt = asctime(gmtm);
	string s = dt;
	//cout << s << endl;

	stringstream linestream(s);
	string dateDayAlp, dateMonth, dateDayNum, dateTime, dateYear, dateReturn;

	getline(linestream, dateDayAlp, ' ');
	getline(linestream, dateMonth, ' ');
	getline(linestream, dateDayNum, ' ');
	getline(linestream, dateTime, ' ');
	getline(linestream, dateYear);
	dateYear.erase(0,2);
	//dateYear.erase(3,5);

	dateReturn = dateDayNum + "-" + dateMonth + "-" + dateYear;
	//dateReturn.erase(std::find_if(dateReturn.rbegin(), dateReturn.rend(), [](int ch) {return !std::isspace(ch);}).base(), dateReturn.end());
    //cout << dateReturn << endl;
	return dateReturn;
}

int returnSummaryStartDate(string summaryPChoice){
	string nowDate = returnNowDate();
	cout << nowDate << endl;
	//string trimDate = nowDate;
	StockRecord uniqueStockArr[50];
	//string strDay, strMonth, strYear;
	int i = 0; 			//Iterators
	int liquid = 0;	//Total costs of stocks from period's transactions
	/*stringstream linestream(trimDate);
	getline(linestream, strDay, '-');
	getline(linestream, strMonth, '-');
	getline(linestream, strYear);

	/*string setMonths[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	while (setMonths[i] != strMonth){
		//cout << setMonths[i] << " :: "<< strMonth << endl;
		i++;
	}//*/

	//string setDays[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"};

	//i = 0;

	if (summaryPChoice == "1"){
		//Daily 
		while (readStockArray[i].PID != 0 || readStockArray[i].Name != ""){ //Runs stock array
			if (nowDate == readStockArray[i].TranscDate){ // If it is present date
				//cout << "================\nMatch Found!" << endl;
				for (int a = 0; a < 50; ++a){
					//cout << "|"<< uniqueStockArr[a].PID << ":" << readStockArray[i].PID << "? ";
					if (uniqueStockArr[a].PID == readStockArray[i].PID && readStockArray[i].Name != ""){ //If names match, and name is not blank add quantity to uniqueStockArr
						uniqueStockArr[a].PID = readStockArray[i].PID;
						uniqueStockArr[a].Name = readStockArray[i].Name;
						uniqueStockArr[a].Category = readStockArray[i].Category;
						uniqueStockArr[a].SubCategory = readStockArray[i].SubCategory;
						uniqueStockArr[a].Price = readStockArray[i].Price;
						uniqueStockArr[a].Quantity = uniqueStockArr[a].Quantity + readStockArray[i].Quantity;
						//cout << "stockitem Updated" << endl;
						a=50;
					} 

					if (uniqueStockArr[a].PID == 0 && uniqueStockArr[a].Name == ""){ //If loop cannot find in uniqueStockArr, means need to add new unique stock entry
						uniqueStockArr[a].PID = readStockArray[i].PID;
						uniqueStockArr[a].Name = readStockArray[i].Name;
						uniqueStockArr[a].Category = readStockArray[i].Category;
						uniqueStockArr[a].SubCategory = readStockArray[i].SubCategory;
						uniqueStockArr[a].Price = readStockArray[i].Price;
						uniqueStockArr[a].Quantity = readStockArray[i].Quantity;
						//cout << "New stockitem Added" << endl;
						a=50;
					}
				}
			}
			i++;
		}
	} else if (summaryPChoice == "2"){
		//Weekly

	} else if (summaryPChoice == "3"){
		//Yearly
	} else if (summaryPChoice == "4"){
		//All-time
		while (readStockArray[i].PID != 0 || readStockArray[i].Name != ""){ //Runs stock array
				//cout << "================\nMatch Found!" << endl;
				for (int a = 0; a < 50; ++a){
					//cout << "|"<< uniqueStockArr[a].PID << ":" << readStockArray[i].PID << "? ";
					if (uniqueStockArr[a].PID == readStockArray[i].PID && readStockArray[i].Name != ""){ //If names match, and name is not blank add quantity to uniqueStockArr
						uniqueStockArr[a].PID = readStockArray[i].PID;
						uniqueStockArr[a].Name = readStockArray[i].Name;
						uniqueStockArr[a].Category = readStockArray[i].Category;
						uniqueStockArr[a].SubCategory = readStockArray[i].SubCategory;
						uniqueStockArr[a].Price = readStockArray[i].Price;
						uniqueStockArr[a].Quantity = uniqueStockArr[a].Quantity + readStockArray[i].Quantity;
						//cout << "stockitem Updated" << endl;
						a=50; //Exits for loop
					} 

					if (uniqueStockArr[a].PID == 0 && uniqueStockArr[a].Name == ""){ //If loop cannot find in uniqueStockArr, means need to add new unique stock entry
						uniqueStockArr[a].PID = readStockArray[i].PID;
						uniqueStockArr[a].Name = readStockArray[i].Name;
						uniqueStockArr[a].Category = readStockArray[i].Category;
						uniqueStockArr[a].SubCategory = readStockArray[i].SubCategory;
						uniqueStockArr[a].Price = readStockArray[i].Price;
						uniqueStockArr[a].Quantity = readStockArray[i].Quantity;
						//cout << "New stockitem Added" << endl;
						a=50; //Exits for loop
					}
				}
			i++;
		}
	}

	//Print table
	int p = 0;
	printf("===========================================================================================================\n%-6s %-30s %-20s %-20s %-11s %-10s\n", "PID", "Name", "Category", "SubCategory", "Price", "Quantity");
	while (uniqueStockArr[p].PID != 0) {
		printf("%-6i %-30s %-20s %-20s %-11f %-10i\n", uniqueStockArr[p].PID, uniqueStockArr[p].Name.c_str(), uniqueStockArr[p].Category.c_str(), uniqueStockArr[p].SubCategory.c_str(), uniqueStockArr[p].Price, uniqueStockArr[p].Quantity);
		liquid = liquid + (uniqueStockArr[p].Price*uniqueStockArr[p].Quantity);
		p++;
	}
	cout << "\n===========================================================================================================\nTotal Cost of displayed Inventory: $" << liquid << "\n===========================================================================================================" << endl;
	//End Print table
	return 1;
}

int commitFileChange(int arri){
	string rawData, strPID;
	fstream filestr;
	stringstream ss;
	
	// the number is converted to string with the help of stringstream
	ss << readStockArray[arri].PID; 
	string ret;
	ss >> strPID;
	
	// Append zero chars
	int str_length = strPID.length();
	for (int i = 0; i < 3 - str_length; i++){
		strPID = "0" + strPID;
	}

	//cout << readStockArray[arri].Price;
	rawData =  strPID + ":" + readStockArray[arri].Name + ":" + readStockArray[arri].Category + ":" + readStockArray[arri].SubCategory + ":" + to_string(readStockArray[arri].Price) + ":" + to_string(readStockArray[arri].Quantity) + ":" +  readStockArray[arri].TranscDate;

  	filestr.open(fileName, fstream::in | fstream::out | fstream::app);
  	filestr << rawData << endl;
	filestr.close();
	return 1;
}

int AddProduct(){
	cout << "AddProduct()\n";
	productName="";
	string sCat, sSubCat, sPrice, sQnty;
	int aPID;

	cout << "Enter the name of Product to Add. [Enter: Return]" << endl;
	getline(std::cin, productName);
	if (productName.empty()){
		cout << "No input was detected!\nReturning to menu.\n" << endl;
		return 0;
	}

	int i = 0;
	int f = 0;
	StockRecord addStockSample, newStockInput;
	while (readStockArray[i].Name != "" || readStockArray[i].PID != 0){
		//if match Product Name
		if (readStockArray[i].Name == productName){
			addStockSample.PID = readStockArray[i].PID;
			addStockSample.Name = readStockArray[i].Name;
			addStockSample.Category = readStockArray[i].Category;
			addStockSample.SubCategory = readStockArray[i].SubCategory;
			addStockSample.Price = readStockArray[i].Price;
			f++;
		}//*/
		i++;
	}

	if (f > 0){
		//There are existing entries in DB
		cout << "Existing entries found!" << endl;
		cout << "\n\n=========================" << endl;
		cout << "PID: 		" << addStockSample.PID << endl;
		cout << "Name:		" << addStockSample.Name << endl;
		cout << "Category:	" << addStockSample.Category << endl;
		cout << "SubCategory:	" << addStockSample.SubCategory << endl;
		cout << "Price: 		" << addStockSample.Price << endl;
		cout << "\n=========================" << endl;//*/

		cout << "Enter Quantity of product to add. [Enter: Return]" << endl;
		string addQnty;
		getline(std::cin, addQnty);

		if (addQnty.empty()){
			cout << "No input was detected!\nReturning to menu.\n" << endl;
			return 0;
		} else if (((!isdigit(addQnty[0])) && (addQnty[0] != '-') && (addQnty[0] != '+'))){
			cout << "Non-numeric characters detected!\n Returning to menu." <<endl;
			return 0;
		} else {
			readStockArray[i].PID = addStockSample.PID;
			readStockArray[i].Name = addStockSample.Name;
			readStockArray[i].Category = addStockSample.Category;
			readStockArray[i].SubCategory = addStockSample.SubCategory;
			readStockArray[i].Price = addStockSample.Price;
			readStockArray[i].Quantity = stoi(addQnty);
			readStockArray[i].TranscDate = returnNowDate();
			commitFileChange(i);
			cout << "File changes committed!\nReturning to menu." <<endl;
		} 

	} else {
		cout << "New entry detected!" << endl;

		cout << "Enter Category of product to add. [Enter: Return]" << endl;
		getline(std::cin, sCat);
		if (sCat.empty()){
			cout << "No input was detected!\nReturning to menu.\n" << endl;
			return 0;
		}

		cout << "Enter SubCategory of product to add. [Enter: Return]" << endl;
		getline(std::cin, sSubCat);
		if (sSubCat.empty()){
			cout << "No input was detected!\nReturning to menu.\n" << endl;
			return 0;
		}

		cout << "Enter Price of product to add. [Enter: Return]" << endl;
		getline(std::cin, sPrice);
		if (sPrice.empty()){
			cout << "No input was detected!\nReturning to menu.\n" << endl;
			return 0;
		}

		cout << "Enter Quantity of product to add. [Enter: Return]" << endl;
		getline(std::cin, sQnty);
		if (sQnty.empty()){
			cout << "No input was detected!\nReturning to menu.\n" << endl;
			return 0;
		} else if (((!isdigit(sQnty[0])) && (sQnty[0] != '-') && (sQnty[0] != '+'))){
			cout << "Non-numeric characters detected!\n Returning to menu." <<endl;
			return 0;
		}

		int searchnewPID = 1;
		i = 0;
		while (readStockArray[i].Name != "" || readStockArray[i].PID != 0){// define unique PID in array;
			if (searchnewPID = readStockArray[i].PID){
				//cout << searchnewPID << ": PID match " << readStockArray[i].Name << endl;
				searchnewPID++;
			}
			cout << "i++" << endl;
			i++;
		}

		if (readStockArray[i].Name == "" && readStockArray[i].PID == 0){ //If array element is empty;
			readStockArray[i].PID = searchnewPID;
			readStockArray[i].Name = productName;
			readStockArray[i].Category = sCat;
			readStockArray[i].SubCategory = sSubCat;
			readStockArray[i].Price = stod(sPrice);
			readStockArray[i].Quantity = stoi(sQnty);
			readStockArray[i].TranscDate = returnNowDate();
			commitFileChange(i);
			cout << "File changes committed!\nReturning to menu." <<endl;
			return 1;
		}
	}
	return 1;
}

int RemoveProduct(){
	cout << "RemoveProduct()\n";
}

int EditProduct(){
	cout << "EditProduct()\n";
	cout << "Enter the name of Product to Search for. [Enter: Return]" << endl;
	getline(std::cin, productName);
	if (productName.empty()){
		cout << "No input was detected!\nReturning to menu.\n" << endl;
		return 0;
	}
}

int SearchProduct(){
	cout << "SearchProduct()\n";
	productName="";
	cout << "Enter the name of Product to Search for. [Enter: Return]" << endl;
	getline(std::cin, productName);
	if (productName.empty()){
		cout << "No input was detected!\nReturning to menu.\n" << endl;
		return 0;
	}
	int i = 0;
	int f = 0;
	int searchStockQnty = 0;
	StockRecord searchStockSample;
	while (readStockArray[i].Name != "" || readStockArray[i].PID != 0){
		
		//if match Product Name
		if (readStockArray[i].Name == productName){
			searchStockSample.PID = readStockArray[i].PID;
			searchStockSample.Name = readStockArray[i].Name;
			searchStockSample.Category = readStockArray[i].Category;
			searchStockSample.SubCategory = readStockArray[i].SubCategory;
			searchStockSample.Price = readStockArray[i].Price;
			searchStockQnty = searchStockQnty + readStockArray[i].Quantity;
			f++;
		}//*/

		i++;
	}

	if (f > 0){
		cout << "\n\n=========================" << endl;
		cout << "PID: " << searchStockSample.PID << endl;
		cout << "Name: " << searchStockSample.Name << endl;
		cout << "Category: " << searchStockSample.Category << endl;
		cout << "SubCategory: " << searchStockSample.SubCategory << endl;
		cout << "Price: " << searchStockSample.Price << endl;
		cout << "Quantity: " << searchStockQnty << endl;
		cout << "=========================" << endl;//*/
	} else {
		cout << "\nNo entries found!" << endl;
	}
}

int SummaryReport(){
	cout << "\n\nSummaryReport()\n";
	string summaryViewInput= "";
	cout << "=========================" << endl;
	cout << "1.		Day" << endl;
	cout << "2.		Month" << endl;
	cout << "3.		Year" << endl;
	cout << "4.		All-Time" << endl;
	cout << "=========================" << endl;
	cout << "Enter the Summary Report View period. [Enter: Return]" << endl;
	


	getline(std::cin, summaryViewInput);
	if (summaryViewInput.empty()){
		cout << "No input was detected!\nReturning to menu.\n" << endl;
		return 0;
	} 
	returnSummaryStartDate(summaryViewInput);
	/*else if (summaryViewInput == "1"){
		//cout <<  returnNowDate() << ": Option 1"<< endl;
		
	} else if (summaryViewInput == "2"){
		cout << returnNowDate() << ": Option 2" <<endl;
	} else if (summaryViewInput == "3"){
		cout << returnNowDate() << ": Option 3" <<endl;
	} else if (summaryViewInput == "4"){
		cout << returnNowDate() << ": Option 4" <<endl;
	}*/
}

int RetrieveProduct(){
	
}

int ReadFile(){
	inFile.open("SampleData.txt");
    if (!inFile){
		cerr << "Unable to open file stockdatafile";
    	exit(1);   // call system to stop
	}

	string line;
	int i = 0;
	while(getline(inFile, line)){
		//cout << "\n-------------\n " << line << endl;
		if (!line.empty()){
			stringstream linestream(line);
			string fPID, fproductName, fproductPrice, fproductQuantity, fproductCategory, fproductSubCategory, fproductTranscDate;
			
			// Save PID into StockArray
			getline(linestream, fPID, ':');
			readStockArray[i].PID = stoi(fPID);

		    //Save Product Name into StockArray
		    getline(linestream, fproductName, ':');
		    readStockArray[i].Name = fproductName;

		    //Save Category into StockArray
		    getline(linestream, fproductCategory, ':');
		    readStockArray[i].Category = fproductCategory;

		    //Save SubCategory into StockArray
		    getline(linestream, fproductSubCategory, ':');
		    readStockArray[i].SubCategory = fproductSubCategory;
		    
		    //Save Product Price into StockArray
		    getline(linestream, fproductPrice, ':');
		    readStockArray[i].Price = stod(fproductPrice, NULL);

		    //Save Product Quantity into StockArray
		    getline(linestream, fproductQuantity, ':');
		    readStockArray[i].Quantity = stoi(fproductQuantity);

		    //Save Product Transaction Date into StockArray
		    getline(linestream, fproductTranscDate, '\r');
		    readStockArray[i].TranscDate = fproductTranscDate;
		}	
		//cout << "i: " << i << endl;
    	i++;
	}
	inFile.close();
}

void Menu(){
	cout << "==================================="<< endl;
	cout << " 1.	Add new transaction" << endl;
	cout << " 2.	Remove transaction record" << endl;
	cout << " 3.	Edit stock item" << endl;
	cout << " 4.	Search stock item" << endl;
	cout << " 5.	Stock summary report" << endl;
	cout << " 6.	Quit" << endl;
    cout << "==================================="<< endl;
    cout << "Enter a number between 1-6: ";
}

int stockMain(){
	cout << "--STAFF LOGIN AUTH--\n";
    ReadFile();
    
    while (1){
    	Menu();
    	string menuInput;
    	getline(std::cin, menuInput);
	    if (menuInput.empty()){
	    	cout << "Please enter an input!\n";
	    } else if (menuInput == "1"){
	    	AddProduct();
	    } else if (menuInput == "2"){
	    	RemoveProduct();
	    } else if (menuInput == "3"){
	    	EditProduct();
	    } else if (menuInput == "4"){
	    	SearchProduct();
	    } else if (menuInput == "5"){
	    	SummaryReport();
	    } else if (menuInput == "6"){
	    	cout << "Logging out!" << endl;
	    	return 1;
	    	cout << "This should not be displayed.\n";
	    } else {
	    	cout << "Please enter within numbers 1-6!\n";
	    }
	}
}

/*int main(){
    cout << "Program Started!\n";
    cout << "--STAFF LOGIN AUTH--\n";
    ReadFile();
    
    while (1){
    	Menu();
    	string menuInput;
    	getline(std::cin, menuInput);
	    if (menuInput.empty()){
	    	cout << "Please enter an input!\n";
	    } else if (menuInput == "1"){
	    	AddProduct();
	    } else if (menuInput == "2"){
	    	RemoveProduct();
	    } else if (menuInput == "3"){
	    	EditProduct();
	    } else if (menuInput == "4"){
	    	SearchProduct();
	    } else if (menuInput == "5"){
	    	SummaryReport();
	    } else if (menuInput == "6"){
	    	cout << "Terminating Program!" << endl;
	    	exit(1);
	    	cout << "This should not be displayed.\n";
	    } else {
	    	cout << "Please enter within numbers 1-6!\n";
	    }
    }
}//*/



/*int Stock::AddProduct(){
	cout << "Enter the name of Product to Add. [Enter: Return]" << endl;
	cin >> productName;
	if (productName.empty()){
		cout << "No input was detected!" << endl;
		return 0;
	}
	//cout << endl << "" << endl;
}

int Stock::EditProduct(){}
int Stock::RemoveProduct(){}
int Stock::SearchProduct(){}
int Stock::SummaryReport(){}
int Stock::RetrieveProduct(){}//*/