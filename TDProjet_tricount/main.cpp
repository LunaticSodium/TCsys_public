#include <cstdio>
#include "tcsys.h"
#include "undoredo.h"
#include "undoredo.cpp"     //or there would be a bug, caused by the fault of inline of VS

int main()
{
    tcsys tcsystem;
    tcsystem.initTcsys();
    undoredo<tcsys> udrd(UNDOREDO_DEPTH);
    std::cout << "Enter \"help\" to have more information. \n";
#ifdef DEBUG
    std::cout << "Maybe the type error is the convertion of size_t, int and uint. that is a thing inbetween error and warning. \n";
#endif // DEBUG

    while (true)
    {
        std::cout << "Please enter a command : ";
        std::string command;
        std::getline(std::cin, command);


        if (command == "help")
        {
            tcsystem.help();
        }


        //Person
        else if (command == "new person")
        {
            std::string firstname, lastname;
            std::cout << "Please enter the first name: ";
            std::getline(std::cin, firstname);
            std::cout << "Please enter the last name: ";
            std::getline(std::cin, lastname);
            const int com = tcsystem.newPerson(firstname, lastname);
            if (com == 0) std::cout << "Operation successed. ";
            else std::cout << "Operation failed. ";
        }
        else if (command == "select person")
        {
            std::string firstname, lastname;
            std::cout << "Please enter the first name: ";
            std::getline(std::cin, firstname);
            std::cout << "Please enter the last name: ";
            std::getline(std::cin, lastname);
            const int com = tcsystem.selectPerson(firstname, lastname);
            if (com == 0) std::cout << "Select successed. ";
            else if (com == 1) std::cout << "Already selected. Use unselect person to unselect. ";
            else if (com == 2) std::cout << "No such person found. Use print person list to check. ";
            ;
        }
        else if (command == "print person list")
        {
            std::cout << "Person list down below : ";
            const int com = tcsystem.printPersonList();
            if (com == 0) std::cout << "Person list end. ";
        }
        else if (command == "unselect person")
        {
            std::string firstname, lastname;
            std::cout << "Please enter the first name: ";
            std::getline(std::cin, firstname);
            std::cout << "Please enter the last name: ";
            std::getline(std::cin, lastname);
            const int com = tcsystem.unSelectPerson(firstname, lastname);
            if (com == 0) std::cout << "Operation successed. ";
            else std::cout << "Operation failed. ";
        }
        else if (command == "remove person")
        {
            const int com = tcsystem.removePerson();
            if (com == 0) std::cout << "Operation successed. ";
            else std::cout << "Operation failed. ";
        }
        else if (command == "checkout person")
        {
            const int com = tcsystem.checkoutPerson();
            if (com == 0) std::cout << "Checkout successed. ";
            else if (com == 1) std::cout << "No person selected yet. ";
        }/*
        else if (command == "copy personal bill")
        {
            const int com = tcsystem.copyPersonalBill();
            if (com == 0) std::cout << "Copy successed. ";
            else std::cout << "Copy failed, error code " << com ;
        }*/
        else if (command == "print personal bill")
        {
            const int com = tcsystem.printPersonalBill();
            if (com == 0) std::cout << "Print successed. ";
            else std::cout << "Print failed, error code " << com;
        }
        else if (command == "equilibe")
        {
            const int com = tcsystem.equilibe();
            if (com == 0) std::cout << "Print successed. ";
            else std::cout << "Print failed, error code " << com;
        }

        //Event (bill)
        else if (command == "new event")
        {
            MONEY amount;
            std::string  am,name,content;
            std::cout << "Please enter the amount: ";
            std::getline(std::cin,am);
            amount = stof(am);
            std::cout << "Please enter the name: ";
            std::getline(std::cin, name);
            std::cout << "Please enter the content: ";
            std::getline(std::cin, content);
            const int com = tcsystem.newEvent(amount,name,content);
            if (com == 0) std::cout << "Operation successed. ";
            else std::cout << "Operation failed. ";
        }
        else if (command == "fast new event")
        {
            MONEY amount;
            std::string am;
            std::cout << "Please enter the amount: ";
            std::getline(std::cin, am);
            amount = stof(am);
            tcsystem.newEvent(amount);
        }
        else if (command == "select all events")
        {
            const int com = tcsystem.selectAllEvent();
            if (com == 0) std::cout << "Operation successed. ";
            else std::cout << "Operation failed. ";
        }
        else if (command == "select one event")
        {
            std::cout << "Please enter the event ID: ";
            ID bl_id;
            std::cin >> bl_id;
            const int com = tcsystem.selectOneEvent(bl_id);
            if (com == 0) std::cout << "Operation successed. ";
            else std::cout << "Operation failed. "; 
        }
        else if (command == "unselect all events")
        {
            const int com =tcsystem.unselectAllEvent();
            if (com == 0) std::cout << "Operation successed. ";
            else std::cout << "Operation failed. ";
        }
        else if (command == "unselect event")
        {
            std::cout << "Please enter the event ID: ";
            ID bl_id;
            std::cin >> bl_id;
            const int com = tcsystem.unselectEvent(bl_id);
            if (com == 0) std::cout << "Operation successed. ";
            else std::cout << "Operation failed. ";
        }
        else if (command == "delete selected events")
        {
            const int com = tcsystem.deleteSelectedEvent();
            if (com == 0) std::cout << "Operation successed. ";
            else std::cout << "Operation failed. ";
        }

        else if (command == "unselect all")
        {
            const int com = tcsystem.unselectAll();
            if (com == 0) std::cout << "Operation successed. ";
            else std::cout << "Operation failed. ";
        }


        //Pool
        else if (command == "new pool")
        {
            const int com = tcsystem.newPool();
            if (com == 0) std::cout << "Operation successed. ";
            else std::cout << "Operation failed. ";
        }
        else if (command == "change pool name")
        {
            std::string name;
            std::cout << "Please enter the name: ";
            std::getline(std::cin, name);
            const int com = tcsystem.changePoolName(name);
            if (com == 0) std::cout << "Operation successed. ";
            else std::cout << "Operation failed. ";
        }
        else if (command == "delete pool")
        {
            std::cout << "Please enter the pool ID: ";
            ID pl_id;
            std::cin >> pl_id;
            const int com = tcsystem.deletePool(pl_id);
            if (com == 0) std::cout << "Operation successed. ";
            else std::cout << "Operation failed. ";
        }
        else if (command == "switch pool")
        {
            std::cout << "Please enter the pool ID: ";
            ID pl_id;
            std::cin >> pl_id;
            const int com = tcsystem.switchPool(pl_id);
            if (com == 0) std::cout << "You are now in pool " << pl_id << " " << tcsystem.getPoolName(pl_id);
            else std::cout << "Operation failed. ";
        }


        //Other
        else if (command == "set exchange rate")
        {
            std::cout << "Please enter the exchange rate: ";
            MONEY rate;
            std::cin >> rate;
            const int com = tcsystem.setExchangeRate(rate);
            if (com == 0) std::cout << "Operation successed. ";
            else std::cout << "Operation failed. ";
        }
        else if (command == "exchange")
        {
            const int com = tcsystem.exchange();
            if (com == 0) std::cout << "Operation successed. ";
            else std::cout << "Operation failed. ";
        }
        else if (command == "set config")
        {
            int ct;
            bool target;
            std::cout << "Which config type to change: \n0: input_as_total \n1: bill_generate_as_pair ";
            std::cin >> ct;
            std::cout << "Please enter the target : ";
            std::cin >> target;
            const int com = tcsystem.setConfig(ct, target);
            if (com == 0) std::cout << "Operation successed. ";
            else std::cout << "Operation failed. ";
            }
        /*
        else if (command == "save config")
        {
            tcsystem.saveConfig();
        }
        else if (command == "load config")
        {
            tcsystem.loadConfig();
        }
        else if (command == "copy")
        {
            std::cout << "Please enter the text to copy: ";
            std::string txt;
            std::getline(std::cin, txt);
            tcsystem.copy(txt);
        }*/

        else if (command == "exit")
        {
            std::cout << "See you soon. ";
            break;
        }

        else if (command == "undo")
        {
            if (udrd.undo(tcsystem) == 0) std::cout << "Undo successful. ";
            else std::cout << "Undo failed. ";
            continue;
        }

        else if (command == "redo")
        {
            if (udrd.redo(tcsystem) == 0) std::cout << "Redo successful. ";
            else std::cout << "Redo failed. ";
            continue;
        }

        else
        {
            std::cout << "Invalid command. \n";
            tcsystem.save();
            continue;
        }

        

        if (udrd.push(tcsystem) != 0) std::cout << "Record failed. ";

    }
    return 0;
}