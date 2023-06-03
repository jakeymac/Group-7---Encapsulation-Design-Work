/*************************************************************
 * 1. Name:
 *      Jacob and Jaden
 * 2. Module
 *      WALLET
 * 3. Assignment Description:
 *      A class to represent an wallet with multiple credit cards
 **************************************************************/

#pragma once

#include <cassert>

class TestWallet;

 /************************************
  * WALLET
  ************************************/
class Wallet
{
   friend TestWallet;
    private:
        double accountSam;
        double accountSue;
        double * pCurrentAccount;
        
    public:
        Wallet() noexcept;
        void updateSam(double amount) {accountSam += amount;};
        void updateSue(double amount) {accountSue += amount;};
        void updateCurrent(double amount) {*pCurrentAccount += amount;};
        void chooseSam() { pCurrentAccount = &accountSam; };
        void chooseSue() { pCurrentAccount = &accountSue; };
        void chooseCurrent();
        double getSam() { return accountSam; };
        double getSue() { return accountSue; };
        double getCurrent() { return *pCurrentAccount; };
    
};

Wallet::Wallet() noexcept {
    accountSam = 0.0;
    accountSue = 0.0;
    pCurrentAccount = &accountSam;
}

void Wallet::chooseCurrent() {
    if (getSam() > getSue()) {
        chooseSam();
    }
    else {
        chooseSue();
    }
}
