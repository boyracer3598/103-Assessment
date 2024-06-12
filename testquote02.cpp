#include <iostream>
#include <string>
#include <iomanip> // setprecision

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
void calculateQuote(int age, int gender, int licenseStatus, int insuranceType, int vehicleType) {
    double baseQuote;

    if (insuranceType == 1) { // Comprehensive
        baseQuote = 60.0;
    } else if (insuranceType == 2) { // Third Party Fire & Theft
        baseQuote = 45.0;
    } else if (insuranceType == 3) { // Third Party Only
        baseQuote = 30.0;
    } else {
        cout << "Invalid input. Please select a valid option." << endl;
        return;
    }
    
    //user cannot enter an age below 16, or above 90
    if (age < 16) {
        cout << "You must be at least 16 years old to register for a policy." << endl;
        return;
    }else if (age > 90) {
        cout << "You must be under 90 years old to register for a policy." << endl;
        return;
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
        return; 
    }
    
    if (licenseStatus == 1) { // Full license
        baseQuote *= 1.05;
    } else if (licenseStatus == 2) { // Restricted license
        baseQuote *= 1.20;
    } else if (licenseStatus == 3) { // Learner's license
        cout << "Unfortunatly, we do not offer insurance to drivers with a learner's license. Please try again later." << endl;
        return;
    } else {
        cout << "Invalid input. Please select a valid option for license status." << endl;
        return;
    }
    
    if (vehicleType == 1) { // Car
        baseQuote *= 1.15;
    } else if (vehicleType == 2) { // Motorcycle
        baseQuote *= 0.90;
    } else {
        cout << "Invalid input. Please select a valid option for vehicle type." << endl;
        return; 
    }
    
    // Display the quote
    cout << "Your fixed quote is: $" << fixed << setprecision(2) << baseQuote << " per month." <<endl;
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
        cout << "You have selected Comprehensive Insurance." << endl;
        cout << "The base quote for this policy is $60. This policy price will change depending on your circumstances." << endl;
        cout << "Please enter your age: ";
        cin.clear();
        age = validInput();

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
        int licenseStatus = validInput();
        //check if the user inputs a valid option
        while (licenseStatus != 1 && licenseStatus != 2 && licenseStatus != 3) {
            cout << "Invalid input. Please enter a valid option: 1 for Full License, 2 for Restricted License, 3 for Learner's License: ";
            cin.clear();
            licenseStatus = validInput();
        }

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
        
        // Calculation
        calculateQuote(age, gender, licenseStatus, insuranceType, vehicleType);
    }if (insuranceType == 2) {
        cout << "You have selected Third Party Fire & Theft." << endl;
        cout << "The base quote for this policy is $45. This policy price will change depending on your circumstances." << endl;
        cout << "Please enter your age: ";
        cin.clear();
        age = validInput();

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
        int licenseStatus = validInput();
        //check if the user inputs a valid option
        while (licenseStatus != 1 && licenseStatus != 2 && licenseStatus != 3) {
            cout << "Invalid input. Please enter a valid option: 1 for Full License, 2 for Restricted License, 3 for Learner's License: ";
            cin.clear();
            licenseStatus = validInput();
        }

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
        
        // Calculation
        calculateQuote(age, gender, licenseStatus, insuranceType, vehicleType);
    }if (insuranceType == 3) {
        cout << "You have selected Third Party Only." << endl;
        cout << "The base quote for this policy is $30. This policy price will change depending on your circumstances." << endl;
        cout << "Please enter your age: ";
        cin.clear();
        age = validInput();

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
        int licenseStatus = validInput();
        //check if the user inputs a valid option
        while (licenseStatus != 1 && licenseStatus != 2 && licenseStatus != 3) {
            cout << "Invalid input. Please enter a valid option: 1 for Full License, 2 for Restricted License, 3 for Learner's License: ";
            cin.clear();
            licenseStatus = validInput();
        }

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
        
        // Calculation
        calculateQuote(age, gender, licenseStatus, insuranceType, vehicleType);
    }
}
