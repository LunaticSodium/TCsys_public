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

/*
streampos tcsys::_end()
{
	streampos g_current = _file.tellg();
	_file.seekg(0, ios::end);
	streampos end = _file.tellg();
	_file.seekg(g_current);
	return end;
}//finish
*/
vector<string> tcsys::_read(ifstream& ifile)
{
	string line;
	vector<string> part;												//whick start with class name and end with "end", all mini
	//streampos part_start_line = -1;
	while (std::getline(ifile, line)) {
		if(!line.empty()) part.push_back(line);
#ifdef DEBUG
		std::cout << to_string(ifile.tellg()) << "\n";
#endif // DEBUG
		//if (!line.empty() && line != "end") {
			//part_start_line = ifile.tellg();
			//continue;
		//}
		//if (part_start_line != -1){		
			//part.push_back(line);
#ifdef DEBUG
		std::cout << line << "\n";
#endif // DEBUG
		//}
		if (line == "end") break;
	}
	while (line.empty())
	{
		std::getline(ifile, line);
		if (ifile.tellg() == -1) break;
	}
#ifdef DEBUG
	//cout << line << "\n";
#endif // DEBUG
	return part;
}//finish

vector<vector<string>> tcsys::_readAll(string const file_name)
{
	vector<vector<string>> parts;
	ifstream ifile;
	ifile.open(file_name, ios::in);
#ifdef DEBUG
	if (!ifile.is_open())
	{
		std::cout << "file " << file_name << " open failed\n";
		return parts;
	}
#endif // DEBUG
	//streampos g_current = ifile.tellg();
	ifile.seekg(0, ios::end);
	streampos end = ifile.tellg();
	//ifile.seekg(g_current);
	ifile.seekg(0, ios::beg);
	while (ifile.tellg() < end && ifile.tellg() != -1)
	{
		parts.push_back(_read(ifile));
#ifdef DEBUG
		std::cout << to_string(ifile.tellg()) << "\n" << to_string(end) << "\n";
#endif // DEBUG
	}
#ifdef DEBUG
	for (vector<string> vs : parts)
	{
		for (string st : vs)
		{
			std::cout << st << '\n';
		}
		std::cout << '\n';
	}
#endif // DEBUG
	ifile.close();
	return parts;
}//finish

const int tcsys::_datafileToTcsys(vector<string> const part)
{
	if (part.size() == 0)return 0;
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
		_datafileToTcsys(nextpart);
	}
	return;
	*/

	PART_TYPE pt = PART_TYPE::DF;
	if (part_type == "bill") pt = PART_TYPE::BL;
	else if (part_type == "person") pt = PART_TYPE::PS;
	else if (part_type == "pool") pt = PART_TYPE::PL;
	switch (pt)
	{
		case PART_TYPE::BL:
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
		case PART_TYPE::PS:
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
			person trperson(tridtt, trid_list);
#ifndef CAPITAL_IGNORE
			trperson.receiveConstuit(trcapital);
#endif // !CAPITAL_IGNORE
			_p().pspool.push_back(trperson);
			bool already_in_personbase = false;
			for (const person& ps : _personbase) if (ps.getIdentity() == tridtt)	//for (int j = 0; j < _personbase.size(); j++) if (_personbase[j].getIdentity() == tridtt)
			{
				already_in_personbase = true;
			}
			if (!already_in_personbase) _personbase.push_back(trperson);		//don't worry the capital or ss, we just use the name in person base
			break;
		}
		case PART_TYPE::PL:
		{
			ID pl_id = stoi(part[i++]);
			string name = part[i++];
			bool existence = false;
			for (POOL pl : _pool) if (pl.pl_id == pl_id) existence = true;
			if (!existence)
			{
				POOL new_pool;
				new_pool.pl_id = pl_id;
				new_pool.pl_name = name;
				_pool.push_back(new_pool);
			}
			_select.pl_id = pl_id;
			break;
		}
		case PART_TYPE::DF:
		{
			std::cout << "key word " << part_type << " transfer failed\n";
			break;
		}
		default:
		{
			std::cout << " enum switcher error : PART_TYPE\n";
			return 1;
			break;
		}
	}
	if (i < part.size() - 1)
	{
		while (part[i].empty() && i < part.size() - 1 && part.size()>1) i++;

		streampos g_current = _file.tellg();
		_file.seekg(0, ios::end);
		streampos end = _file.tellg();
		_file.seekg(g_current);

		if (part[i] != "end" && _file.tellg()<end)
		{
			vector<string> nextpart(part.begin() + i, part.end());
			_datafileToTcsys(nextpart);
		}
	}
	return 0;
}//finish


const int tcsys::_regist(bill const bl)//i wish i have a generic type but i dont. I have no power here
{
	_file << "bill\n";
	_file << bl.getEventID() << '\n';
	_file << bl.getAmount() << '\n';
	_file << bl.getName() << '\n';
	_file << bl.doesReverse() << '\n';
	_file << bl.getContest() << '\n';
	_file << "end\n\n";
	return 0;
}
const int tcsys::_regist(person const ps)
{
	_file << "person\n";
	_file << ps.getIdentity().first << '\n';
	_file << ps.getIdentity().second << '\n';
#ifndef CAPITAL_IGNORE
	_file << ps.getCapital() << '\n';
#endif // !CAPITAL_IGNORE
	_file << ' ';
	for (int i = 0; i < ps.getBills().size(); i++)
	{
		_file << ps.getBills()[i] << ' ';
	}
	_file << '\n';
	_file << "end\n\n";
	return 0;
}
const int tcsys::_regist(ID const pl_id)//will change the _cpn to pl_id
{
	_file << "pool\n";
	_file << pl_id << '\n';
	_file << _pool[pl_id].pl_name << '\n';
	_file << "end\n\n";
	_select.pl_id = pl_id;
	return 0;
}

const int tcsys::_registOne()//without Type T ,genetic or <any>.type(), which is totally a overkill, we use function overload. 
{
	if (_file.is_open()) _file.close();
	_file.open(DATA_FILE_NAME, ios::out | ios::app);
	_regist();
	_file.close();
	return 0;
}
const int tcsys::_registOne(bill const bl)
{
	if (_file.is_open()) _file.close();
	_file.open(DATA_FILE_NAME, ios::out | ios::app);
	_regist(bl);
	_file.close();
	return 0;
}
const int tcsys::_registOne(person const ps)
{
	if (_file.is_open()) _file.close();
	_file.open(DATA_FILE_NAME, ios::out | ios::app);
	_regist(ps);
	_file.close();
	return 0;
}
const int tcsys::_registOne(ID const pl_id)
{
	if (_file.is_open()) _file.close();
	_file.open(DATA_FILE_NAME, ios::out | ios::app);
	_regist(pl_id);
	_file.close();
	return 0;
}

const int tcsys::_registAll()
{
	ID cpn = _select.pl_id;
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
	return 0;
}//finish

#ifndef ANDROID_DEPLOY
const int tcsys::_copy(string txt)//copy in windows, rely on <Windows.h>
{
	if (!OpenClipboard(nullptr)) return 5;
	if (!EmptyClipboard()) {
		CloseClipboard();
		return 1;
	}
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, txt.size() + 1);
	if (!hMem) {
		CloseClipboard();
		return 2;
	}
	char* pMem = static_cast<char*>(GlobalLock(hMem));
	if (!pMem) {
		GlobalFree(hMem);
		CloseClipboard();
		return 3;
	}
	strcpy_s(pMem, COPY_LENGTH, txt.c_str());
	GlobalUnlock(hMem);
	if (!SetClipboardData(CF_TEXT, hMem)) {
		GlobalFree(hMem);
		CloseClipboard();
		return 4;
	}
	CloseClipboard();
	return 0;
}
#else
void tcsys::_copy(string txt)//copy in android
{
	return;
}
#endif // !ANDROID_DEPLOY

const int tcsys::initTcsys()
{
#ifdef DEBUG
	_file.open(DATA_FILE_NAME,ios::out | ios::app);
	if (!_file.is_open())
	{
		std::cout << "datafile open failed\n";
		return 1;
	}
	_file.close();

	_file.open(CONFIG_FILE_NAME, ios::out | ios::app);
	if (!_file.is_open())
	{
		std::cout << "configfile open failed\n";
		return 2;
	}
	_file.close();
#endif // DEBUG

	vector<vector<string>> parts = _readAll(DATA_FILE_NAME);
	if (parts.empty())
	{
		POOL pl;
		pl.pl_id = 0;
		_pool.push_back(pl);
		_registOne(pl.pl_id);
	}
	for (int i = 0; i < parts.size(); i++) if(!parts[i].empty()) _datafileToTcsys(parts[i]);
	_loadConfig();
	return 0;
}

const int tcsys::_saveConfig()
{
	//if (_config_file.is_open()) _config_file.close();
	_config_file.open(CONFIG_FILE_NAME, ios::out | ios::trunc);
#ifdef DEBUG
	if (!_config_file.is_open())
	{
		std::cout << "configfile open failed\n";
		return 1;
	}
#endif // DEBUG

	_config_file << "exchange_rate " << to_string(_config.exchange_rate) << '\n';
	_config_file << "is_exchanged " << to_string(_config.is_exchanged) << '\n';
	_config_file << "input_as_total " << to_string(_config.input_as_total) << '\n';
	_config_file << "bill_generate_as_pair " << to_string(_config.bill_generate_as_pair) << '\n';
	
	_config_file << "end\n";

	_config_file.close();
	return 0;
}//finish

const int tcsys::_loadConfig()
{
	vector<vector<string>> parts = _readAll(CONFIG_FILE_NAME);
	if (parts.empty())
	{
#ifdef DEBUG
		std::cout << "config file is empty\n";
#endif // DEBUG
		_saveConfig();
		return 0;
		vector<vector<string>> parts = _readAll(CONFIG_FILE_NAME);
	}
	vector<string> config_part = parts.back();
	string str; 
	for (const string config_line : config_part)
	{
		istringstream iss(config_line);
		string config_type;
		iss >> config_type;					//for the same reason in _datafileToTcsys, we use if/else to compara string to avoid petential problem
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
		else if (config_type == "end")
		{
			break;
		}
		else
		{
			std::cout << "config_line " << config_line << " transfer failed\n";
			//return 1;
		}
	}

	if (_config.is_exchanged) exchange();
	return 0;
}//finish


tcsys::tcsys()
{
	_config.exchange_rate = DEFAUTE_EXCHANGE_RATE;
	_config.is_exchanged = false;
	_config.input_as_total = false;

	_select.pl_id = 0;
	_ursp = 0;
	/*
	_select = POOL{};
	_pool = vector<POOL>{};
	_undoredo = vector<POOL>{};
	_personbase = PERSON_LIST{};
	*/
}
tcsys::~tcsys()
{

}
const int tcsys::save()
{
	_registAll();
	_file.close();
	return 0;
}
//finish


const int tcsys::newPerson(string const firstname, string const lastname, MONEY const rcv)
{

	person ps(IDENTITY(firstname, lastname));
	//ps.receiveConstuit(rcv);
	if (rcv != 0)ps.participe(newEvent(rcv, "pre paid", "rcv for new person"));
	_p().pspool.push_back(ps);
	_registOne(ps);
	return 0;
}

const int tcsys::selectPerson(string const firstname, string const lastname)
{
	bool already_selected = false;
	bool success = false;
	for (person& ps : _select.pspool) if (ps.getIdentity().first == firstname && ps.getIdentity().second == lastname)already_selected = true;;
	if (already_selected)return 1;
	for (person& ps : _p().pspool) if (ps.getIdentity().first == firstname && ps.getIdentity().second == lastname)
	{
		_select.pspool.push_back(ps);
		success = true;
	}
	if (!success) return 2;
	return 0;
}

const int tcsys::unSelectPerson(string const firstname, string const lastname)
{
	bool success = false;
	for (int i = 0; i < _select.pspool.size(); i++) if (_select.pspool[i].getIdentity().first == firstname && _select.pspool[i].getIdentity().second == lastname)
	{
		_select.pspool.erase(_select.pspool.begin() + i);
		success = true;
	}
	if (!success) return 1;
	return 0;
}

const int tcsys::removePerson()
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
	return 0;
}

const int tcsys::unselectAll()
{
	_select.pspool.clear();
	_select.blpool.clear();
	return 0;
}

const int tcsys::printPersonList()
{
	std::cout << "\n";
	for (person ps : _p().pspool) std::cout << ps.getIdentity().first << ' ' << ps.getIdentity().second << '\n';
	std::cout << "\n";
	return 0;
}

const int tcsys::checkoutPerson()
{
	if (_select.pspool.empty()) return 1;
	else for (person ps : _select.pspool)
	{
		ID_LIST idl = ps.getBills();
		int success = 0;
		for (int id : idl)
		{
			 success += ps.deParticipe(id);
		}
		if (success != 0) return 1;
	}
	return 0;
}


const int tcsys::copyPersonalBill()
{
	if (_select.pspool.empty()) return 1;
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
			MONEY mn = ps.getCapital(_p().blpool);
			if (mn != 0) bills += "capital total : " + to_string(mn) + '\n';
#ifdef DEBUG
			std::cout << to_string(ps.getCapital(_p().blpool));
#endif // DEBUG
		}
	}
	_copy(bills);
#ifdef DEBUG
	std::cout << bills;
#endif // DEBUG
	return 0;
}

const int tcsys::printPersonalBill()
{
	if (_select.pspool.empty()) return 1;
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
			MONEY mn = ps.getCapital(_p().blpool);
			if (mn != 0) bills += "capital total : " + to_string(mn) + '\n';
		}
	}
	cout << bills;
	return 0;
}

const int tcsys::newEvent(MONEY const amount, std::string const name, std::string const contest, bool single)
{
	const int num_selected = _select.pspool.size();
	ID bl_id = 0;
	if (!_p().blpool.empty()) bl_id = _p().blpool.back().getEventID() + 1;
	string firstname, lastname;

	MONEY am = amount;
	if (_config.input_as_total)am = amount / num_selected;

	bill bl(bl_id, am, name, false, contest);
	_p().blpool.push_back(bl);
	_registOne(bl);

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
	
	const int num_unselected = _p().pspool.size() - num_selected;

	if (_config.bill_generate_as_pair && !single && num_unselected > 0)
	{
		bill blc = bill::generateEventCounter(_p().blpool, bl, num_selected, num_unselected);
		_p().blpool.push_back(blc);
		_registOne(blc);

		bool selected = false;
		for (person& psp : _p().pspool)
		{
			firstname = psp.getIdentity().first;
			lastname = psp.getIdentity().second;
			for (person& pss : _select.pspool) if (pss.getIdentity().first == firstname && pss.getIdentity().second == lastname)selected = true;
			if (!selected) psp.participe(blc);
		}
	}

	unselectAll();
	_registAll();
	return 0;
}

const int tcsys::selectAllEvent()
{
	_select.blpool.clear();
	for (bill& bl : _p().blpool)_select.blpool.push_back(bl);
	return 0;
}//finish

const int tcsys::selectOneEvent(ID const bl_id)
{
	bool already_selected = false;
	for (bill& bl : _select.blpool) if (bl.getEventID() == bl_id) already_selected = true;
	if (already_selected)return 1;
	for (bill& bl : _p().blpool) if (bl.getEventID()==bl_id)_select.blpool.push_back(bl);
	return 0;
}//finish

const int tcsys::unselectAllEvent()
{
	_select.blpool.clear();
	return 0;
}//finish

const int tcsys::unselectEvent(ID const bl_id)
{
	for (int i = 0; i < _select.blpool.size(); i++) if (_select.blpool[i].getEventID() == bl_id)_select.blpool.erase(_select.blpool.begin() + i);
	return 0;
}//finish

const int tcsys::deleteSelectedEvent()
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
	return 0;
}//finish

const int tcsys::newPool()//new/deletePool has two ways to achieve, sequence & random. in /**/ is random, and here use sequence.
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
	unselectAll();
	_registOne(pl.pl_id);
	return 0;
}//finish
const int tcsys::deletePool(ID const pl_id)
{
	/*
	ID shift = 0;
	for (int i = 0; i < _pool.size(); i++) if (_pool[i].pl_id == pl_id) shift = i;
	_pool.erase(_pool.begin() + shift);
	if(_cpn == pl_id) _cpn=_pool[0].pl_id;
	*/
	_pool.erase(_pool.begin() + pl_id);
	for (POOL pl : _pool) if (pl.pl_id > pl_id) pl.pl_id -= 1;
	if (_select.pl_id > pl_id) _select.pl_id -= 1;
	unselectAll();
	return 0;
}
const int tcsys::namerPool(string name)
{
	_p().pl_name = name;
	return 0;
}
const int tcsys::switchPool(ID const pl_id)
{
	_registOne(pl_id);
	unselectAll();
	return 0;
}//finish

const int tcsys::setExchangeRate(MONEY const rate)
{
	_config.exchange_rate = rate;
	return 0;
}//finish

const int tcsys::exchange()
{
	for (POOL pl : _pool) for (bill bl : pl.blpool) bl.setAmount(bl.getAmount() * _config.exchange_rate);
	_config.exchange_rate = 1 / _config.exchange_rate;
	_config.is_exchanged = !_config.is_exchanged;
	return 0;
}//finish

const int tcsys::setConfig(CONFIG_TYPE const ct, bool const target)
//void tcsys::setConfig(int const ct, bool const target)
{
	switch (ct)
	{
	case IAT:
		_config.input_as_total = target;
		break;
	case BGAP:
		_config.bill_generate_as_pair = target;
		break;
	default:
#ifdef DEBUG
		std::cout << " enum switcher error : CONFIG_TYPE\n";
#endif // DEBUG
		break;
	}
	_saveConfig();
	return 0;
}

tcsys& tcsys::operator=(const tcsys& target)
{
	if (this == &target) return *this;
	_personbase=target._personbase;
	_select=target._select;
	_pool = target._pool;
	_undoredo = target._undoredo;
	_ursp = target._ursp;
	_config = target._config;
	return *this;
}

const int tcsys::help()
{
	std::cout << HELP;
	return 0;
}


