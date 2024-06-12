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
#include <iomanip>


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

string date() {
    //get the current date
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    //return the date in the format dd/mm/yyyy
    return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    
}


//make sure the input is a int
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

// Function for calculating the quote based on the user's input
double calculateQuote(int age, int gender, int licenseStatus, int insuranceType, int vehicleType) {
    double baseQuote;

    if (insuranceType == 1) { // Comprehensive
        baseQuote = 60.0;
    } else if (insuranceType == 2) { // Third Party Fire & Theft
        baseQuote = 45.0;
    } else if (insuranceType == 3) { // Third Party Only
        baseQuote = 30.0;
    } else {
        cout << "Invalid input. Please select a valid option." << endl;
        return 0;
    }

    if (age > 16 || age <= 25) {
        baseQuote *= 1.15;
    }
    
    if (gender == 1) { // male
        baseQuote *= 1.20;
    }else if (gender == 2) { //female
        baseQuote *= 1.00;
    } else {
        cout << "Invalid input. Please select a valid gender." << endl;
        return 0; 
    }
    
    if (licenseStatus == 1) { // Full license
        baseQuote *= 1.05;
    } else if (licenseStatus == 2) { // Restricted license
        baseQuote *= 1.20;
    } else if (licenseStatus == 3) { // Learner's license
        cout << "Unfortunatly, we do not offer insurance to drivers with a learner's license. Please try again later." << endl;
        return 0;
    } else {
        cout << "Invalid input. Please select a valid option for license status." << endl;
        return 0;
    }
    
    if (vehicleType == 1) { // Car
        baseQuote *= 1.15;
    } else if (vehicleType == 2) { // Motorcycle
        baseQuote *= 0.90;
    } else {
        cout << "Invalid input. Please select a valid option for vehicle type." << endl;
        return 0; 
    }
    
    // Display the quote
    cout << "Your fixed quote is: $" << fixed << setprecision(2) << baseQuote << " per month." <<endl;
    return baseQuote;
}

void displayQuote(string quoteType, int age) {
    string licenseStatus;
    string baseQuote;
    if (quoteType == "Comprehensive") {
        baseQuote = "$60.00";
    }else if (quoteType == "Third Party Fire & Theft") {
        baseQuote = "$45.00";
    }else if (quoteType == "Third Party Only") {
        baseQuote = "$30.00";
    }
    cout << "You have selected: " << quoteType << endl;
    cout << "The base quote for this policy is: " << baseQuote << " This policy price will change depending on your circumstances." << endl;
    cout << "Please enter your age: ";
    cin.clear();
    age = validInput();
    while (age < 16) {
        cout << "You must be at least 16 years old to apply for a quote." << endl;
        Sleep(3000);
        return;
    }
    while (age >= 90) {
        cout << "You must be under 90 years old to apply for a quote." << endl;
        Sleep(3000);
        return;
    }

    cout << "Please select a gender option: " << endl;
    cout << "1. Male" << endl;
    cout << "2. Female" << endl;
    cin.clear();
    cin.ignore();
    int gender = validInput();
    //check if the user inputs a valid option
    while (gender != 1 && gender != 2) {
        cout << "Invalid input. Please enter a valid option: 1 for Male, 2 for Female: ";
        cin.clear();
        gender = validInput();
    }

    cout << "Please select your current license status: " << endl;
    cout << "1. Full License" << endl;
    cout << "2. Restricted License" << endl;
    cout << "3. Learner's License" << endl;
    cin.clear();
    cin.ignore();
    getline(cin, licenseStatus);
    //check if the user inputs a valid option
    while (licenseStatus != "1" && licenseStatus != "2" && licenseStatus != "3") {
        cout << "Invalid input. Please enter a valid option: 1 for Full License, 2 for Restricted License, 3 for Learner's License: ";
        cin.clear();
        getline(cin, licenseStatus);
        
    }
    if (licenseStatus == "3") {
        cout << "Unfortunatly, we do not offer insurance to drivers with a learner's license. Please try again later." << endl;
        Sleep(3000);
        return;
    }
    int licenseStatusInt = stoi(licenseStatus);
    
    cout << "Please select the vehicle type you wish to register: " << endl;
    cout << "1. Car" << endl;
    cout << "2. Motorcycle" << endl;
    cin.clear();
    int vehicleType = validInput();
    //check if the user inputs a valid option
    while (vehicleType != 1 && vehicleType != 2) {
        cout << "Invalid input. Please enter a valid option: 1 for Car, 2 for Motorcycle: ";
        cin.clear();
        vehicleType = validInput();
    }
    double Quote = 0;
    int insuranceType = 0;
    if (quoteType == "Comprehensive") {
        // Calculation
        insuranceType = 1; 
    }else if (quoteType == "Third Party Fire & Theft") {
        // Calculation
        insuranceType = 2; 
    }else if (quoteType == "Third Party Only") {
        // Calculation
        insuranceType = 3;
    }
    
    // Calculation
    Quote = calculateQuote(age, gender, licenseStatusInt, insuranceType, vehicleType);
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
    //checks if there is a space in the password and asks the user to enter a new password
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
    cout << "Enter your gender: ";// gender input can be anything
    getline(cin, gender);

    cout << "Enter your address: ";
    //user can enter multiple words for the address ,and does not check if number is first
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
    //checks if the RegoNum is in the correct format and contains no spaces. only letting you put a string with a length of 6 
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
            cout << "2. Claims" << endl; //needs work
            cout << "3. Renewals" << endl; //needs to be made
            cout << "4. Benefits of Mors Mutual Insurance" << endl; //needs to be made
            cout << "5. Back" << endl;
            int CustomerChoice = validInput(); // this was choice3
            
            if (CustomerChoice == 1) {
                system("CLS");
                cout << "Policy and Insurance" << endl;
                cout << "1. View & Register for Policies" << endl; //done
                cout << "2. Get a Quote" << endl; //needs work
                cout << "3. Back" << endl;
                int policyInsureanceChoice = validInput();// this was choice4
                if (policyInsureanceChoice == 1) {
                    //clear screen
                    system("CLS");      

                    //policy screen menu  
                    cout << "1. Comprehensive" << endl;
                    cout << "2. Third Party Fire & Theft" << endl;
                    cout << "3. Third Party Only" << endl;
                    cout << "4. Register for Policy" << endl;
                    cout << "5. Back" << endl;
                    int policyChoice = validInput(); // this was choice5
                
                    if (policyChoice == 1) {
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

                    }else if (policyChoice == 2) {
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
                    }else if (policyChoice == 3) {
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

                    }else if (policyChoice == 4) {
                        cout << "Register for a Policy" << endl;
                        cout << "Please select the Policy type you would like to register for:" << endl;
                        cout << "1. Comprehensive" << endl;
                        cout << "2. Third Party Fire & Theft" << endl;
                        cout << "3. Third Party Only" << endl;
                        cout << "4. Back" << endl;
                        int regPoliceyChoice = validInput();// was choice8
                        if (regPoliceyChoice == 1) {
                            //clear screen
                            system("CLS");
                            //read the csv file to get user details: username, dob, gender, address, phone, email, RegoNum
                            vector<pair<string, vector<string>>> result = read_csv("Customer_registration.csv");
                            for (int i = 0; i < result.size(); i++) {
                                if (result.at(i).first == currentUsername) {
                                    cout << "Is this the correct account to register for a policy with? (y/n): " << result.at(i).first << endl;
                                    cin.clear();
                                    char choice;
                                    cin >> choice;
                                    if (choice == 'y') {
                                        //from the user account details, get the registration number, contact number, email and address and store variables
                                        //create a csv that will store policy data
                                        string RegoNum = result.at(i).second.at(7);
                                        string phone = result.at(i).second.at(5);
                                        string email = result.at(i).second.at(6);
                                        string address = result.at(i).second.at(4);
                                        
                                        cout << "Some Policy information has been pre-filled for you from your account. Please provide further details towards your Comprehensive Policy." << endl;
                                        cin.clear();
                                        cin.ignore(1000, '\n');
                                        
                                        cout << "Enter the date that the policy will start (dd/mm/yyyy): ";
                                        string startDate;
                                        //checks if the date of birth is in the correct format
                                        getline(cin, startDate);
                                        cin.clear();
                                        while (startDate.length() != 10 || startDate[2] != '/' || startDate[5] != '/') {
                                            cout << "Invalid date, please enter in the format dd/mm/yyyy: ";
                                            cin.clear();
                                            getline(cin, startDate);
                                        }
                                        //user must enter input for their vehicle make, model and year
                                        cout << "Enter the make of your vehicle: ";
                                        string make;
                                        cin.clear();
                                        getline(cin, make);
                                        cout << "Enter the model of your vehicle: ";
                                        string model;
                                        cin.clear();
                                        getline(cin, model);
                                        cout << "Enter the year of your vehicle: ";
                                        string year;
                                        cin.clear();
                                        //check if the year is an int with 4 digits and no spaces
                                        getline(cin, year);
                                        while (year.length() != 4 || year.find(" ") != string::npos || year.find_first_not_of("0123456789") != string::npos) {
                                            cout << "Invalid year, please enter a valid year: ";
                                            cin.clear();
                                            getline(cin, year);
                                        }
                                        int policyNum;
                                        
                                        vector<pair<string, vector<string>>> result1 = read_csv("Policies.csv");
                                        for (int i = 0; i < result1.size(); i++) {
                                            if (result1.size() == 0) {
                                                policyNum = 1;
                                            }else {
                                                policyNum = i + 1;
                                            }
                                        }
                                        
                                        
                                        
                                        cout << "Your policy number is: " << policyNum << endl;

                                        //store the policy data in a csv file
                                        ofstream file("Policies.csv", ios::app);
                                        file << currentUsername << "," << RegoNum << "," << phone << "," << email << "," << address << "," << startDate << "," << make << "," << model << "," << year << "," << policyNum << "," << "comprehensive" <<endl;
                                        
                                        file.close();
                                        Sleep(3000);
                                        cout << "Policy registered successfully. Thank you for choosing Mors Mutual Insurance!" << endl;
                                        logAction(currentUsername + "::" + "Policy registered");
                                        break; 
                                    }
                                    

                                }
                            }
                        }else if (regPoliceyChoice == 2) {
                            //clear screen
                            system("CLS");
                            //read the csv file to get user details: username, dob, gender, address, phone, email, RegoNum
                            vector<pair<string, vector<string>>> result = read_csv("Customer_registration.csv");
                            for (int i = 0; i < result.size(); i++) {
                                if (result.at(i).first == currentUsername) {
                                    cout << "Is this the correct account to register for a policy with? (y/n): " << result.at(i).first << endl;
                                    cin.clear();
                                    char choice;
                                    cin >> choice;
                                    if (choice == 'y') {
                                        //from the user account details, get the registration number, contact number, email and address and store variables
                                        //create a csv that will store policy data
                                        string RegoNum = result.at(i).second.at(7);
                                        string phone = result.at(i).second.at(5);
                                        string email = result.at(i).second.at(6);
                                        string address = result.at(i).second.at(4);
                                        cout << "Some Policy information has been pre-filled for you from your account. Please provide further details towards your Third Party Fire & Theft Policy." << endl;
                                        cin.clear();
                                        cin.ignore(1000, '\n');
                                        cout << "Enter the date that the policy will start (dd/mm/yyyy): ";
                                        string startDate;
                                        //checks if the date of birth is in the correct format
                                        getline(cin, startDate);
                                        cin.clear();
                                        while (startDate.length() != 10 || startDate[2] != '/' || startDate[5] != '/') {
                                            cout << "Invalid date, please enter in the format dd/mm/yyyy: ";
                                            cin.clear();
                                            getline(cin, startDate);
                                        }
                                        //user must enter input for their vehicle make, model and year
                                        cout << "Enter the make of your vehicle: ";
                                        string make;
                                        cin.clear();
                                        getline(cin, make);
                                        cout << "Enter the model of your vehicle: ";
                                        string model;
                                        cin.clear();
                                        getline(cin, model);
                                        cout << "Enter the year of your vehicle: ";
                                        string year;
                                        cin.clear();
                                        //check if the year is an int with 4 digits and no spaces
                                        getline(cin, year);
                                        while (year.length() != 4 || year.find(" ") != string::npos || year.find_first_not_of("0123456789") != string::npos) {
                                            cout << "Invalid year, please enter a valid year: ";
                                            cin.clear();
                                            getline(cin, year);
                                        }
                                        int policyNum;
                                        
                                        vector<pair<string, vector<string>>> result1 = read_csv("Policies.csv");
                                        for (int i = 0; i < result1.size(); i++) {
                                            if (result1.size() == 0) {
                                                policyNum = 1;
                                            }else {
                                                policyNum = i + 1;
                                            }
                                        }
                                        
                                        
                                        
                                        cout << "Your policy number is: " << policyNum << endl;

                                        //store the policy data in a csv file
                                        ofstream file("Policies.csv", ios::app);
                                        file << currentUsername << "," << RegoNum << "," << phone << "," << email << "," << address << "," << startDate << "," << make << "," << model << "," << year << "," << policyNum << "," << "third party fire & theft" << endl;
                                        //clear screen
                                        system("CLS");
                                        file.close();
                                        Sleep(3000);
                                        cout << "Policy registered successfully. Thank you for choosing Mors Mutual Insurance!" << endl;
                                        logAction(currentUsername + "::" + "Policy registered");
                                        break; 
                                    }
                                    

                                }
                            }
                        }else if (regPoliceyChoice == 3) {
                            //clear screen
                            system("CLS");
                            //read the csv file to get user details: username, dob, gender, address, phone, email, RegoNum
                            vector<pair<string, vector<string>>> result = read_csv("Customer_registration.csv");
                            for (int i = 0; i < result.size(); i++) {
                                if (result.at(i).first == currentUsername) {
                                    cout << "Is this the correct account to register for a policy with? (y/n): " << result.at(i).first << endl;
                                    cin.clear();
                                    char choice;
                                    cin >> choice;
                                    if (choice == 'y') {
                                        //from the user account details, get the registration number, contact number, email and address and store variables
                                        //create a csv that will store policy data
                                        string RegoNum = result.at(i).second.at(7);
                                        string phone = result.at(i).second.at(5);
                                        string email = result.at(i).second.at(6);
                                        string address = result.at(i).second.at(4);
                                        cout << "Some Policy information has been pre-filled for you from your account. Please provide further details towards your Third Party Only Policy." << endl;
                                        cin.clear();
                                        cin.ignore(1000, '\n');
                                        cout << "Enter the date that the policy will start (dd/mm/yyyy): ";
                                        string startDate;
                                        //checks if the date of birth is in the correct format
                                        getline(cin, startDate);
                                        cin.clear();
                                        while (startDate.length() != 10 || startDate[2] != '/' || startDate[5] != '/') {
                                            cout << "Invalid date, please enter in the format dd/mm/yyyy: ";
                                            cin.clear();
                                            getline(cin, startDate);
                                        }
                                        //user must enter input for their vehicle make, model and year
                                        cout << "Enter the make of your vehicle: ";
                                        string make;
                                        cin.clear();
                                        getline(cin, make);
                                        cout << "Enter the model of your vehicle: ";
                                        string model;
                                        cin.clear();
                                        getline(cin, model);
                                        cout << "Enter the year of your vehicle: ";
                                        string year;
                                        cin.clear();
                                        //check if the year is an int with 4 digits and no spaces
                                        getline(cin, year);
                                        while (year.length() != 4 || year.find(" ") != string::npos || year.find_first_not_of("0123456789") != string::npos) {
                                            cout << "Invalid year, please enter a valid year: ";
                                            cin.clear();
                                            getline(cin, year);
                                        }
                                        int policyNum;
                                        
                                        vector<pair<string, vector<string>>> result1 = read_csv("Policies.csv");
                                        for (int i = 0; i < result1.size(); i++) {
                                            if (result1.size() == 0) {
                                                policyNum = 1;
                                            }else {
                                                policyNum = i + 1;
                                            }
                                        }
                                        
                                        
                                        
                                        cout << "Your policy number is: " << policyNum << endl;

                                        //store the policy data in a csv file
                                        ofstream file("Policies.csv", ios::app);
                                        file << currentUsername << "," << RegoNum << "," << phone << "," << email << "," << address << "," << startDate << "," << make << "," << model << "," << year << "," << policyNum << "," << "third party only" << endl;
                                        //clear screen
                                        system("CLS");
                                        file.close();
                                        Sleep(3000);
                                        cout << "Policy registered successfully. Thank you for choosing Mors Mutual Insurance!" << endl;
                                        logAction(currentUsername + "::" + "Policy registered");
                                        break; 
                                    }   
                                }
                            }
                        }
                           
                    }else if (policyChoice == 5) {
                        break;
                    }
                    

                //claims menu
                }else if (policyInsureanceChoice == 2) {
                    int age;
                    int gender;
                    int licenseStatus;
                    int insuranceType;
                    int vehicleType;
                    double baseQuote;
                    
                    cout << "Request a Quote" << endl;
                    cout << "Please select the policy you would like to recieve a quote for:" << endl;
                    cout << "1. Comprehensive" << endl;
                    cout << "2. Third Party Fire & Theft" << endl;
                    cout << "3. Third Party Only" << endl;
                    insuranceType = validInput();

                    if (insuranceType == 1) {
                        string quoteType = "Comprehensive";
                        displayQuote(quoteType, age);
                        
                    }if (insuranceType == 2) {
                        string quoteType = "Third Party Fire & Theft";
                        displayQuote(quoteType, age);
                        
                    }if (insuranceType == 3) {
                        string quoteType = "Third Party Only";
                        displayQuote(quoteType, age);
                    
                    } 
                    //wait for user to press enter twice
                    cout << "Press enter twice to continue" << endl;
                    cin.ignore();
                    cin.get();
                    if (cin.get()) {
                        continue;
                    }

                }
                     
            }else if (CustomerChoice == 2) {

                while (true) { 
                    cout << "Claims Menu\n" << endl;
                    cout << "1. Make a Claim" << endl;
                    cout << "2. Back" << endl;
                    int claimsChoice = validInput(); // this was choice6
                    
                    if (claimsChoice == 2) {
                        break;

                    }else if (claimsChoice == 1) {
                        while (true) {
                            cout << "Make a Claim" << endl;
                            cout << "Please select your policy type:" << endl;
                            cout << "1. Comprehensive" << endl;
                            cout << "2. Third Party Fire & Theft" << endl;
                            cout << "3. Third Party Only" << endl;
                            cout << "4. Back" << endl;
                            int subClaimsChoice = validInput();//this was choice7
                           //check with user if this is the correct account to make a claim with
                            if(subClaimsChoice == 1) {
                                
                                //clear screen
                                system("CLS");
                                
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
                                            cout << "You are making a Claim for a Comprehensive Policy." << endl;
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
                                            file << currentUsername << "," << RegoNum << "," << phone << "," << email << "," << address << "," << incidentDate << "," << incidentTime << "," << description << "," << endl;
                                            file.close();
                                            cout << "Claim made successfully" << endl;
                                            logAction(currentUsername + "::" + "Claim made");
                                            break;

                                        }else if (choice == 'n') {
                                            cout << "Please login with the correct account you wish to make a Claim with." << endl;
                                            Sleep(3000);
                                            system("CLS");
                                            break; 

                                        }

                                    }
                                }
                            }else if(subClaimsChoice == 2) {
                                
                                //clear screen
                                system("CLS");
                                
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
                                            cout << "You are making a claim for a Third Party Fire & Theft Policy." << endl;
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
                                            file << currentUsername << "," << RegoNum << "," << phone << "," << email << "," << address << "," << incidentDate << "," << incidentTime << "," << description << "," << endl;
                                            file.close();
                                            cout << "Claim made successfully" << endl;
                                            logAction(currentUsername + "::" + "Claim made");
                                            break;

                                        }else if (choice == 'n') {
                                            cout << "Please login with the correct account you wish to make a Claim with." << endl;
                                            Sleep(3000);
                                            system("CLS");
                                            break; 

                                        }
                                    }
                                }
                            }else if (subClaimsChoice == 3) {
                                
                                //clear screen
                                system("CLS");
                                
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
                                            cout << "You are making a claim for a Third Party Only Policy." << endl;
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
                                            file << currentUsername << "," << RegoNum << "," << phone << "," << email << "," << address << "," << incidentDate << "," << incidentTime << "," << description << "," << endl;
                                            file.close();
                                            cout << "Claim made successfully" << endl;
                                            logAction(currentUsername + "::" + "Claim made");
                                            break;

                                        }else if (choice == 'n') {
                                            cout << "Please login with the correct account you wish to make a Claim with." << endl;
                                            Sleep(3000);
                                            system("CLS");
                                            break; 

                                        }
                                    }
                                }
                            }
                        }                               
                    }
                }   
                
            }else if (CustomerChoice ==3) {
                bool renew = true;
                cout << "Renewals" << endl;
                cout << "Is this the correct account to renew your policy with? (y/n): " << currentUsername << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                string choice;
                getline(cin, choice);
                //checks that the user inputs the correct input
                while (choice != "y" && choice != "n") {
                    cout << "Invalid input, please enter 'y' for yes or 'n' for no: ";
                    cin.clear();
                    getline(cin, choice);
                }
                if (choice == "y") {
                    //read csv to find the row with the current username
                    vector<pair<string, vector<string>>> result = read_csv("Policies.csv");
                    //check the current policy type
                    for (int i = 0; i < result.size(); i++) {
                        if (result.at(i).first == currentUsername) {
                            cout << "Your current policy type is: " << result.at(i).second.at(10) << endl;
                            cout << "Would you like to renew your policy? (y/n): ";
                            char renewChoice;
                            cin >> renewChoice;
                            if (renewChoice == 'y') {
                                //check the policy type and calculate the renewal cost
                                if (result.at(i).second.at(10) == "comprehensive") {
                                    cout << "The renewal cost for your Comprehensive policy is $60 per month." << endl;
                                    //asks for users card info
                                    cout << "Please enter your card details to renew your policy: " << endl;
                                    cout << "Card Number: ";
                                    string cardNum;
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    getline(cin, cardNum);
                                    //check that the card numbger is all numbers
                                    while (cardNum.find_first_not_of("0123456789") != string::npos) {
                                        cout << "Invalid card number, please enter a valid card number (it may only contain numbers): ";
                                        cin.clear();
                                        getline(cin, cardNum);
                                    }
                                    //adds the current users policy info to a new csv file with the renewal date
                                    ofstream file("Renewals.csv", ios::app);
                                    
                                    //from the result vector, get the start date and add 1 year to it
                                    string startDate = result.at(i).second.at(5);
                                    string year = startDate.substr(6, 4);
                                    string month = startDate.substr(3, 2);
                                    string day = startDate.substr(0, 2);
                                    int yearInt = stoi(year);
                                    int monthInt = stoi(month);
                                    int dayInt = stoi(day);
                                    yearInt += 1;
                                    string newYear = to_string(yearInt);
                                    string newStartDate = day + "/" + month + "/" + newYear;

                                    renew = true;
                                    
                                    file << currentUsername << "," << result.at(i).second.at(1) << "," << result.at(i).second.at(2) << "," << result.at(i).second.at(3) << "," << result.at(i).second.at(4) << "," << result.at(i).second.at(5) << "," << result.at(i).second.at(6) << "," << result.at(i).second.at(7) << "," << result.at(i).second.at(8) << "," << result.at(i).second.at(9) << "," << result.at(i).second.at(10) << "," << newStartDate << "," << cardNum << endl;
                                    file.close();
                                }else if (result.at(i).second.at(10) == "third party fire & theft") {
                                    cout << "The renewal cost for your Third Party Fire & Theft policy is $45 per month." << endl;
                                    cout << "Please enter your card details to renew your policy (or press n to cancel): " << endl;
                                    cout << "Card Number: ";
                                    string cardNum;
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    getline(cin, cardNum);
                                    //check for cancel
                                    if (cardNum == "n") {
                                        cout << "Policy not renewed" << endl;
                                        break;
                                    }
                                    //check that the card number is all numbers
                                    while (cardNum.find_first_not_of("0123456789") != string::npos) {
                                        cout << "Invalid card number, please enter a valid card number (it may only contain numbers): ";
                                        cin.clear();
                                        getline(cin, cardNum);
                                    }
                                    //adds the current users policy info to a new csv file with the new renewal date
                                    ofstream file("Renewals.csv", ios::app);
                                    //from the result vector, get the start date and add 1 year to it
                                    string startDate = result.at(i).second.at(5);
                                    string year = startDate.substr(6, 4);
                                    string month = startDate.substr(3, 2);
                                    string day = startDate.substr(0, 2);
                                    int yearInt = stoi(year);
                                    int monthInt = stoi(month);
                                    int dayInt = stoi(day);
                                    yearInt += 1;
                                    string newYear = to_string(yearInt);
                                    string newStartDate = day + "/" + month + "/" + newYear;

                                    renew = true;

                                    file << currentUsername << "," << result.at(i).second.at(1) << "," << result.at(i).second.at(2) << "," << result.at(i).second.at(3) << "," << result.at(i).second.at(4) << "," << result.at(i).second.at(5) << "," << result.at(i).second.at(6) << "," << result.at(i).second.at(7) << "," << result.at(i).second.at(8) << "," << result.at(i).second.at(9) << "," << result.at(i).second.at(10) << "," << newStartDate << "," << cardNum << endl;
                                    
                                }else if (result.at(i).second.at(10) == "third party only") {
                                    cout << "The renewal cost for your Third Party Only policy is $30 per month." << endl;
                                    cout << "Please enter your card details to renew your policy (or press n to cancel): " << endl;
                                    cout << "Card Number: ";
                                    string cardNum;
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    getline(cin, cardNum);
                                    //check for cancel
                                    if (cardNum == "n") {
                                        cout << "Policy not renewed" << endl;
                                        break;
                                    }
                                    //check that the card number is all numbers
                                    while (cardNum.find_first_not_of("0123456789") != string::npos) {
                                        cout << "Invalid card number, please enter a valid card number (it may only contain numbers): ";
                                        cin.clear();
                                        getline(cin, cardNum);
                                    }
                                    //adds the current users policy info to a new csv file with the new renewal date
                                    ofstream file("Renewals.csv", ios::app);
                                    //from the result vector, get the start date and add 1 year to it
                                    string startDate = result.at(i).second.at(5);
                                    string year = startDate.substr(6, 4);
                                    string month = startDate.substr(3, 2);
                                    string day = startDate.substr(0, 2);
                                    int yearInt = stoi(year);
                                    int monthInt = stoi(month);
                                    int dayInt = stoi(day);
                                    yearInt += 1;
                                    string newYear = to_string(yearInt);
                                    string newStartDate = day + "/" + month + "/" + newYear;

                                    renew = true;

                                    file << currentUsername << "," << result.at(i).second.at(1) << "," << result.at(i).second.at(2) << "," << result.at(i).second.at(3) << "," << result.at(i).second.at(4) << "," << result.at(i).second.at(5) << "," << result.at(i).second.at(6) << "," << result.at(i).second.at(7) << "," << result.at(i).second.at(8) << "," << result.at(i).second.at(9) << "," << result.at(i).second.at(10) << "," << newStartDate << "," << cardNum << endl;
                                }
                                if (renew == true) {
                                    cout << "Your policy has been renewed successfully. Thank you for choosing Mors Mutual Insurance!" << endl;

                                    logAction(currentUsername + "::" + "Policy renewed");
                                    break;
                                }
                                
                            }else if (renewChoice == 'n') {
                                cout << "Policy not renewed" << endl;
                                break;
                            }
                        }
                    }
                   
                } else if (choice == "n") {
                    cout << "Please login with the correct account you wish to renew your policy with." << endl;
                    Sleep(3000);
                    system("CLS");
                }





            } else if (CustomerChoice == 4) {
                /* Benefits screen should include the following:
                New sign up discounts
                Multi-policy discounts
                renewal discounts
                discounts for introducing friends or family
                discounts for multiple vehicles
                all information displayed in a menu format
                */
                cout << "Benefits of Mors Mutual Insurance" << endl;
                cout << "1. New sign-up Discounts" << endl;
                cout << "2. Multi-policy Discounts" << endl;
                cout << "3. Renewal Discounts" << endl;
                cout << "4. Discounts for Friends or Family" << endl;
                cout << "5. Discounts for Multiple Vehicles" << endl;
                cout << "6. Back" << endl;
                int benefitsChoice = validInput();
                if (benefitsChoice == 1) {
                    cout << "New sign-up Discounts" << endl;
                    cout << "When you sign up for a policy with Mors Mutual Inssurance, you will receive a 10% discount off any policy that you register with for the first month." << endl;//placeholder text
                    cout << "Press enter twice to continue" << endl;
                    cin.ignore();
                    cin.get();
                    if (cin.get()) {
                        continue;
                    }
                }else if (benefitsChoice == 2) {
                    cout << "Multi-Policy Discounts" << endl;
                    cout << "When you sign up for multiple policies with Mors Mutual Insurance, you will receive a 15% discount on your first month's payment." << endl;//placeholder text
                    cout << "Press enter twice to continue" << endl;
                    cin.ignore();
                    cin.get();
                    if (cin.get()) {
                        continue;
                    }
                }else if (benefitsChoice == 3) {
                    cout << "Renewal Discounts" << endl;
                    cout << "When you renew your policy with Mors Mutual Insurance, you will receive a 5% discount on your first month's payment." << endl;//placeholder text
                    cout << "Press enter twice to continue" << endl;
                    cin.ignore();
                    cin.get();
                    if (cin.get()) {
                        continue;
                    }
                }else if (benefitsChoice == 4) {
                    cout << "Discounts for Friends and Family" << endl;
                    cout << "When you introduce a friend or family member to Mors Mutual Insurance, you will receive a 10% discount on your next month's payment." << endl;//placeholder text
                    cout << "Press enter twice to continue" << endl;
                    cin.ignore();
                    cin.get();
                    if (cin.get()) {
                        continue;
                    }
                }else if (benefitsChoice == 5) {
                    cout << "Discounts for Multiple Vehicles" << endl;
                    cout << "When you sign up for multiple policies with Mors Mutual Insurance, you will receive a 20% discount on your first month's payment." << endl;//placeholder text
                    cout << "Press enter twice to continue" << endl;
                    cin.ignore();
                    cin.get();
                    if (cin.get()) {
                        continue;
                    }
                }else if (benefitsChoice == 6) {
                    continue;
                }
            } else if (CustomerChoice == 5) {
                system("CLS");
                break;
            }  
        }
    
    }else {
        cout << "Invalid access, please login first." << endl;
        Sleep(3000);
        system("CLS");
    }


}

void AdminConsole() {
    //clear the screen
    while (true) {
        system("CLS");
        cout << "Welcome to the admin console" << endl;
        cout << "1. View all accounts" << endl;
        cout << "2. Delete account" << endl;
        cout << "3. View all registrations" << endl;
        cout << "4. Back" << endl;
        cout << "please enter the number of the option you would like to select" << endl;
        int choice = validInput();// will be changed to mainmenuChoice when we have functions
        if (choice == 1) {
            vector<pair<string, vector<string>>> result = read_csv("Customer_registration.csv");
            for (int i = 0; i < result.size(); i++) {
                cout << "Username: " << result.at(i).first << " " << "dob: " << result.at(i).second.at(2) <<  " gender: " << result.at(i).second.at(3) << " address: " << result.at(i).second.at(4) << " phone: " << result.at(i).second.at(5) << " email: " << result.at(i).second.at(6) << " RegoNum: " << result.at(i).second.at(7) << " admin: " << result.at(i).second.at(8) << endl;
            }
            cout << "Press enter twice to continue" << endl;
            cin.ignore();
            cin.get();
            if (cin.get()) {
                continue;
            }
        } else if (choice == 2) {
            cout << "Enter the username of the account you would like to delete: ";
            string username;
            bool found = false;
            cin >> username;
            vector<pair<string, vector<string>>> result = read_csv("Customer_registration.csv");
            for (int i = 0; i < result.size(); i++) {
                if (result.at(i).first == username) {
                    result.erase(result.begin() + i);
                    cout << "Account deleted successfully" << endl;
                    logAction(currentUsername + "::" + "Account deleted: " + username);
                    found = true;
                }
                //if username not found, notify user
                if (i == result.size() - 1 && found == false) {
                    cout << "Username not found" << endl;
                }
            }
            ofstream file("Customer_registration.csv");
            for (int i = 0; i < result.size(); i++) {
                for (int j = 0; j < result.at(i).second.size(); j++) {
                    file << result.at(i).second.at(j);
                    if (j != result.at(i).second.size() - 1) {
                        file << ",";
                    }
                }
                file << endl;
            }
            file.close();
            

            Sleep(2000);
        } else if (choice == 3) {
            vector<pair<string, vector<string>>> result = read_csv("Policies.csv");
            for (int i = 0; i < result.size(); i++) {
                cout << "Username: " << result.at(i).first << " " << "RegoNum: " << result.at(i).second.at(1) << " phone: " << result.at(i).second.at(2) << " email: " << result.at(i).second.at(3) << " address: " << result.at(i).second.at(4) << " startDate: " << result.at(i).second.at(5) << " make: " << result.at(i).second.at(6) << " model: " << result.at(i).second.at(7) << " year: " << result.at(i).second.at(8) << " policyNum: " << result.at(i).second.at(9) << "type of insurance: " << result.at(i).second.at(10) << endl;
            }
            cout << "Press enter twice to continue" << endl;
            cin.ignore();
            cin.get();
            if (cin.get()) {
                continue;
            }
            
        } else if (choice == 4) {
            system("CLS");
            return;
        }
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
        if (admin == true) {
            cout << "5. Admin Screen" << endl;
        }
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
            int loginChoice = validInput();//  loginChoice is was choice2
            if (loginChoice == 1 && access == false) {
                system("CLS");
                while (access == false && attempts < 3) {
                    
                    cin.clear();
                    
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
            else if (loginChoice == 1 && access == true) {
                //clear the screen'
                system("CLS");
                cout << "You are already logged in" << endl;
                cout << "Please logout to login with a different account" << endl;
            }
            else if (loginChoice == 2) {
                createAccount();
            }
            else if (loginChoice == 3) {
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
        else if (choice == 5 && admin == true) {
            AdminConsole();
        }

    }
    logAction("::Program ended::");
    return 0;
}