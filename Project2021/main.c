#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// author Keelan duddy = G00385886

//users log Details 
typedef struct login
{
	char username[10];
	char password[10];
	
}login;


// struct
typedef struct NodeT_
{
	int PPSNumber;
	char firstName[30];
	char secondName[30];
	int yearBorn;
	char email[40];
	int areasTravelFrom;
	int typeTicket;
	int tripsPerYear;
	int averageSpent;
	

	struct NodeT_* NEXT;
}node;

//Auhtenticates/validates  the users sign in information 
int verifyLogin();
// adds elements to front of list when nothing yet exists
void addElementAtTheStart(node** top);
// adds element when link exists
void addElement(node* top);
// display all patients in list
void DisplayList(node* top);
// search's for customer
void SearchCustomerPPS(struct node* top);
void SearchCustomerName(struct node* top);
//updates customer
void UpdateCustomerPPS(struct node* top);
void UpdateCustomerName(struct node*top);

// deletes customer
void DeleteCustomer(struct node** top, int position);
//wrtie to file
void outputReport(struct node* headptr);
// save and load file
void saveFile(struct node* headptr);
// sort
void bubbleSort(struct node* start);
void swap(struct node* a, struct node* b);
void displaySort(struct node* top);


main() {
	
	// variables
    node* headPtr = NULL;
	FILE* filep;//initlize file
	int choice;
	int n = 0;
	int i;
	int numRead;


	char fileUser[10];
	char filePass[10];
	int searchOption=0;
	int updateOption = 0;
	int searchPPS = 0;

	
	// Header
	printf("======================================\n");
	printf("ABC Cinema\n");
	printf("======================================\nlogin details in file\n");

	//open and read file for read
	filep = fopen("login.txt", "r");

	//display all the users passwords/usernames for testing purposes 
	while (!feof(filep))
	{
		//read users input  from file
		numRead = fscanf(filep, "%s %s ", fileUser, filePass);
		//read only the two variables
		if (numRead == 2)
		{
			//display to the screen
			printf("The userName is %s, The password  is %s\n", fileUser, filePass);
		}
	}
	//close filep after reading
	fclose(filep);

	//begin function verifyLogin();
	verifyLogin();


	if (verifyLogin() == 1) {
		printf("\nLogin succesfull!\n"); // prints if login works

		//Menu Options	
		printf("MENU\n");
		printf("Press 1 To Add customer \n");
		printf("Press 2 To Display all customer Details to screen \n");
		printf("Press 3	To search for a specific customer details \n");
		printf("Press 4 To Update a customer's  details\n");
		printf("press 5 To search and Delete a customer's  details  \n");
		printf("press 6 To Generate Statistics  \n");
		printf("press 7 To Print all customer into a report file   \n");
		printf("press 8 To List all the  customer in order of their year born \n");

		printf("Or Press -1 to exit  \n");
		scanf("%d", &choice);


		//  the menu while loop which call the functions
		while (choice != -1) {

			if (choice == 1) {

				if (headPtr == NULL)
					addElementAtTheStart(&headPtr);
				else
				{
					addElement(headPtr);
				}//else


			}//if

			else if(choice == 2)
			{
				DisplayList(headPtr);

			}//else if

			else if (choice == 3) {
				printf("Please enter 1 to search by PPS number or press 2 to search by first name (int)\n");
				scanf("%d", &searchOption);

				if (searchOption == 1) {
					SearchCustomerPPS(headPtr);
				}//if
				else if (searchOption == 2) {
					SearchCustomerName(headPtr);
				}// else if
				else {
					printf("You entered an invalid option!, retry again...\n");
				}// else
				
			}// else if
			else if (choice == 4) {
				
				printf("Please enter 1 to use PPS Number to update customer details or enter 2 to use first name to update the customer (int)\n");
				scanf("%d", &updateOption);

				if (updateOption == 1) {
					UpdateCustomerPPS(headPtr);
				}//if
				else if (updateOption == 2) {
					UpdateCustomerName(headPtr);
				}//else if
				else {

					printf("You entered an invalid option!, retry again...\n");

				}//else
			}// else if

			else if (choice == 5) {
				
				printf("Please enter the PPS number of the customer you're looking to delete from the list! (int)\n");
				scanf("%d", &searchPPS);
				DeleteCustomer(&headPtr, searchPPS);
				


			}// else if
			else if (choice == 6) {
				
				printf("Unfinished\n");

			}// else if
			else if (choice == 7) {

				outputReport(headPtr);
			}// else if
			else if (choice == 8) {

				bubbleSort(headPtr);
				displaySort(headPtr);
				

			}//else if

            //Menu Options	
			printf("MENU\n");
			printf("Press 1 To Add customer \n");
			printf("Press 2 To Display all customer Details to screen \n");
			printf("Press 3	To search for a specific customer details \n");
			printf("Press 4 To Update a customer's details\n");
			printf("press 5 To search and Delete a customer's  details  \n");
			printf("press 6 To Generate Statistics  \n");
			printf("press 7 To Print all customer into a report file   \n");
			printf("press 8 To List all the  customer in order of their year born \n");

			printf("Or Press -1 to exit  \n");
			scanf("%d", &choice);

			if (choice == -1) {
				//on exit by -1 the program will save to file .txt via  saveFile function call
				saveFile(headPtr);
				//alert user
				printf("You have chosen to exit the program.The database will now be updated \n");
			}//if



		}// while loop






	}// if


}// main

 
int verifyLogin(){

	//variable declaration

	FILE* filep;//initlize file
	int input;
	int i;
	char ch;
	
	char loginUser[10];
	char loginPass[10];
	char fileUser[10];
	char filePass[10];
   
	
		//enter username and password
		printf("\nEnter username (6 characters):\n");
		scanf("%s", loginUser);
		printf("\nEnter 6 digit  password:\n");
	
	


	//replace char with * for each char entered by user (HIDE PASSWORD ENTRY)
	for (i = 0; i < 6; i++)// loop through the number of characters in password
	{
		ch = getch();//get next char
		loginPass[i] = ch; //HOLD 
		ch = '*';  //REPLACE
		printf("%c", ch);//DISPLAY
	}//for

	loginPass[i] = '\0';//add null terminater

	filep = fopen("login.txt", "r");//open file for read

	//make sure file has contents
	if (filep == NULL) {
		printf("Error No File\n");
		return 0;
	}//if
	while (!feof(filep)) {
		//read file fileUser + filePassword
		input = fscanf(filep, "%s %s", fileUser, filePass);

		//compare the username + password 
		if (strcmp(loginUser, fileUser) == 0 && strcmp(loginPass, filePass) == 0) {
			printf("\nCredentials exist and are found! \n ");
			printf("\nWelcome  back : %s \n", loginUser);
			return 1;
			break;
		}// if	

	}//while
	
	//close the file
	fclose(filep);
	//verifyLogin
	

	


}//verifyLogin

void addElementAtTheStart(node** top) {

	node* temp;

	// adds all struct details to start of list when there isn't anything in the list yet

	temp = (node*)malloc(sizeof(node));

	printf("Please enter PPS number (int)\n");
	scanf("%d", &temp->PPSNumber);

	printf("Please enter your first name (char)\n");
	scanf("%s", temp->firstName);

	printf("Please enter your second name (char)\n");
	scanf("%s", temp->secondName);

	printf("Please enter the year you're born (int)\n");
	scanf("%d", &temp->yearBorn);

	do
	{
		printf("Please enter your E-MAIL must contain '@' (char)\n");
		scanf("%s", temp->email);
	} while (strchr(temp->email, '@') == NULL); // while loop to make sure @ is used
	
    printf("Please enter which of the following areas you came from: (int)\n");
	printf("Press 1 for Galway City\n");
	printf("Press 2 for Galway County\n");
	printf("Press 3 for Connacht\n");
	printf("Press 4 for other areas of ireland\n");
	printf("Press 5 for outside ireland\n");
	scanf("%d", &temp->areasTravelFrom);

	printf("Which ticket did you purchase: 1 for Normal or 2 for Luxury (int) \n");
	scanf("%d", &temp->typeTicket);
	
	printf("How many trips to the cinema do you make per year (int)\n");
	printf("Press 1 for :Less than 3 times per year\n");
	printf("Press 2 for :Less than 5 times per year\n");
	printf("Press 3 for: More than 5 times per year\n");
	scanf("%d", &temp->tripsPerYear);

	printf("on average how much do you spend in the cinema shop (int)\n");
	printf("Press 1 :nothing\n");
	printf("Press 2 :Less than 5 euro\n");
	printf("Press 3 :less than 10 euro\n");
	printf("Press 4 :More than 10 euro\n");
	scanf("%d", &temp->averageSpent);

	temp->NEXT = *top;

	*top = temp;



}//addElementAtTheStart

void addElement(node* top) {
	node* temp;
	node* temp2;

	// adds all struct details to list

	temp = (node*)malloc(sizeof(node));

	printf("Please enter PPS number (int)\n");
	scanf("%d", &temp->PPSNumber);

	printf("Please enter your first name (char)\n");
	scanf("%s", temp->firstName);

	printf("Please enter your second name (char)\n");
	scanf("%s", temp->secondName);

	printf("Please enter the year you're born (int)\n");
	scanf("%d", &temp->yearBorn);

	do
	{
		printf("Please enter your E-MAIL must contain '@' (char)\n");
		scanf("%s", temp->email);
	} while (strchr(temp->email, '@') == NULL);

	printf("Please enter which of the following areas you came from: (int)\n");
	printf("Press 1 for Galway City\n");
	printf("Press 2 for Galway County\n");
	printf("Press 3 for Connacht\n");
	printf("Press 4 for other areas of ireland\n");
	printf("Press 5 for outside ireland\n");
	scanf("%d", &temp->areasTravelFrom);

	printf("Which ticket did you purchase: Press 1 for Normal or 2 for Luxury (int) \n");
	scanf("%d", &temp->typeTicket);

	printf("How many trips to the cinema do you make per year (int)\n");
	printf("Press 1: Less than 3 times per year\n");
	printf("Press 2: Less than 5 times per year\n");
	printf("Press 3: More than 5 times per year\n");
	scanf("%d", &temp->tripsPerYear);

	printf("on average how much do you spend in the cinema shop (int)\n");
	printf("Press 1: nothing\n");
	printf("Press 2: Less than 5 euro\n");
	printf("Press 3: less than 10 euro\n");
	printf("Press 4: more than 10 euro\n");
	scanf("%d", &temp->averageSpent);

	temp->NEXT = NULL;

	temp2 = top;
	while (temp2->NEXT != NULL) {

		temp2 = temp2->NEXT;
	}// while

	temp2->NEXT = temp;



}//addElement


void DisplayList(struct node* top) {

	// displays the list on to screen

	 node* temp ;
	if (top == NULL)
	{
		printf("Nothing in list\n");
	}
	else
	{
		temp = top;

		while (temp != NULL)
		{
			printf("======DisplayList=========\n");
			printf(" PPS Number:%d\n", temp->PPSNumber);
			printf(" First Name:%s\n", temp->firstName);
			printf(" Second Name:%s\n", temp->secondName);
			printf(" Year born: %d\n", temp->yearBorn);
			printf(" Email: %s\n", temp->email);
			
			//area travelled from
			printf("Area travelled from:\n");
			if (temp->areasTravelFrom == 1)
			{
				printf("Traveled from Galway city\n");
			}
			else if (temp->areasTravelFrom == 2)
			{
				printf("Traveled from Galway county\n");
			}
			else if (temp->areasTravelFrom == 3)
			{
				printf("Traveled from Connacht\n");
			}
			else if (temp->areasTravelFrom == 4)
			{
				printf("Traveled from other areas in Ireland\n");
			}
			else if (temp->areasTravelFrom == 5)
			{
				printf("Traveled from outside Ireland\n");
			}

			// type of tickets
			printf("Type of ticket purchased:\n");
			if (temp->typeTicket == 1)
			{
				printf("Normal Ticket\n");
			}
			else if (temp->typeTicket)
			{
				printf("Luxury ticket\n");
			}

			// trips to cinema
			printf("Trips made to the cinema per year:\n");
			if (temp->tripsPerYear == 1)
			{
				printf("Less than 3 times per year\n");
			}
			else if (temp->tripsPerYear == 2)
			{
				printf("Less than 5 times per year\n");
			}
			else if (temp->tripsPerYear == 3)
			{
				printf("More than 5 times per year\n");
			}

			// average spend on shop
			printf("average spend on cinema shop:\n");
			if (temp->averageSpent == 1) {

				printf("Nothing\n");
			}
			else if (temp->averageSpent == 2) {

				printf("Less than 5 euro\n");
			}
			else if (temp->averageSpent == 3) {

				printf("Less than 10 euro\n");
			}
			else if (temp->averageSpent == 4) {

				printf("More than 10 euro\n");
			}


			printf("++++++++++++++++++++++++++++\n");
			temp = temp->NEXT;






		}// while

	}//else


}// display list

void SearchCustomerPPS(struct node* top) {


	// variables
    node* temp;
	int count = 0;
	int found = 0;
	int option;
	int searchPPS;

	

	temp = (struct node*)malloc(sizeof(node));
	temp = top;

	// search by pps number
	printf("Enter customers PPS Number: (int)\n");
	scanf("%d", &searchPPS);
	
	// displays the information is the pps number exists in the linked list
	if (top == NULL) {
		printf("The list is empty\n");
	}
	else {
		
		temp = top;
		while (temp != NULL) {

			
              if (temp->PPSNumber == searchPPS)
				{
				
				printf("======DisplayList=========\n");
				printf(" PPS Number:%d\n", temp->PPSNumber);
				printf(" First Name:%s\n", temp->firstName);
				printf(" Second Name:%s\n", temp->secondName);
				printf(" Year born: %d\n", temp->yearBorn);
				printf(" Email: %s\n", temp->email);

				//area travelled from
				printf("Area travelled from:\n");
				if (temp->areasTravelFrom == 1)
				{
					printf("Traveled from Galway city\n");
				}
				else if (temp->areasTravelFrom == 2)
				{
					printf("Traveled from Galway county\n");
				}
				else if (temp->areasTravelFrom == 3)
				{
					printf("Traveled from Connacht\n");
				}
				else if (temp->areasTravelFrom == 4)
				{
					printf("Traveled from other areas in Ireland\n");
				}
				else if (temp->areasTravelFrom == 5)
				{
					printf("Traveled from outside Ireland\n");
				}

				// type of tickets
				printf("Type of ticket purchased:\n");
				if (temp->typeTicket == 1)
				{
					printf("Normal Ticket\n");
				}
				else if (temp->typeTicket == 2)
				{
					printf("Luxury ticket\n");
				}

				// trips to cinema
				printf("Trips made to the cinema per year:\n");
				if (temp->tripsPerYear == 1)
				{
					printf("Less than 3 times per year\n");
				}
				else if (temp->tripsPerYear == 2)
				{
					printf("Less than 5 times per year\n");
				}
				else if (temp->tripsPerYear == 3)
				{
					printf("more than 5 times per year\n");
				}

				// average spend on shop
				printf("average spend on cinema shop:\n");
				if (temp->averageSpent == 1) {

					printf("Nothing\n");
				}
				else if (temp->averageSpent == 2) {

					printf("Less than 5 euro\n");
				}
				else if (temp->averageSpent == 3) {

					printf("Less than 10 euro\n");
				}
				else if (temp->averageSpent == 4) {

					printf("More than 5 euro\n");
				}


				printf("++++++++++++++++++++++++++++\n");
				}// if

				temp = temp->NEXT;

        }//while

		

	}// else

	



}// search

void SearchCustomerName(struct node*top) {
	
	// variables
	node* temp;
	int count = 0;
	int found = 0;
	int option;


	char searchName[30];

	temp = (struct node*)malloc(sizeof(node));
	temp = top;

	// search by customer name

	printf("Enter customers Name: (char)\n");
	scanf("%s", searchName);

	// if found display list

	if (top == NULL) {
		printf("The list is empty\n");
	}
	else {

		temp = top;
		while (temp != NULL) {


			if (strcmp(temp->firstName,searchName) == 0)
			{

				printf("======DisplayList=========\n");
				printf(" PPS Number:%d\n", temp->PPSNumber);
				printf(" First Name:%s\n", temp->firstName);
				printf(" Second Name:%s\n", temp->secondName);
				printf(" Year born: %d\n", temp->yearBorn);
				printf(" Email: %s\n", temp->email);

				//area travelled from
				printf("Area travelled from:\n");
				if (temp->areasTravelFrom == 1)
				{
					printf("Traveled from Galway city\n");
				}
				else if (temp->areasTravelFrom == 2)
				{
					printf("Traveled from Galway county\n");
				}
				else if (temp->areasTravelFrom == 3)
				{
					printf("Traveled from Connacht\n");
				}
				else if (temp->areasTravelFrom == 4)
				{
					printf("Traveled from other areas in Ireland\n");
				}
				else if (temp->areasTravelFrom == 5)
				{
					printf("Traveled from outside Ireland\n");
				}

				// type of tickets
				printf("Type of ticket purchased:\n");
				if (temp->typeTicket == 1)
				{
					printf("Normal Ticket\n");
				}
				else if (temp->typeTicket == 2)
				{
					printf("Luxury ticket\n");
				}

				// trips to cinema
				printf("Trips made to the cinema per year:\n");
				if (temp->tripsPerYear == 1)
				{
					printf("Less than 3 times per year\n");
				}
				else if (temp->tripsPerYear == 2)
				{
					printf("Less than 5 times per year\n");
				}
				else if (temp->tripsPerYear == 3)
				{
					printf("More than 5 times per year\n");
				}

				// average spend on shop
				printf("average spend on cinema shop:\n");
				if (temp->averageSpent == 1) {

					printf("Nothing\n");
				}
				else if (temp->averageSpent == 2) {

					printf("Less than 5 euro\n");
				}
				else if (temp->averageSpent == 3) {

					printf("Less than 10 euro\n");
				}
				else if (temp->averageSpent == 4) {

					printf("More than 10 euro\n");
				}


				printf("++++++++++++++++++++++++++++\n");
			}// if

			temp = temp->NEXT;

		}//while



	}// else


}//search customer name 

void UpdateCustomerPPS(struct node* top) {
	// variables
	node* temp;

	int found = 0;
	int searchPPS;

	temp = (struct node*)malloc(sizeof(node));
	temp = top;

	// searchs by PPS number and if found it updates the details

	printf("Enter the PPS NUMBER of the customer, to update the details  (int)\n");
	scanf("%d", &searchPPS);

	if (top == NULL) {
		printf("The list is empty\n");
	}
	else {

		while (temp != NULL) {

			if (temp->PPSNumber == searchPPS)
			{
				printf("Customer has been found, please enter the new details\n");

				printf("Please enter PPS number (int)\n");
				scanf("%d", &temp->PPSNumber);

				printf("Please enter your first name (char)\n");
				scanf("%s", temp->firstName);

				printf("Please enter your second name (char)\n");
				scanf("%s", temp->secondName);

				printf("Please enter the year you're born (int)\n");
				scanf("%d", &temp->yearBorn);

				do
				{
					printf("Please enter your E-MAIL must contain '@' (char)\n");
					scanf("%s", temp->email);
				} while (strchr(temp->email, '@') == NULL);

				printf("Please enter which of the following areas you came from: (int)\n");
				printf("Press 1 for Galway City\n");
				printf("Press 2 for Galway County\n");
				printf("Press 3 for Connacht\n");
				printf("Press 4 for other areas of ireland\n");
				printf("Press 5 for outside ireland\n");
				scanf("%d", &temp->areasTravelFrom);

				printf("Which ticket did you purchase: Press 1 for Normal or 2 for Luxury (int) \n");
				scanf("%d", &temp->typeTicket);

				printf("How many trips to the cinema do you make per year (int)\n");
				printf("Press 1: Less than 3 times per year\n");
				printf("Press 2: Less than 5 times per year\n");
				printf("Press 3: More than 5 times per year\n");
				scanf("%d", &temp->tripsPerYear);

				printf("on average how much do you spend in the cinema shop (int)\n");
				printf("Press 1: nothing\n");
				printf("Press 2: Less than 5 euro\n");
				printf("Press 3: less than 10 euro\n");
				printf("Press 4: more than 10 euro\n");
				scanf("%d", &temp->averageSpent);

				found = 1;
				break;


			}//if 

			temp = temp->NEXT;

		}// WHILE

	}//else

	// not found message
	if (found == 0)
	{
		printf("Customer not found in the system\n");
	}//if




}// update customer PPS

void UpdateCustomerName(struct node* top) {
		
	    // variables
	    node* temp;

		int found = 0;
		char searchName[30];

		temp = (struct node*)malloc(sizeof(node));
		temp = top;

		// customers first name to search and update details
		printf("Enter the First Name of customer, to update the details (char)\n");
		scanf("%s", searchName);

		if (top == NULL) {
			printf("The list is empty\n");
		}
		
		else{

			// list to update
		while (temp != NULL) {

			if (strcmp(temp->firstName, searchName) == 0)
			{
				printf("Customer has been found, please enter the new details\n");

				printf("Please enter PPS number (int)\n");
				scanf("%d", &temp->PPSNumber);

				printf("Please enter your first name (char)\n");
				scanf("%s", temp->firstName);

				printf("Please enter your second name (char)\n");
				scanf("%s", temp->secondName);

				printf("Please enter the year you're born (int)\n");
				scanf("%d", &temp->yearBorn);

				do
				{
					printf("Please enter your E-MAIL must contain '@' (char)\n");
					scanf("%s", temp->email);
				} while (strchr(temp->email, '@') == NULL);

				printf("Please enter which of the following areas you came from: (int)\n");
				printf("Press 1 for Galway City\n");
				printf("Press 2 for Galway County\n");
				printf("Press 3 for Connacht\n");
				printf("Press 4 for other areas of ireland\n");
				printf("Press 5 for outside ireland\n");
				scanf("%d", &temp->areasTravelFrom);

				printf("Which ticket did you purchase: Press 1 for Normal or 2 for Luxury (int) \n");
				scanf("%d", &temp->typeTicket);

				printf("How many trips to the cinema do you make per year (int)\n");
				printf("Press 1: Less than 3 times per year\n");
				printf("Press 2: Less than 5 times per year\n");
				printf("Press 3: More than 5 times per year\n");
				scanf("%d", &temp->tripsPerYear);

				printf("on average how much do you spend in the cinema shop (int)\n");
				printf("Press 1: nothing\n");
				printf("Press 2: Less than 5 euro\n");
				printf("Press 3: less than 10 euro\n");
				printf("Press 4: More than 10 euro\n");
				scanf("%d", &temp->averageSpent);

				found = 1;
				break;
				// found and break out

			}//if 

			temp = temp->NEXT;

		}// WHILE

	}//else

		// not found message
	if (found == 0)
	{
		printf("Customer not found in the system\n");
	}








}// UPDATE CUSTOMER NAME

void DeleteCustomer(struct node** top, int position) {

	// Store head node 
	 node* temp = *top, * prev;

	// If head node itself holds the pps to be deleted 
	if (temp != NULL && temp->PPSNumber == position)
	{
		*top = temp->NEXT;
		free(temp);
		printf("Customer deleted\n");
		return;
	}

	// Search for the key to be deleted, keep track of the 
	// previous node as we need to change 'prev->NEXT' 
	while (temp != NULL && temp->PPSNumber != position)
	{
		prev = temp;
		temp = temp->NEXT;
	}

	// If key was not present in linked list 
	if (temp == NULL)
	{
		printf("Customer does not exist, try again...\n");
		return;
	}
	// Unlink the node from linked list 
	prev->NEXT = temp->NEXT;

	free(temp);  // Free memory


}// deleteCustomer

void outputReport(struct node* headptr) {

	//variable declaration
	FILE* customerDetails;//file pointer
	node* temp;//node pointer temp
	temp = (struct node*)malloc(sizeof(node));
	temp = headptr;

	//open customerFile.txt
	customerDetails = fopen("customer.txt", "w");

	// prints out list info to file
	while (temp !=NULL)
	{
		fprintf(customerDetails, "======DisplayList=========\n");
		fprintf(customerDetails," PPS Number:%d\n", temp->PPSNumber);
		fprintf(customerDetails, " First Name:%s\n", temp->firstName);
		fprintf(customerDetails, " Second Name:%s\n", temp->secondName);
		fprintf(customerDetails, " Year born: %d\n", temp->yearBorn);
		fprintf(customerDetails, " Email: %s\n", temp->email);

		//area travelled from
		fprintf(customerDetails, "Area travelled from:\n");
		if (temp->areasTravelFrom == 1)
		{
			fprintf(customerDetails, "Traveled from Galway city\n");
		}
		else if (temp->areasTravelFrom == 2)
		{
			fprintf(customerDetails, "Traveled from Galway county\n");
		}
		else if (temp->areasTravelFrom == 3)
		{
			fprintf(customerDetails, "Traveled from Connacht\n");
		}
		else if (temp->areasTravelFrom == 4)
		{
			fprintf(customerDetails, "Traveled from other areas in Ireland\n");
		}
		else if (temp->areasTravelFrom == 5)
		{
			fprintf(customerDetails, "Traveled from outside Ireland\n");
		}

		// type of tickets
		fprintf(customerDetails, "Type of ticket purchased:\n");
		if (temp->typeTicket == 1)
		{
			fprintf(customerDetails, "Normal Ticket\n");
		}
		else if (temp->typeTicket == 2)
		{
			fprintf(customerDetails, "Luxury ticket\n");
		}

		// trips to cinema
		fprintf(customerDetails, "Trips made to the cinema per year:\n");
		if (temp->tripsPerYear == 1)
		{
			fprintf(customerDetails, "Less than 3 times per year\n");
		}
		else if (temp->tripsPerYear == 2)
		{
			fprintf(customerDetails, "Less than 5 times per year\n");
		}
		else if (temp->tripsPerYear == 3)
		{
			fprintf(customerDetails, "More than 5 times per year\n");
		}

		// average spend on shop
		fprintf(customerDetails, "average spend on cinema shop:\n");
		if (temp->averageSpent == 1) {

			fprintf(customerDetails, "Nothing\n");
		}
		else if (temp->averageSpent == 2) {

			fprintf(customerDetails, "Less than 5 euro\n");
		}
		else if (temp->averageSpent == 3) {

			fprintf(customerDetails, "Less than 10 euro\n");
		}
		else if (temp->averageSpent == 4) {

			fprintf(customerDetails, "More than 10 euro\n");
		}


		fprintf(customerDetails, "++++++++++++++++++++++++++++\n");
		temp = temp->NEXT;


    }//while

	//confirm to screeen
	printf("All Details recorded in Customer.txt\n");
	fprintf(customerDetails, "  \n");
	fclose(customerDetails);//close file

}// output report

void saveFile(struct node* headptr)
{


	FILE* customerDetails;//file pointer

	node* temp;//node pointer temp
	temp = (struct node*)malloc(sizeof(node));

	temp = headptr;
	customerDetails = fopen("customer.txt", "w");//open file

	// prints to file when exists out of program
	while (temp != NULL)
	{
		fprintf(customerDetails, "======DisplayList=========\n");
		fprintf(customerDetails, " PPS Number:%d\n", temp->PPSNumber);
		fprintf(customerDetails, " First Name:%s\n", temp->firstName);
		fprintf(customerDetails, " Second Name:%s\n", temp->secondName);
		fprintf(customerDetails, " Year born: %d\n", temp->yearBorn);
		fprintf(customerDetails, " Email: %s\n", temp->email);

		//area travelled from
		fprintf(customerDetails, "Area travelled from:\n");
		if (temp->areasTravelFrom == 1)
		{
			fprintf(customerDetails, "Traveled from Galway city\n");
		}
		else if (temp->areasTravelFrom == 2)
		{
			fprintf(customerDetails, "Traveled from Galway county\n");
		}
		else if (temp->areasTravelFrom == 3)
		{
			fprintf(customerDetails, "Traveled from Connacht\n");
		}
		else if (temp->areasTravelFrom == 4)
		{
			fprintf(customerDetails, "Traveled from other areas in Ireland\n");
		}
		else if (temp->areasTravelFrom == 5)
		{
			fprintf(customerDetails, "Traveled from outside Ireland\n");
		}

		// type of tickets
		fprintf(customerDetails, "Type of ticket purchased:\n");
		if (temp->typeTicket == 1)
		{
			fprintf(customerDetails, "Normal Ticket\n");
		}
		else if (temp->typeTicket == 2)
		{
			fprintf(customerDetails, "Luxury ticket\n");
		}

		// trips to cinema
		fprintf(customerDetails, "Trips made to the cinema per year:\n");
		if (temp->tripsPerYear == 1)
		{
			fprintf(customerDetails, "Less than 3 times per year\n");
		}
		else if (temp->tripsPerYear == 2)
		{
			fprintf(customerDetails, "Less than 5 times per year\n");
		}
		else if (temp->tripsPerYear == 3)
		{
			fprintf(customerDetails, "More than 5 times per year\n");
		}

		// average spend on shop
		fprintf(customerDetails, "average spend on cinema shop:\n");
		if (temp->averageSpent == 1) {

			fprintf(customerDetails, "Nothing\n");
		}
		else if (temp->averageSpent == 2) {

			fprintf(customerDetails, "Less than 5 euro\n");
		}
		else if (temp->averageSpent == 3) {

			fprintf(customerDetails, "Less than 10 euro\n");
		}
		else if (temp->averageSpent == 4) {

			fprintf(customerDetails, "More than 10 euro\n");
		}


		fprintf(customerDetails, "++++++++++++++++++++++++++++\n");
		temp = temp->NEXT;

	}//while

}// save file

void bubbleSort(struct node* start) {
	 
	// variables
	 int swapped, i;
	 node* ptr1;
	 node* lptr = NULL;

	/* Checking for empty list */
	 if (start == NULL)
		 printf(" List is empty\n");
		return;

		// sorts by yearborn
	do
	{
		swapped = 0;
		ptr1 = start;

		while (ptr1->NEXT != lptr)
		{
			if (ptr1->yearBorn > ptr1->NEXT->yearBorn)
			{
				swap(ptr1, ptr1->NEXT); // calls swap function
				

				swapped = 1;
			}
			ptr1 = ptr1->NEXT;
		}
		lptr = ptr1;
	}
	while (swapped);


}// bubble

void swap( node* a, node* b) {

	// swap the year born and PPSnumber that relates to the same customer until they're in order

	int temp = a->yearBorn;
	a->yearBorn = b->yearBorn;
	b->yearBorn = temp;

	int temp1 = a->PPSNumber;
	a->PPSNumber = b->PPSNumber;
	b->PPSNumber = temp1;

	

	
	
	


}// swap

void displaySort(struct node* top) {
	
	//displays the details of the sort
	
	node* temp;
	if (top == NULL)
	{
		printf("Nothing in list\n");
	}
	else
	{
		temp = top;

		printf("This is the all customer's in the list PPSN and year born sorted by the year born oldest date\n");

		while (temp != NULL)
		{
			
			printf(" PPS Number:%d\n", temp->PPSNumber);
		    printf(" Year born: %d\n", temp->yearBorn);
			printf("++++++++++++++++++++++++++++\n");
			temp = temp->NEXT;






		}// while

	}//else

}// display sort
