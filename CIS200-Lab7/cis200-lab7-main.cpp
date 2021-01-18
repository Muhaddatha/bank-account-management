#include<iostream>
#include<string>
#include<fstream>
#include<ostream>
/*
Author: Muhaddatha Abdulghani
Date created: 3/15/19
Date updated: 3/15/19
File: Lab7-2/Souce.cpp
purpose: The purpose of this lab is learning how to use write and blocks
of code int a binary file.
*/
struct clientData {
	int accountNumber;
	char lastName[16];
	char firstName[11];
	float balance;
};
const int STRUCT_SIZE = sizeof(clientData);
int main() {
	//initializing file
	std::fstream creditFile("credit.dat", std::ios::binary |
		std::ios::out | std::ios::in);
	clientData blankClient = { 0, "Last", "First", 0.0 };
	for (int i = 0; i < 101; i++) {
		blankClient.accountNumber = i;
		creditFile.write(reinterpret_cast<const char
			*>(&blankClient), sizeof(clientData));
	}
	if (!creditFile.is_open()) {
		std::cout << "Error while opening file." << std::endl;
	}
	int numberOfAccountsWritten = 0;
	int howManyAccountsToWrite;
	int accountNum;
	std::string fName, lName;
	float accountBalance;
	std::cout << "----------------------------------------------------"
		<< std::endl;
	std::cout << " Welcome to this program ."
		<< std::endl;
	std::cout << "----------------------------------------------------"
		<< std::endl;
	std::cout << "How many accounts would you like to create? ";
	std::cin >> howManyAccountsToWrite;
	while (numberOfAccountsWritten < howManyAccountsToWrite) {
		clientData newClient;
		//getting the account number from user
		std::cout << "Account number: "; std::cin >> accountNum;
		while (accountNum <= 0 || accountNum > 100 ||
			std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << "Please enter a valid account number: ";
				std::cin >> accountNum;
		}
		newClient.accountNumber = accountNum;
		//getting last name from user
		std::cout << "Last Name: "; std::cin >> lName;
		int lNameSize;
		if (lName.length() >= 16) {
			lNameSize = 16;
		}
		else {
			lNameSize = lName.length();
		}
		for (int i = 0; i < lNameSize; i++) {
			newClient.lastName[i] = lName.at(i);
		}
		newClient.lastName[lNameSize] = '\0';
		//getting first name from user
		std::cout << "First name: "; std::cin >> fName;
		int fNameSize;
		if (fName.length() >= 11) {
			fNameSize = 11;
		}
		else {
			fNameSize = fName.length();
		}
		for (int i = 0; i < fNameSize; i++) {
			newClient.firstName[i] = fName.at(i);
		}
		newClient.firstName[fNameSize] = '\0';
		//getting account balance from user
		std::cout << "Account balance: "; std::cin >>
			accountBalance;
		while (accountBalance < 0 || std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << "Please enter a valid account balance: "; std::cin >> accountBalance;
		}
		newClient.balance = accountBalance;
		creditFile.seekg(0, std::ios::beg);
		for (int i = 0; i < accountNum; i++) {
			creditFile.seekp(STRUCT_SIZE, std::ios::cur);
		}
		creditFile.write(reinterpret_cast<const char
			*>(&newClient), sizeof(clientData));
		std::cout << "*Success" << std::endl;
		std::cout << std::endl;
		numberOfAccountsWritten++;
	}//end of creating accounts
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "--------------------------------------------" <<
		std::endl;
	std::cout << " Printing accounts " << std::endl;
	std::cout << "--------------------------------------------" <<
		std::endl;
	creditFile.seekg(creditFile.tellg(), std::ios::beg);
	int howManyAccountsRead = 0;
	clientData currentData;
	creditFile.seekg(0, std::ios::beg);
	for (int i = 0; i < 101; i++) {
		creditFile.read(reinterpret_cast<char *>(&currentData),
			STRUCT_SIZE);
		if (currentData.accountNumber != 0) {
			std::cout << "Account number: " <<
				currentData.accountNumber << std::endl;
			std::cout << "Name: " <<
				currentData.firstName << " " << currentData.lastName << std::endl;
			std::cout << "Balance: " <<
				currentData.balance << std::endl;
			std::cout << std::endl;
			howManyAccountsRead++;
		}
	}
	//std::cout << "How many account printed: " << howManyAccountsRead;
	char choice;
	std::cout << "Would you like to update an account?(y or n) ";
	std::cin >> choice;
	clientData updateClient;
	while (choice == 'y' || choice == 'Y') {
		std::cout << "Which account number: "; std::cin >>
			accountNum;
		while (accountNum < 0 || accountNum > 100 ||
			std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << "Please enter a valid account number: ";
				std::cin >> accountNum;
		}
		updateClient.accountNumber = accountNum;
		std::cout << "Please enter the updated last name: ";
		std::cin >> lName;
		int lNameSize;
		if (lName.length() >= 16) {
			lNameSize = 16;
		}
		else {
			lNameSize = lName.length();
		}
		for (int i = 0; i < lNameSize; i++) {
			updateClient.lastName[i] = lName.at(i);
		}
		updateClient.lastName[lNameSize] = '\0';
		std::cout << "Please enter the updated first name: ";
		std::cin >> fName;
		int fNameSize;
		if (fName.length() >= 11) {
			fNameSize = 11;
		}
		else {
			fNameSize = fName.length();
		}
		for (int i = 0; i < fNameSize; i++) {
			updateClient.firstName[i] = fName.at(i);
		}
		updateClient.firstName[fNameSize] = '\0';
		std::cout << "Please enter the updated balance: ";
		std::cin >> accountBalance;
		while (accountBalance < 0 || std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << "Please enter a valid account balance: "; std::cin >> accountBalance;
		}
		updateClient.balance = accountBalance;
		creditFile.seekg(0, std::ios::beg);
		for (int i = 0; i < accountNum; i++) {
			creditFile.seekp(STRUCT_SIZE, std::ios::cur);
		}
		creditFile.write(reinterpret_cast<const char
			*>(&updateClient), sizeof(clientData));
		std::cout << "*Success" << std::endl;
		std::cout << std::endl;
		creditFile.seekg(creditFile.tellg(), std::ios::beg);
		creditFile.seekg(0, std::ios::beg);
		for (int i = 1; i < 101; i++) {
			creditFile.seekp(STRUCT_SIZE, std::ios::cur);
			if (i == accountNum) {
				creditFile.read(reinterpret_cast<char
					*>(&currentData), STRUCT_SIZE);
				std::cout << "The updated information is: " << std::endl;
					std::cout << "Account number: " <<
					currentData.accountNumber << std::endl;
				std::cout << "Name: " <<
					currentData.firstName << " " << currentData.lastName << std::endl;
				std::cout << "Balance: " <<
					currentData.balance << std::endl;
				std::cout << std::endl;
			}
		}
		std::cout << "Continue updating accounts?(y or n) ";
		std::cin >> choice;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	char option;
	bool printAllAccounts = true;
	std::cout << "Please choose an option" << std::endl;
	std::cout << "1. Print all accounts(empty and initialized account)."
		<< std::endl;
	std::cout << "2. Print initialized accounts only." << std::endl;
	std::cout << "Option: "; std::cin >> option;
	while (option != '1' && option != '2') {
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Please enter a valid option (1 or 2): ";
		std::cin >> option;
	}
	if (option == '1') {
		printAllAccounts = true;
	}
	else {
		printAllAccounts = false;
	}
	creditFile.seekg(creditFile.tellg(), std::ios::beg);
	clientData currentData1;
	creditFile.seekg(0, std::ios::beg);
	for (int i = 0; i < 100; i++) {
		creditFile.read(reinterpret_cast<char *>(&currentData1),
			STRUCT_SIZE);
		if (printAllAccounts) {
			std::cout << "Account number: " <<
				currentData1.accountNumber << std::endl;
			std::cout << "Name: " <<
				currentData1.firstName << " " << currentData1.lastName << std::endl;
			std::cout << "Balance: " <<
				currentData1.balance << std::endl;
			std::cout << std::endl;
		}
		else {
			if (currentData1.balance > 0) {
				std::cout << "Account number: " <<
					currentData1.accountNumber << std::endl;
				std::cout << "Name: " <<
					currentData1.firstName << " " << currentData1.lastName << std::endl;
				std::cout << "Balance: " <<
					currentData1.balance << std::endl;
				std::cout << std::endl;
			}
		}
	}
	system("pause");
	return 0;
}