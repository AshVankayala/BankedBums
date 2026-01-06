//==========================================================
//
// Title: Banked Bums - Main
// Author: Ash Vankayala
// Date: 11/21/2025
// Description:
// This program reads transactions from a text file, checks if the data is valid,
// throws error codes for anything invalid, and prints the correct error message.
// For valid transactions, it calculates the deposit, prints the cash back, and
// breaks the cash back into 50s, 20s, 10s, 5s, and 1s.
//==========================================================

#include <iostream>
#include <fstream>
using namespace std;

// Constants
const string FILE_NAME = "BankTransactions.txt"; // Input file name
const int MAX_RECEIVED = 10000; // Maximum amount that can be received
const int MAX_RETURNED = 5000; // Maximum amount that can be returned

// Error codes
// Each constant represents a specific error condition
const int ERR_RECEIVED_LE_ZERO = 1;
const int ERR_RECEIVED_GT_MAX = 2;
const int ERR_RETURN_LT_ZERO = 3;
const int ERR_RETURN_GT_MAX = 4;
const int ERR_RECEIVED_LT_RETURN = 5;

// Function to calculate number of bills of a specific denomination
int getBills(int& amount, int value) {
    int count = amount / value;
    amount %= value;
    return count;
}

int main() {
    ifstream infile(FILE_NAME); // Open input file

    cout << "Welcome to Banked Bums\n";
    cout << "----------------------\n\n";

    cout << "Reading file '" << FILE_NAME << "' ...\n\n"; // Notify user of file being read
    cout << "Line: account, $received, $cashback\n\n"; // Header for output

    if (!infile.is_open()) { // Check if file opened successfully
        cout << "Error: unable to open input file.\n";
        return 1;
    }

    int account, received, cashback;
    int lineNum = 0;

    while (infile >> account >> received >> cashback) { // Read each transaction from file
        lineNum++; // Increment line number

        cout << lineNum << ": " << account << ", $" << received << ", $" << cashback << "\n"; // Print transaction details

        try { // Validate transaction data
            if (received <= 0)
                throw ERR_RECEIVED_LE_ZERO; // Invalid: received amount must be > 0

            if (received > MAX_RECEIVED)
                throw ERR_RECEIVED_GT_MAX; // Invalid: received amount exceeds maximum

            if (cashback < 0)
                throw ERR_RETURN_LT_ZERO; // Invalid: cashback amount must be >= 0

            if (cashback > MAX_RETURNED)
                throw ERR_RETURN_GT_MAX; // Invalid: cashback amount exceeds maximum

            if (received < cashback)
                throw ERR_RECEIVED_LT_RETURN; // Invalid: received amount must be >= cashback amount

            int deposit = received - cashback; // Calculate deposit amount

            cout << "Deposit amount ($): " << deposit << "\n"; // Print deposit amount
            cout << "Cash back ($): " << cashback << "\n"; // Print cash back amount

            // Denominations
            int remaining = cashback;

            // usage
            int bill50 = getBills(remaining, 50);
            int bill20 = getBills(remaining, 20);
            int bill10 = getBills(remaining, 10);
            int bill5  = getBills(remaining, 5);
            int bill1  = getBills(remaining, 1);

            // Print breakdown of cash back into denominations
            cout << "50s: " << bill50 << "\n";
            cout << "20s: " << bill20 << "\n";
            cout << "10s: " << bill10 << "\n";
            cout << "5s: " << bill5 << "\n";
            cout << "1s: " << bill1 << "\n\n";

        } catch (int code) { // Handle errors by printing appropriate messages
            switch (code) { // Handle specific error codes
                case ERR_RECEIVED_LE_ZERO: // Invalid: received amount must be > 0
                    cout << "Error: amount received must be > $0.\n\n";
                    break;
                case ERR_RECEIVED_GT_MAX: // Invalid: received amount exceeds maximum
                    cout << "Error: amount received must be <= $10000.\n\n";
                    break;
                case ERR_RETURN_LT_ZERO:
                    cout << "Error: amount returned must be >= $0.\n\n";
                    break;
                case ERR_RETURN_GT_MAX: // Invalid: cashback amount exceeds maximum
                    cout << "Error: amount returned must be <= $5000.\n\n";
                    break;
                case ERR_RECEIVED_LT_RETURN: // Invalid: received amount must be >= cashback amount
                    cout << "Error: amount received must be >= amount returned.\n\n";
                    break;
            }
        }
    }

    cout << lineNum << " line(s) read from file '" << FILE_NAME << "'.\n\n"; // Print total lines read
    cout << "End of Banked Bums\n"; // End message

    return 0;
}