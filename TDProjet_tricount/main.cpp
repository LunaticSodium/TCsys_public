#include <cstdio>
#include "tcsys.h"

int main()
{
    tcsys system;
    std::cout << "Enter \"help\" to have more information. \n";
    while (true)
    {
        std::cout << "Please enter a command : ";
        std::string command;
        std::getline(std::cin, command);


        if (command == "help")
        {
            system.help();
        }


        //Person
        else if (command == "new person")
        {
            std::string firstname, lastname;
            std::cout << "Please enter the first name: ";
            std::getline(std::cin, firstname);
            std::cout << "Please enter the last name: ";
            std::getline(std::cin, lastname);
            system.newPerson(firstname, lastname);
        }
        else if (command == "select person")
        {
            std::string firstname, lastname;
            std::cout << "Please enter the first name: ";
            std::getline(std::cin, firstname);
            std::cout << "Please enter the last name: ";
            std::getline(std::cin, lastname);
            system.selectPerson(firstname, lastname);
        }
        else if (command == "unselect person")
        {
            std::string firstname, lastname;
            std::cout << "Please enter the first name: ";
            std::getline(std::cin, firstname);
            std::cout << "Please enter the last name: ";
            std::getline(std::cin, lastname);
            system.unSelectPerson(firstname, lastname);
        }
        else if (command == "remove person")
        {
            system.removePerson();
        }
        else if (command == "checkout person")
        {
            system.checkoutPerson();
        }
        else if (command == "copy personal bill")
        {
            system.copyPersonalBill();
        }


        //Event (bill)
        else if (command == "new event")
        {
            MONEY amount;
            std::string  name,content;
            std::cout << "Please enter the amount: ";
            std::cin >> amount;
            std::cout << "Please enter the name: ";
            std::getline(std::cin, name);
            std::cout << "Please enter the content: ";
            std::getline(std::cin, content);
            system.newEvent(amount,name,content);
        }
        else if (command == "fast new event")
        {
            MONEY amount;
            std::cout << "Please enter the amount: ";
            std::cin >> amount;
            system.newEvent(amount);
        }
        else if (command == "select all events")
        {
            system.selectAllEvent();
        }
        else if (command == "select one event")
        {
            std::cout << "Please enter the event ID: ";
            ID bl_id;
            std::cin >> bl_id;
            system.selectOneEvent(bl_id);
        }
        else if (command == "unselect all events")
        {
            system.unselectAllEvent();
        }
        else if (command == "unselect event")
        {
            std::cout << "Please enter the event ID: ";
            ID bl_id;
            std::cin >> bl_id;
            system.unselectEvent(bl_id);
        }
        else if (command == "delete selected events")
        {
            system.deleteSelectedEvent();
        }

        else if (command == "unselect all")
        {
            system.unselectAll();
        }


        //Pool
        else if (command == "new pool")
        {
            system.newPool();
        }
        else if (command == "delete pool")
        {
            std::cout << "Please enter the pool ID: ";
            ID pl_id;
            std::cin >> pl_id;
            system.deletePool(pl_id);
        }
        else if (command == "switch pool")
        {
            std::cout << "Please enter the pool ID: ";
            ID pl_id;
            std::cin >> pl_id;
            system.switchPool(pl_id);
        }


        //Other
        else if (command == "set exchange rate")
        {
            std::cout << "Please enter the exchange rate: ";
            MONEY rate;
            std::cin >> rate;
            system.setExchangeRate(rate);
        }
        else if (command == "exchange")
        {
            system.exchange();
        }
        else if (command == "set config")
        {
            int ct;
            bool target;
            std::cout << "Which config type to change: \n0: input_as_total \n1: bill_generate_as_pair ";
            std::cin >> ct;
            std::cout << "Please enter the target : ";
            std::cin >> target;
            system.setConfig(ct, target);
            }
        /*
        else if (command == "save config")
        {
            system.saveConfig();
        }
        else if (command == "load config")
        {
            system.loadConfig();
        }
        else if (command == "copy")
        {
            std::cout << "Please enter the text to copy: ";
            std::string txt;
            std::getline(std::cin, txt);
            system.copy(txt);
        }*/


        else if (command == "exit")
        {
            cout << "See you soon. ";
            break;
        }


        else
        {
            std::cout << "Invalid command.\n";
        }
    }
    return 0;
}