//not finished, need to add more functionality to the program

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <windows.h>
#include <limits>
#include <sstream>
#include <cstring>


using namespace std;
bool access = false;
bool admin = false;
bool loggedIn = false;
string currentUsername = "";

int validInput()
{
    int x;
    cin >> x;
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Bad entry.  Enter a NUMBER: ";
        cin >> x;
    }
    return x;
}

//create a log of actions taken in the program, appends to the bottom of the file
void logAction(string action) {
    ofstream file("log.txt", ios::app);
    file << action << endl;
    file.close();
}

//create new account in txt file
void createAccount() {
    cin.ignore(1000, '\n');
    string username, password, dob, gender, address, phone, email, RegoNum;
    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter new password: ";
    cin >> password;
    cout << "Enter your date of birth (dd/mm/yyyy): ";
    cin >> dob;
    //checks if the date of birth is in the correct format
    while (dob.length() != 10 || dob[2] != '/' || dob[5] != '/') {
        cout << "Invalid date of birth, please enter in the format dd/mm/yyyy: ";
        cin >> dob;
    }
    cout << "enter your gender: ";
    cin >> gender;

    cout << "Enter your address: ";
    //user can enter multiple words for the address
    cin.ignore(1000, '\n');
    getline(cin, address);

    cout << "Enter your phone number: ";
    cin >> phone;
    cout << "Enter your email: ";
    cin >> email;
    cout << "Enter your vehicle registration number: ";
    cin >> RegoNum;


    if (admin == true) {
        cout << "Do you want to give admin permissions to this account? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y') {
            ofstream file("Customer_registration.txt", ios::app);
            file << endl << username << " " << password << " " << dob << " " << gender << " >" <<address << "< " << phone << " " << email << " " << RegoNum << "_" << "1";
            file.close();
            cout << "Account created successfully" << endl;
            logAction(currentUsername + "::" + "Admin account created: " + username);
            return;
        }
    } else {
        ofstream file("Customer_registration.txt", ios::app);
        file << endl << username << " " << password << " " << dob << " " << gender << " >" <<address << "< " << phone << " " << email << " " << RegoNum << "_" << "0";
        file.close();
        cout << "Account created successfully" << endl;
        logAction(currentUsername + "::" + "Account created: " + username);
    }
}

int main() {
    logAction("::Program started::");
    cout << "Hello!" << endl;
    cout << "Welcome to the Mors Mutual Insurance Vehicle Management System" << endl;
    while (true) {
        
        
        cout << "what would you like to do?" << endl;
        cout << "1. Login/registration" << endl;
        cout << "2. info and contact" << endl;
        cout << "3. Exit" << endl;
        cout << "please enter the number of the option you would like to select" << endl;
        int choice = validInput();
        if (choice == 1) {
            //clear the screen
            system("CLS");
            cout << "Welcome to the login/registration page" << endl;
            cout << "1. Login" << endl;
            cout << "2. Register" << endl;
            cout << "3. logout" << endl;
            cout << "4. Back" << endl;
            cout << "please enter the number of the option you would like to select" << endl;
            int choice2 = validInput();
            if (choice2 == 1 && access == false) {
                cout << "Enter username: ";
                string username;
                cin >> username;
                cout << "Enter password: ";
                string password;
                cin >> password;
                ifstream file("Customer_registration.txt");
                string line;
                string actualUsername;
                string actualPassword;
                while (getline(file, line)) {
                    //uses strtok to split the line into the username, paswsword, and the rest of the line
                    char *cstr = new char[line.length() + 1];
                    char *Ptoken = new char[line.length() + 1];
                    strcpy(cstr, line.c_str());
                    char *token = strtok(cstr, " ");
                    strcpy(Ptoken, line.c_str());\
                    actualUsername = token;
                    token = strtok(NULL, " ");
                    actualPassword = Ptoken;
                    Ptoken = strtok(NULL, " ");
                

                    cout << actualUsername << endl;
                    cout << actualPassword << endl;
                    if (actualUsername == username && actualPassword == password){
                        cout << "Login successful" << endl;
                        currentUsername = username;
                        logAction(currentUsername + "::" + "Login");
                        access = true;
                        if (line.find("_1") != string::npos) {
                            admin = true;
                            logAction(currentUsername + "::" + "Admin login");
                            cout << "You have admin permissions" << endl;
                        }
                        break;
                    }
                }
                if (access == false) {
                    cout << "Login failed" << endl;
                    cout << "would you like to create an account? (y/n): ";
                    char choice;
                    cin >> choice;
                    if (choice == 'y') {
                        createAccount();

                    }
                }
            } else if (choice2 == 1 && access == true) {
                //clear the screen'
                system("CLS");
                cout << "You are already logged in" << endl;
                cout << "please logout to login with a different account" << endl;
            } else if (choice2 == 2) {
                createAccount();
            } else if (choice2 == 3) {
                access = false;
                admin = false;
                currentUsername = "";
                cout << "Goodbye!" << endl;
                logAction(currentUsername + "::loged out");
                Sleep(3000);
                //clear the screen
                system("CLS");
            
            }else {
                //clear the screen
                system("CLS");
            }
        
    
        
        } else if (choice == 2) {
            //clear the screen
            system("CLS");
            cout << "Mors Mutual Insurance" << endl;
            cout << "Contact: 1-866-922-8694" << endl;
            cout << "Email: MMI@insurance.com" << endl;

        }else if (choice == 3){
            break;
        }
        
    }
    logAction("::Program ended::");
    return 0;
}
