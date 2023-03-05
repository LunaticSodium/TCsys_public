#include "tcsys.h"

/*
File example :

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

streampos tcsys::_end()
{
	streampos g_current = _file.tellg();
	_file.seekg(0, ios::end);
	streampos end = _file.tellg();
	_file.seekg(g_current);
	return end;
}//finish

vector<string> tcsys::_read(fstream& file)
{
	string line;
	vector<string> part;												//whick start with class name and end with "end", all mini
	streampos part_start_line = -1;
	while (std::getline(file, line)) {
		if (!line.empty() && line != "end") {
			part_start_line = file.tellg();
			continue;
		}
		if (part_start_line != -1) {
			part.push_back(line);
			if (line == "end") break;
		}
	}
	return part;
}//finish

vector<vector<string>> tcsys::_readAll(string const file_name)
{
	vector<vector<string>> parts;
	fstream file;
	file.open(file_name, ios::in);
#ifdef DEBUG
	if (!file.is_open())
	{
		cout << "file " << file_name << " open failed\n";
		return parts;
	}
#endif // DEBUG
	streampos end = _end();
	//file.seekg(0, ios::beg);
	while (file.tellg() < end)parts.push_back(_read(file));
	file.close();
	return parts;
}//finish

void tcsys::_transfer(vector<string> const part)
{
	int i = 0;
	while (part[i].empty() && i < part.size() - 1) i++;					//jump over the empty line
	string part_type= part[i++];
	/*
	switch (part_type)													ONLY available for c++ 17+ to use switch with string. So c++ 14, by default, won't compile successfully
	{																	so we'll do it in the boring old way to make sure anyone can compile it
	case "bill":
	{
		ID trid = stoul(part[i++]);
		MONEY tramount = stof(part[i++]);
		string trname = part[i++];
		REVERSE trrvs = part[i++] == "true";
		string trcontest = part[i++];
		bill trbill(trid, tramount, trname, trrvs, trcontest);
		_p().blpool.push_back(trbill);
		break;
	}
	case "person":
	{
		IDENTITY tridtt(part[i++],part[i++]);
		MONEY trcapital = stof(part[i++]);
		stringstream ss(part[i++]);
		ID_LIST trid_list;
		int trid = -1;
		while (ss >> trid) trid_list.push_back(trid);
		person trperson(tridtt, trcapital, trid_list);
		_p().pspool.push_back(trperson);
		bool already_in_personbase = false;
		for (int j = 0; j < _personbase.size(); j++) if (_personbase[j].getIdentity() == tridtt) already_in_personbase = true;
		if (!already_in_personbase) _personbase.push_back(trperson);		//don't worry the capital or ss, we just use the name in person base
		break;
	}
	case "pool":
	{
		_cpn = stoi(part[i++]);
		break;
	}
	default:
	{
		cout << "key word " << part_type << " transfer failed";
		break;
	}
	while (part[i].empty() && i < part.size()) i++;
	if (part[i] != "end" && _file.tellg()<_end())
	{
		vector<string> nextpart(part.begin() + i, part.end());
		_transfer(nextpart);
	}
	return;
	*/

	PARTTYPE pt = PARTTYPE::DF;
	if (part_type == "bill") pt = PARTTYPE::BL;
	else if (part_type == "person") pt = PARTTYPE::PS;
	else if (part_type == "pool") pt = PARTTYPE::PL;
	switch (pt)
	{
		case PARTTYPE::BL:
		{
			ID trid = stoul(part[i++]);
			MONEY tramount = stof(part[i++]);
			string trname = part[i++];
			REVERSE trrvs = part[i++] == "1";
			string trcontest = part[i++];
			bill trbill(trid, tramount, trname, trrvs, trcontest);
			_p().blpool.push_back(trbill);
			break;
		}
		case PARTTYPE::PS:
		{
			IDENTITY tridtt(part[i++], part[i++]);
			MONEY trcapital = 0;
#ifndef CAPITAL_IGNORE
			trcapital = stof(part[i++]);
#endif // !CAPITAL_IGNORE.											As we def the CAP, trc is 0. remember that this would cause different datafile between ver def/ndef be UNCOMPATIBLE
			stringstream ss(part[i++]);
			ID_LIST trid_list;
			int trid = -1;
			while (ss >> trid) trid_list.push_back(trid);
			person trperson(tridtt, trcapital, trid_list);
			_p().pspool.push_back(trperson);
			bool already_in_personbase = false;
			for (const person& ps : _personbase) if (ps.getIdentity() == tridtt)	//for (int j = 0; j < _personbase.size(); j++) if (_personbase[j].getIdentity() == tridtt)
			{
				already_in_personbase = true;
			}
			if (!already_in_personbase) _personbase.push_back(trperson);		//don't worry the capital or ss, we just use the name in person base
			break;
		}
		case PARTTYPE::PL:
		{
			_cpn = stoi(part[i++]);
			break;
		}
		case PARTTYPE::DF:
		{
			cout << "key word " << part_type << " transfer failed\n";
			break;
		}
		default:
		{
			cout << " enum switcher error : PARTTYPE\n";
			break;
		}
	}
	while (part[i].empty() && i < part.size() - 1) i++;
	if (part[i] != "end" && _file.tellg()<_end())
	{
		vector<string> nextpart(part.begin() + i, part.end());
		_transfer(nextpart);
	}
	return;
}//finish



void tcsys::_regist(bill const bl)//i wish i have a generic type but i dont. I have no power here
{
	_file << "bill\n";
	_file << bl.getEventID() << '\n';
	_file << bl.getAmount() << '\n';
	_file << bl.getName() << '\n';
	_file << bl.doesReverse() << '\n';
	_file << bl.getContest() << '\n';
	_file << "end\n\n";
	return;
}//finish

void tcsys::_regist(person const ps)
{
	_file << "person\n";
	_file << ps.getIdentity().first << '\n';
	_file << ps.getIdentity().second << '\n';
#ifndef CAPITAL_IGNORE
	_file << ps.getCapital() << '\n';
#endif // !CAPITAL_IGNORE
	for (int i = 0; i < ps.getBills().size(); i++)
	{
		_file << ps.getBills()[i] << ' ';
	}
	_file << '\n';
	_file << "end\n\n";
	return;
}//finish

void tcsys::_regist(ID const pl_id)//will change the _cpn to pl_id
{
	_file << "pool\n";
	_file << pl_id << '\n';
	_file << "end\n\n";
	_cpn = pl_id;
	return;
}//finish

void tcsys::_registOne(void)//without Type T ,genetic or <any>.type(), which is totally a overkill, we use function overload. 
{
	if (_file.is_open()) _file.close();
	_file.open(DATA_FILE_NAME, ios::out | ios::app);
	_regist();
	_file.close();
	return;
}

void tcsys::_registOne(bill const bl)
{
	if (_file.is_open()) _file.close();
	_file.open(DATA_FILE_NAME, ios::out | ios::app);
	_regist(bl);
	_file.close();
	return;
}

void tcsys::_registOne(person const ps)
{
	if (_file.is_open()) _file.close();
	_file.open(DATA_FILE_NAME, ios::out | ios::app);
	_regist(ps);
	_file.close();
	return;
}

void tcsys::_registOne(ID const pl_id)
{
	if (_file.is_open()) _file.close();
	_file.open(DATA_FILE_NAME, ios::out | ios::app);
	_regist(pl_id);
	_file.close();
	return;
}

void tcsys::_registAll()
{
	ID cpn = _cpn;
	if (_file.is_open()) _file.close();
	_file.open(DATA_FILE_NAME, ios::out | ios::trunc);
	for (const POOL& pl : _pool)
	{										_regist(pl.pl_id);
		for (const person& ps : pl.pspool)	_regist(ps);
		for (const bill& bl : pl.blpool)	_regist(bl);
	}
	_regist(cpn);
	//_cpn = cpn;
	_file.close();
	return;
}//finish



int tcsys::_initTcsys()
{
	/*
	_file.open(DATA_FILE_NAME);
	if (!_file.is_open())
	{
		cout << "datafile open failed\n";
		return 1;
	}
	*/
	vector<vector<string>> parts = _readAll(DATA_FILE_NAME);
	for (int i = 0; i < parts.size(); i++) _transfer(parts[i]);
	_loadConfig();
	return 0;
}

int tcsys::_saveConfig()
{
	//if (_config_file.is_open()) _config_file.close();
	_config_file.open(CONFIG_FILE_NAME, ios::out);
#ifdef DEBUG
	if (!_config_file.is_open())
	{
		cout << "configfile open failed\n";
		return 1;
	}
#endif // DEBUG

	_config_file << "exchange_rate " << to_string(_config.exchange_rate) << '\n';
	_config_file << "is_exchanged " << to_string(_config.is_exchanged) << '\n';
	_config_file << "input_as_total " << to_string(_config.input_as_total) << '\n';
	_config_file << "bill_generate_as_pair " << to_string(_config.bill_generate_as_pair) << '\n';
	

	_config_file.close();
	return 0;
}//finish

int tcsys::_loadConfig()
{
	vector<vector<string>> parts = _readAll(CONFIG_FILE_NAME);
	vector<string> config_part = parts[0];
	string str; 
	for (const string config_line : config_part)
	{
		istringstream iss(config_line);
		string config_type;
		iss >> config_type;					//for the same reason in _transfer, we use if/else to compara string to avoid petential problem
		if (config_type == "exchange_rate")
		{
			iss >> str;
			_config.exchange_rate = stof(str);
		}
		else if (config_type == "is_exchanged")
		{
			iss >> str;
			_config.is_exchanged = (str == "1");
		}
		else if (config_type == "input_as_total")
		{
			iss >> str;
			_config.input_as_total = (str == "1");
		}
		else if (config_type == "bill_generate_as_pair")
		{
			iss >> str;
			_config.bill_generate_as_pair = (str == "1");
		}
		else
		{
			cout << "config_line " << config_line << " transfer failed\n";
		}
	}

	if (_config.is_exchanged) exchange();
	return 0;
}//finish


#ifndef ANDROID_DEPLOY
void tcsys::_copy(string txt)//copy in windows, rely on <Windows.h>
{
	if (!OpenClipboard(nullptr)) return;
	if (!EmptyClipboard()) {
		CloseClipboard();
		return;
	}
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, txt.size() + 1);
	if (!hMem) {
		CloseClipboard();
		return;
	}
	char* pMem = static_cast<char*>(GlobalLock(hMem));
	if (!pMem) {
		GlobalFree(hMem);
		CloseClipboard();
		return;
	}
	strcpy_s(pMem, COPY_LENGTH, txt.c_str());
	GlobalUnlock(hMem);
	if (!SetClipboardData(CF_TEXT, hMem)) {
		GlobalFree(hMem);
		CloseClipboard();
		return;
	}
	CloseClipboard();
	return;
}
#else
void tcsys::_copy(string txt)//copy in android
{
	return;
}
#endif // !ANDROID_DEPLOY



tcsys::tcsys()
{
	_config.exchange_rate = (MONEY)DEFAUTE_EXCHANGE_RATE;
	_config.is_exchanged = false;
	_config.input_as_total = false;

	_cpn = 0;
	_ursp = 0;

	_select = POOL();
	_pool = vector<POOL>();
	_undoredo = vector<POOL>();
	_personbase = PERSON_LIST();
	_initTcsys();
}//finish

tcsys::~tcsys()
{
	_registAll();
	_file.close();
}//finish



void tcsys::newPerson(string const firstname, string const lastname, MONEY const rcv)
{
	person ps(IDENTITY(firstname, lastname), rcv);
	_p().pspool.push_back(ps);
	_registOne(ps);
	return;
}//finish

void tcsys::selectPerson(string const firstname, string const lastname)
{
	bool already_selected = false;
	for (person& ps : _select.pspool) if (ps.getIdentity().first == firstname && ps.getIdentity().second == lastname)already_selected = true;;
	if (already_selected)return;
	for (person& ps : _p().pspool) if (ps.getIdentity().first == firstname && ps.getIdentity().second == lastname)_select.pspool.push_back(ps);
	return;
}//finish

void tcsys::unSelectPerson(string const firstname, string const lastname)
{
	for (int i = 0; i < _select.pspool.size(); i++) if (_select.pspool[i].getIdentity().first == firstname && _select.pspool[i].getIdentity().second == lastname)_select.pspool.erase(_select.pspool.begin() + i);
	return;
}//finish

void tcsys::removePerson()
{
	string firstname, lastname;
	for (person& pss : _select.pspool)
	{
		firstname = pss.getIdentity().first;
		lastname = pss.getIdentity().second;
		for (int i = 0; i < _p().pspool.size(); i++) if (_p().pspool[i].getIdentity().first == firstname && _p().pspool[i].getIdentity().second == lastname)_p().pspool.erase(_select.pspool.begin() + i);
	}
	_select.pspool.clear();
	_registAll();
	return;
}//finish

void tcsys::unSelectedAll()
{
	_select.pspool.clear();
	_select.blpool.clear();
	return;
}//finish

void tcsys::checkOutPerson()
{

}


void tcsys::copyPersonalBill()
{
	string firstname, lastname, bills;
	ID_LIST list;
	for (person& ps : _select.pspool)
	{
		firstname = ps.getIdentity().first;
		lastname = ps.getIdentity().second;
		for (person& ps : _p().pspool) if (ps.getIdentity().first == firstname && ps.getIdentity().second == lastname)
		{
			bills += ps.getIdentity().first + ' ' + ps.getIdentity().second + '\n';
			bills += ps.printBill(_p().blpool);
			/*
			list = ps.getBills();
			for (ID bl_id : list)
			{

			}*/
			bills += "capital total : " + to_string(ps.capital(_p().blpool)) + '\n';
#ifdef DEBUG
			cout << to_string(ps.capital(_p().blpool));
#endif // DEBUG
		}
	}
	_copy(bills);
#ifdef DEBUG
	cout << bills;
#endif // DEBUG
	return;
}//finish

void tcsys::newEvent(MONEY const amount, std::string const name, std::string const contest)
{
	const int num_selected = _select.pspool.size();
	const ID bl_id = _p().blpool.back().getEventID() + 1;
	string firstname, lastname;

	MONEY am = amount;
	if (_config.input_as_total)am = amount / num_selected;

	bill bl(bl_id, am, name, false, contest);
	_p().blpool.push_back(bl);

	for (person& psp : _p().pspool)
	{
		firstname = psp.getIdentity().first;
		lastname = psp.getIdentity().second;
		for (person& pss : _select.pspool) if (pss.getIdentity().first == firstname && pss.getIdentity().second == lastname)
		{
			psp.participe(bl);
			//unSelectPerson(firstname, lastname);
			break;
		}
	}

	if (_config.bill_generate_as_pair)
	{
		const int num_unselected = _p().pspool.size() - num_selected;
		bill blc = bill::generateEventCounter(_p().blpool, bl, num_selected, num_unselected);
		_p().blpool.push_back(blc);

		bool selected = false;
		for (person& psp : _p().pspool)
		{
			firstname = psp.getIdentity().first;
			lastname = psp.getIdentity().second;
			for (person& pss : _select.pspool) if (pss.getIdentity().first == firstname && pss.getIdentity().second == lastname)selected = true;
			if (!selected) psp.participe(blc);
		}
	}
	unSelectedAll();
	return;
}//finish

void tcsys::selectAllEvent()
{
	_select.blpool.clear();
	for (bill& bl : _p().blpool)_select.blpool.push_back(bl);
	return;
}//finish

void tcsys::selectOneEvent(ID const bl_id)
{
	bool already_selected = false;
	for (bill& bl : _select.blpool) if (bl.getEventID() == bl_id) already_selected = true;
	if (already_selected)return;
	for (bill& bl : _p().blpool) if (bl.getEventID()==bl_id)_select.blpool.push_back(bl);
	return;
}//finish

void tcsys::unSelectAllEvent()
{
	_select.blpool.clear();
	return;
}//finish

void tcsys::unSelectEvent(ID const bl_id)
{
	for (int i = 0; i < _select.blpool.size(); i++) if (_select.blpool[i].getEventID() == bl_id)_select.blpool.erase(_select.blpool.begin() + i);
	return;
}//finish

void tcsys::deleteSelectedEvent()
{
	ID bl_id;
	for (int i = 0; i < _select.blpool.size(); i++)
	{
		bl_id = _select.blpool[i].getEventID();
		for (int j = 0; j < _p().blpool.size(); j++)
		{
			if (_p().blpool[j].getEventID() == bl_id)
			{
				_p().blpool.erase(_p().blpool.begin() + j);
				//_select.blpool.erase(_select.blpool.begin() + i);
				continue;
			}
		}
	}
	_select.blpool.clear();
	_registAll();
	return;
}//finish

void tcsys::newPool()//new/deletePool has two ways to achieve, sequence & random. in /**/ is random, and here use sequence.
{
	POOL pl;
	/*
	bool unique;
	for (int i = 0; i < _pool.size() + 1; i++)//uniqueness detection
	{
		unique = true;
		for (int j = 0; j < _pool.size(); j++) if (_pool[j].pl_id == i)unique = false;
		if (unique)
		{
			pl.pl_id = i;
			break;
		}
	}
	*/
	pl.pl_id = _pool.size();
	_pool.push_back(pl);
	unSelectedAll();
	_registOne(pl.pl_id);
	return;
}//finish

void tcsys::deletePool(ID const pl_id)
{
	/*
	ID shift = 0;
	for (int i = 0; i < _pool.size(); i++) if (_pool[i].pl_id == pl_id) shift = i;
	_pool.erase(_pool.begin() + shift);
	if(_cpn == pl_id) _cpn=_pool[0].pl_id;
	*/
	_pool.erase(_pool.begin() + pl_id);
	for (POOL pl : _pool) if (pl.pl_id > pl_id) pl.pl_id -= 1;
	if (_cpn > pl_id) _cpn -= 1;
	unSelectedAll();
	return;
}//finish

void tcsys::switchPool(ID const pl_id)
{
	_registOne(pl_id);
	unSelectedAll();
	return;
}//finish

void tcsys::setExchangeRate(MONEY const rate)
{
	_config.exchange_rate = rate;
	return;
}//finish

void tcsys::exchange()
{
	for (POOL pl : _pool) for (bill bl : pl.blpool) bl.setAmount(bl.getAmount() * _config.exchange_rate);
	_config.exchange_rate = 1 / _config.exchange_rate;
	_config.is_exchanged = !_config.is_exchanged;
	return;
}//finish

