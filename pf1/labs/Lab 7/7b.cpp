
#include <iostream>
using namespace std;

char GetConcert() {
    char Concert;
    cout << "The following concerts are available:\n";
    cout << "     B for Beyonce\n";
    cout << "     L for Lady Gaga\n";
    cout << "     T for Taylor Swift\n";
    cout << "Enter the letter for the concert you want:\n";
    cin >> Concert;

    while (Concert != 'B' && Concert != 'L' && Concert != 'T') {
        cout << "Invalid choice. Please enter B, L, or T:\n";
        cin >> Concert;
    }

    return Concert;
}

int GetNumTickets() {
    int NumTickets;
    cout << "Enter the number of tickets you want:\n";
    cin >> NumTickets;

    while (NumTickets < 0 || NumTickets > 10) {
        if (NumTickets < 0)
            cout << "You can not sell tickets here.\n";
        else
            cout << "You may not purchase more than 10 tickets.\n";

        cout << "Enter the number of tickets you want:\n";
        cin >> NumTickets;
    }

    return NumTickets;
}

float GetCost(char Concert, int NumTickets) {
    float Cost = 0;
    float PricePerTicket = 0;

    if (Concert == 'B')
        PricePerTicket = 35;
    else if (Concert == 'L')
        PricePerTicket = 45;
    else if (Concert == 'T')
        PricePerTicket = 40;

    Cost = PricePerTicket * NumTickets;

    if (NumTickets >= 5)
        Cost *= 0.9; // Apply 10% discount

    return Cost;
}

int main() {
    char Concert = 0;
    int NumTickets = 0;
    float Cost = 0;

    Concert = GetConcert();
    NumTickets = GetNumTickets();
    Cost = GetCost(Concert, NumTickets);

    cout << "\nThe customer has placed the following order:\n";
    cout << "Concert: " << Concert << endl;
    cout << "Number of Tickets: " << NumTickets << endl;
    cout << "Total Cost: $" << Cost << endl;

    return 0;
}

