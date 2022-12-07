/* DATE: 10/30/2020
	This program is just like a simple vending machine that sells
specific items : chips, candy, soda. These items have different 
details and the contents of it will be shown to the user to 
choose, the user supposed to enter a number of quarter and
make selection for their item. 
If they dont have enough money, the machine wont sell it
If they sucessfully bought an item, the transaction will be recorded
When the user stop using the program, it will display the details
about the transaction, the instock items, and the profits.
*/

//declaring library
#include <iostream>
#include<string>
#include<iomanip>
#include<ctime>
#include<cstring>
#pragma warning (disable:4996)
using namespace std;


//Class Snack
class Snack {
	//Private attributes
private:
	string snackName;
	double snackPrice;
	int stockQuantity;
	int numSoldItems;
	string* Timeptr;

	//Function getCurrentTime
	string getCurrentTime() {
		time_t t = time(0);
		struct tm ts;
		char buff[10];
		ts = *localtime(&t);
		strftime(buff, sizeof(buff), "%X", &ts);
		return buff;
	}

	//public methods
public:
	//default constructor
	Snack() {
		//define everything to 0
		numSoldItems = 0;
		snackPrice = 0.0;
		snackName = "";
		stockQuantity = 0;
	}

	//overloaded constructor 

	Snack(string n, double p, int q) {
		// this constructor accepts a string, a double, a integer
		//represent for the name, the price and the stock
		snackName = n;
		snackPrice = p;
		stockQuantity = q;
		numSoldItems = 0;
		Timeptr = new string[q];
	}

	/*DESTRUCTOR
	The Destructor display the quantity in stock, the number
of item sold and the money gained from the sales*/
	~Snack() {
		//if nothing was bought then did not display anything
		if (numSoldItems * snackPrice == 0) {

		}
		else {
			//displaying the info for successful bought
			cout << "\nClosing info for " << snackName << ":" << endl;
			cout << "\t" << stockQuantity << " in stock" << endl;
			cout << "\t" << numSoldItems << " sold for a profit of $"
				<< numSoldItems * snackPrice << endl;

			if (numSoldItems > 0) {
				cout << "\nTransaction occured at: " << endl;
				for (int i = 0; i < numSoldItems; i++) {
					cout << "\t" << Timeptr[i] << endl;
				}
				//Clean the array on the heap
				delete[] Timeptr;
			}
		}
	}

	//Mutators methods
	void setQuantity(int q);
	void setName(string n);
	void setPrice(double p);

	//Accessor methods
	string getName() const;
	double getPrice() const;
	int getQuantity() const;
	string getTime() const;
	//bool function to buy item
	bool buyItem(double&);
};

/*getQuarter function: 
This functions accepts nothing and returns an integer that represent
the number of quarter. It prompt the user to enter a valid 
number of quarters

*/
int getQuarter();//Prototype
int getQuarter() {
	int numQuarter;
	//check the conditions for the number of quarter
	do {
		cout << "Enter a number of quarter: ";
		cin >> numQuarter;
		if (numQuarter < 1) {
			cout << "Please enter a number greater than 0. "
				<< endl << endl;
		}
	} while (numQuarter < 1);
	return numQuarter;


}


/*DisplayVendingMachine function:
This function accepts the array of objects from class and 
the number of elements in the array which is the size
It displays the contents in a formatted fashion and return nothing
*/
void displayVendingMachine(const Snack snack[], int numEle);//Prototype
void displayVendingMachine(const Snack snack[], int numEle) {
	//displaying the vending machine
	cout << "Item#\tItem name\tPrice\t# in-stock" << endl;
	cout << "-----------------------------------------------" << endl;
	for (int x = 0; x < numEle;x++) {
		cout << x + 1 << "\t" << snack[x].getName()
			<< "\t\t" << fixed << setprecision(2) <<
			snack[x].getPrice() << "\t" <<
			snack[x].getQuantity() << endl;
	}
	cout << endl;

}



/*PrompToContinue function:
This function will ask the user if they want to
continue the program or not. If the user enter y or Y, 
the program should continue, if not the program should stop
It returns bool value, either true or false
*/

bool PromptToContinue(); // Prototype
bool PromptToContinue() {
	char input; 
	bool check;
	
	while (true) {
		cout << "Continue? (Y/N): ";
		cin >> input;
		cout << endl;
		//This function ignore all the characters starting from the 
		//index 1
		cin.ignore(INT64_MAX, '\n');

		//Checking if the user input yes or no 
		if (input == 'y' || input == 'Y' ) {
			check = true;
			
			return check;
		}
		else if (input == 'n' || input == 'N') {
			check = false; 
			return check;
		}
		//If they put other characters rather than yes or no
		else {
			cout << "Please enter yes(Y or y) or no(N or n) " << endl;
		}
	}
	return check;

}

/*userBuyItem Function:
This function accepts the array of objects from class
and the number of elements in the array. It display the content
in the vending machine and prompt the user to enter
a number of quarter and user selection to buy. Then it execute the 
buying process and give back the amount of remaining money
It returns nothing

*/
void userBuyItem(Snack[], int); // prototype
void userBuyItem(Snack snackArr[], int numElem) {
	cout << endl;
	//displaying the vending machine
	displayVendingMachine(snackArr, numElem);
	int quarter = getQuarter();

	//Calculate the amount entered in dollars and cents
	double price = static_cast<double>(quarter) * .25;
	cout << "Amount entered : $" << price << showpoint
		<< setprecision(2) << endl;
	cout << endl;
	int select;
	//Conditions for the user selection
	do {
		cout << "Enter a number between 1-3 to make your selection: ";
		cin >> select;
		if (select < 1 || select > 3) {
			cout << "Please enter a number between 1 and 3 " << endl;
		}
	} while (select < 1 || select > 3);

	cout << endl;

	//Execute each of the selection
	if (select == 1) {
		snackArr[select - 1].getPrice();
		snackArr[select - 1].buyItem(price);
		snackArr[select - 1].getTime();
		if (snackArr[select - 1].getQuantity() < 0) {
			PromptToContinue();
		}
		displayVendingMachine(snackArr, numElem);

	}
	else if (select == 2) {
		snackArr[select - 1].getPrice();
		snackArr[select - 1].buyItem(price);
		snackArr[select - 1].getTime();
		if (snackArr[select - 1].getQuantity() < 0) {
			PromptToContinue();
		}
		displayVendingMachine(snackArr, numElem);
	}
	else if (select == 3) {
		snackArr[select - 1].getPrice();
		snackArr[select - 1].buyItem(price);
		snackArr[select - 1].getTime();
		if (snackArr[select - 1].getQuantity() < 0) {
			PromptToContinue();
		}
		displayVendingMachine(snackArr, numElem);
	}
}

//Main
int main() {
	//use the chips objects with the defaul constructor
	const int SIZE = 3;
	
	//create an array to store three objects 
	Snack snackArr[SIZE] = { Snack(), Snack ("Candy",1.25,5),
		Snack("Soda",1.00,2)  };

	//set info for the Chips object
	snackArr[0].setName("Chips");
	snackArr[0].setPrice(1.75);
	snackArr[0].setQuantity(3);

	cout << "Welcome to the vending machine!" << endl;
	
	//while loop
	bool check = true;
	while (check) {
		userBuyItem(snackArr, SIZE);
		bool result = PromptToContinue();
		if (result == true) {
		}
		else {
			check= false;
		}
	}

}

//Method members definition
/*This method accept the moneyEntered from the user and
check for the stock of the item, check if the money is enough
or not, check if the machine need to return the money to the user
or not and get the time of the transaction
*/
bool Snack::buyItem(double& moneyEntered) {
	bool check = true;
	if (moneyEntered >= snackPrice ) {
		//Check if the item is still in-stock
		if (stockQuantity <= 0) {
			check = false;
			cout << "Error: Item is sold-out!" << endl;
			cout << "$" << moneyEntered << 
				showpoint << setprecision(2) <<
				" dispendsed below" << endl;
			return check;
		}
		double temp = moneyEntered - snackPrice;
		//Check if we need to return the money
		if (temp > 0) {
			stockQuantity--;
			numSoldItems++;
			*Timeptr = getCurrentTime();
			/*for (int i = 0; i < numSoldItems; i++) {
				Timeptr[i] = getCurrentTime();
			}*/
			cout << "Item has been dispensed below" << endl;
			cout << "$" << temp << showpoint << setprecision(2) <<
				" dispendsed below" << endl << endl;
		}
		//Check if the machine dont have to return any money
		else if (temp == 0) {
			stockQuantity--;
			numSoldItems++;
			*Timeptr = getCurrentTime();
			/*for (int i = 0; i < numSoldItems; i++) {
				Timeptr[i] = getCurrentTime();
			}*/
			cout << "Item has been dispensed below" << endl << endl;
		}
	}
	//Check if the money is enough
	else {
		cout << "You don't have enough money please try again. " 
			<< endl << endl;
		check = false;
		return check;
	}
}

//Mutator
void Snack::setName(string n) {
	snackName = n;
}

void Snack::setPrice(double p) {
	snackPrice = p;
}

void Snack::setQuantity(int q) {
	stockQuantity = q;
	Timeptr = new string[q];
}

//Accesors
string Snack::getName() const {
	return snackName;
}

double Snack::getPrice() const {
	return snackPrice;
}

int Snack::getQuantity() const{
	return stockQuantity;
}
string Snack::getTime() const {
	return *Timeptr;
}


/*````````````````````````` SAMPLE RUN ````````````````````````````

Welcome to the vending machine!

Item#   Item name       Price   # in-stock
-----------------------------------------------
1       Chips           1.75    3
2       Candy           1.25    5
3       Soda            1.00    2

Enter a number of quarter: -7
Please enter a number greater than 0.

Enter a number of quarter: 25
Amount entered : $6.25

Enter a number between 1-3 to make your selection: 1

Item has been dispensed below
$4.50 dispendsed below

Item#   Item name       Price   # in-stock
-----------------------------------------------
1       Chips           1.75    2
2       Candy           1.25    5
3       Soda            1.00    2

Continue? (Y/N): y


Item#   Item name       Price   # in-stock
-----------------------------------------------
1       Chips           1.75    2
2       Candy           1.25    5
3       Soda            1.00    2

Enter a number of quarter: 2
Amount entered : $0.50

Enter a number between 1-3 to make your selection: 3

You don't have enough money please try again.

Item#   Item name       Price   # in-stock
-----------------------------------------------
1       Chips           1.75    2
2       Candy           1.25    5
3       Soda            1.00    2

Continue? (Y/N): y


Item#   Item name       Price   # in-stock
-----------------------------------------------
1       Chips           1.75    2
2       Candy           1.25    5
3       Soda            1.00    2

Enter a number of quarter: 5
Amount entered : $1.25

Enter a number between 1-3 to make your selection: 2

Item has been dispensed below

Item#   Item name       Price   # in-stock
-----------------------------------------------
1       Chips           1.75    2
2       Candy           1.25    4
3       Soda            1.00    2

Continue? (Y/N): asdf

Please enter yes(Y or y) or no(N or n)
Continue? (Y/N): Y


Item#   Item name       Price   # in-stock
-----------------------------------------------
1       Chips           1.75    2
2       Candy           1.25    4
3       Soda            1.00    2

Enter a number of quarter: 48
Amount entered : $12.00

Enter a number between 1-3 to make your selection: 11
Please enter a number between 1 and 3
Enter a number between 1-3 to make your selection: 1

Item has been dispensed below
$10.25 dispendsed below

Item#   Item name       Price   # in-stock
-----------------------------------------------
1       Chips           1.75    1
2       Candy           1.25    4
3       Soda            1.00    2

Continue? (Y/N): y


Item#   Item name       Price   # in-stock
-----------------------------------------------
1       Chips           1.75    1
2       Candy           1.25    4
3       Soda            1.00    2

Enter a number of quarter: 15
Amount entered : $3.75

Enter a number between 1-3 to make your selection: 3

Item has been dispensed below
$2.75 dispendsed below

Item#   Item name       Price   # in-stock
-----------------------------------------------
1       Chips           1.75    1
2       Candy           1.25    4
3       Soda            1.00    1

Continue? (Y/N): n


Closing info for Soda:
		1 in stock
		1 sold for a profit of $1.00

Transaction occured at:
		21:23:22

Closing info for Candy:
		4 in stock
		1 sold for a profit of $1.25

Transaction occured at:
		21:22:40

Closing info for Chips:
		1 in stock
		2 sold for a profit of $3.50

Transaction occured at:
		21:23:12
		21:23:12

D:\CIS 22 B\Assignment 4\Assignment 4\Debug\Assignment 4.exe (process 38232)
exited with code 0.
Press any key to close this window . . .


----------------------------- END OF SAMPLE RUN -----------------------
*/
