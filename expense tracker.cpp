// EXPENSE TRACKER

#include <iostream>
#include <fstream>
using namespace std;

enum Categories {
    SHOPPING,
    ENTERTAINMENT,
    GENERAL,
    BILLS,
    HEALTH
};

struct Expense {
    int amount;
    Categories category;
};

struct Budget {
    int Shopping;
    int Entertainment;
    int General;
    int Bills;
    int Health;
};

int main() {

    cout << "EXPENSE TRACKER!!!\n";

    char decision;
    Budget B;
    Expense E;

    int Salary;
    int totalBudget;
    int choice;

    cout << "Enter Your Salary: ";
    cin >> Salary;

    cout << "\n";

    // Setting Budget
    while (true) {

        do {
            cout << "Enter budget for Shopping: ";
            cin >> B.Shopping;

            if (B.Shopping < 0)
                cout << "Invalid!\n";

        } while (B.Shopping < 0);


        do {
            cout << "Enter budget for Entertainment: ";
            cin >> B.Entertainment;

            if (B.Entertainment < 0)
                cout << "Invalid!\n";

        } while (B.Entertainment < 0);


        do {
            cout << "Enter budget for General: ";
            cin >> B.General;

            if (B.General < 0)
                cout << "Invalid!\n";

        } while (B.General < 0);


        do {
            cout << "Enter budget for Bills: ";
            cin >> B.Bills;

            if (B.Bills < 0)
                cout << "Invalid!\n";

        } while (B.Bills < 0);


        do {
            cout << "Enter budget for Health: ";
            cin >> B.Health;

            if (B.Health < 0)
                cout << "Invalid!\n";

        } while (B.Health < 0);


        totalBudget =
            B.Shopping +
            B.Entertainment +
            B.General +
            B.Bills +
            B.Health;


        if (totalBudget > Salary) {
            cout << "Budget is Invalid\n";
            cout << "Please enter the budget again.\n\n";
        }
        else {
            cout << "Budget is Fine\n";
            break;
        }
    }


    // Main Menu
    while (true) {

        cout << "\n";
        cout << "1. Add Expense\n";
        cout << "2. Show Expense\n";
        cout << "3. Exit\n";

        cout << "Enter the choice: ";
        cin >> choice;


        switch (choice) {

        // ADD EXPENSE
        case 1:

            decision = 'Y';

            while (decision == 'Y' || decision == 'y') {

                cout << "\n";

                cout << "Select the Category\n";
                cout << "0 - Shopping\n";
                cout << "1 - Entertainment\n";
                cout << "2 - General\n";
                cout << "3 - Bills\n";
                cout << "4 - Health\n";

                cout << "Select: ";
                int categoryChoice;
                cin >> categoryChoice;


                if (categoryChoice < 0 || categoryChoice > 4) {
                    cout << "Invalid\n";
                    break;
                }

                E.category = static_cast<Categories>(categoryChoice);


                cout << "Enter the amount to spend: ";
                cin >> E.amount;


                if (E.amount <= 0) {
                    cout << "Invalid\n";
                    break;
                }


                switch (E.category) {

                case SHOPPING:

                    B.Shopping -= E.amount;

                    if (B.Shopping < 0)
                        cout << "Insufficient Funds\n";

                    break;


                case ENTERTAINMENT:

                    B.Entertainment -= E.amount;

                    if (B.Entertainment < 0)
                        cout << "Insufficient Funds\n";

                    break;


                case GENERAL:

                    B.General -= E.amount;

                    if (B.General < 0)
                        cout << "Insufficient Funds\n";

                    break;


                case BILLS:

                    B.Bills -= E.amount;

                    if (B.Bills < 0)
                        cout << "Insufficient Funds\n";

                    break;


                case HEALTH:

                    B.Health -= E.amount;

                    if (B.Health < 0)
                        cout << "Insufficient Funds\n";

                    break;
                }


                // Display Remaining Budget
                cout << "\nRemaining Budget\n";

                cout << "Amount left in Shopping: "
                     << B.Shopping << "\n";

                cout << "Amount left in Entertainment: "
                     << B.Entertainment << "\n";

                cout << "Amount left in General: "
                     << B.General << "\n";

                cout << "Amount left in Bills: "
                     << B.Bills << "\n";

                cout << "Amount left in Health: "
                     << B.Health << "\n";

                cout << "Total Amount Left: "
                     << B.Shopping +
                        B.Entertainment +
                        B.General +
                        B.Bills +
                        B.Health
                     << "\n";


                // Save expense to file
                ofstream file("expense.txt", ios::app);

                if (file.is_open()) {

                    file << "Category: "
                         << E.category << "\n";

                    file << "Amount: "
                         << E.amount << "\n";

                    file << "------------------\n";

                    file.close();
                }
                else {
                    cout << "Unable to open file!\n";
                }


                // Continue?
                do {

                    cout << "\nDo you want to continue "
                         << "YES(Y/y) OR NO(N/n): ";

                    cin >> decision;


                    if (decision == 'Y' || decision == 'y') {

                        cout << "CONTINUING...\n";

                    }
                    else if (decision == 'N' || decision == 'n') {

                        cout << "EXITING...\n";

                    }
                    else {

                        cout << "INVALID\n";
                    }

                } while (
                    decision != 'Y' &&
                    decision != 'y' &&
                    decision != 'N' &&
                    decision != 'n'
                );
            }

            break;


        // SHOW EXPENSE / REMAINING BUDGET
        case 2:

            cout << "\nRemaining Budget\n";

            cout << "Amount left in Shopping: "
                 << B.Shopping << "\n";

            cout << "Amount left in Entertainment: "
                 << B.Entertainment << "\n";

            cout << "Amount left in General: "
                 << B.General << "\n";

            cout << "Amount left in Bills: "
                 << B.Bills << "\n";

            cout << "Amount left in Health: "
                 << B.Health << "\n";

            cout << "Total Amount Left: "
                 << B.Shopping +
                    B.Entertainment +
                    B.General +
                    B.Bills +
                    B.Health
                 << "\n";

            break;


        // EXIT
        case 3:

            cout << "EXIT";
            return 0;


        default:

            cout << "Invalid Choice\n";
        }
    }

    return 0;
}