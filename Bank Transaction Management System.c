#include <stdio.h>
#include <string.h>

// Structure to hold account information
struct Account {
    char name[50];
    char username[30];
    char mobile[15];
    int pin;
    double balance;
};

// Global variables
struct Account userAccounts[10]; // Array to store multiple user accounts
int totalAccounts = 0;           // Counter for total accounts

// Function prototypes
void displayMenu();
void createAccount();
void login();
void saveAccountsToFile();
int loadAccountsFromFile();
void displayAccountMenu(int userIndex);
void balanceInquiry(int userIndex);
void deposit(int userIndex);
void withdraw(int userIndex);
void balanceStatement(int userIndex);
void showProfile(int userIndex);
void updateProfile(int userIndex);
void contactUs();
void adminLogin();
void viewAllUsers();
void deleteAccount();
void changeUserPassword();

// Function to display the main menu
void displayMenu() {
    printf("\n--------Welcome to the Bank System---------\n");
    printf("\n");
    printf("Choose an option below:\n");
    printf("1. Login\n");
    printf("2. Registration\n");
    printf("3. Admin Portal\n");
    printf("4. Exit\n");
}

// Function to handle account creation
void createAccount() {
    if (totalAccounts >= 10) {
        printf("Account limit reached. Cannot create more accounts.\n");
        return;
    }

    char name[50], username[30], mobile[15];
    int pin, confirmPin;

    printf("\n------------------ Create a New Account ------------------\n");

    printf("Enter your full name: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Create a username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter your mobile number: ");
    fgets(mobile, sizeof(mobile), stdin);
    mobile[strcspn(mobile, "\n")] = '\0';

    while (1) {
        printf("Set a 4-digit PIN: ");
        scanf("%d", &pin);
        if (pin >= 1000 && pin <= 9999) {
            printf("Confirm your PIN: ");
            scanf("%d", &confirmPin);
            if (pin == confirmPin) {
                printf("PIN set successfully!\n");
                break;
            } else {
                printf("PINs do not match. Please try again.\n");
            }
        } else {
            printf("Invalid PIN. Please enter a 4-digit number.\n");
        }
    }

    strcpy(userAccounts[totalAccounts].name, name);
    strcpy(userAccounts[totalAccounts].username, username);
    strcpy(userAccounts[totalAccounts].mobile, mobile);
    userAccounts[totalAccounts].pin = pin;
    userAccounts[totalAccounts].balance = 0.0;

    totalAccounts++;  // Increment total accounts counter

    printf("\nAccount created successfully!\n");

    // Save accounts to file after creating a new account
    saveAccountsToFile();
}

// Function to log in
void login() {
    if (totalAccounts == 0) {
        printf("\nNo account found. Please create an account first.\n");
        return;
    }

    char enteredMobile[15];
    int enteredPin;
    int found = -1;

    printf("\n------------------ Login to Your Account ------------------\n");

    printf("Enter your mobile number: ");
    getchar();  // Clear the input buffer
    fgets(enteredMobile, sizeof(enteredMobile), stdin);
    enteredMobile[strcspn(enteredMobile, "\n")] = '\0';

    printf("Enter your PIN: ");
    scanf("%d", &enteredPin);

    // Find the account with the matching mobile number and pin
    for (int i = 0; i < totalAccounts; i++) {
        if (strcmp(enteredMobile, userAccounts[i].mobile) == 0 && enteredPin == userAccounts[i].pin) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        printf("\nLogin successful! Welcome, %s!\n", userAccounts[found].name);
        displayAccountMenu(found);
    } else {
        printf("\nInvalid mobile number or PIN. Please try again.\n");
    }
}

// Function to display account options after login
void displayAccountMenu(int userIndex) {
    int choice;

    while (1) {
        printf("\n------------------ Account Menu ------------------\n");
        printf("1. Balance Inquiry\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Statement\n");
        printf("5. Profile\n");
        printf("6. Contact Us\n");
        printf("7. Logout\n");
        printf("--------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                balanceInquiry(userIndex);
                break;
            case 2:
                deposit(userIndex);
                break;
            case 3:
                withdraw(userIndex);
                break;
            case 4:
                balanceStatement(userIndex);
                break;
            case 5:
                showProfile(userIndex);
                break;
            case 6:
                contactUs();
                break;
            case 7:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function for Balance Inquiry
void balanceInquiry(int userIndex) {
    printf("\nYour current balance is: %.2f Taka\n", userAccounts[userIndex].balance);
}

// Function for Deposit
void deposit(int userIndex) {
    double amount;
    printf("\nEnter amount to deposit (or 0 to go back): ");
    scanf("%lf", &amount);

    if (amount == 0) {
        printf("Returning to the account menu...\n");
        return;
    } else if (amount >= 500) {
        userAccounts[userIndex].balance += amount;
        printf("Deposit successful! Your new balance is: %.2f Taka\n", userAccounts[userIndex].balance);
    } else {
        printf("Minimum deposit is 500 Taka. Deposit failed.\n");
    }
}

// Function for Withdraw
void withdraw(int userIndex) {
    double amount;
    printf("\nEnter amount to withdraw (or 0 to go back): ");
    scanf("%lf", &amount);

    if (amount == 0) {
        printf("Returning to the account menu...\n");
        return;
    } else if (amount >= 500 && amount <= userAccounts[userIndex].balance) {
        userAccounts[userIndex].balance -= amount;
        printf("Withdrawal successful! Your new balance is: %.2f Taka\n", userAccounts[userIndex].balance);
    } else {
        printf("Invalid amount or insufficient balance. Withdrawal failed.\n");
    }
}

// Function for Balance Statement
void balanceStatement(int userIndex) {
    printf("\nYour current balance is: %.2f Taka\n", userAccounts[userIndex].balance);
    printf("Returning to the account menu...\n");
}

// Function for showing and updating profile
void showProfile(int userIndex) {
    int choice;

    while (1) {
        printf("\n------------------ Profile ------------------\n");
        printf("Name: %s\n", userAccounts[userIndex].name);
        printf("Username: %s\n", userAccounts[userIndex].username);
        printf("Mobile Number: %s\n", userAccounts[userIndex].mobile);
        printf("Balance: %.2f Taka\n", userAccounts[userIndex].balance);
        printf("\n1. Update Profile\n");
        printf("2. Back to Menu\n");
        printf("---------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                updateProfile(userIndex);
                break;
            case 2:
                printf("Returning to the account menu...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to update profile information
void updateProfile(int userIndex) {
    printf("\nEnter new full name: ");
    getchar();  // Clear input buffer
    fgets(userAccounts[userIndex].name, sizeof(userAccounts[userIndex].name), stdin);
    userAccounts[userIndex].name[strcspn(userAccounts[userIndex].name, "\n")] = '\0';

    printf("Enter new mobile number: ");
    fgets(userAccounts[userIndex].mobile, sizeof(userAccounts[userIndex].mobile), stdin);
    userAccounts[userIndex].mobile[strcspn(userAccounts[userIndex].mobile, "\n")] = '\0';

    printf("Profile updated successfully! Returning to profile...\n");
}

// Function to handle contact us option
void contactUs() {
    printf("\nFor any inquiries, please contact support@bank.com.\n");
}

// Admin Login
void adminLogin() {
    char adminUsername[30], adminPassword[30];

    printf("\n------------------ Admin Login ------------------\n");

    printf("Enter admin username: ");
    getchar();
    fgets(adminUsername, sizeof(adminUsername), stdin);
    adminUsername[strcspn(adminUsername, "\n")] = '\0';

    printf("Enter admin password: ");
    fgets(adminPassword, sizeof(adminPassword), stdin);
    adminPassword[strcspn(adminPassword, "\n")] = '\0';

    if (strcmp(adminUsername, "admin") == 0 && strcmp(adminPassword, "admin123") == 0) {
        printf("\nAdmin login successful!\n");
        viewAllUsers();
    } else {
        printf("\nInvalid admin credentials. Returning to main menu...\n");
    }
}

// Admin View All Users
void viewAllUsers() {
    if (totalAccounts == 0) {
        printf("\nNo account found. Please create an account first.\n");
        return;
    }

    int choice;
    while (1) {
        printf("\n------------------ All Users ------------------\n");
        for (int i = 0; i < totalAccounts; i++) {
            printf("User %d:\n", i + 1);
            printf("Name: %s\n", userAccounts[i].name);
            printf("Username: %s\n", userAccounts[i].username);
            printf("Mobile: %s\n", userAccounts[i].mobile);
            printf("Balance: %.2f Taka\n", userAccounts[i].balance);
            printf("---------------------------------------------\n");
        }

        printf("\n1. Change User Password\n");
        printf("2. Delete User Account\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                changeUserPassword();
                break;
            case 2:
                deleteAccount();
                break;
            case 3:
                printf("Returning to the admin menu...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Admin Change User Password
void changeUserPassword() {
    int accountId;
    printf("\nEnter the user ID to change password: ");
    scanf("%d", &accountId);

    if (accountId >= 1 && accountId <= totalAccounts) {
        int newPin;
        printf("\nEnter new 4-digit PIN for user %d: ", accountId);
        scanf("%d", &newPin);
        userAccounts[accountId - 1].pin = newPin;
        printf("Password changed successfully for User %d!\n", accountId);

        // Save updated accounts to file
        saveAccountsToFile();
    } else {
        printf("Invalid user ID. No such account found.\n");
    }
}

// Admin Delete Account
void deleteAccount() {
    int accountId;
    printf("\nEnter the user ID to delete: ");
    scanf("%d", &accountId);

    if (accountId >= 1 && accountId <= totalAccounts) {
        for (int i = accountId - 1; i < totalAccounts - 1; i++) {
            userAccounts[i] = userAccounts[i + 1];
        }
        totalAccounts--;
        printf("\nAccount deleted successfully!\n");

        // Save updated accounts to file
        saveAccountsToFile();
    } else {
        printf("Invalid user ID. No such account found.\n");
    }
}

// Function to save accounts to a text file with labels
void saveAccountsToFile() {
    FILE *file = fopen("accounts.txt", "w");
    if (file == NULL) {
        printf("Error saving accounts to file.\n");
        return;
    }

    for (int i = 0; i < totalAccounts; i++) {
        fprintf(file, "Name: %s\n", userAccounts[i].name);
        fprintf(file, "Username: %s\n", userAccounts[i].username);
        fprintf(file, "Mobile: %s\n", userAccounts[i].mobile);
        fprintf(file, "PIN: %d\n", userAccounts[i].pin);
        fprintf(file, "Balance: %.2f\n\n", userAccounts[i].balance);
    }
    fclose(file);
}

// Function to load accounts from a text file
int loadAccountsFromFile() {
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        return 0;  // No file found
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Name:", 5) == 0) {
            sscanf(line, "Name: %[^\n]", userAccounts[totalAccounts].name);
            fgets(line, sizeof(line), file); // Read "Username:"
            sscanf(line, "Username: %[^\n]", userAccounts[totalAccounts].username);
            fgets(line, sizeof(line), file); // Read "Mobile:"
            sscanf(line, "Mobile: %[^\n]", userAccounts[totalAccounts].mobile);
            fgets(line, sizeof(line), file); // Read "PIN:"
            sscanf(line, "PIN: %d", &userAccounts[totalAccounts].pin);
            fgets(line, sizeof(line), file); // Read "Balance:"
            sscanf(line, "Balance: %lf", &userAccounts[totalAccounts].balance);

            totalAccounts++;
        }
    }
    fclose(file);
    return 1;
}

// Main function
int main() {
    int choice;

    loadAccountsFromFile();  // Load accounts from file if available

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                createAccount();
                break;
            case 3:
                adminLogin();
                break;
            case 4:
                printf("Exiting the system... Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
