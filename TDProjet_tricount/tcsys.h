#pragma once

#ifndef HELP
#define HELP ""\
"Welcome to use tcsys, Trip-Count Simulation YS. Here is to represent some functions. ver.18042023\n" \
"new person: creates a new person in the current pool, with the input parameters being their first name, last name, and an optional amount received.\n"\
"select person : selects a person by their first and last name.\n"\
"unselect person : unselects a person by their first and last name.\n"\
"remove person : removes the selected person from the pool.\n"\
"checkout person : calculates the total amount owed by the selected persons and prints it out.\n"\
"print person list : print a list of all persons in current pool.\n"\
"copy personal bill : copies the bills of the selected persons to the clipboard.\n"\
"new event : creates a new event with the input parameters being the amount, name, and contest associated with the event.\n"\
"fast new event : creates a new event with only the amount"\
"select all event : selects all events in the current pool.\n"\
"select one event : selects one event by its ID.\n"\
"unselect all events : unselects all currently selected events.\n"\
"unselect event : unselects an event by its ID.\n"\
"delete selected event : deletes all selected events.\n"\
"unselect all : unselects all currently selected persons.\n"\
"new pool : creates a new pool.\n"\
"change pool name : change one pool's name.\n"\
"delete pool : deletes a pool by its ID.\n"\
"switch pool : switches to a different pool by its ID.\n"\
"set exchange rate : sets the exchange rate between two currencies.\n"\
"exchange : converts all amounts in the current pool from one currency to another using the exchange rate.\n"\
"set config : sets a configuration option to a specific value.\n"\
"undo : cancel the last move.\n"\
"redo : redo the move that is canceled.\n"\
"help : displays help information about the system.\n"\
"exit : exit tcsys.\n"
#endif // !HELP


#define UNDOSTACK_LENGTH 20
#define COPY_LENGTH 200
#define DATA_FILE_NAME "data.txt"
#define CONFIG_FILE_NAME "config.txt"
#define DEFAUTE_EXCHANGE_RATE 7.34                  //EUR to CNY rate, 03032023 

#ifndef ANDROID_DEPLOY                              //this define allow to jump over some code that made for windows and into those for android deploy. work for _copy
//#define ANDROID_DEPLOY                        
#endif

#ifndef DEBUG                                       //generate extra infomation as possible and may enable some uncompleted functions
#define DEBUG
#endif

#ifndef ANDROID_DEPLOY
#include <Windows.h>
#else

#endif

#include "reaction.h"
#include <fstream>
#include <iostream>
#include <sstream>

/*
data file example :

pool
1
end

bill
1
20
dinner
false
just a dinner
end

bill
2
20
dinner
true
as a counter of dinner
end

bill
3
40
lunch
false
meals
end

person
Alexander
Robinson
150
1 3 5 7 10
end


or the same it would work:


pool
1

bill
1
20
dinner
false
just a dinner




bill
2
20
dinner
true
as a counter of dinner

bill
3
40
lunch
false
meals
person
Alexander
Robinson
150
1 3 5 7 10
end

use \end as a \} which doesn't need a \{
*/

using namespace std;

struct POOL {
    ID pl_id{};
    string pl_name {};
    PERSON_LIST pspool{};
    BILL_LIST blpool{};
    POOL() { pl_name = "default pool"; }
};
enum PART_TYPE {DF,BL,PS,PL};                        //as default, bill, person, pool; to help function _datafileToTcsys() compilable in case of c++ 14 or former

struct CONFIG {
    MONEY exchange_rate{};
    bool is_exchanged{};                              //true if all amount is in second currency, in which case the exchange
    bool input_as_total{};                            //true if all input number is for total amount, and for individual person it should divide by the number of person, fulse by default
    bool bill_generate_as_pair{};                     //trun if when generate one bill, always to generate one opposite to maintain the sum as zero
    CONFIG() {}
};
enum CONFIG_TYPE {IAT,BGAP};

class tcsys /* :
    public reaction */                              //as class reaction is a pure abstract class to list the possible goals, which we have no need to actually fulfill all of them, it's canceled when we finally compile this
{
private:
    PERSON_LIST _personbase;
    //POOL _currentpool;                            present by _p now
    POOL _select;                                   //include which have been selected temperely
    vector<POOL> _pool,_undoredo;
    ID _ursp;                                  //current pool number and undo-redo stack position
    CONFIG _config;

    fstream _file;                                  //no caplock plz, all in mini. notice that the get & set point of file is, in fact, as global. make sure it's well defined in beginning
    fstream _config_file;
    POOL& _p() { return _pool[_select.pl_id]; };


    //streampos _end();                             return the current end streampos without changing the current get point. while you should have a fixed end in beginning of any function which may use this multiple times
                                                    //while the reason why there isnt "const" is, it use a temp variant to regist the get point, so it's not const actually
                                                    //disabled, still too dangerous to jump pointer between functions. every function shall manage it saperately

    vector<vector<string>> _readAll(string const file_name);//read all the base form file. return all the content by parts. rely on _read(). also change _cpn at the last
    vector<string> _read(ifstream& file);            //read a block which end up with "end" from current get position. https://cplusplus.com/doc/tutorial/files/ for more infomation if u forgot
                                                    //NOT all of these function geste the get/set point of _file, and _file.open is often in different mode
                                                    //make SURE that use always readALL() outside of itself 

    const int _datafileToTcsys(vector<string> const part);            //convert a part start with classname/typename and end with "end" into _pool

    const int _regist(void) { return 0; };	                //convert a member into part. regist the change of system into file in current get point.
    const int _regist(bill const bl);
    const int _regist(person const ps);
    const int _regist(ID const pl_id);                   //also change _cpn at the last, same as readAll

    const int _registOne(void);                          //_regist can only be used by _rOne and _rAll, because they dont have _file.open() so they dont know it's ios in or out.
    const int _registOne(bill const bl);
    const int _registOne(person const ps);
    const int _registOne(ID const pl_id);                //only _rO(ID) will change _cpn in all registO/A function.
    const int _registAll();                              //rOne() like push_back, it add a new part in the LAST of file. rAll overwrite the whole file.
    //void virtual _refresh()=0;                      //used to be the name of rereadall, well it suppose to be a function only calling a physic engine's refresh function


    const int _saveConfig();
    const int _loadConfig();
    const int _copy(string const txt);                   //copy a text

    //streampos _locatepersonidlist(ID pl_id, IDENTITY idtt);

public:                                             
    tcsys();
    ~tcsys();
    const int save();

    const int initTcsys();                               //initiale the system by importing the file(str) as datapool(LIST). rely on _readAll() so also _read() and _datafileToTcsys()

    //desorla, down-below here, for safety reason, unless you just drinked a coffee and you know what you are doing,
    //these user-level functions shall use only these _f inbetween all private functions : _readAll(), _registOne(any) and _registAll()  ...  maybe also _refresh()

    const int newPerson(string const firstname, string const lastname, MONEY const rcv = 0);//in current pool
    //void addPerson(ID id);
    const int selectPerson(string const firstname, string const lastname);

    const int unSelectPerson(string const firstname, string const lastname);
    const int removePerson();
    //void deleteSelectedPerson(ID id);

    const int unselectAll();
    const int printPersonList();
    const int checkoutPerson();
    const int copyPersonalBill();//copy *selected* persons' bills. not working. 
    const int printPersonalBill();


    //Event listed in pool and templist, no database. Class event is renamed as bill because it's actually a key word.

    const int newEvent(MONEY const amount = 0, string const name = "\n", string const contest = "\n", bool single = false);
    //void newEvent(string const amount, string const name = "\n", string const contest = "\n") { newEvent(stof(amount), name, contest); return; };
    //void fastNewEventPair(MONEY const amount);
    const int changePoolName(string const name) { _p().pl_name = name; return 0; };
    const int selectAllEvent();
    const int selectOneEvent(ID const bl_id);

    const int unselectAllEvent();
    const int unselectEvent(ID const bl_id);
    const int deleteSelectedEvent();


    //Other system function.
    const int newPool();
    const string getPoolName(ID const pl_id) { if (pl_id < _pool.size()) return _pool[pl_id].pl_name; else return "error"; };
    const int deletePool(ID const pl_id);
    const int namerPool(string name);
    const int switchPool(ID const pl_id);

    const int setExchangeRate(MONEY const rate);
    //MONEY getExchangeRate() { return exchange_rate; };
    const int exchange();
    //void reverseExchange();

    const int setConfig(CONFIG_TYPE const ct, bool const target);
    const int setConfig(int const ct, bool const target) { setConfig(bit_cast<CONFIG_TYPE,int>(ct), target); return 0; }

    tcsys& operator=(const tcsys& tc1);
    //void openConfigPage();
    //void openMainPage();
    //void openEventPage();
    //void openPersonPage();

    //void undo();
    //void redo();

    const int help();
};

