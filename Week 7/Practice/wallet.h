/*************************************************************
 * 1. Name:
 *      -your name-
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
    Wallet();
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

void Wallet::chooseCurrent() {
    if (getSam() > getSue()) {
        chooseSam();
    }
    else {
        chooseSue();
    }
}
