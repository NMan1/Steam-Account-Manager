#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <algorithm>

#define STEAM_DIRECTORY "C:\\Program Files (x86)\\Steam\\Steam.exe"

using namespace std;


int main()
{
	int accNum = 0;
	string line;
	fstream myFile;

	myFile.open("SteamAccountManager.txt", ios::in);

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, 400, 550, TRUE); //  width,  height

	if (!myFile.is_open())
	{
		cout << "Could Not Open File, exiting..." << endl;
		Sleep(100);
	}
	else
	{
		cout << "File Opened. ";
		cout << "To add or remove accounts, open the SteamAcountManager.txt file. \nNow displaying all stored accounts...\n" << endl;
	}


	if (myFile.is_open())
	{ 
		while (getline(myFile, line))
		{
			accNum++; //Add 1
			cout << accNum << " ";
			cout << line << endl;
		}
	}

	cout << "\nTotal Accounts: " << accNum << endl;

	int pick;
	cout << "Enter Account Number: ";
	cin >> pick;

	int line_no = 0;

	/* Resets getline to beegining of file */
	myFile.clear();
	myFile.seekg(0, ios::beg);

	for (int i = 1; i <= pick; i++) //loops through beegining of file to the amount of times pick was set to. Stops at the right account
	{
		getline(myFile, line);

		line_no++;
	}

	size_t findSemi = line.find(":"); // Attempts to find ":" in username and password

	if (findSemi != string::npos) //If line.find fails its equal to string::npos meaning not found
		line.erase(findSemi, 1); //Deltes semi coloin

	line.insert(findSemi, " "); //Inserts a space at the semi colons postion after it got delted pos (position)

	string passWord = line.substr(findSemi); //gets last string after semi collon, pos should be secound paramnter but if its shorter than strringeverything after will be included

	passWord.erase(remove_if(passWord.begin(), passWord.end(), isspace), passWord.end());

	line.insert(0, " ");
	
	int usernameLength = 0;

	for (int i = 0; i <= findSemi; i++) //adds 1 to the usernameLenght, this int tells us how many charcters in the username before stopping at findSemi
		usernameLength++;

	string userName = line.substr(0, usernameLength);

	userName.erase(remove_if(userName.begin(), userName.end(), isspace), userName.end());

	/* Final step, exuctes CMD commands to close steam, lanunch it with correct account*/

	string arguments = "-login " + userName + " " + passWord;
	ShellExecute(NULL, "open", STEAM_DIRECTORY, arguments.c_str(), NULL, SW_SHOWMINIMIZED);

	myFile.close();
	return 0;
}
