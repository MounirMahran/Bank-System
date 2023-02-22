#include <iostream>
#include "ReadInputsLib.h"
#include <fstream>
#include <iomanip>

using namespace std;

void BankSystem();

const string ClientsFileName = "Clients.txt";

struct stBankClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool ToDelete = false;
	bool ToUpdate = false;
};

stBankClient ReadClientData() {
	stBankClient Client1;

	Client1.AccountNumber = ReadInput::ReadString("Please enter Account Number");
	Client1.PinCode = ReadInput::ReadString("Please enter Pin Code");
	Client1.Name = ReadInput::ReadString("Please enter Name");
	Client1.Phone = ReadInput::ReadString("Please enter Phone Number");
	Client1.AccountBalance = ReadInput::ReadNumber("Please enter Balance");

	return Client1;
}

void PrintClientData(stBankClient Client) {
	cout << "Account Number: " << Client.AccountNumber << endl;
	cout << "Account Pin Code: " << Client.PinCode << endl;
	cout << "User Name: " << Client.Name << endl;
	cout << "Phone Number: " << Client.Phone << endl;
	cout << "Accout Balance: " << Client.AccountBalance << endl;
}

void AddDataLineToFile(string FileName, string DataLine) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {
		MyFile << DataLine << endl;
		MyFile.close();
	}
}

string ConvertRecordToLine(stBankClient Client1, string Del = "#//#") {
	string Record = "";

	Record += Client1.AccountNumber;
	Record += Del;
	Record += Client1.PinCode;
	Record += Del;
	Record += Client1.Name;
	Record += Del;
	Record += Client1.Phone;
	Record += Del;
	Record += to_string(Client1.AccountBalance);

	return Record;


}

stBankClient ConvertLineToRecord(string S1, string Del = "#//#") {
	short Pos = S1.find(Del);
	stBankClient Client1;
	string sWord;


	sWord = S1.substr(0, Pos);
	S1.erase(0, Pos + Del.length());
	Client1.AccountNumber = sWord;
	Pos = S1.find(Del);


	sWord = S1.substr(0, Pos);
	S1.erase(0, Pos + Del.length());
	Client1.PinCode = sWord;
	Pos = S1.find(Del);

	sWord = S1.substr(0, Pos);
	S1.erase(0, Pos + Del.length());
	Client1.Name = sWord;
	Pos = S1.find(Del);

	sWord = S1.substr(0, Pos);
	S1.erase(0, Pos + Del.length());
	Client1.Phone = sWord;

	Client1.AccountBalance = stod(S1);


	return Client1;
}

void AddNewClient() {
	cout << "Adding New Client" << endl;
	stBankClient Client1;
	Client1 = ReadClientData();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client1, "#//#"));
}

void AddClients() {
	char AddMore = 'Y';

	do {
		AddNewClient();
		cout << "Do you want to add more clients? Y/N" << endl;
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

vector <stBankClient> ReadClientsFromFile(string FileName) {
	vector <stBankClient> vClients;

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string Line;
		stBankClient Client;
		while (getline(MyFile, Line)) {
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}

		MyFile.close();

	}

	return vClients;
}

void PrintHorizontalLine() {
	for (short i = 0; i < 60; i++) cout << "__";
	cout << endl;
}

void PrintSeparator() {
	cout << " | ";
}

void PrintHeader(short NumOfRecords) {

	cout << setw(55) << "Client List(" << NumOfRecords << ") Client(s)." << endl;
	PrintHorizontalLine();
	cout << endl;
	PrintSeparator();
	cout.width(15); cout << left << "Account Number";
	PrintSeparator();
	cout.width(10); cout << left << "Pin Code";
	PrintSeparator();
	cout.width(35); cout << left << "Client Name";
	PrintSeparator();
	cout.width(15); cout << left << "Phone";
	PrintSeparator();
	cout.width(10); cout << left << "Balance" << endl;
	PrintHorizontalLine();
}

void PrintOneClient(stBankClient Client1) {
	cout << endl;
	PrintSeparator();
	cout.width(15); cout << left << Client1.AccountNumber;
	PrintSeparator();
	cout.width(10); cout << left << Client1.PinCode;
	PrintSeparator();
	cout.width(35); cout << left << Client1.Name;
	PrintSeparator();
	cout.width(15); cout << left << Client1.Phone;
	PrintSeparator();
	cout.width(10); cout << left << Client1.AccountBalance << endl;
}

void PrintOneClientBalance(stBankClient Client1) {
	cout << endl;
	PrintSeparator();
	cout.width(15); cout << left << Client1.AccountNumber;
	PrintSeparator();
	cout.width(35); cout << left << Client1.Name;
	PrintSeparator();
	cout.width(10); cout << left << Client1.AccountBalance << endl;
}

void PrintAllClients(vector <stBankClient> Clients) {
	PrintHeader(Clients.size());

	for (stBankClient& Client : Clients) {
		PrintOneClient(Client);
	}

}

void AllBalancesHeader(short NumOfRecords) {
	cout << setw(55) << "Client List(" << NumOfRecords << ") Client(s)." << endl;
	PrintHorizontalLine();
	cout << endl;
	PrintSeparator();
	cout.width(15); cout << left << "Account Number";
	PrintSeparator();
	cout.width(35); cout << left << "Client Name";
	PrintSeparator();
	cout.width(10); cout << left << "Balance" << endl;
	PrintHorizontalLine();
}

void PrintAllClientsBalances(vector <stBankClient> Clients) {
	AllBalancesHeader(Clients.size());
	for (stBankClient& Client : Clients) {
		PrintOneClientBalance(Client);
	}
}

bool IsAccount(string AccountNumber, stBankClient& Client, vector <stBankClient> vClients) {

	for (stBankClient& C : vClients) {
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

void MarkForDeletion(string AccountNumber, vector <stBankClient>& vClients) {
	for (stBankClient& Client : vClients) {
		if (Client.AccountNumber == AccountNumber) {
			Client.ToDelete = true;
		}
	}
}

void SaveVectorToFile(string FileName, vector <stBankClient> vClients) {
	fstream MyFile;
	string Line;

	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {
		for (stBankClient& Client : vClients) {
			Line = ConvertRecordToLine(Client);
			MyFile << Line << endl;
		}

		MyFile.close();
	}
}

void SaveVectorToFileToDelete(string FileName, vector <stBankClient> vClients) {
	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open()) {
		for (stBankClient& Client : vClients) {
			if (Client.ToDelete == false) {
				MyFile << ConvertRecordToLine(Client) << endl;
			}
		}
		MyFile.close();
	}

}

void DeleteAccount(string AccountNumber, vector <stBankClient>& vClients) {
	char Delete;
	stBankClient Client;
	if (IsAccount(AccountNumber, Client, vClients)) {

		PrintClientData(Client);
		Delete = ReadInput::ReadCharacter("Are you sure you want to delete it? Y/N");
		if (toupper(Delete) == 'Y') {
			MarkForDeletion(AccountNumber, vClients);
			SaveVectorToFileToDelete(ClientsFileName, vClients);
			vClients = ReadClientsFromFile(ClientsFileName);
			cout << "Account Deleted Successfully" << endl;
		}

	}
	else {
		cout << "Account Can't be found :-(" << endl;
	}

}

void MarkForUpdate(string AccountNumber, vector <stBankClient>& vClients) {
	for (stBankClient& Client : vClients) {
		if (Client.AccountNumber == AccountNumber) {
			Client.ToUpdate = true;
		}
	}
}

void SaveVectorToFileToUpdate(string FileName, vector <stBankClient> vClients) {
	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open()) {
		for (stBankClient& Client : vClients) {
			if (Client.ToUpdate == false) {
				MyFile << ConvertRecordToLine(Client) << endl;
			}
			else {
				Client = ReadClientData();
				MyFile << ConvertRecordToLine(Client) << endl;
			}
		}
		MyFile.close();
	}
}

void UpdateAccount(string AccountNumber, vector <stBankClient>& vClients) {
	char Update;
	stBankClient Client;
	if (IsAccount(AccountNumber, Client, vClients)) {

		PrintClientData(Client);
		Update = ReadInput::ReadCharacter("Are you sure you want to update it? Y/N");
		if (toupper(Update) == 'Y') {
			MarkForUpdate(AccountNumber, vClients);
			SaveVectorToFileToUpdate(ClientsFileName, vClients);
			vClients = ReadClientsFromFile(ClientsFileName);
		}
		cout << "Account Updated Successfully" << endl;
	}
	else {
		cout << "Account Can't be found :-(" << endl;
	}
}

void MainMenuScreen() {
	cout << "===============================================" << endl;
	cout << "               Main Menu Screen               " << endl;
	cout << "===============================================" << endl;

	cout << "\t[1] Show Client List." << endl;
	cout << "\t[2] Add New Client." << endl;
	cout << "\t[3] Delete Client." << endl;
	cout << "\t[4] Update Client Info." << endl;
	cout << "\t[5] Find Client." << endl;
	cout << "\t[6] Transactions." << endl;
	cout << "\t[7] Exit." << endl;
	cout << "===============================================" << endl;

}

void ShowClientListScreen() {
	vector <stBankClient> vClients;
	vClients = ReadClientsFromFile(ClientsFileName);
	system("cls");
	PrintAllClients(vClients);
}

void ShowBalancesScreen() {
	vector <stBankClient> vClients;
	vClients = ReadClientsFromFile(ClientsFileName);
	system("cls");
	PrintAllClientsBalances(vClients);
}

void AddNewClientScreen() {
	system("cls");
	cout << "===============================================" << endl;
	cout << "             Add New Client Screen             " << endl;
	cout << "===============================================" << endl;
	AddClients();
}

void DeleteAccountScreen() {

	system("cls");
	vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);
	cout << "===============================================" << endl;
	cout << "             Delete Account Screen             " << endl;
	cout << "===============================================" << endl;
	string AccNum;
	AccNum = ReadInput::ReadString("Please enter account number you want to delete");
	DeleteAccount(AccNum, vClients);
}

void UpdateAccountScreen() {
	system("cls");
	vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);
	cout << "===============================================" << endl;
	cout << "             Update Account Screen             " << endl;
	cout << "===============================================" << endl;
	string AccNum;
	AccNum = ReadInput::ReadString("Please enter account number you want to update");
	UpdateAccount(AccNum, vClients);
}

void FindClientScreen() {
	system("cls");
	vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);
	cout << "===============================================" << endl;
	cout << "             Find Account Screen             " << endl;
	cout << "===============================================" << endl;
	string AccNum;
	AccNum = ReadInput::ReadString("Please enter account number you want to search for");
	stBankClient Client;

	if (IsAccount(AccNum, Client, vClients))
		PrintClientData(Client);
	else cout << "Account Can't be found :-(" << endl;

}

void TransactionsMenuScreen() {
	system("cls");
	cout << "===============================================" << endl;
	cout << "            Transactions Menu Screen           " << endl;
	cout << "===============================================" << endl;
	cout << "\t[1] Deposit." << endl;
	cout << "\t[2] Withdraw." << endl;
	cout << "\t[3] Total Balances." << endl;
	cout << "\t[4] Main Menu" << endl;
	cout << "===============================================" << endl;

}

void Deposit(string AccNum) {
	vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);
	double Amount;
	cout << "Please enter amount you want to deposit" << endl;
	cin >> Amount;
	char Dep = 'N';
	cout << "Are you sure you want to deposit: $" << Amount << " to " << AccNum << endl;
	cin >> Dep;
	if (toupper(Dep) == 'Y') {
		for (stBankClient& Client : vClients) {
			if (Client.AccountNumber == AccNum) {
				Client.AccountBalance += Amount;
				SaveVectorToFile(ClientsFileName, vClients);
				cout << "Amount of: $" << Amount << " has been deposited to " << Client.Name << " Successfully" << endl;
			}
		}
	}
	else return;

}

void DepositScreen() {
	vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);
	stBankClient Client;
	system("cls");
	cout << "===============================================" << endl;
	cout << "                 Deposit Screen                " << endl;
	cout << "===============================================" << endl;
	string AccNum;
	AccNum = ReadInput::ReadString("Please enter account number you want to deposit to");
	if (IsAccount(AccNum, Client, vClients)) {
		PrintClientData(Client);
		Deposit(AccNum);
	}
	else {
		cout << "Account is not found" << endl;
		system("pause");
		DepositScreen();
	}
}

void Withdraw(string AccNum) {
	vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);
	double Amount;
	cout << "Please enter amount you want to withdraw" << endl;
	cin >> Amount;
	char Dep = 'N';
	cout << "Are you sure you want to withdraw: $" << Amount << " from " << AccNum << endl;
	cin >> Dep;
	if (toupper(Dep) == 'Y') {
		for (stBankClient& Client : vClients) {
			if (Client.AccountNumber == AccNum) {
				Client.AccountBalance -= Amount;
				SaveVectorToFile(ClientsFileName, vClients);
				cout << "Amount of: $" << Amount << " has been withdrawed from " << Client.Name << " Successfully" << endl;
			}
		}
	}
	else return;
}

void WithdrawalScreen() {
	vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);
	stBankClient Client;
	system("cls");
	cout << "===============================================" << endl;
	cout << "               Withdrawal Screen               " << endl;
	cout << "===============================================" << endl;
	string AccNum;
	AccNum = ReadInput::ReadString("Please enter account number you want to withdraw from");
	if (IsAccount(AccNum, Client, vClients)) {
		PrintClientData(Client);
		Withdraw(AccNum);
	}
	else {
		cout << "Account is not found" << endl;
		system("pause");
		WithdrawalScreen();
	}
}

void TransactionsScreen() {
	TransactionsMenuScreen();
	short Choice = ReadInput::ReadNumInRange(1, 4, "Please choose what do you want to do [1] -> [4]");
	switch (Choice)
	{
	case 1:
		DepositScreen();
		system("pause");
		TransactionsScreen();
	case 2:
		WithdrawalScreen();
		system("pause");
		TransactionsScreen();
	case 3:
		ShowBalancesScreen();
		system("pause");
		TransactionsScreen();
	case 4:
		BankSystem();
	}
}

void BankSystem() {
	vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);
	system("cls");
	int Choice;
	MainMenuScreen();
	Choice = ReadInput::ReadNumInRange(1, 6, "Choose what do you want to do [1] -> [6]");
	switch (Choice)
	{
	case 1:
		ShowClientListScreen();
		system("pause");
		BankSystem();
	case 2:
		AddNewClientScreen();
		system("pause");
		BankSystem();
	case 3:
		DeleteAccountScreen();
		system("pause");
		BankSystem();
	case 4:
		UpdateAccountScreen();
		system("pause");
		BankSystem();
	case 5:
		FindClientScreen();
		system("pause");
		BankSystem();
	case 6:
		TransactionsScreen();
		system("pause");
	case 7:
		break;
	}
}

int main()
{
	BankSystem();


	system("pause");
	return 0;
}