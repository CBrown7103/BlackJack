#include <iostream>   // Include input-output stream library
#include <cstdlib>    // Include standard library with functions like rand()
#include <ctime>      // Include time library for seeding random number generator

using namespace std;  // Allow usage of standard library components without prefix

// Function prototypes
int rollDice();               // Declares a function to simulate rolling a dice
int getWager(int moneyOnHand); // Declares a function to get player's wager
void playerTurn(bool &playerBust, int &playerTotal);  // Declares a function for player's turn
void houseTurn(bool &houseBust, int &houseTotal);     // Declares a function for house's turn

int main() {
    srand(time(0)); // Seed for random number generation using current time

    int playerMoney = 100;  // Initialize player's money to 100
    char playAgain = 'y';   // Initialize playAgain to 'y'

    while (playerMoney > 0 && (playAgain == 'y' || playAgain == 'Y')) { // Start of the main game loop
        int playerTotal = 0, houseTotal = 0;  // Initialize player's and house's totals to 0
        bool playerBust = false, houseBust = false;  // Initialize bust flags to false

        int wager = getWager(playerMoney);  // Get player's wager
        playerMoney -= wager;  // Deduct wager from player's money

        // Player's turn
        playerTurn(playerBust, playerTotal);  // Execute player's turn

        if (!playerBust) {  // Check if player hasn't busted
            // House's turn
            houseTurn(houseBust, houseTotal);  // Execute house's turn

            // Determine winner
            if (!houseBust) {  // Check if house hasn't busted
                if (playerTotal > houseTotal) {  // Check if player's total is greater than house's total
                    cout << "You win $" << wager << "!" << endl;  // Display win message
                    playerMoney += 2 * wager;  // Double player's money
                } else if (playerTotal < houseTotal) {  // Check if player's total is less than house's total
                    cout << "You lose $" << wager << "." << endl;  // Display lose message
                } else {  // If totals are equal
                    cout << "It's a push. You get back $" << wager << "." << endl;  // Display push message
                    playerMoney += wager;  // Give back player's wager
                }
            } else {  // If house busted
                cout << "House busted! You win $" << wager << "!" << endl;  // Display win message
                playerMoney += 2 * wager;  // Double player's money
            }
        } else {  // If player busted
            cout << "You busted! You lose $" << wager << "." << endl;  // Display bust message
        }

        cout << "Your current balance is: $" << playerMoney << endl;  // Display player's current balance
        
        if (playerMoney > 0) {  // Check if player still has money
            cout << "Do you want to play again? (y/n): ";  // Prompt for playing again
            cin >> playAgain;  // Get user's choice
        } else {  // If player is out of money
            cout << "You're out of money. Game over." << endl;  // Display game over message
        }
    }

    return 0;  // Return 0 to indicate successful execution
}

// Rolls a 2-10, Jack, Queen, King, or Ace and returns the value
int rollDice() {
    int roll = rand() % 13 + 2; // Generates a random number between 2 and 14
    if (roll > 10) {  // If roll is greater than 10
        return 10;  // Return 10 (Jack, Queen, King, or Ace)
    }
    return roll;  // Otherwise, return the roll value
}

// Inputs a wager from the keyboard and returns the amount
int getWager(int moneyOnHand) {
    int wager;  // Declare variable to hold wager
    do {
        cout << "Enter your wager (current balance: $" << moneyOnHand << "): ";  // Prompt for wager
        cin >> wager;  // Get user's input for wager
    } while (wager <= 0 || wager > moneyOnHand);  // Repeat until valid wager is entered
    return wager;  // Return the valid wager
}

// Implements the game logic for one round for the human player
void playerTurn(bool &playerBust, int &playerTotal) {
    cout << "Player's turn:" << endl;  // Display player's turn message
    for (int i = 0; i < 2; ++i) {  // Loop twice for initial two rolls
        int roll = rollDice();  // Roll the dice
        cout << "You rolled: " << roll << endl;  // Display rolled value
        playerTotal += roll;  // Add rolled value to player's total
    }

    cout << "Your total: " << playerTotal << endl;  // Display player's total
    
    while (playerTotal < 21) {  // Loop until player's total is less than 21
        char choice;  // Declare variable to hold player's choice
        cout << "Do you want to hit (h) or stand (s)? ";  // Prompt for hit or stand
        cin >> choice;  // Get player's choice
        if (choice == 'h' || choice == 'H') {  // If player chooses to hit
            int roll = rollDice();  // Roll the dice
            cout << "You rolled: " << roll << endl;  // Display rolled value
            playerTotal += roll;  // Add rolled value to player's total
            cout << "Your total: " << playerTotal << endl;  // Display updated total
        } else if (choice == 's' || choice == 'S') {  // If player chooses to stand
            break;  // Exit the loop
        }
    }

    if (playerTotal > 21) {  // If player's total exceeds 21
        playerBust = true;  // Set bust flag to true
    }
}

// Implements the logic for one round for the house or computer player
void houseTurn(bool &houseBust, int &houseTotal) {
    cout << "House's turn:" << endl;  // Display house's turn message
    int roll = rollDice();  // Roll the dice
    cout << "House rolled: " << roll << endl;  // Display rolled value
    houseTotal += roll;  // Add rolled value to house's total

    cout << "House's total: " << houseTotal << endl;  // Display house's total
    
    while (houseTotal < 17) {  // Loop while house's total is less than 17
        roll = rollDice();  // Roll the dice for the house
        cout << "House rolled: " << roll << endl;  // Display rolled value
        houseTotal += roll;  // Add rolled value to house's total
        cout << "House's total: " << houseTotal << endl;  // Display updated total
    }

    if (houseTotal > 21) {  // If house's total exceeds 21
        houseBust = true;  // Set bust flag to true
    }
}