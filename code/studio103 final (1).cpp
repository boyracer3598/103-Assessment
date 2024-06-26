// Mors Mutual Car Insurance
// Authors: Richard Gillingham, Renley Hutton, Cole Porter, Benjamin Ameye
// Date: 
// Description: A car insurance program that allows users to register for an account, get a quote, register for a policy, make a claim, and view their policy details.
// The program also allows an admin to create an account, view all accounts, and view all claims made by customers.

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

//function to clean up blank lines in the csv file
void cleanFile(string filename) {
    ifstream file(filename);
    ofstream temp("temp.csv");
    string line;
    file.seekg(0, ios::end);
    int length = file.tellg();
    if (length == 0) {
        return;
    }
    file.seekg(0, ios::beg);
    int count = 0;
    while (count <= length) {
        getline(file, line);
        if (line.length() > 0 && line != "\n" && line[0] != ',' && line[0] != ' ') {
            temp << line << endl;
        }
        count += 1;
    }
    
    file.close();
    temp.close();
    remove(filename.c_str());
    rename("temp.csv", filename.c_str());
}

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

//function: make sure the input is a int
int validInput()
{
    int x;
    cin >> x;
    while (cin.fail() || x < 0 || x > 100)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Bad entry.  Enter a NUMBER: ";
        cin >> x;
    }
    return x;
}

//function: create a log of actions taken in the program
void logAction(string action) {
    ofstream file("log.txt", ios::app);
    file << action << endl;
    file.close();
}

//function: calculating the quote based on the user's input
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

    try {
        cleanFile("Customer_registration.csv");
        vector<pair<string, vector<string>>> result = read_csv("Customer_registration.csv");
        for (int i = 0; i < result.size(); i++) {
            if (result.at(i).first == currentUsername) {
                string discount;
                discount = result.at(i).second.at(9);
                double discountValue = stod(discount);
                if (discountValue > 0) {
                    cout << "You have a discount of " << discountValue << "percent applied to your quote." << endl;
                    baseQuote *= (1 - (discountValue / 100));
                }
            }
        }
    } catch(const std::exception& e){
        cout << "discount value error" << endl;
    }
    
    //display the quote
    cout << "Your fixed quote is: $" << fixed << setprecision(2) << baseQuote << " per month." <<endl;
    return baseQuote;
}

//function: display the quote to the user
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
        insuranceType = 1; 
    }else if (quoteType == "Third Party Fire & Theft") {
        insuranceType = 2; 
    }else if (quoteType == "Third Party Only") {
        insuranceType = 3;
    }
    
    //calculation
    Quote = calculateQuote(age, gender, licenseStatusInt, insuranceType, vehicleType);
}

//function: create new account inside csv file
void createAccount() {
    cin.ignore(1000, '\n');
    cin.clear();
    string username = "", password = "", dob, gender, address, phone, email, RegoNum;
    cout << "register for an account with Mor Mutual Car Insurance" << endl;
    cout << "Enter new username: ";
    getline(cin, username);
    //checks if the username contains spaces
    while (username.find(" ") != string::npos || username.find(",") != string::npos) {
        cout << "Username cannot contain spaces or commas, please enter a new username: ";
        cin.clear();
        getline(cin, username);
    }

    cout << "Enter new password: ";
    cin.clear();
    getline(cin, password);
    //checks if the password contains spaces
    while (password.find(" ") != string::npos || password.find(",") != string::npos) {
        cout << "password cannot contain spaces or commas, please enter a new password: ";
        cin.clear();
        getline(cin, password);
    }
    cin.clear();
    cout << "Enter your date of birth (dd/mm/yyyy): ";
    getline(cin, dob);
    //checks if the date of birth is in the correct format
    while (dob.length() != 10 || dob[2] != '/' || dob[5] != '/' || dob.find_first_not_of("0123456789/") != string::npos){
        cout << "Invalid date of birth, please enter in the format dd/mm/yyyy: ";
        cin.clear();
        getline(cin, dob);
    }
    cin.clear();
    cout << "Enter your gender(m/f): ";// gender input can be M or F for quote reasons
    getline(cin, gender);
    //checks if gender is in the correct format
    while (gender != "M" && gender != "F" && gender != "m" && gender != "f"){
        cout << "please enter a valid input (M/F): ";
        cin.clear();
        getline(cin, gender);
    }

    cout << "Enter your address: ";
    //user can enter multiple words for the address ,and does not check if number is first
    cin.clear();

    getline(cin, address);
    //checks the address doesnt contain commas
    while (address.find(",") != string::npos) {
        cout << "Invalid address, please enter a valid address without commas: ";
        cin.clear();
        getline(cin, address);
    }

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
    while (RegoNum.length() != 6 || RegoNum.find(" ") != string::npos || RegoNum.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != string::npos){
        cout << "Invalid registration number, please enter a valid registration number: ";
        cin.clear();
        getline(cin, RegoNum);
    }


    if (admin == true) {
        cout << "Do you want to give admin permissions to this account? (y/n): ";
        string choice;
        cin.clear();
        getline(cin, choice);
        //checks if the user inputs a valid option
        while (choice != "y" && choice != "n" && choice != "Y" && choice != "N") {
            cout << "Invalid input, please use the correct format. 'y' for YES, 'n' for NO: ";
            cin.clear();
            getline(cin, choice);
        }
        if (choice == "y") {
            ofstream file("Customer_registration.csv", ios::app);
            file << username << "," << password << "," << dob << "," << gender << "," << address << "," << phone << "," << email << "," << RegoNum << "," << "1" << "," << 0 << endl;
            file.close();
            cout << "Account created successfully" << endl;
            logAction(currentUsername + "::" + "Admin account created: " + username);
            return;
        }
    }
    
    ofstream file("Customer_registration.csv", ios::app);
    file << username << "," << password << "," << dob << "," << gender << "," << address << "," << phone << "," << email << "," << RegoNum << "," << "0" << "," << 0 << endl;
    file.close();
    system("CLS");
    cout << "Account created successfully" << endl;
    logAction(currentUsername + "::" + "Account created: " + username);
    
}

//function: display the policy to the user
void displayPolicy(int policyType = 0) { 
    string policyTypeStr;
    if (policyType == 1) {
        policyTypeStr = "Comprehensive";
    }else if (policyType == 2) {
        policyTypeStr = "Third Party Fire & Theft";
    }else if (policyType == 3) {
        policyTypeStr = "Third Party Only";
    }else {
        cout << "Invalid selection. Please select an option: 1: Comprehensive, 2: Third Party Fire & Theft, 3: Third Party Only." << endl;
        return;
    }

    
    try {
        //cleans csv
        cleanFile("Customer_registration.csv");
        cout << "You have selected: " << policyTypeStr << endl;
        vector<pair<string, vector<string>>> result = read_csv("Customer_registration.csv");
        for (int i = 0; i < result.size(); i++) {
            if (result.at(i).first == currentUsername) {
                cout << "Is this the correct account to register for a policy with? (y/n): " << result.at(i).first << endl;
                cin.clear();
                char choice;
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    string RegoNum = result.at(i).second.at(7);
                    string phone = result.at(i).second.at(5);
                    string email = result.at(i).second.at(6);
                    string address = result.at(i).second.at(4);
                    string gender = result.at(i).second.at(3);
                    cout << "Some Policy information has been pre-filled for you from your account. Please provide further details towards your " << policyTypeStr << " policy." << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Enter the date that the policy will start (dd/mm/yyyy): ";
                    string startDate;
                    //checks date format: (dd/mm/yyyy)
                    getline(cin, startDate);
                    cin.clear();
                    while (startDate.length() != 10 || startDate[2] != '/' || startDate[5] != '/'|| startDate.find_first_not_of("0123456789/") != string::npos) {
                        cout << "Invalid date, please enter in the format (dd/mm/yyyy): ";
                        cin.clear();
                        getline(cin, startDate);

                    }
                    cout << "Enter the make of your vehicle: " << endl;
                    string carMake;
                    cin.clear();
                    getline(cin, carMake);
                    cout << "Enter the model of your vehicle: " << endl;
                    string carModel;
                    cin.clear();
                    getline(cin, carModel);
                    cout << "Enter the year of your vehicle: " << endl;
                    string carYear;
                    cin.clear();
                    getline(cin, carYear);
                    //checks if the year is an int with 4 digits and no spaces
                    while (carYear.length() != 4 || carYear.find(" ") != string::npos || carYear.find_first_not_of("0123456789") != string::npos) {
                        cout << "Invalid year, please enter a valid year: ";
                        cin.clear();
                        getline(cin, carYear);
                    }
                    int policyNum = 1;
                    try {
                        vector<pair<string, vector<string>>> result1 = read_csv("Policies.csv");
                        for (int i = 0; i < result1.size(); i++) {
                            if (result1.size() == 0) {
                                policyNum = 2;
                            }else {
                                policyNum = i + 2;
                            }
                        }
                    }catch(const std::exception& e){
                        policyNum = 1;
                    }
                    //enter age
                    cout << "Please enter your age: ";
                    int age;
                    int genderConverted;
                    string licenseStatus;
                    int vehicleType;

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
                    if (gender == "m" || gender == "M") {
                        genderConverted = 1;
                    } else {
                        genderConverted = 2;
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

                    cout << "Please enter your vehicle type." << endl;
                    cout << "1. Car" << endl;
                    cout << "2. Motorcycle" << endl;
                    string vehicle;
                    cin.clear();
                    
                    getline(cin, vehicle);
                    while (vehicle != "1" && vehicle != "2") {
                        cout << "Invalid input, please use the correct format. 1: Car, 2: Motorcycle: ";
                        cin.clear();
                        getline(cin, vehicle);
                    }
                    if (vehicle == "1") {
                        vehicleType = 1;
                    } else if (vehicle == "2") {
                        vehicleType = 2;
                    }
                    

                    //uses calcuateQuote function to get the quote for the user
                    double quote = calculateQuote(age, genderConverted, licenseStatusInt, policyType, vehicleType);

                    //asks user if quote is ok
                    cout << "Is this quote acceptable? (y/n): ";
                    string quoteChoice;
                    cin.clear();
                    
                    getline(cin, quoteChoice);
                    while (quoteChoice != "y" && quoteChoice != "n" && quoteChoice != "Y" && quoteChoice != "N") {
                        cout << "Invalid input, please use the correct format. 'y' for YES, 'n' for NO: ";
                        cin.clear();
                        getline(cin, quoteChoice);
                    }
                    if (quoteChoice == "y" || quoteChoice == "Y") {
                        cout << "Your policy number is: " << policyNum << endl;
                        ofstream file("Policies.csv", ios::app);
                        file << currentUsername << "," << RegoNum << "," << phone << "," << email << "," << address << "," << startDate << "," << carMake << "," << carModel << "," << carYear << "," << policyNum << "," << policyTypeStr << endl;
                        file.close();
                        Sleep(3000);
                        cout << "Your " << policyType << " policy has been registered sucessfully. Thank you for choosing Mors Mutual Car Insurance!" << endl;
                        logAction(currentUsername + "::" + "Policy registered");
                        break;
                    } else {
                        cout << "Policy registration cancelled" << endl;
                        Sleep(3000);
                        return;
                    }

                    
                }
            }
        }
    }catch(const std::exception& e){
        cout << "You do not have an account to register a policy with" << endl;
        Sleep(3000);
    }
}

//function: display the claims to the user
void displayClaims(int claimsType) {
    string claimsTypeStr;
    if (claimsType == 1) {
        claimsTypeStr = "Comprehensive";
    }else if (claimsType == 2) {
        claimsTypeStr = "Third Party Fire & Theft";
    }else if (claimsType == 3) {
        claimsTypeStr = "Third Party Only";
    }else { 
        cout << "Invalid selection. Please select an option: 1: Comprehensive, 2: Third Party Fire & Theft, 3: Third Party Only." << endl;
        Sleep(3000);
        return;
    }
    
    
    
    try {
        //cleans csv
        cleanFile("Customer_registration.csv");
        cleanFile("Policies.csv");
        vector<pair<string, vector<string>>> result = read_csv("Customer_registration.csv");
        vector<pair<string, vector<string>>> result1 = read_csv("Policies.csv");
        //gets the users policy number
        int policyNum = 0;
        for (int i = 0; i < result1.size(); i++) {
            if (result1.at(i).first == currentUsername) {
                policyNum = stoi(result1.at(i).second.at(9));
            }
        }
        
        for (int i = 0; i < result.size(); i++) {
            if (result.at(i).first == currentUsername) {
                cin.clear();
                
                cout << "Is this the correct account to make a claim with? (y/n): " << result.at(i).first << endl;
                
                string checkChoice;
                getline(cin, checkChoice);
                while (checkChoice != "y" && checkChoice != "n" && checkChoice != "Y" && checkChoice != "N") {
                    cout << "Invalid input, please enter 'y' for yes or 'n' for no: " << endl;
                    cin.clear();
                    getline(cin, checkChoice);
                }
                if (checkChoice == "y" || checkChoice == "Y") {
                    string RegoNum = result.at(i).second.at(7);
                    string phone = result.at(i).second.at(5);
                    string email = result.at(i).second.at(6);
                    string address = result.at(i).second.at(4);

                    cout << "Some Claim information has been pre-filled for you from your account. Please provide further details towards your Claim." << endl;
                    cout << "Enter the date that the incident occured (dd/mm/yyyy): ";
                    
                
                    string incidentDate;
                    cin.clear();
                    //checks if the date of birth is in the correct format
                    getline(cin, incidentDate);
                    
                    while (incidentDate.length() != 10 || incidentDate[2] != '/' || incidentDate[5] != '/') {
                        cout << "Invalid date, please enter in the format dd/mm/yyyy: ";
                        cin.clear();
                        getline(cin, incidentDate);
                    }
                    //checks if the time is in the correct format
                    cout << "Enter the time that the incident occured (hh:mm): ";
                    string incidentTime;
                    cin.clear();
                    getline(cin, incidentTime);
                    while (incidentTime.length() != 5 || incidentTime[2] != ':' || incidentTime.find_first_not_of("0123456789:") != string::npos) {
                        cout << "Invalid time, please enter in the format hh:mm  ";
                        cin.clear();
                        getline(cin, incidentTime);
                    }
                    
                    cout << "Please provide a brief description of the incident: ";
                    string description;
                    cin.clear();
                    getline(cin, description);
                    //check theres no commas in the description
                    while (description.find(",") != string::npos) {
                        cout << "Invalid description, please enter a valid description without commas: ";
                        cin.clear();
                        getline(cin, description);
                    }

                    //store the claim data in a csv file
                    ofstream file("Claims.csv", ios::app);
                    file << currentUsername << "," << RegoNum << "," << phone << "," << email << "," << address << "," << incidentDate << "," << incidentTime << "," << description << ","  << claimsTypeStr << "," << policyNum << endl;
                    file.close();
                    cout << "Claim made successfully. Thank you for choosing Mors Mutual Car Insurance!" << endl;
                    logAction(currentUsername + "::" + "Claim made");
                    Sleep(3000);
                    return;
                } else {
                    cout << "Claim cancelled" << endl;
                    Sleep(3000);
                    return;
                }
            }
        }
    } catch(const std::exception& e){
        cout << "You do not have an account to make a claim with" << endl;
        Sleep(3000);
    }

}

//function: display the customer menu to the user
void customerMenu() {

    if (access == true) {
               
        while (true) {

            system("CLS"); 
            //customer menu screen
            cout << "Welcome to the Customer Menu. Please select an option.\n" << endl;
            cout << "1. Policy and Insurance" << endl; 
            cout << "2. Claims" << endl; // Needs work
            cout << "3. Renewals" << endl; // Needs work
            cout << "4. Benefits of Mors Mutual Insurance" << endl; // Done
            cout << "5. Back" << endl;
            int CustomerChoice = validInput(); 
            
            if (CustomerChoice == 1) {
                system("CLS");
                cout << "Policy and Insurance" << endl;
                cout << "1. View & Register for Policies" << endl; // Editing
                cout << "2. Get a Quote" << endl; // Done
                cout << "3. Back" << endl;
                int policyInsureanceChoice = validInput();
                if (policyInsureanceChoice == 1) {
                    //clear screen
                    system("CLS");      
                    
                    cout << "1. Comprehensive" << endl;
                    cout << "2. Third Party Fire & Theft" << endl;
                    cout << "3. Third Party Only" << endl;
                    cout << "4. Register for Policy" << endl;
                    cout << "5. Back" << endl;
                    int policyChoice = validInput();
                
                    if (policyChoice == 1) {
                        //read each line of the comprehensive_info.txt file and display it to the user
                        //if the file doesnt exsist, it will display alert the user, and return to the menu
                        system("CLS");
                        ifstream file("comprehensive_info.txt");
                        if (!file.is_open()) {
                            cout << "File not found" << endl;
                            Sleep(3000);
                            continue;
                        }
                        string line;
                        while (getline(file, line)) {
                            cout << line << endl;
                        }
                        cout << "Press enter twice to continue" << endl;
                        cin.ignore();
                        cin.get();
                        if (cin.get()) {
                            continue;
                        }

                    }else if (policyChoice == 2) {
                        system("CLS");
                        ifstream file("Fire_and_theft_info.txt");
                        if (!file.is_open()) {
                            cout << "File not found" << endl;
                            Sleep(3000);
                            continue;
                        }
                        string line;
                        while (getline(file, line)) {
                            cout << line << endl;
                        }
                        cout << "Press enter twice to continue" << endl;
                        cin.ignore();
                        cin.get();
                        if (cin.get()) {
                            continue;
                        }
                    }else if (policyChoice == 3) {
                        system("CLS");
                        ifstream file("Third_party_info.txt");
                        if (!file.is_open()) {
                            cout << "File not found" << endl;
                            Sleep(3000);
                            continue;
                        }
                        string line;
                        while (getline(file, line)) {
                            cout << line << endl;
                        }
                        cout << "Press enter twice to continue" << endl;
                        cin.ignore();
                        cin.get();
                        if (cin.get()) {
                            continue;
                        }

                    }else if (policyChoice == 4) {
                        system("CLS");
                        cout << "Register for a Policy" << endl;
                        //checks if the user already has a policy
                        try {
                            //cleans csv
                            cleanFile("Policies.csv");
                            vector<pair<string, vector<string>>> result = read_csv("Policies.csv");
                            for (int i = 0; i < result.size(); i++) {
                                if (result.at(i).first == currentUsername) {
                                    cout << "You already have a policy registered. Would you like to view your policy? (y/n): " << endl;
                                    string viewChoice;
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    getline(cin, viewChoice);
                                    while (viewChoice != "y" && viewChoice != "n" && viewChoice != "Y" && viewChoice != "N") {
                                        cout << "Invalid input, please enter 'y' for yes or 'n' for no: " << endl;
                                        cin.clear();
                                        getline(cin, viewChoice);
                                    }
                                    if (viewChoice == "y" || viewChoice == "Y") {
                                        cout << "Your current policy is: " << result.at(i).second.at(10) << endl;
                                        cout << "Press enter twice to continue" << endl;
                                        cin.ignore();
                                        cin.get();
                                        if (cin.get()) {
                                            continue;
                                        }
                                    }else if (viewChoice == "n" || viewChoice == "N") {
                                        continue;
                                    }
                                }
                            }
                       
                        } catch(const std::exception& e){
                            cout << "No polices registered, please continue" << endl;
                        }
                        cout << "Please select the policy you would like to register for:" << endl;
                        cout << "1. Comprehensive" << endl;
                        cout << "2. Third Party Fire & Theft" << endl;
                        cout << "3. Third Party Only" << endl;
                        cout << "4. Back" << endl;
                        int policyChoice = validInput();
                        if (policyChoice == 1) {
                            displayPolicy(1);
                        }else if (policyChoice == 2) {
                            displayPolicy(2);
                        }else if (policyChoice == 3) {
                            displayPolicy(3);
                        }else if (policyChoice == 4) {
                            break;
                        }
                           
                    }else if (policyChoice == 5) {
                        break;
                    }

                
                }else if (policyInsureanceChoice == 2) {
                    int age = 0;
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
                system("CLS");
                cout << "Claims" << endl;
                bool claim = false;

              
                try{
                    //cleans csv
                    cleanFile("Policies.csv");
                    //read the policy csv to see what policy type the user has
                    vector<pair<string, vector<string>>> result = read_csv("Policies.csv");
                    
                    
                    

                    //check the current policy type
                    for (int i = 0; i < result.size(); i++) {
                        if (result.at(i).first == currentUsername) {
                            string policyType = result.at(i).second.at(10);
                            string claimChoice;
                            int policyConverted = 0;
                            claim = true;
                            
                            
                            cout << "Your current policy type is: " << result.at(i).second.at(10) << endl;
                            cout << "Would you like to make a claim? (y/n): " << endl;
                            
                            cin.clear();
                            cin.ignore(1000, '\n');
                            getline(cin, claimChoice);
                            //checks that the user inputs the correct input
                            while (claimChoice != "y" && claimChoice != "n" && claimChoice != "Y" && claimChoice != "N") {
                                cout << "Invalid input, please use the correct format: 'y' for YES, 'n' for NO: " << endl;
                                cin.clear();
                                getline(cin, claimChoice);
                            }
                            if (claimChoice == "y" || claimChoice == "Y") {
                                
                                
                                if (policyType == "Comprehensive") {
                                    //cout << "Your current policy type is Comprehensive" << endl;
                                    
                                    policyConverted = 1;
                                    displayClaims(policyConverted);
                                }else if (policyType == "Third Party Fire & Theft") {
                                    //cout << "Your current policy type is Third Party Fire & Theft" << endl;
                                    
                                    policyConverted = 2;
                                    displayClaims(policyConverted);
                                }else if (policyType == "Third Party Only") {
                                    //cout << "Your current policy type is Third Party Only" << endl;
                                    
                                    policyConverted = 3;
                                    displayClaims(policyConverted);
                                }
                            }else if (claimChoice == "n" || claimChoice == "N") {
                                break;
                            }
                        }
                        
                    } 
                    if (claim == false) {
                        cout << "You do not have a policy to make a claim with" << endl;
                        Sleep(3000);
                    }
                }catch(const std::exception& e){
                    cout << "You do not have a policy to make a claim with" << endl;
                    Sleep(3000);
                }
            }else if (CustomerChoice ==3) {
                bool renew = true;
                system("CLS");
                cout << "Renewals" << endl;
                cout << "Is this the correct account to renew your policy with? (y/n): " << currentUsername << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                string choice;
                getline(cin, choice);
                //checks that the user inputs the correct input
                while (choice != "y" && choice != "n" && choice != "Y" && choice != "N") {
                    cout << "Invalid input, please use the correct format: 'y' for YES, 'n' for NO: " << endl;
                    cin.clear();
                    getline(cin, choice);
                }

                
                if (choice == "y" || choice == "Y") {
                    
                    try{
                        //cleans csv
                        cleanFile("Policies.csv");
                        //read csv to find the row with the current username
                        vector<pair<string, vector<string>>> result = read_csv("Policies.csv");
                        //check the current policy type
                        for (int i = 0; i < result.size(); i++) {
                            if (result.at(i).first == currentUsername) {
                                cout << "Your current policy type is: " << result.at(i).second.at(10) << endl;
                                cout << "Would you like to renew your policy? (y/n): " << endl;
                                renew = true;
                                string renewChoice;
                                cin.clear();
                                getline(cin, renewChoice);
                                //checks that the user inputs the correct input
                                while (renewChoice != "y" && renewChoice != "n" && renewChoice != "Y" && renewChoice != "N") {
                                    cout << "Invalid input, please use the correct format: 'y' for YES, 'n' for NO: " << endl;
                                    cin.clear();
                                    getline(cin, renewChoice);
                                }
                                if (renewChoice == "y" || renewChoice == "Y") {
                                    //check currentusername to find what policy type the user has in policies.csv
                                    
                                    string policyType = result.at(i).second.at(10);
                                    
                                    int policyConverted = 0;
                                    if (policyType == "Comprehensive") {
                                        cout << "Your current policy type is Comprehensive" << endl;
                                        policyConverted = 1;
                                        
                                    }else if (policyType == "Third Party Fire & Theft") {
                                        cout << "Your current policy type is Third Party Fire & Theft" << endl;
                                        policyConverted = 2;
                                    }else if (policyType == "Third Party Only") {
                                        cout << "Your current policy type is Third Party Only" << endl;
                                        policyConverted = 3;
                                    }
                                    //intialise variables for calculateQuote function
                                    int ageConverted = 0;
                                    int gender = 0;
                                    int licenseStatus = 0;
                                    int insuranceType = 0;
                                    int vehicleType = 0;
                                    double quotedValue = 0.0;

                                    //ask user for the date they want to policy to start
                                    cout << "Please enter the date you would like your policy to be renewed (dd/mm/yyyy): " << endl;
                                    string startDate;
                                    cin.clear();
                                    getline(cin, startDate);
                                    //checks if the date is in the correct format
                                    while (startDate.length() != 10 || startDate[2] != '/' || startDate[5] != '/' || startDate.find_first_not_of("0123456789/") != string::npos || startDate.find(",") != string::npos){
                                        if (startDate.find(",") != string::npos) {
                                            cout << "Invalid input, please remove commas: ";
                                        } else {
                                            cout << "Invalid date, please enter in the correct format dd/mm/yyyy: ";
                                        }
                                        cin.clear();
                                        getline(cin, startDate);
                                    }
                                    

                                    //ask user for their age
                                    cout << "Please enter your age: ";
                                    string age;
                                    cin.clear();
                                    getline(cin, age);

                                    //checks if age contain spaces and is a number
                                    while (age.find(" ") != string::npos || age.find_first_not_of("0123456789") != string::npos) {
                                        cout << "Invalid input, please enter a valid age: ";
                                        cin.clear();
                                        getline(cin, age);
                                    }

                                    ageConverted = stoi(age);

                                    if (ageConverted < 16 || ageConverted > 90) {
                                        cout << "Unfortunately we cannot renew your policy as you are not within the age range of 16-90" << endl;
                                        Sleep(3000);
                                        break;
                                    }
                                    //ask user for their gender
                                    cout << "Please enter your gender (m/f):" << endl;
                                    string genderChoice;
                                    cin.clear();
                                    getline(cin, genderChoice);
                                    while (genderChoice != "m" && genderChoice != "f" && genderChoice != "M" && genderChoice != "F") {
                                        cout << "Invalid input, please use the correct format: 'm' for MALE, 'f' for FEMALE: " << endl;
                                        cin.clear();
                                        getline(cin, genderChoice);
                                    }
                                    if (genderChoice == "m" || genderChoice == "M") {
                                        gender = 1;
                                    } else if (genderChoice == "f" || genderChoice == "F") {
                                        gender = 2;
                                    }

                                    //ask user for their license status
                                    cout << "Please select your current license status: " << endl;
                                    cout << "1. Full License" << endl;
                                    cout << "2. Restricted License" << endl;
                                    cout << "3. Learner's License" << endl;
                                    string licenseChoice;
                                    cin.clear();
                                    getline(cin, licenseChoice);
                                    while (licenseChoice != "1" && licenseChoice != "2" && licenseChoice != "3") {
                                        cout << "Invalid input, please select: 1: Full, 2: Restricted, 3: Learner: " << endl;
                                        cin.clear();
                                        getline(cin, licenseChoice);
                                    }

                                    if (licenseChoice == "3") {
                                        cout << "Unfortunately, we are unable to renew a policy with a learners license." << endl;
                                        Sleep(3000);
                                        break;
                                    }

                                    if (licenseChoice == "1") {
                                        licenseStatus = 1;
                                    } else if (licenseChoice == "2") {
                                        licenseStatus = 2;
                                    }

                                    //ask user for their vehicle type
                                    cout << "Please select your vehicle type: " << endl;
                                    cout << "1. Car" << endl;
                                    cout << "2. Motorcycle" << endl;
                                    string vehicleChoice;
                                    cin.clear();
                                    getline(cin, vehicleChoice);
                                    while (vehicleChoice != "1" && vehicleChoice != "2") {
                                        cout << "Invalid input, please use the correct format: 1: Car, 2: Motorcycle: " << endl;
                                        cin.clear();
                                        getline(cin, vehicleChoice);
                                    }

                                    if (vehicleChoice == "1") {
                                        vehicleType = 1;
                                    } else if (vehicleChoice == "2") {
                                        vehicleType = 2;
                                    }
                                    
                                    //call the calculateQuote function to get the quote for the user
                                    double quote = calculateQuote(ageConverted, gender, licenseStatus, policyConverted, vehicleType);
                                    cout << "Would you like to renew your policy with this quote? (y/n): " << endl;
                                    string renewChoice1;
                                    cin.clear();
                                    getline(cin, renewChoice1);
                                    //checks that the user inputs the correct input
                                    while (renewChoice1 != "y" && renewChoice1 != "n" && renewChoice1 != "Y" && renewChoice1 != "N") {
                                        cout << "Invalid input, use the correct format: 'y' for YES, 'n' for NO: " << endl;
                                        cin.clear();
                                        getline(cin, renewChoice1);
                                    }
                                    if (renewChoice1 == "y" || renewChoice1 == "Y") {
                                        //store the renewal data in a csv file
                                        ofstream file("Renewals.csv", ios::app);
                                        file << currentUsername << "," << quote << "," << startDate << endl;
                                        file.close();
                                        cout << "Policy renewed successfully" << endl;
                                        logAction(currentUsername + "::" + "Policy renewed");
                                        Sleep(3000);
                                        break;
                                    }else if (renewChoice1 == "n" || renewChoice1 == "N") {
                                        cout << "Policy not renewed" << endl;
                                        Sleep(3000);
                                        break;
                                    }
                                }else if (renewChoice == "n" || renewChoice == "N") {
                                    cout << "Policy not renewed" << endl;
                                    Sleep(3000);
                                    break;
                                }
                            } else {
                                renew = false;
                            }

                        }
                        if (renew == false) {
                            cout << "No current policy found. Please login with the correct account you wish to renew your policy with." << endl;
                            Sleep(3000);
                            system("CLS");
                            break;
                        }
                    } catch(const std::exception& e){
                        cout << "No current policy found. Please login with the correct account you wish to renew your policy with." << endl;
                        Sleep(3000);
                        system("CLS");
                    }

                    
                   
                } else if (choice == "n" || choice == "N") {
                    cout << "Please login with the correct account you wish to renew your policy with." << endl;
                    Sleep(3000);
                    system("CLS");
                }
            //benefits menu
            }else if (CustomerChoice == 4) {
                
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
                    cout << "When you sign up for a policy with Mors Mutual Inssurance, you will receive a 10% discount off any policy that you register with for the first month." << endl;
                    cout << "Press enter twice to continue" << endl;
                    cin.ignore();
                    cin.get();
                    if (cin.get()) {
                        continue;
                    }
                }else if (benefitsChoice == 2) {
                    cout << "Multi-Policy Discounts" << endl;
                    cout << "When you sign up for multiple policies with Mors Mutual Insurance, you will receive a 15% discount on your first month's payment." << endl;
                    cout << "Press enter twice to continue" << endl;
                    cin.ignore();
                    cin.get();
                    if (cin.get()) {
                        continue;
                    }
                }else if (benefitsChoice == 3) {
                    cout << "Renewal Discounts" << endl;
                    cout << "When you renew your policy with Mors Mutual Insurance, you will receive a 5% discount on your first month's payment." << endl;
                    cout << "Press enter twice to continue" << endl;
                    cin.ignore();
                    cin.get();
                    if (cin.get()) {
                        continue;
                    }
                }else if (benefitsChoice == 4) {
                    cout << "Discounts for Friends and Family" << endl;
                    cout << "When you introduce a friend or family member to Mors Mutual Insurance, you will receive a 10% discount on your next month's payment." << endl;
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

//function: display the admin console to the user
void AdminConsole() {
    
    while (true) {
        system("CLS");
        cout << "Welcome to the admin console" << endl;
        cout << "1. View all customers" << endl;
        cout << "2. Delete account" << endl;
        cout << "3. View weekly registrations" << endl;
        cout << "4. view weekly claims" << endl;
        cout << "5. View weekly renewals" << endl;
        cout << "6. issue discounts" << endl;
        cout << "7. update policy information" << endl;
        cout << "8. Back" << endl;
        cout << "please enter the number of the option you would like to select" << endl;
        int choice = validInput();
        if (choice == 1) {
            
            try{
                //clean the csv
                cleanFile("Customer_registration.csv");

                vector<pair<string, vector<string>>> result = read_csv("Customer_registration.csv");
                for (int i = 0; i < result.size(); i++) {
                    cout << "Username: " << result.at(i).first << " " << "dob: " << result.at(i).second.at(2) <<  " gender: " << result.at(i).second.at(3) << " address: " << result.at(i).second.at(4) << " phone: " << result.at(i).second.at(5) << " email: " << result.at(i).second.at(6) << " RegoNum: " << result.at(i).second.at(7) << " admin: " << result.at(i).second.at(8) << " discount: " << result.at(i).second.at(9) << endl;
                }
                cout << "Press enter twice to continue" << endl;
                cin.ignore();
                cin.get();
                if (cin.get()) {
                    continue;
                }
            } catch(const std::exception& e){
                cout << "No accounts found" << endl;
                Sleep(3000);
            }
           
        } else if (choice == 2) {
            cout << "Enter the username of the account you would like to delete: ";
            string username;
            bool found = false;
            cin >> username;

           
            try {
                //clean the csv
                cleanFile("Customer_registration.csv");
                vector<pair<string, vector<string>>> result = read_csv("Customer_registration.csv");
                for (int i = 0; i < result.size(); i++) {
                    if (result.at(i).first == username) {
                        if (currentUsername == username) {
                            cout << "You cannot delete your own account" << endl;
                            Sleep(3000);
                            continue;
                        }
                        result.erase(result.begin() + i);
                        cout << "Account deleted successfully" << endl;
                        logAction(currentUsername + "::" + "Account deleted: " + username);
                        found = true;
                    }
                    //if username not found, notify the user
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
            } catch(const std::exception& e){
                cout << "Username not found" << endl;
                Sleep(3000);
            }
            
              
        } else if (choice == 3) {
            
            try {
                //clean the csv
                cleanFile("Policies.csv");
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
            } catch(const std::exception& e){
                cout << "No registrations found" << endl;
                Sleep(3000);
            }
           
            
        } else if (choice == 4) {
            try {
                //clean the csv
                cleanFile("Claims.csv");
                vector<pair<string, vector<string>>> result = read_csv("Claims.csv");
                for (int i = 0; i < result.size(); i++) {
                    cout << "Username: " << result.at(i).first << " " << "RegoNum: " << result.at(i).second.at(1) << " phone: " << result.at(i).second.at(2) << " email: " << result.at(i).second.at(3) << " address: " << result.at(i).second.at(4) << " incidentDate: " << result.at(i).second.at(5) << " incidentTime: " << result.at(i).second.at(6) << " description: " << result.at(i).second.at(7) << " type of claim: " << result.at(i).second.at(8) << " policy number: " << result.at(i).second.at(9) << endl;
                }
                cout << "Press enter twice to continue" << endl;
                cin.ignore();
                cin.get();
                if (cin.get()) {
                    continue;
                }
            } catch(const std::exception& e){
                cout << "No claims found" << endl;
                Sleep(3000);
            }
            
        } else if (choice == 5) {
            try {
                //clean the csv
                cleanFile("Renewals.csv");
                vector<pair<string, vector<string>>> result = read_csv("Renewals.csv");
                for (int i = 0; i < result.size(); i++) {
                    cout << "Username: " << result.at(i).first << " " << "quote: " << result.at(i).second.at(1) << " startDate: " << result.at(i).second.at(2) << endl;
                }
                cout << "Press enter twice to continue" << endl;
                cin.ignore();
                cin.get();
                if (cin.get()) {
                    continue;
                }
            } catch(const std::exception& e){
                cout << "No renewals found" << endl;
                Sleep(3000);
            }
            
        } else if(choice == 6) {
            cout << "please enter the username of the account you would like to issue a discount to: ";
            string username;
            cin.clear();
            cin.ignore(1000, '\n');
            getline(cin, username);
            //check the username is valid with no spaces or commas
            while (username.find(" ") != string::npos || username.find(",") != string::npos) {
                cout << "Invalid input, please enter a valid username (no spaces or commas): ";
                cin.clear();
                getline(cin, username);
            }
            try {
                //clean the csv
                cleanFile("Customer_registration.csv");
                vector<pair<string, vector<string>>> result = read_csv("Customer_registration.csv");
                bool found = false;
                for (int i = 0; i < result.size(); i++) {
                    if (result.at(i).first == username) {
                        cout << "Account found" << endl;
                        found = true;
                        cout << "Please enter the discount you would like to issue (in percentage): " << endl;
                        string discount;
                        cin.clear();
                        getline(cin, discount);
                        //check the discount is a valid number
                        while (discount.find_first_not_of("0123456789") != string::npos || discount.length() >= 3) {
                            cout << "Invalid input, please enter a valid number: ";
                            cin.clear();
                            getline(cin, discount);
                        }
                        //store the discount at the 10th position in the current row, overwrite current value
                        result.at(i).second.at(9) = discount;
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
                        
                        

                        cout << "Discount issued successfully" << endl;
                        logAction(currentUsername + "::" + "Discount issued to: " + username);
                        Sleep(3000);
                    }
                    if (i == result.size() - 1 && found == false) {
                        cout << "Username not found" << endl;
                        Sleep(3000);
                    }
                }
            } catch(const std::exception& e){
                cout << "Username not found" << endl;
                Sleep(3000);
            }
            bool found = false;

        } else if (choice == 7) {
            cout << "Please select the policy you would like to update: " << endl;
            cout << "1. Comprehensive" << endl;
            cout << "2. Third Party Fire & Theft" << endl;
            cout << "3. Third Party Only" << endl;
            int policyType = validInput();
            if (policyType == 1) {
                cout << "You are editing the Comprehensive Policy." << endl;
                cout << "Updated information: " << endl;
                string newInfo;
                cin.clear();
                cin.ignore(1000, '\n');
                getline(cin, newInfo);
                ofstream file("comprehensive_info.txt");
                file << newInfo;
                file.close();
                cout << "Information updated successfully" << endl;
                Sleep(3000);


            } else if (policyType == 2) {
                cout << "You are editing the Third Party Fire & Theft Policy." << endl;
                cout << "Updated information: " << endl;
                string newInfo;
                cin.clear();
                cin.ignore(1000, '\n');
                getline(cin, newInfo);
                ofstream file("Fire_and_theft_info.txt");
                file << newInfo;
                file.close();
                cout << "Information updated successfully" << endl;
                Sleep(3000);

            } else if (policyType == 3) {
                cout << "You are editing the Third Party Only Policy." << endl;
                cout << "Updated information: " << endl;
                string newInfo;
                cin.clear();
                cin.ignore(1000, '\n');
                getline(cin, newInfo);
                ofstream file("Third_party_info.txt");
                file << newInfo;
                file.close();
                cout << "Information updated successfully" << endl;
                Sleep(3000);
            }
        } else if (choice == 8) {
            system("CLS");
            return;
        }
    }
}

//function: main function to run the program
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
                    
                    try{
                        //cleans csv
                        cleanFile("Customer_registration.csv");
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
                            system("CLS");
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
                    } catch(const std::exception& e){
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