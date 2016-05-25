/*
* Program Name: Theater Seating
* Authors: Brad Haydell
* Class: PRG/410
* Date: 1/17/2016
* Description: This program displays and tracks seats sold for a small theater. Available and sold seats are printed to the screen and the user has the option to purchase tickets for desired seats.
*			    Sales of all the seats sold are tracked. Users have the ability to see how many sets are available per row instead of viewing the entire auditorium.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <locale>
using namespace std;

void ViewSeating();
void UpdateSeating();
void ShowMenu();
void SeatPrices();
void TotalPrices();
void PurchaseTicket();
void SoldCount();
void AvailCount();
void AvailPerRow();
char getChoice(string p);	//Ask a Y or N question
int getInt(string p);		//Get an int from the user
int getRow();				//Get a row from the user
int getCol();				//Get a column from the user


const char sold = '*';			//Seat taken
const char available = '#';		   //Seat open
const int cBlock = 4;
const int aBlock = 5;
const int rows = 12;			   //Number of rows
const int columns = 9;		   //Number of seats per row
const int totalSeats = rows*columns;
char seating[rows][columns];
double totalSales[rows][columns];
double price = 24.00, totals = 0;

int main()
{
	system("cls");
	cout.imbue(locale("ENGLISH_US"));
	cout << showbase;
	cout << fixed << showpoint << setprecision(2);
	cout << "Welcome to our Theatre" << endl;

	ViewSeating();
	ShowMenu();
}

void ViewSeating()
{

	cout << endl << "Seating Chart" << endl << endl;
	cout << "# = Seats available" << endl;
	cout << "* = Seats sold" << endl;
	cout << endl;

	cout << setw(cBlock) << " ";

	for (int i = 0; i < columns; i++)
	{
		cout << setw(aBlock) << i + 1;
	}

	cout << endl << "__________________________________________________" << endl;

	for (int r = 0; r < rows; r++) //Loop for rows
	{

		for (int c = 0; c < columns; c++) //Loop for columns
		{
			if (c == 0)
			{
				cout << setw(cBlock) << left << "Row " << setw(cBlock) << left << r + 1;
			}
			seating[r][c] = available; //Sets seat to AVAILABLE const 

			cout << setw(cBlock) << seating[r][c] << " "; //Prints the seat to the screen.
		}
		cout << endl;
	}

	cout << "__________________________________________________" << endl;
	cout << "Seats Sold: ";  //Prints the number of sold seats after the seating is printed
	SoldCount();
	cout << "Seats Available: ";  //Prints the number of available seats after the seating is printed
	AvailCount();
	cout << endl;

}

void UpdateSeating()
{
	cout << endl << "Seating Chart" << endl << endl;
	cout << "# = Seats available" << endl;
	cout << "* = Seats sold" << endl;
	cout << endl;

	cout << setw(cBlock) << right << " ";

	for (int i = 0; i < columns; i++)
	{
		cout << setw(aBlock) << i + 1;
	}

	cout << endl << "__________________________________________________" << endl;

	for (int r = 0; r < rows; r++)//Loop for rows
	{

		for (int c = 0; c < columns; c++) //Loop for columns
		{
			if (c == 0)
			{
				cout << setw(cBlock) << left << "Row " << setw(cBlock) << left << r + 1;
			}

			cout << setw(cBlock) << seating[r][c] << " "; //Prints the seat to the screen
		}
		cout << endl;
	}

	cout << "__________________________________________________" << endl;

	cout << "Seats Sold: ";
	SoldCount();
	cout << "Seats Available: ";
	AvailCount();
	TotalPrices();
	cout << endl;
}

void ShowMenu()
{

	int choice = 0;
	cout << endl << endl;
	cout << " \tMAIN MENU\n";
	cout << " 1. View Seat Prices.\n";
	cout << " 2. Purchase a Ticket.\n";
	cout << " 3. View Available Seats.\n";
	cout << " 4. View Available Seats in Each Row.\n";
	cout << " 5. Quit the program.\n";
	cout << "_____________________\n\n";
	choice = getInt("Please enter your choice");
	cout << endl << endl;

	switch (choice) //Switch statement for above menu choice
	{
	case 1:
	{
		system("cls");
		SeatPrices();
		ShowMenu();
		break;
	}
	case 2:
	{
		system("cls");
		PurchaseTicket();
		ShowMenu();
		break;
	}
	case 3:
	{
		system("cls");
		UpdateSeating();
		ShowMenu();
		break;
	}
	case 4:
	{
		system("cls");
		AvailPerRow();
		ShowMenu();
		break;
	}
	case 5:
	{
		break;
	}
	default:
	{
		cout << "Please choose a valid menu option\n";
		ShowMenu();
	}
	}
}

void SeatPrices()
{
	cout << "The price for each ticket is "
		<< put_money(price * 100) << endl; //Prints the cost of the seat tickets
}

void TotalPrices()
{
	double tPrice = 0;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)
		{
			tPrice = tPrice + totalSales[r][c]; //Adds all elements in the array to tprice for a total amount
		}
	}
	cout << "Total Sales: " << put_money(tPrice * 100) << endl; //Prints total sales to screen
}

void PurchaseTicket()
{
	system("cls");
	char choice;
	int rowChoice = 0, colChoice = 0, purchase = 0, purchase2 = 0;
	double totalPurchase = 0;

	cout << endl; // << "Would you like to buy some tickets (Y or N): ";
	choice = getChoice("Would you like to buy some tickets"); //Sets choice variable through data validation function

	purchase = getInt("How many tickets would you like to purchase"); //Sets how many tickets will be purchased through data validation function

	purchase2 = purchase;


	while (choice == 'Y' || choice == 'y') //Loop for ticket purchases
	{
		for (int i = 0; i < purchase; i++) //Loop to set which seats would like to be purchased
		{
			rowChoice = getRow(); //Stores row of desired seat
			colChoice = getCol(); //Stores column of desired seat

			if (seating[rowChoice - 1][colChoice - 1] == sold) //Checks if the seat has already been sold
			{
				cout << "The seat selected is already sold, please choose again.\n";
				i--; //Makes sure the loop will not advance too fast as the seat was already taken
			}
			else
			{
				seating[rowChoice - 1][colChoice - 1] = sold; //Sets the seat to the SOLD const
				totalSales[rowChoice - 1][colChoice - 1] = price; //Adds to total sales array
				cout << endl;
			}

		}


		choice = getChoice("Would you like to buy another ticket"); //Asks if user would like another ticket
		if (choice == 'Y' || choice == 'y')
		{

			purchase = getInt("How many tickets would you like to purchase"); //Gets how many tickets through data validation function

		}

		purchase2 = purchase + purchase2;
	}

	system("cls"); //Removes previous clutter from console

	cout << "The total for this purchase is: " << put_money(((purchase2 - purchase) * price) * 100) << endl;
	cout << "Thank you for your purchase. Have a great day!" << endl << endl;
	UpdateSeating(); //Updates the seats based on purchases that just occured
}

void SoldCount()
{
	int count = 0;
	for (int r = 0; r < rows; r++) //Loop for Rows
	{
		for (int c = 0; c < columns; c++) //Loop for Columns
		{
			if (seating[r][c] == sold) //Checks if elements equal the SOLD const defined 
			{
				count++; //Adds 1 to counter of sold seats
			}
		}
	}
	cout << count << endl; //Prints out how many seats are sold
}

void AvailCount()
{
	int count = 0;
	for (int r = 0; r < rows; r++) // Loop for Rows
	{
		for (int c = 0; c < columns; c++) //Loop for Columns
		{
			if (seating[r][c] == available) //Checks if elements equal the AVAILABLE const defined
			{
				count++; //Adds 1 to counter of available seats
			}
		}
	}
	cout << count << endl; //Prints out how many seats are available
}

void AvailPerRow()
{

	int openSeats = columns; //Sets default seats to the number of columns in seating array

	for (int r = 0; r < rows; r++) //Loop for array rows
	{
		for (int c = 0; c < columns; c++) //Loop for array columns
		{
			if (seating[r][c] == '*') //Checks if current seat in the loop is a * or #
			{
				openSeats--; //If it is a *, take 1 seat away from
			}
			if (c == columns - 1)
			{
				cout << "Seats Available in Row " << (r + 1) << ": " << openSeats << endl; //Prints the number of open seats in the row
				openSeats = columns; //Restarts open seats for the next row
			}
		}
	}
}

char getChoice(string p)
{
	char c;
	bool gotAnswer = false;
	while (!gotAnswer)
	{
		cout << p << " (Y or N): ";
		cin.clear();
		cin.ignore(256, '\n'); //Clear the input buffer
		c = getchar();
		if (cin.fail())  //If the user input is not a char, tell the user, clear buffer, and restart the loop.
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "\nYour entry did not seem valid\n";
		}
		else if (c != 'y' && c != 'Y' && c != 'N' && c != 'n')  //If the input is not yes or no
		{
			cout << "\nYour entry is not seem to be Y or N\n";
		}
		else
		{
			cout << "\n";

			gotAnswer = true;
		}
	}

	return c;

}

int getInt(string p)
{
	int x = -1;
	bool gotInt = false;
	while (!gotInt)
	{
		cout << p << ": ";
		//cin.clear();
		//cin.ignore(256, '\n'); //Clear the input buffer
		cin >> x;
		if (cin.fail() || x < 0)  //If the user input is not an integer, tell the user, clear buffer, and restart the loop.
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "\nPlease enter a positive whole number\n";
		}
		else
		{
			cout << "\n";
			gotInt = true;
		}
	}

	return x;

}

int getRow()
{
	int x = -1; //Variable to flag if loop is complete
	while (x == -1)
	{
		x = getInt("Pick a Row"); //Runs fucntion to get an Int from the user and sets it to while loop check variable
		if (x == 0 || x > rows)
		{
			cout << "Please select a row between 1 and " << rows << ".\n"; //Requests that the user enters a valid number if input is not valid
			x = -1;

		}
	}
	return x;
}

int getCol()
{
	int x = -1; //Variable to flag if loop is complete
	while (x == -1)
	{
		x = getInt("Pick a Column"); //Runs fucntion to get an Int from the user and sets it to while loop check variable
		if (x == 0 || x > columns)
		{
			cout << "Please select a column between 1 and " << columns << ".\n"; //Requests that the user enters a valid number if input is not valid
			x = -1;

		}
	}
	return x;
}
