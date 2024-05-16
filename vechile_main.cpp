//not finished, need to add more functionality to the program

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <windows.h>
#include <limits>

using namespace std;
bool access = false;
bool admin = false;
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
    string username, password;
    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter new password: ";
    cin >> password;
    if (admin == true) {
        cout << "Do you want to give admin permissions to this account? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y') {
            ofstream file("loginData.txt", ios::app);
            file << endl << username << " " << password << "_" << "1";
            file.close();
            cout << "Account created successfully" << endl;
            logAction(currentUsername + "::" + "Admin account created: " + username);
            return;
        }
    } else {
        ofstream file("loginData.txt", ios::app);
        file << endl << username << " " << password << "_" << "0";
        file.close();
        cout << "Account created successfully" << endl;
        logAction(currentUsername + "::" + "Account created: " + username);
    }
    
}

//delete an account in the txt file
void deleteAccount() {
    bool accountDeleted = false;
    string username, password;
    cout << "Enter username to delete: ";
    cin >> username;
    cout << "Enter password of user to delete: ";
    cin >> password;
    
    //checks if user is sure
    if (username == currentUsername) {
        cout << "You cannot delete your own account" << endl;
        return;
    }
    cout << "Are you sure you want to delete this account? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'n') {
       
        cout << "Account deletion cancelled" << endl;
        return;
    }

    ifstream file("loginData.txt");
    
    string line2;
    
    ofstream temp("temp.txt");
    Sleep(1000);
    while (getline(file, line2)) {
        if (line2 != username + " " + password + "_0" && line2 != username + " " + password + "_1") {
            
           
            temp << line2 << endl;
        } else {
            cout << "deleting account" << endl;
            cout << "Account deleted successfully" << endl;
            logAction(currentUsername + "::" + "Account deleted: " + username);
            accountDeleted = true;
        }
    }
    file.close();
    temp.close();

    if (accountDeleted == false) {
        cout << "Account not found" << endl;
        logAction(currentUsername + "::" + "Account not found: " + username);
        
    }
    
    remove("loginData.txt");
    rename("temp.txt", "loginData.txt");
    
    
    
    
   
        
    
    file.close();
}

void login() {
    int attempts = 0;
    while (access == false) {
        map <string, string> logins;
        map <string, string> adminPerms;
        //read login data from file
        ifstream file("loginData.txt");
        string line;
        while (getline(file, line)) {
            string username = line.substr(0, line.find(' '));
            string password = line.substr(line.find(' ') + 1, line.find('_') - line.find(' ') - 1);
            string adminPerm = line.substr(line.find('_') + 1, line.length() - 1);

            
            
           
            logins[username] = password;
            adminPerms[username] = adminPerm;
        }

        //login
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (logins[username] == password) {
            currentUsername = username;
            cout << "Login successful" << endl;
            logAction(currentUsername + "::" + "Login successful: " + username);
            if (adminPerms[username] == "1") {
                admin = true;
                cout << "welcome admin" << endl;
                logAction(currentUsername + "::" + "Admin login");
            }
            access = true;
            break;
        } else {
            cout << "Login failed" << endl;
            logAction(currentUsername + "::" + "Login failed: " + username);
            attempts++;
            if (attempts == 3) {
                cout << "You have reached the maximum number of attempts" << endl;
                logAction(currentUsername + "::" + "Reached maximum login attempts");
                break;
            }
            //asks user if they would like to try again
            cout << "Would you like to try again? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'n') {
                //asks user if they would like to make a account
                cout << "Would you like to create an account? (y/n): ";
                char choice2;
                cin >> choice2;
                if (choice2 == 'y') {
                    createAccount();
                    logAction(currentUsername + "::" + "Account created after failed login");
                    //changes current username to the new account
                    

                } else {
                    break;
                }
                
            }

           

        }
    }
    
}

int main() {
    logAction("::Program started::");
    while (true) {
        //menu
        cout << "Welcome to the vehicle management system" << endl;
        cout << "1. login" << endl;
        cout << "2. create account" << endl;
        cout << "3. delete account" << endl;
        cout << "4. logout" << endl;
        cout << "5. exit" << endl;

        int choice = validInput();
        switch (choice) {
            case 1:
                if (access == true) {
                    cout << "You are already logged in, please log out to continue" << endl;
                    logAction(currentUsername + "::" + "Attempted to login while already logged in");
                    break;
                } else {
                    login();
                }
                
                break;
            case 2:
                createAccount();
                break;
            case 3:
                if (access == false || admin == false) {
                    cout << "You must login as admin first" << endl;
                    logAction(currentUsername + "::" + "Attempted to delete account without admin login");
                    login();
                } else {
                    deleteAccount();
                    logAction(currentUsername + "::" + "attempting to delete account");
                }
                
                break;
            case 4:
                access = false;
                admin = false;
                
                logAction(currentUsername + "::" + "Logout");
                currentUsername = "";
                break;
            case 5:
                logAction("::Program ended::");
                return 0;
            default:
                cout << "Invalid choice" << endl;
                logAction(currentUsername + "::" + "Invalid choice taken in menu");

        }
    }
    
    return 0;
}
