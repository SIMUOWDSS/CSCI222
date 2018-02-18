#ifndef STOCK_H
#define STOCK_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

typedef struct StockRecord
{
	int PID = 0;
	string Name;
	string Category;
	string SubCategory;
	double Price;
	int Quantity;
	string TranscDate;

}	StockRecord;

class Stock {
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
	
	string returnNowDate();
	int AddProduct();
	int RemoveProduct();
	int SearchProduct();
	int SummaryReport();
	
private:
	int returnSummaryStartDate(string summaryPChoice);
	int commitFileChange(int arri);
	int ReadFile();
	void main();
};
int stockMain();

#endif // COUNTRY_DATA_H