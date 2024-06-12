#include <iostream>
#include <string>
#include <iomanip> // setprecision
#include <windows.h> // Sleep

using namespace std;

// Function for checking if user inputs an integer
int validInput() {
    int x;
    cin >> x;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Bad entry. Enter a NUMBER: ";
        cin >> x;
    }
    return x;
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
        cin.clear();
        age = validInput();
    }
    while (age >= 90) {
        cout << "You must be under 90 years old to apply for a quote." << endl;
        cin.clear();
        age = validInput();
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

int main() {

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
    
    Sleep(5000);
    return 0;
}
