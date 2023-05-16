//
//  main.cpp
//  week 5 file problem set
//
//  Created by Jacob on 5/16/23.
//

#include <iostream>
#include <fstream>

double readBalance() {
    std::ifstream output;
    output.open("data.txt");
    std::string return_val;
    std::getline(output, return_val);
    output.close();
    return std::stod(return_val);

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
    std::cout << "Current Balance: $" << currentBalance << "\n";
    currentBalance += updateBalance();
    writeBalance(currentBalance);
    
    
}
