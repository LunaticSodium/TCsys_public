#pragma once
#include "reaction.h"
#include <fstream>
#include <iostream>
#include <sstream>

#define UNDOSTACKLENGTH 20
#define DATAFILENAME "data.txt"

using namespace std;

typedef struct {
    PERSON_LIST pspool;
    BILL_LIST blpool;
}POOL;

class tcsys :
    public reaction
{
private:
    PERSON_LIST _personbase;
    //POOL _currentpool;        //present by _p
    vector<POOL> _pool,_undoredo;
    ID _cpn,_ursp;              //current pool number and undo-redo stack position
    fstream _file;              //no caplock plz, all in mini. notice that the get & set point of file is, in fact, as global. make sure it's well defined in beginning
    POOL _p() { return _pool[_cpn]; };

    streampos _end();          //return the current end streampos without changing the current get point. while you should have a fixed end in beginning of any function which may use this multiple times

    vector<string> _read();     //read a block which end up with "end" from current get position. https://cplusplus.com/doc/tutorial/files/ for more infomation if u forgot
    void _write(string str);    

    vector<vector<string>> _reReadAll();//read all the base form file. return all the file by parts. rely on _read()	
	void _regist();	            //regist the change of system into file
    void _reflesh();            //used to be the name of rereadall, well it suppose to be a function only calling a physic engine's refresh function

    void _transfer(vector<string> part);//convert a part start with classname/typename and end with "end" into _pool

    int _initTcsys();           //initiale the system by importing the file(str) as datapool(LIST). rely on _rereadall() soalso _read(), and _transfer()


public:
    tcsys();
    ~tcsys();

    void newPerson(string firstname, string lastname, MONEY rcv = 0);
    void addPerson(ID id);
    void selectPerson(ID id);

    void unSelectPerson(ID id);
    void cancelPerson(ID id);
    void deleteSelectedPerson(ID id);

    void clearSelectedPerson();
    void copyPersonalBill();



    //Event listed in pool and templist, no database. Class event is renamed as bill because it's actually a key word.

    void newEvent();
    void fastNewEvent();

    void selectAllEvent();
    void selectOneEvent();

    void unSelectEvent();
    void deleteSelectedEvent();


    //Other system function.
    void newPool();
    void deletePool();

    void setExchangeRate();
    void exchange();
    void reverseExchange();

    void openConfigPage();
    void openMainPage();
    void openEventPage();
    void openPersonPage();

    void Undo();
    void Redo();

};

