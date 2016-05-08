/**
 * @brief Zawera wystąpienia wszystkich metod obiektu Ts3API
 * @file Ts3API.cpp
 */

#include "Ts3API.hpp"

using namespace std;

Ts3API::Ts3API(struct serverConfig config) : config(config) 
{
	logerAddInfo("Pomyślnie utworzono obiekt API");
    setName(config.nickname);
}

bool Ts3API::executeCommand(const string &command) 
{
	string returnedValue = "ERROR";
	return sock.sendMessage(returnedValue, command);
}

bool Ts3API::executeCommand(map<string, string>& returnedMap, const string& command) 
{
	returnedMap.clear(); string returnedValue;
	
	if(sock.sendMessage(returnedValue, command))    split(returnedMap, returnedValue);
	else                                            return false;
	return true;
}

bool Ts3API::executeCommand(map<string, map<string, string>> &returnedMap, string mapIndex, const string &command) 
{
	string returnedValue; returnedMap.clear();
	
	if(sock.sendMessage(returnedValue, command))    split(returnedMap, mapIndex, returnedValue);
	else                                            return false;
	return true;
}

bool Ts3API::executeCommand(map<string, struct clientInfo> &returnedMap, string mapIndex, const string &command) 
{
	string returnedValue; returnedMap.clear();
	
	if(sock.sendMessage(returnedValue, command))    split(returnedMap, mapIndex, returnedValue);
	else                                            return false;
	return true;
}

bool Ts3API::executeCommand(clientInfo &returnedStruct, const string &command) 
{
	string returnedValue = "ERROR"; returnedStruct.clear();
	
	if(sock.sendMessage(returnedValue, command))    split(returnedStruct.info, returnedValue);
	else                                            return false;
	return true;
}

bool Ts3API::trystoi(string str, int& returnedValue)
{
	try 
	{
		returnedValue = stoi(str, nullptr);
		return true;
	}
	catch (invalid_argument) 
	{
		logerAddWarrning("Konwersja ciągu znaków na liczbę nie powiodła się.");
		return false;
	}
}

bool Ts3API::trystoi(string str, unsigned int& returnedValue)
{
	try 
	{
		int returnedInt = stoi(str, nullptr);
        
		if(returnedInt < 0)     returnedValue = 0;
		else                    returnedValue = returnedInt;
        
		return true;
	}
	catch (invalid_argument) 
	{
		logerAddWarrning("Konwersja ciągu znaków na liczbę nie powiodła się.");
		return false;
	}
}

void Ts3API::split(map<string, string>& returnedMap, string &input)
{
	size_t pos = 0, buffPos = 0;
	regex wzorzec("(.+)=(.+(=)*)"); smatch wynik;
	string buffer;


	if ((pos = input.find(" ")) != string::npos) 
	{
		input.append(" ");
		buffer.insert(0, input, 0, pos);
		sock.stringDecode(buffer);
		
		if (regex_search(buffer, wynik, wzorzec)) returnedMap[wynik[1]] = wynik[2];
		
		buffer.clear();
		buffPos = pos;
		while ((pos = input.find(" ", pos + 1)) != string::npos) {
			buffer.insert(0, input, buffPos + 1, pos - buffPos - 1);
			sock.stringDecode(buffer);
			
			if (regex_search(buffer, wynik, wzorzec)) returnedMap[wynik[1]] = wynik[2];
			
			buffer.clear();
			buffPos = pos;
		}
	}
	else 
	{
		sock.stringDecode(input);
		
		if (regex_search(input, wynik, wzorzec)) returnedMap[wynik[1]] = wynik[2];
	}
	input.erase(input.length() -1, 1);
}

void Ts3API::split(clientInfo &returnedStruct, string &input) 
{
	split(returnedStruct.info, input);
}

void Ts3API::split(map<string, map<string, string>>& returnedMap, string mapIndex, string &input)
{
	map<string, string> bufferMap;
	size_t buffPos = 0, pos = 0;
	string buffer;

	if (mapIndex == "auto") 
	{
		int index = 0;
		if ((pos = input.find("|")) != string::npos) 
		{
			input.append("|");

			buffer.insert(0, input, 0, pos);
			split(bufferMap, buffer);
			returnedMap[to_string(index)] = bufferMap;
			buffer.clear();
			index++;
			buffPos = pos;
			while ((pos = input.find("|", pos + 1)) != string::npos) {
				buffer.insert(0, input, buffPos + 1, pos - buffPos - 1);
				split(bufferMap, buffer);
				returnedMap[to_string(index)] = bufferMap;
				buffer.clear();
				index++;
				buffPos = pos;
			}
		}
		else 
		{
			split(bufferMap, input);
			returnedMap["0"] = bufferMap;
		}
		input.erase(input.length() -1, 1);
		return;
	}
	else 
	{
		if ((pos = input.find("|")) != string::npos) 
		{
			input.append("|");

			buffer.insert(0, input, 0, pos);
			split(bufferMap, buffer);
			if (bufferMap[mapIndex] == "") {
				logerAddWarrning("Próbowano zwinąć mapę z nieistniejącym lub pustym indeksem. index: " + mapIndex);
				input.erase(input.length() -1, 1);
				return;
			}
			returnedMap[bufferMap[mapIndex]] = bufferMap;
			buffer.clear();
			buffPos = pos;
			while ((pos = input.find("|", pos + 1)) != string::npos) {
				buffer.insert(0, input, buffPos + 1, pos - buffPos - 1);
				if (bufferMap[mapIndex] == "") {
					logerAddWarrning("Próbowano zwinąć mapę z nieistniejącym lub pustym indeksem. index: " + mapIndex);
					input.erase(input.length() -1, 1);
					return;
				}
				split(bufferMap, buffer);
				returnedMap[bufferMap[mapIndex]] = bufferMap;
				buffer.clear();
				buffPos = pos;
			}
			input.erase(input.length() -1, 1);
			return;
		}
		else 
		{
			split(bufferMap, input);
			returnedMap["0"] = bufferMap;
		}
	}
}

void Ts3API::split(map<string, struct clientInfo>& returnedMap, string mapIndex, string &input)
{
	map<string, string> bufferMap;
	size_t buffPos = 0, pos = 0;
	string buffer;

	if (mapIndex == "auto") 
	{
		int index = 0;
		if ((pos = input.find("|")) != string::npos) 
		{
			input.append("|");

			buffer.insert(0, input, 0, pos);
			split(bufferMap, buffer);
			returnedMap[to_string(index)].info = bufferMap;
			returnedMap[to_string(index)].api = this;
			buffer.clear();
			index++;
			buffPos = pos;
			
			while ((pos = input.find("|", pos + 1)) != string::npos) {
				buffer.insert(0, input, buffPos + 1, pos - buffPos - 1);
				split(bufferMap, buffer);
				returnedMap[to_string(index)].info = bufferMap;
				returnedMap[to_string(index)].api = this;
				buffer.clear();
				index++;
				buffPos = pos;
			}
			
		}
		else 
		{
			split(bufferMap, input);
			returnedMap["0"].info = bufferMap;
			returnedMap["0"].api = this;
		}
		input.erase(input.length() -1, 1);
		return;
	}
	else 
	{
		if ((pos = input.find("|")) != string::npos) 
		{
			input.append("|");

			buffer.insert(0, input, 0, pos);
			split(bufferMap, buffer);
			if (bufferMap[mapIndex] == "") {
				logerAddWarrning("Próbowano zwinąć mapę z nieistniejącym lub pustym indeksem. index: " + mapIndex);
				input.erase(input.length() -1, 1);
				return;
			}
			returnedMap[bufferMap[mapIndex]].info = bufferMap;
			returnedMap[bufferMap[mapIndex]].api = this;
			buffer.clear();
			buffPos = pos;
			while ((pos = input.find("|", pos + 1)) != string::npos) {
				buffer.insert(0, input, buffPos + 1, pos - buffPos - 1);
				if (bufferMap[mapIndex] == "") {
					logerAddWarrning("Próbowano zwinąć mapę z nieistniejącym lub pustym indeksem. index: " + mapIndex);
					input.erase(input.length() -1, 1);
					return;
				}
				split(bufferMap, buffer);
				returnedMap[bufferMap[mapIndex]].info = bufferMap;
				returnedMap[bufferMap[mapIndex]].api = this;
				buffer.clear();
				buffPos = pos;
			}
			input.erase(input.length() -1, 1);
			return;
		}
		else
		{
			split(bufferMap, input);
			returnedMap["0"].info = bufferMap;
			returnedMap["0"].api = this;
		}
	}
}

timeStruct Ts3API::convertTime(string strTime) 
{
	int time;
	timeStruct returnedStruct;
	trystoi(strTime, time);
	returnedStruct.years = time/31536000;
	returnedStruct.months = time/2592000;
	returnedStruct.days = time/86400;
	returnedStruct.hours = (time-returnedStruct.days*86400)/3600;
	returnedStruct.minutes = (time - (returnedStruct.days*86400 + returnedStruct.hours*3600))/60;
	returnedStruct.seconds = time - (returnedStruct.days*86400 + returnedStruct.hours*3600 + returnedStruct.minutes*60);
	return returnedStruct;
	
}

string Ts3API::convertTimestampTime(string timestamp) 
{
	int timestampint;
	if(!trystoi(timestamp, timestampint)) logerAddWarrning("Nie udało się zamienić typu string na int. convertTimetampTime()");
	
	time_t timet = time_t(timestampint);
	
	tm *t = localtime(&timet);
	
	return to_string(t->tm_mday) + "." + to_string(t->tm_mon) + "." + to_string(t->tm_year) + " " + to_string(t->tm_hour) + "." + to_string(t->tm_min); 
}

string Ts3API::convertTimeToStr(timeStruct tStruct) 
{
	string buffer;
	
	// Dni
	if(tStruct.days < 2)    buffer = to_string(tStruct.days) + " dzień ";
	else                    buffer = to_string(tStruct.days) + " dni ";
	
	// Godziny
	if(tStruct.hours < 2)       buffer += to_string(tStruct.hours) + " godzinę ";
	else if(tStruct.hours < 5)  buffer += to_string(tStruct.hours) + " godziny ";
	else                        buffer += to_string(tStruct.hours) + " godzin ";
	
	// Minuty
	if(tStruct.minutes < 2)         buffer += to_string(tStruct.minutes) + " minutę ";
	else if(tStruct.minutes < 5)    buffer += to_string(tStruct.minutes) + " minuty ";
	else                            buffer += to_string(tStruct.minutes) + " minut ";
	
	// Sekundy
	if(tStruct.seconds < 2)         buffer += to_string(tStruct.seconds) + " sekundę ";
	else if(tStruct.seconds < 5)    buffer += to_string(tStruct.seconds) + " sekundy ";
	else                            buffer += to_string(tStruct.seconds) + " sekund ";
	
	if(tStruct.months > 0) // Miesiące
	{
		if(tStruct.months < 2)      buffer = to_string(tStruct.months) + " miesiąc " + buffer;
		else if(tStruct.months < 5) buffer = to_string(tStruct.months) + " miesiące " + buffer;
		else                        buffer = to_string(tStruct.months) + " miesięcy " + buffer;
		
		if(tStruct.years > 0) // Lata
		{
			if(tStruct.years < 2)       buffer = to_string(tStruct.years) + " rok " + buffer;
			else if(tStruct.years < 5)  buffer = to_string(tStruct.years) + " lata " + buffer;
			else                        buffer = to_string(tStruct.years) + " lat " + buffer;
		}
	}
	return buffer;
}

bool Ts3API::getServerClientList(map<string, map<string, string>> &returnedMap, const string &mapIndex, const string &flags) 
{
	returnedMap.clear();
	return executeCommand(returnedMap, mapIndex, "clientlist " + flags);
}

bool Ts3API::getServerClientList(map<string, struct clientInfo> &returnedMap, const string &mapIndex, const string &flags) 
{
	returnedMap.clear();
	return executeCommand(returnedMap, mapIndex, "clientlist " + flags);
}

bool Ts3API::getChannelClientList(map<string, clientInfo> &returnedStruct, string const &channelId, string const &mapIndex, string const &flags) 
{
	map<string, clientInfo> clientList;
	if(getServerClientList(clientList, mapIndex, flags)) 
	{
		for(map<string, clientInfo>::iterator it = clientList.begin(); it != clientList.end(); it++) {
			if(it->second["cid"] == channelId) returnedStruct[it->first] = it->second;
		}
		return true;
	}
	return false;
}

bool Ts3API::sendMessage(string message, int target, short targetmode) 
{
	string recv;
	sock.stringEncode(message);
	return sock.sendMessage(recv, "sendtextmessage targetmode=" + to_string(targetmode) + " target=" + to_string(target) + " msg=" + message);
}

bool Ts3API::pokeClient(unsigned int id, string msg) 
{
	sock.stringEncode(msg);
	return executeCommand("clientpoke clid=" + to_string(id) + " msg=" + msg);
}

bool Ts3API::getClientInfo(clientInfo &returnedStruct, unsigned int clid) 
{
	if(executeCommand(returnedStruct, "clientinfo clid=" + to_string(clid)))    returnedStruct["clid"] = to_string(clid);
    else                                                                        return false;
    return true;
}

bool Ts3API::getClientInfo(map<string, string> &returnedMap, unsigned int clid) 
{
	if(executeCommand(returnedMap, "clientinfo clid=" + to_string(clid)))   returnedMap["clid"] = to_string(clid);
    else                                                                    return false;
    return true;
}

bool Ts3API::getServerInfo(serverInfo &returnedStruct) 
{
	if(executeCommand(returnedStruct.info, "serverinfo"))   returnedStruct.api = this;
    else                                                    return false;
    return true;
}

bool Ts3API::clientKickFromServer(unsigned int clid, string message) 
{
	sock.stringEncode(message);
	return executeCommand("clientkick clid=" + to_string(clid) + " reasonid=5 reasonmsg=" + message);
}

bool Ts3API::clientKickFromChannel(unsigned int clid, string message) 
{
	sock.stringEncode(message);
	return executeCommand("clientkick clid=" + to_string(clid) + " reasonid=4 reasonmsg=" + message);
}

bool Ts3API::getServerGroupClientList(map<string, clientInfo> &returnedStruct, unsigned int id, string mapIndex, bool names) 
{
	if(names)   return executeCommand(returnedStruct, mapIndex, "servergroupclientlist sgid=" + to_string(id) + " -names");
	else        return executeCommand(returnedStruct, mapIndex, "servergroupclientlist sgid=" + to_string(id));
	return false;
}

bool Ts3API::clientGetIds(struct clientInfo &returnedStruct, string uid) 
{
	return executeCommand(returnedStruct, "clientgetids cluid=" + uid);
}

bool Ts3API::clientGetIds(map<string, string> &returnedMap, string uid) 
{
	return executeCommand(returnedMap, "clientgetids cluid=" + uid);
}

bool Ts3API::getClientNameFromUid(struct clientInfo &returnedStruct, string uid) 
{
	return executeCommand(returnedStruct, "clientgetdbidfromuid cluid=" + uid);
}

bool Ts3API::getClientNameFromDbid(struct clientInfo &returnedStruct, unsigned int dbid) 
{
	return executeCommand(returnedStruct, "clientgetdbidfromdbid cldbid=" + dbid);
}

bool Ts3API::getClientNameFromDbid(map<string, string> &returnedMap, unsigned int dbid) 
{
	return executeCommand(returnedMap, "clientgetdbidfromdbid cldbid=" + dbid);
}

bool Ts3API::whoAmi(map<string, string> &returnedMap) {
    return executeCommand(returnedMap, "whoami");
}

bool Ts3API::setName(string name) {
    return executeCommand("clientupdate client_nickname=" + name);
}


// struct clientInfo
bool clientInfo::sendMessage(const string &message) 
{
	if(!checkApi()) return false;

	return api->sendMessage(message, getClid(), 1);
}

bool clientInfo::empty() 
{
	return info.empty();
}

string& clientInfo::operator[](const string &name) 
{
	return info[name];
}

bool clientInfo::operator==(struct clientInfo clientStruct) {
    if((!clientStruct["cluid"].empty() && !info["cluid"].empty()) && (clientStruct["cluid"] == info["cluid"])) 
        return true;
    if((!clientStruct["client_unique_identifier"].empty() && !info["client_unique_identifier"].empty()) && (clientStruct["client_unique_identifier"] == info["client_unique_identifier"])) 
        return true;
    
    if((!clientStruct["clid"].empty() && !info["clid"].empty()) && (clientStruct["clid"] == info["clid"])) {
        if((!clientStruct["cluid"].empty() && !info["cluid"].empty()) && (clientStruct["cluid"] == info["cluid"])) 
            return true;
        else if((!clientStruct["client_unique_identifier"].empty() && !info["client_unique_identifier"].empty()) && (clientStruct["client_unique_identifier"] == info["client_unique_identifier"]))
            return true;
        else if((!clientStruct["client_nickname"].empty() && !info["client_nickname"].empty()) && (clientStruct["client_nickname"] == info["client_nickname"])) 
            return true;
    }
    return false;
}

void clientInfo::clear() 
{
	info.clear();
}

bool clientInfo::kickFromServer(const string &msg) 
{
	if(!checkApi()) return false;
	
	int clid;
	if(api->trystoi(info["clid"], clid)) {
		if(api->clientKickFromServer(clid, msg)) {
			clear();
			return true;
		}
	}else {
		return false;
	}
	return false;
}

bool clientInfo::kickFromChannel(const string &msg) 
{
	if(!checkApi()) return false;
	
	int clid;
	if(api->trystoi(info["clid"], clid)) {
		return api->clientKickFromChannel(clid, msg);
	}else {
		return false;
	}
}

timeStruct clientInfo::getTime(string key) 
{
	if(!checkApi()) return *(new timeStruct);
	
	return api->convertTime(info[key]);
}

string clientInfo::getStrTime(string key) 
{
	if(!checkApi()) return  "";
	
	return api->convertTimeToStr(api->convertTime(info[key]));
}

string clientInfo::getTimestampTime(string key) 
{
	if(!checkApi()) return "";
	
	return api->convertTimestampTime(info[key]);
}

unsigned int clientInfo::getClid() 
{
	if(!checkApi()) return 0;
    
	string uid;
	unsigned int intBuffer; clientInfo clientInfoBuffer;
	
	//CLID
	if(!info["clid"].empty())
	{
		return (api->trystoi(info["clid"], intBuffer))? intBuffer : 0;
	}
    /*
    // DBID
	else if(!info["cldbid"].empty())
	{ 
		if(api->trystoi(info["cldbid"], intBuffer)) api->getClientNameFromDbid(clientInfoBuffer, intBuffer);
		else                                        return 0;
        
       // for(map<string, string>::iterator it = clientInfoBuffer.info.begin(); it != clientInfoBuffer.info.end(); it++) {
            //cout << " [ " << it->first << " ] => " << it->second << endl;
      //  }
        //sleep(50);
		
		infoUpdate(clientInfoBuffer["client_unique_identifier"]);
        
         for(map<string, string>::iterator it = info.begin(); it != info.end(); it++) {
            cout << " [ " << it->first << " ] => " << it->second << endl;
        }
        cout << "TUTAJ" << endl;
        sleep(50);
		
		return (api->trystoi(info["clid"], intBuffer))? intBuffer : 0;
	}
     */
	//UID
	else if((uid = getUid()) != "NULL")
	{ 
        if(!info["clid"].empty()) return getClid();
        
		if(api->clientGetIds(info, uid))    return (api->trystoi(info["clid"], intBuffer))? intBuffer : 0;
        else                                return 0;
	}
	return 0;
}

string clientInfo::getUid() 
{
	if(!checkApi()) return "";
	
	if(!info["cluid"].empty())                          return info["cluid"];
	else if(!info["client_unique_identifier"].empty())  return info["client_unique_identifier"];
	else 
	{
        if(info["clid"].empty() && info["cldbid"].empty()) return "NULL";
        
        clientInfo clientInfoBuffer;
		api->getClientInfo(clientInfoBuffer, getClid());
        
		if(!clientInfoBuffer["client_unique_identifier"].empty())   return clientInfoBuffer["client_unique_identifier"];
		else                                                        return "NULL";
	}
}

bool clientInfo::infoUpdate() 
{
	if(!checkApi()) return false;
	
	info.clear();
	return api->getClientInfo(info, getClid());
}

bool clientInfo::infoUpdate(string uid) 
{
	if(!checkApi()) return false;
	
	info.clear();
	info["cluid"] = uid;
	return api->getClientInfo(info, getClid());
}

void clientInfo::setAPI(Ts3API &api) 
{
	this->api = &api;
}

bool clientInfo::isOnline() 
{
	if(!checkApi()) return false;
	
	map<string, string> bufferMap;
	
	api->clientGetIds(bufferMap, getUid());
	if(bufferMap["clid"].empty() || (bufferMap["clid"] == "0")) {
		return false;
	}else {
		return true;
	}
}

bool clientInfo::poke(string message) 
{
	return api->pokeClient(getClid(), message);
}

///////////////
//  Private  //
///////////////

bool clientInfo::checkApi() 
{
	return (api != NULL)? true : false;
}
//* stuct clientInfo






// struct serverInfo
string& serverInfo::operator[](const string &name) 
{
	return info[name];
}

void serverInfo::clear() 
{
	info.clear();
}

string serverInfo::getStrTime(string key) 
{
	if(!checkApi()) {
		return "";
	}
	
	return api->convertTimeToStr(api->convertTime(info[key]));
}

timeStruct serverInfo::getTime(string key) 
{
	if(!checkApi()) return *(new timeStruct);
	
	return api->convertTime(info[key]);
}

string serverInfo::getTimestampTime(string key) 
{
	if(!checkApi()) return "";
	
	return api->convertTimestampTime(info[key]);
}

/////////////
// Private //
/////////////
bool serverInfo::checkApi() {
	return (api != NULL)? false : true;
}
//* struct serverInfo





// struct timeStruct
void timeStruct::clear() 
{
	years = 0;
	months = 0;
	days = 0;
	hours = 0;
	minutes = 0;
	seconds = 0;
}
