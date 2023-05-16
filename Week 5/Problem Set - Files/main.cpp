//
//  main.cpp
//  week 5 file problem set
//
//  Created by Jacob on 5/16/23.
//

#include <iostream>
#include <fstream>

void displayBalance(double balance) {
    std::cout << "Current balance: $" << balance << "\n";
}

double readBalance() {
    std::ifstream output;
    output.open("data.txt");
    if (output.fail()) {
        std::cout << "Unable to open data.txt";
        return 0.00;
    } else {
        
        double return_val;
        output >> return_val;
        displayBalance(return_val);
        output.close();
        return return_val;
    }
   

}

double updateBalance() {
    std::cout << "Deposit Amount >>>";
    double deposit;
    std::cin >> deposit;
    return deposit;
    
}

void writeBalance(double balance) {
    std::ofstream input;
    input.open("data.txt");
    
    input << balance;
    if (input.fail()) {
        std::cout << "Unable to write balance to data.txt\n";
    } else {
        std::cout << "Balance successfuly written to data.txt\n";
        input.close();
    }
    
    
}

int main() {
    double currentBalance;
    currentBalance = readBalance();
    currentBalance += updateBalance();
    writeBalance(currentBalance);
    
    
}
