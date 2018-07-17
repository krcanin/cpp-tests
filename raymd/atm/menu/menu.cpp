#include "menu.hpp"
#include "../bank/bank.hpp"
#include "../customer/customer.hpp"

#include <vector>
#include <limits>

using namespace std;

#define WINDOWS

void showMenu(Bank &b) {
    int zahl;

    do {
        // Menue anzeigen
        std::cout << "Bankverwaltungssystem\n";
        std::cout << "--------------------------------------\n";
        std::cout << "(1) Kunden anzeigen\n";
        std::cout << "(2) Kunden hinzufuegen\n";
        std::cout << "(3) Kunden entfernen\n";
        std::cout << "(4) Kunden anpassen\n";
        std::cout << "(0) Beenden\n";
        std::cout << "--------------------------------------" << std::endl;

        // Entscheidung abfragen
        std::cin >> zahl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Entscheidung verarbeiten
        // read -n1 -r -p "Press any key to continue..." key
        switch(zahl) {
            case 1:
                {
                    std::cout << b.operator string();

                    cout << "Beliebe Taste zum Fortfahren druecken...";

                    #ifdef WINDOWS
                    system("pause > NUL");
                    #else
                    system("read -n1 -r -p \"\" key");
                    #endif
                }

                break;
            case 2:
                {
                    string name;
                    int pin;

                    cout << "Name: ";
                    getline(cin, name);
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "PIN: ";
                    cin >> pin;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    Customer c(name, pin);

                    b.addCustomer(c);
                }

                break;
            case 3:
                {

                }

                break;
            case 4:
                {

                }

                break;
            case 0:
                {
                    goto END;
                }

                break;
        }

        #ifdef WINDOWS
        system("cls");
        #else
        system("clear");
        #endif
    } while(true);

    END: ;
}
