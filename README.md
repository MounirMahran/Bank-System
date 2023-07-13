# Bank System
This code implements a simple menu-driven banking system in C++. The program reads client information from a file, displays a main menu screen, and prompts the user to choose one of six options to perform various banking operations. The program uses recursive calls to itself after each operation is performed, allowing the user to perform multiple operations without having to exit and restart the program.

## Options
1.Show Client List: Displays a list of all clients.
2.Add New Client: Adds a new client to the system.
3.Delete Account: Deletes an existing client from the system.
4.Update Account: Updates an existing client's information.
5.Find Client: Finds a client based on their account information.
6.Transactions: Performs banking transactions for a client.
7.Exit: Exits the program.

## How to Compile and Run
To compile the program, you can use any C++ compiler that supports C++11 or later. For example, you can use the g++ compiler on Linux or the Visual C++ compiler on Windows.

To run the program, simply execute the compiled executable. The program will read client information from a file named Clients.txt, which should be located in the same directory as the executable.


## Limitations
This code provides a very basic framework for a simple banking system, but would require additional implementation to be fully functional. Additionally, the program does not include any input validation or error handling, so invalid user input or file read errors may cause the program to crash.


