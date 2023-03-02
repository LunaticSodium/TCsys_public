#pragma once

#define UNDOSTACKLENGTH 20
#define DATAFILENAME "data.txt"

#ifndef ANDROID_DEPLOY                              //this define allow to jump over some code that made for windows and into those for android deploy. work for _copy
//#define ANDROID_DEPLOY                        
#endif

#ifndef DEBUG                                       //generate extra infomation as possible and may enable some uncompleted functions
#define DEBUG
#endif

#ifndef CAPITAL_IGNORE                              //put before include. this define cancel the capital member of class person, to simplify the protocode
#define CAPITAL_IGNORE                             
#endif

#ifndef ANDROID_DEPLOY
#include <Windows.h>
#else

#endif

#include "reaction.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

typedef struct {
    ID pl_id;
    PERSON_LIST pspool;
    BILL_LIST blpool;
}POOL;

enum PARTTYPE {DF,BL,PS,PL};                        //as default, bill, person, pool; to help function _transfer() compilable in case of c++ 14 or former

class tcsys /* :
    public reaction */                              //as class reaction is a pure abstract class to list the possible goals, which we have no need to actually fulfill all of them, it's canceled when we finally compile this
{
private:
    PERSON_LIST _personbase;
    //POOL _currentpool;                            present by _p now
    POOL _select;                                   //include which have been selected temperely
    vector<POOL> _pool,_undoredo;
    ID _cpn,_ursp;                                  //current pool number and undo-redo stack position
    fstream _file;                                  //no caplock plz, all in mini. notice that the get & set point of file is, in fact, as global. make sure it's well defined in beginning

    POOL& _p() { return _pool[_cpn]; };
    MONEY _exchangerate;
    bool _if_exchanged;

    streampos _end();                               //return the current end streampos without changing the current get point. while you should have a fixed end in beginning of any function which may use this multiple times
                                                    //while the reason why there isnt "const" is, it use a temp variant to regist the get point, so it's not const actually
    
    vector<vector<string>> _readAll();              //read all the base form file. return all the file by parts. rely on _read(). also change _cpn at the last
    vector<string> _read();                         //read a block which end up with "end" from current get position. https://cplusplus.com/doc/tutorial/files/ for more infomation if u forgot
                                                    //NOT all of these function geste the get/set point of _file, and _file.open is often in different mode
                                                    //make SURE that use always readALL() outside of itself 

    void _transfer(vector<string> part);            //convert a part start with classname/typename and end with "end" into _pool

    void _regist(void) { return; };	                //convert a member into part. regist the change of system into file in current get point.
    void _regist(bill bl);
    void _regist(person ps);
    void _regist(ID pl_id);                         //also change _cpn at the last, same as readAll

    void _registOne(void);                          //_regist can only be used by _rOne and _rAll, because they dont have _file.open() so they dont know it's ios in or out.
    void _registOne(bill bl);                       
    void _registOne(person ps);
    void _registOne(ID pl_id);
    void _registAll();                              //rOne() like push_back, it add a new part in the LAST of file. rAll overwrite the whole file.
    void virtual _refresh()=0;                      //used to be the name of rereadall, well it suppose to be a function only calling a physic engine's refresh function

    int _initTcsys();                               //initiale the system by importing the file(str) as datapool(LIST). rely on _readAll() so also _read() and _transfer()

    void _copy(string txt);                          //copy a text

    //streampos _locatepersonidlist(ID pl_id, IDENTITY idtt);

public:                                             
    tcsys();
    ~tcsys();

    //desorla, down-below here, for safety reason, unless you just drinked a coffee and you know what you are doing,
    //these user-level functions shall use only these _f inbetween all private functions : _readAll(), _registOne(any) and _registAll()  ...  maybe also _refresh()

    void newPerson(string firstname, string lastname, MONEY rcv = 0);//in current pool
    //void addPerson(ID id);
    void selectPerson(string firstname, string lastname);

    void unSelectPerson(string firstname, string lastname);
    void removePerson();
    //void deleteSelectedPerson(ID id);

    void clearSelectedPerson();
    void copyPersonalBill();//copy *selected* persons' bills



    //Event listed in pool and templist, no database. Class event is renamed as bill because it's actually a key word.

    void newEvent(MONEY seperate);
    void newEvent(MONEY total, unsigned int num);
    void fastNewEvent(MONEY total);

    void selectAllEvent();
    void selectOneEvent();

    void unSelectEvent();
    void deleteSelectedEvent();


    //Other system function.
    void newPool();
    void deletePool(ID pl_id);
    void switchPool(ID pl_id);

    void setExchangeRate(MONEY rate);
    //MONEY getExchangeRate() { return _exchangerate; };
    void exchange();
    //void reverseExchange();

    //void openConfigPage();
    //void openMainPage();
    //void openEventPage();
    //void openPersonPage();

    //void Undo();
    //void Redo();

};

