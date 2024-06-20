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
    //if there is a blank line in the csv file, the program will skip it
    //if there is more than 2 blank line in a row, the program will stop reading the file
    //stop reading file if it reaches the end of the file


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




//make sure the input is a int
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
    cout << "Enter your gender(m/f): ";// gender input can be M or F for quote reasons
    getline(cin, gender);
    //checks
    while (gender != "M" && gender != "F" && gender != "m" && gender != "f"){
        cout << "please enter a valid input (M/F): ";
        cin.clear();
        getline(cin, gender);
    }

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


void displayPolicy(int policyType) { 
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
        cout << "You have selected: " << policyTypeStr << endl;
        vector<pair<string, vector<string>>> result = read_csv("Customer_registration.csv");
        for (int i = 0; i < result.size(); i++) {
            if (result.at(i).first == currentUsername) {
                cout << "Is this the correct account to register for a policy with? (y/n): " << result.at(i).first << endl;
                cin.clear();
                char choice;
                cin >> choice;
                if (choice == 'y') {
                    string RegoNum = result.at(i).second.at(7);
                    string phone = result.at(i).second.at(5);
                    string email = result.at(i).second.at(6);
                    string address = result.at(i).second.at(4);
                    string gender = result.at(i).second.at(3);
                    cout << "Some Policy information has been pre-filled for you from your account. Please provide further details towards your " << policyType << " policy." << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Enter the date that the policy will start (dd/mm/yyyy): ";
                    string startDate;
                    //checks date format: (dd/mm/yyyy)
                    getline(cin, startDate);
                    cin.clear();
                    while (startDate.length() != 10 || startDate[2] != '/' || startDate[5] != '/') {
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
                    int policyNum;
                    try {
                        vector<pair<string, vector<string>>> result1 = read_csv("Policies.csv");
                        for (int i = 0; i < result1.size(); i++) {
                            if (result1.size() == 0) {
                                policyNum = 1;
                            }else {
                                policyNum = i + 1;
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

                    cout << "Please enter the type of vehicle you have (1 for car, 2 for motorcycle): ";
                    string vehicle;
                    cin.clear();
                    
                    getline(cin, vehicle);
                    while (vehicle != "1" && vehicle != "2") {
                        cout << "Invalid input, please enter '1' for car and '2' for motorcycle: ";
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
                        cout << "Invalid input, please enter 'y' for yes or 'n' for no: ";
                        cin.clear();
                        getline(cin, quoteChoice);
                    }
                    if (quoteChoice == "y") {
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
        vector<pair<string, vector<string>>> result = read_csv("Customer_registration.csv");
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

                    //store the claim data in a csv file
                    ofstream file("Claims.csv", ios::app);
                    file << currentUsername << "," << RegoNum << "," << phone << "," << email << "," << address << "," << incidentDate << "," << incidentTime << "," << description << ","  << claimsTypeStr << endl;
                    file.close();
                    cout << "Claim made successfully. Thank you for choosing Mors Mutual Car Insurance!" << endl;
                    Sleep(3000);
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
                        //checks if the user already has a policy
                        try {
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
                            cout << "no polices registered, please continue" << endl;
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
                cout << "Claims" << endl;
                bool claim = true;

              
                try{
                    //read the policy csv to see what policy type the user has
                    vector<pair<string, vector<string>>> result = read_csv("Policies.csv");
                    //if file contains no information then the user has no policy to make a claim with
                    
                    if (result.size() == 0) {
                        cout << "You do not have a policy to make a claim with" << endl;
                        Sleep(3000);
                        break;
                    }
                    

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
                                cout << "Invalid input, please enter 'y' for yes or 'n' for no: " << endl;
                                cin.clear();
                                getline(cin, claimChoice);
                            }
                            if (claimChoice == "y" || claimChoice == "Y") {
                                
                                
                                if (policyType == "Comprehensive") {
                                    //cout << "Your current policy type is Comprehensive" << endl;
                                    
                                    policyConverted = 1;
                                    displayClaims(policyConverted);
                                }else if (policyType == "third party fire & theft") {
                                    //cout << "Your current policy type is Third Party Fire & Theft" << endl;
                                    
                                    policyConverted = 2;
                                    displayClaims(policyConverted);
                                }else if (policyType == "third party only") {
                                    //cout << "Your current policy type is Third Party Only" << endl;
                                    
                                    policyConverted = 3;
                                    displayClaims(policyConverted);
                                }
                            }else if (claimChoice == "n" || claimChoice == "N") {
                                break;
                            }
                        } else {
                            claim = false;
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
                cout << "Renewals" << endl;
                cout << "Is this the correct account to renew your policy with? (y/n): " << currentUsername << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                string choice;
                getline(cin, choice);
                //checks that the user inputs the correct input
                while (choice != "y" && choice != "n" && choice != "Y" && choice != "N") {
                    cout << "Invalid input, please enter 'y' for yes or 'n' for no: " << endl;
                    cin.clear();
                    getline(cin, choice);
                }

                
                if (choice == "y") {
                    
                    try{
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
                                while (renewChoice != "y" && renewChoice != "n") {
                                    cout << "Invalid input, please enter 'y' for yes or 'n' for no: " << endl;
                                    cin.clear();
                                    getline(cin, renewChoice);
                                }
                                if (renewChoice == "y") {
                                    //check currentusername to find what policy type the user has in policies.csv
                                    //then checks the price of renewing the policy using calculatequote function
                                    //then creates qa renewals.csv file and stores the data

                                    

                                    string policyType = result.at(i).second.at(10);
                                    
                                    int policyConverted = 0;
                                    if (policyType == "comprehensive") {
                                        cout << "Your current policy type is Comprehensive" << endl;
                                        policyConverted = 1;
                                        
                                    }else if (policyType == "third party fire & theft") {
                                        cout << "Your current policy type is Third Party Fire & Theft" << endl;
                                        policyConverted = 2;
                                    }else if (policyType == "third party only") {
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
                                            cout << "Invalid date, please enter in the format dd/mm/yyyy: ";
                                        }
                                        cin.clear();
                                        getline(cin, startDate);
                                    }
                                    

                                    //ask user for their age
                                    cout << "Please enter your age: ";
                                    string age;
                                    cin.clear();
                                    getline(cin, age);
                                    //check if the age is an int with no spaces
                                    while (age.find(" ") != string::npos || age.find_first_not_of("0123456789") != string::npos) {
                                        cout << "Invalid age, please enter a valid age: " << endl;
                                        cin.clear();
                                        getline(cin, age);
                                    }
                                    ageConverted = stoi(age);
                                    if (ageConverted < 16 || ageConverted > 90) {
                                        cout << "Unfortunately we cannot renew your policy as you are not within the age range of 16-90" << endl;
                                        break;
                                    }
                                    //ask user for their gender
                                    cout << "please enter your gender (m/f)" << endl;
                                    string genderChoice;
                                    cin.clear();
                                    getline(cin, genderChoice);
                                    while (genderChoice != "m" && genderChoice != "f" && genderChoice != "M" && genderChoice != "F") {
                                        cout << "Invalid input, please enter 'm' for male and 'f' for female" << endl;
                                        cin.clear();
                                        getline(cin, genderChoice);
                                    }
                                    if (genderChoice == "m") {
                                        gender = 1;
                                    } else if (genderChoice == "f") {
                                        gender = 2;
                                    }

                                    //ask user for their license status
                                    cout << "please enter your license status (L for learners, R for ristricted, F for full)" << endl;
                                    string licenseChoice;
                                    cin.clear();
                                    getline(cin, licenseChoice);
                                    while (licenseChoice != "L" && licenseChoice != "R" && licenseChoice != "F") {
                                        cout << "Invalid input, please enter 'L' for learners, 'R' for restricted and 'F' for full" << endl;
                                        cin.clear();
                                        getline(cin, licenseChoice);
                                    }

                                    if (licenseChoice == "L" || licenseChoice == "l") {
                                        licenseStatus = 3;
                                        cout << "unfortunately we cannot renew your policy as you are on a learners license" << endl;
                                        break;
                                    } else if (licenseChoice == "R" || licenseChoice == "r") {
                                        licenseStatus = 2;
                                    } else if (licenseChoice == "F" || licenseChoice == "f") {
                                        licenseStatus = 1;
                                    }

                                    //ask user for their vehicle type
                                    cout << "please enter your vehicle type (1 for car, 2 for motorcycle)" << endl;
                                    string vehicleChoice;
                                    cin.clear();
                                    getline(cin, vehicleChoice);
                                    while (vehicleChoice != "1" && vehicleChoice != "2") {
                                        cout << "Invalid input, please enter '1' for car and '2' for motorcycle" << endl;
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
                                        cout << "Invalid input, please enter 'y' for yes or 'n' for no: " << endl;
                                        cin.clear();
                                        getline(cin, renewChoice1);
                                    }
                                    if (renewChoice1 == "y") {
                                        //store the renewal data in a csv file
                                        ofstream file("Renewals.csv", ios::app);
                                        file << currentUsername << "," << quote << "," << startDate << endl;
                                        file.close();
                                        cout << "Policy renewed successfully" << endl;
                                        logAction(currentUsername + "::" + "Policy renewed");
                                        Sleep(3000);
                                        break;
                                    }else if (renewChoice1 == "n") {
                                        cout << "Policy not renewed" << endl;
                                        break;
                                    }
                                }else if (renewChoice == "n") {
                                    cout << "Policy not renewed" << endl;
                                    break;
                                }
                            } else {
                                renew = false;
                            }

                        }
                        if (renew == false) {
                            cout << "no current policy found, Please login with the correct account you wish to renew your policy with." << endl;
                            Sleep(3000);
                            system("CLS");
                            break;
                        }
                    } catch(const std::exception& e){
                        cout << "no current policy found, Please login with the correct account you wish to renew your policy with." << endl;
                        Sleep(3000);
                        system("CLS");
                    }

                    
                   
                } else if (choice == "n") {
                    cout << "Please login with the correct account you wish to renew your policy with." << endl;
                    Sleep(3000);
                    system("CLS");
                }
            }else if (CustomerChoice == 4) {
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
            
            try{
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
            } catch(const std::exception& e){
                cout << "Username not found" << endl;
                Sleep(3000);
            }
            
            

            
        } else if (choice == 3) {
            
            try {
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
                    
                    try{
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