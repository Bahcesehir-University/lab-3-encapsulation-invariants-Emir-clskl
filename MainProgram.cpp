// ============================================================
// CMP1002 - Lab: Encapsulation and Invariants
// Student Version - MainProgram.cpp
// ============================================================
// Instructions:
//   Complete all TODO sections below.
//   Do NOT modify function signatures or class interfaces.
//   All logic must remain in this single file.
// ============================================================

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

// ================================
// CLASS DEFINITIONS
// ================================

// --------------------------------------------------
// Class: Temperature
// Represents a temperature in Celsius.
// Invariant: temperature must be >= -273.15 (absolute zero)
// --------------------------------------------------
class Temperature {
private:
    double celsius_;
public:
    // Constructor: initialize with a Celsius value.
    // Must enforce the invariant.
    // Throw std::invalid_argument if value < -273.15
    explicit Temperature(int celsius) {
        if (celsius<-273.15){
            throw invalid_argument("Temperature cannot be below absolute zero(-273.15)");
        }
    celsius_ = celsius;
    }
     

    // Getter: return the temperature in Celsius
    double getCelsius() const {
        // TODO: Implement
        return celsius_;
    }

    // Getter: return the temperature converted to Fahrenheit
    // Formula: F = C * 9/5 + 32
    double getFahrenheit() const {
        // TODO: Implement
        return celsius_*9.0/5.0+32.0;
    }

    // Setter: update the temperature in Celsius
    // Must enforce the invariant.
    // Throw std::invalid_argument if value < -273.15
    void setCelsius(double celsius) {
        // TODO: Implement
         if (celsius<-273.15){
            throw invalid_argument("Temperature cannot be below absolute zero(-273.15)");
         }
    celsius_ = celsius;
    }
};

// --------------------------------------------------
// Class: BankAccount
// Represents a simple bank account.
// Invariants:
//   - balance must never be negative
//   - owner name must not be empty
// --------------------------------------------------
class BankAccount {
private:
    string owner_;
    double balance_;

public:
    // Constructor: initialize with owner name and starting balance.
    // Throw std::invalid_argument if owner is empty or balance < 0
    BankAccount(const string& owner, double initialBalance) {
        // TODO: Validate and set members
        if (owner.empty())
        {
            throw invalid_argument("owner name cannot be empty");
        }
        if (initialBalance<0)
        {
            throw invalid_argument("initial balance cannot be negative");
        }
        owner_=owner;
        balance_=initialBalance;
    }

    // Getter: return the owner's name
    string getOwner() const {
        // TODO: Implement

        return owner_;
    }

    // Getter: return the current balance
    double getBalance() const {
        // TODO: Implement
        return balance_;
    }

    // Deposit money into the account.
    // Throw std::invalid_argument if amount <= 0
    void deposit(double amount) {
        // TODO: Implement
        if(amount<=0){ 
            throw invalid_argument("deposite amount must be positive");
            
        }
        balance_ +=amount;
    }

    // Withdraw money from the account.
    // Throw std::invalid_argument if amount <= 0
    // Throw std::runtime_error if insufficient funds
    void withdraw(double amount) {
        // TODO: Implement
        if(amount<=0){
            throw invalid_argument("withdrawal amount must be positive");
        }
        if(amount>balance_){
            throw runtime_error("insufficient funds");
        }
        balance_-=amount;
    }

    // Transfer money from this account to another.
    // Throw std::invalid_argument if amount <= 0
    // Throw std::runtime_error if insufficient funds
    void transfer(BankAccount& other, double amount) {
        // TODO: Implement using withdraw() and deposit()
        if(amount <= 0){
            throw invalid_argument("transfer amount must be positive");
        }
        withdraw(amount);
        other.deposit(amount);
    }
};

// --------------------------------------------------
// Class: Password
// Represents a password with strength rules.
// Invariants:
//   - password length must be >= 8
//   - password must contain at least one digit
// --------------------------------------------------
class Password {
private:
    string password_;

    // Helper: check if a string contains at least one digit
    static bool hasDigit(const string& s) {
        // TODO: Implement
        for(char c:s){
            if(c>='0'&&c<='9'){
                return true;
            }
        }
        return false;
    }

    // Helper: validate password against all rules
    static void validate(const string& pwd) {
        // TODO: Check length >= 8 and hasDigit
        // Throw std::invalid_argument with descriptive message if invalid
        if(pwd.length()<8){
            throw invalid_argument("Password must be at least 8 char long.");
        }
        if(!hasDigit(pwd)){
            throw invalid_argument("Password must contain at least one digit");
        }
        
    }

public:
    // Constructor: create a password.
    // Must pass validation.
    explicit Password(const string& pwd) {
        // TODO: Validate and set password_
        validate(pwd);
        password_=pwd;
        
    }

    // Change password: old password must match, new must be valid.
    // Throw std::invalid_argument if oldPassword doesn't match
    // Throw std::invalid_argument if newPassword fails validation
    void change(const string& oldPassword, const string& newPassword) {
        // TODO: Implement
        if(oldPassword != password_){
            throw invalid_argument("old password does not match");
        }
        validate(newPassword);
        password_=newPassword;
    }

    // Check if a given string matches the stored password.
    bool matches(const string& attempt) const {
        // TODO: Implement
        return attempt==password_;
    }

    // Return the length of the password (safe to expose)
    size_t getLength() const {
        // TODO: Implement
        return password_.length();
    }

    // NOTE: There is deliberately NO getPassword() method.
    // Exposing the raw password would break encapsulation.
};


// ================================
// MAIN FUNCTION
// ================================
int main() {
    cout << "=== Encapsulation and Invariants Lab ===" << endl;
    cout << endl;

    // --- Temperature Demo ---
    cout << "--- Temperature ---" << endl;
    try {
        Temperature t(100.0);
        cout << "Celsius: " << t.getCelsius() << endl;
        cout << "Fahrenheit: " << t.getFahrenheit() << endl;
        t.setCelsius(-40.0);
        cout << "Updated Celsius: " << t.getCelsius() << endl;
        cout << "Updated Fahrenheit: " << t.getFahrenheit() << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    // Try invalid temperature
    try {
        Temperature bad(-300.0);
        cout << "This should not print!" << endl;
    } catch (const invalid_argument& e) {
        cout << "Caught expected error: " << e.what() << endl;
    }
    cout << endl;

    // --- BankAccount Demo ---
    cout << "--- BankAccount ---" << endl;
    try {
        BankAccount alice("Alice", 1000.0);
        BankAccount bob("Bob", 500.0);
        cout << alice.getOwner() << " balance: " << alice.getBalance() << endl;

        alice.deposit(200.0);
        cout << "After deposit: " << alice.getBalance() << endl;

        alice.transfer(bob, 300.0);
        cout << "After transfer:" << endl;
        cout << "  Alice: " << alice.getBalance() << endl;
        cout << "  Bob:   " << bob.getBalance() << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    // --- Password Demo ---
    cout << "--- Password ---" << endl;
    try {
        Password pw("Secure99");
        cout << "Password length: " << pw.getLength() << endl;
        cout << "Matches 'wrong': " << pw.matches("wrong") << endl;
        cout << "Matches 'Secure99': " << pw.matches("Secure99") << endl;
        pw.change("Secure99", "NewPass1");
        cout << "Password changed successfully." << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << endl;
    cout << "=== Lab Complete ===" << endl;
    return 0;
}
