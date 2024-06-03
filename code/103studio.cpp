//not finished, need to add more functionality to the program

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <windows.h>
#include <limits>
#include <sstream>
#include <cstring>
#include <utility> 
#include <stdexcept> 
#include <vector>
#include <regex>


using namespace std;
bool access = false;
bool admin = false;
bool loggedIn = false;
string currentUsername = "";

//function to read the csv file and return a vector of pairs with the vector containing the data
vector<pair<string, vector<string>>> read_csv(string filename) {
    ifstream file(filename);
    vector<pair<string, vector<string>>> result;
    string line;
    string cell;
    vector<string> values;
    while (getline(file, line)) {
        stringstream lineStream(line);
        while (getline(lineStream, cell, ',')) {
            values.push_back(cell);
        }
        result.push_back(make_pair(values.at(0), values));
        values.clear();
    }
    return result;
}



int validInput()
{
    int x;
    cin >> x;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
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
    cin.clear();
    string username = "", password = "", dob, gender, address, phone, email, RegoNum;
    cout << "Enter new username: ";
    getline(cin, username);
    //checks if there is a space in the username and asks the user to enter a new username
    while (username.find(" ") != string::npos) {
        cout << "Username cannot contain spaces, please enter a new username: ";
        cin.clear();
        getline(cin, username);
    }

    cout << "Enter new password: ";
    cin.clear();
    getline(cin, password);
    while (password.find(" ") != string::npos) {
        cout << "password cannot contain spaces, please enter a new password: ";
        cin.clear();
        getline(cin, password);
    }
    cin.clear();
    cout << "Enter your date of birth (dd/mm/yyyy): ";
    getline(cin, dob);
    //checks if the date of birth is in the correct format
    while (dob.length() != 10 || dob[2] != '/' || dob[5] != '/') {
        cout << "Invalid date of birth, please enter in the format dd/mm/yyyy: ";
        cin.clear();
        getline(cin, dob);
    }
    cin.clear();
    cout << "enter your gender: ";
    getline(cin, gender);

    cout << "Enter your address: ";
    //user can enter multiple words for the address
    cin.clear();

    getline(cin, address);
    cin.clear();

    cout << "Enter your phone number: ";
    getline(cin, phone);
    //checks if the phone number is an int and contains no spaces
    while (phone.find(" ") != string::npos || phone.find_first_not_of("0123456789") != string::npos) {
        cout << "Invalid phone number, please enter a valid phone number: ";
        cin.clear();
        getline(cin, phone);
    }

    cout << "Enter your email: ";
    cin.clear();
    getline(cin, email);
    //checks if the email is in the correct format
    while (!regex_match(email, regex("([a-zA-Z0-9]+)@([a-zA-Z0-9]+)\\.([a-zA-Z0-9]+)"))) {
        cout << "Invalid email, please enter a valid email: ";
        cin.clear();
        getline(cin, email);
    }
    cout << "Enter your vehicle registration number: ";
    cin.clear();
    getline(cin, RegoNum);
    //checks if the RegoNum is in the correct format and contains no spaces
    while (RegoNum.length() != 6 || RegoNum.find(" ") != string::npos) {
        cout << "Invalid registration number, please enter a valid registration number: ";
        cin.clear();
        getline(cin, RegoNum);
    }


    if (admin == true) {
        cout << "Do you want to give admin permissions to this account? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y') {
            ofstream file("Customer_registration.csv", ios::app);
            file << username << "," << password << "," << dob << "," << gender << "," << address << "," << phone << "," << email << "," << RegoNum << "," << "1" << endl;
            file.close();
            cout << "Account created successfully" << endl;
            logAction(currentUsername + "::" + "Admin account created: " + username);
            return;
        }
    }
    else {
        ofstream file("Customer_registration.csv", ios::app);
        file << username << "," << password << "," << dob << "," << gender << "," << address << "," << phone << "," << email << "," << RegoNum << "," << "0" << endl;
        file.close();
        cout << "Account created successfully" << endl;
        logAction(currentUsername + "::" + "Account created: " + username);
    }
}

void customerMenu() {

    if (access == true) {
               
        while (true) {

            system("CLS"); 
            //customer screen menu
            cout << "Welcome to the Customer Menu. Please select an option.\n" << endl;
            cout << "1. Policy and Insurance" << endl;
            cout << "2. Claims" << endl;
            cout << "3. Renewals" << endl;
            cout << "4. Benefits of Mors Mutual Insurance" << endl;
            cout << "5. Back" << endl;
            int choice3 = validInput();
            if (choice3 == 5) {
                cout << "Goodbye\n" << endl;
                system("CLS");
                break;

            }
            else if (choice3 == 1) {
                cout << "Policy and Insurance" << endl;
                cout << "1. View Policies" << endl;
                cout << "2. Register for a Policy" << endl;
                cout << "3. Get a Quote" << endl;
                cout << "4. Back" << endl;
                int choice4 = validInput();
                if (choice4 == 1) {
                    //clear screen
                    system("CLS");      

                    //policy screen menu  
                    cout << "1. Comprehensive\n" << endl;
                    cout << "2. Third Party Fire & Theft" << endl;
                    cout << "3. Third Party Only" << endl;
                    cout << "4. Register for Policy" << endl;
                    cout << "5. Back" << endl;
                    int choice5 = validInput();
                
                    if (choice5 == 1) {
                        cout << "Comprehensive Insurance\n" << endl;
                        cout << "Keep yourself and your car completely protected with our most popular policy. We will cover the damage to your car, as well as any damage you might cause to someone else’s vehicle or property." << endl;
                        cout << "Benefits:" << endl;
                        cout << "- Damage to your vehicle" << endl;
                        cout << "- Damage caused by fire or theft" << endl;
                        cout << "- Damage to other people’s vehicles or property" << endl;
                        cout << "- Damage caused by an uninsured third party" << endl;
                        cout << "Press enter twice to continue" << endl;
                        cin.ignore();
                        cin.get();
                        if (cin.get()) {
                            continue;
                        }

                    }else if (choice5 == 2) {
                        cout << "Third Party Fire & Theft Insurance\n" << endl;
                        cout << "Cover for your car if it's damaged by fire or stolen, and if you accidentally cause damage to someone else's car or property." << endl;
                        cout << "Benefits:" << endl;
                        cout << "- Damage caused by fire" << endl;
                        cout << "- Theft of vehcile" << endl;
                        cout << "- Damage caused by uninsured third party" << endl;
                        cout << "- Damage to other people's property" << endl;
                        cout << "Press enter twice to continue" << endl;
                        cin.ignore();
                        cin.get();
                        if (cin.get()) {
                            continue;
                        }
                    }else if (choice5 == 3) {
                        cout << "Third Party Only Insurance\n" << endl;
                        cout << "Our most basic policy. It covers the damage you might cause to someone else’s vehicle or property, but not your own." << endl;
                        cout << "Benefits:" << endl;
                        cout << "- Damage to other people’s vehicles or property" << endl;
                        cout << "- Damage caused by an uninsured third party" << endl;
                        cout << "Press enter twice to continue" << endl;
                        cin.ignore();
                        cin.get();
                        if (cin.get()) {
                            continue;
                        }

                    }
                }else if (choice4 == 2) {
                    cout << "Register for a Policy" << endl;
                    cout << "Please select the Policy type you would like to register for:" << endl;
                    cout << "1. Comprehensive" << endl;
                    cout << "2. Third Party Fire & Theft" << endl;
                    cout << "3. Third Party Only" << endl;
                    cout << "4. Back" << endl;
                    int choice8 = validInput();
                    if (choice8 == 1) 

                }
        
            }else if (choice3 == 2) {

                while (true) { 
                    cout << "Claims Menu\n" << endl;
                    cout << "1. Make a Claim" << endl;
                    cout << "2. Check Claim Status" << endl;
                    cout << "3. Back" << endl;
                    int choice6 = validInput();
                    
                    if (choice6 == 3) {
                        break;

                    }else if (choice6 == 1) {
                        while (true) {
                            cout << "Make a Claim" << endl;
                            cout << "Please select your policy type:" << endl;
                            cout << "1. Comprehensive" << endl;
                            cout << "2. Third Party Fire & Theft" << endl;
                            cout << "3. Third Party Only" << endl;
                            cout << "4. Back" << endl;
                            int choice7 = validInput();
                           //check with user if this is the correct account to make a claim with
                            if(choice7 == 1) {
                                cout << "Comprehensive Insurance" << endl;
                                vector<pair<string, vector<string>>> result = read_csv("Customer_registration.csv");
                                for (int i = 0; i < result.size(); i++) {
                                    if (result.at(i).first == currentUsername) {
                                        cout << "Is this the correct account to make a claim with? (y/n): " << result.at(i).first << endl;
                                        cin.clear();
                                        char choice;
                                        cin >> choice;
                                        if (choice == 'y') {
                                            //from the user account details, get the registration number, contact number, email and address and store variables
                                            //create a csv that will store claim data

                                            string RegoNum = result.at(i).second.at(7);
                                            string phone = result.at(i).second.at(5);
                                            string email = result.at(i).second.at(6);
                                            string address = result.at(i).second.at(4);
                                            cout << "Some Claim information has been pre-filled for you from your account. Please provide further details towards your Claim." << endl;
                                            cin.clear();
                                            cin.ignore(1000, '\n');
                                            cout << "Enter the date that the incident occured (dd/mm/yyyy): ";
                                            string incidentDate;
                                            //checks if the date of birth is in the correct format
                                            getline(cin, incidentDate);
                                            cin.clear();
                                            while (incidentDate.length() != 10 || incidentDate[2] != '/' || incidentDate[5] != '/') {
                                                cout << "Invalid date, please enter in the format dd/mm/yyyy: ";
                                                cin.clear();
                                                getline(cin, incidentDate);
                                            }
                                            //checks if the time is in the correct format
                                            cout << "Enter the time that the incident occured (hh.mm): ";
                                            string incidentTime;
                                            cin.clear();
                                            getline(cin, incidentTime);
                                            while (incidentTime.length() != 5 || incidentTime[2] != '.') {
                                                cout << "Invalid time, please enter in the format hhmm: ";
                                                cin.clear();
                                                getline(cin, incidentTime);
                                            }
                                            cout << "Please provide a brief description of the incident: ";
                                            string description;
                                            cin.clear();
                                            getline(cin, description);

                                            //store the claim data in a csv file
                                            ofstream file("Claims.csv", ios::app);
                                            file << currentUsername << "," << RegoNum << "," << phone << "," << email << "," << address << "," << incidentDate << "," << incidentTime << "," << description << endl;
                                            file.close();
                                            cout << "Claim made successfully" << endl;
                                            logAction(currentUsername + "::" + "Claim made");
                                            break;
                                        }
                                    }
                                }
                            }else if (choice7 == 4) {
                                break;
                            }
                        
                       
                        }



                    }




                        



                }
            }
    
        }
    
    }else {
        cout << "Invalid access, please login first." << endl;
        Sleep(3000);
        system("CLS");
    }


}

int main() {
    logAction("::Program started::");
    cout << "Hello!" << endl;
    cout << "Welcome to the Mors Mutual Insurance Vehicle Management System" << endl;
    while (true) {


        cout << "What would you like to do?\n" << endl;
        cout << "1. Login/Registration" << endl;
        cout << "2. Customer Menu" << endl;
        cout << "3. Info and Contact" << endl;
        cout << "4. Exit" << endl;
        cout << "Please enter the number of the option you would like to select" << endl;
        int choice = validInput();
        if (choice == 1) {
            int attempts = 0;
            int accountNum = 0;
            //clear the screen
            system("CLS");
            cout << "Welcome to the Login/Registration page\n" << endl;
            cout << "1. Login" << endl;
            cout << "2. Register" << endl;
            cout << "3. Logout" << endl;
            cout << "4. Back" << endl;
            cout << "Please enter the number of the option you would like to select" << endl;
            int choice2 = validInput();
            if (choice2 == 1 && access == false) {
                while (access == false && attempts < 3) {
                    //clear the screen
                    system("CLS");
                    cout << "Enter username: ";
                    string username;
                    cin >> username;
                    cout << "Enter password: ";
                    string password;
                    cin >> password;
                    //uses readcsv function to read the csv file
                    vector<pair<string, vector<string>>> result = read_csv("Customer_registration.csv");
                    //loops through the vector of pairs to check if the username and password match
                    string actualUsername = "";
                    string actualPassword = "";
                    for (int i = 0; i < result.size(); i++) {
                        if (result.at(i).first == username) {
                            actualUsername = result.at(i).first;
                            actualPassword = result.at(i).second.at(1);
                            accountNum = i;
                        }

                    }



                    if (actualUsername == username && actualPassword == password) {
                        cout << "Login successful!\n" << endl;
                        currentUsername = username;
                        logAction(currentUsername + "::" + "Login");
                        access = true;
                        //check if the account has admin permissions
                        if (result.at(accountNum).second.at(8) == "1") {
                            admin = true;
                            cout << "You have admin permissions" << endl;
                        }

                    }
                    else {
                        cout << "Login failed" << endl;
                        attempts++;
                        if (attempts == 3) {
                            cout << "You have reached the maximum number of attempts" << endl;
                            cout << "would you like to create an account? (y/n): ";
                            char choice;
                            cin >> choice;
                            if (choice == 'y') {
                                createAccount();
                            }
                            //clear the screen
                            system("CLS");
                        }

                    }
                }






            }
            else if (choice2 == 1 && access == true) {
                //clear the screen'
                system("CLS");
                cout << "You are already logged in" << endl;
                cout << "Please logout to login with a different account" << endl;
            }
            else if (choice2 == 2) {
                createAccount();
            }
            else if (choice2 == 3) {
                access = false;
                admin = false;
                currentUsername = "";
                cout << "Goodbye!\n" << endl;
                logAction(currentUsername + "::loged out");
                Sleep(3000);
                //clear the screen
                system("CLS");

            }
            else {
                //clear the screen
                system("CLS");
            }



        } else if (choice == 2) {
      
            customerMenu();
                    
                
           

      
        }
        else if (choice == 3) {
            //clear the screen
            system("CLS");
            cout << "Mors Mutual Insurance" << endl;
            cout << "Contact: 1-866-922-8694" << endl;
            cout << "Email: MMI@insurance.com" << endl;

        }
        else if (choice == 4) {
            break;
        }

    }
    logAction("::Program ended::");
    return 0;
}