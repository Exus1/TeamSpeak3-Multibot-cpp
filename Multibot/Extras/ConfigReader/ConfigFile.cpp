#include "ConfigFile.hpp"

using namespace std;

ConfigFile::ConfigFile(string const file) : fileName(file) 
{
	getContent();
}

void ConfigFile::save() 
{
	fstream file;
	file.open(fileName, ios::trunc | ios::out);
		
	if(!file.good()) {
		logerAddWarrning("Nie udało sie zapisać " + fileName);
        return;
	}
		
	for(map<string, map<string, string>>::iterator it = fileContent.begin(); it != fileContent.end(); it++) 
	{
		file << "[" << it->first << "]\n";
		for(map<string, string>::iterator it1 = it->second.begin(); it1 != it->second.end(); it1++) file << it1->first << "=" << it1->second << "\n";
	}
	file.close();
}

map<string, string>& ConfigFile::operator[](string name)  
{
	return fileContent[name];
}

string ConfigFile::trim(string const& source, char const* delims) 
{
	string result(source);
	string::size_type index = result.find_last_not_of(delims);
	if (index != string::npos)
		result.erase(++index);

	index = result.find_first_not_of(delims);
	if (index != string::npos)
		result.erase(0, index);
	else
		result.erase();
	return result;
}

void ConfigFile::getContent() 
{
	fstream file;
	string line;
		
	file.open(fileName, ios::out | ios::in);
		
	if(!file.good()) return;
		
	string section = "";
	int pos;
		
	while(getline(file, line)) 
	{
			
		if (!line.length()) continue;

		if (line[0] == '#') continue;
		if (line[0] == ';') continue;
			
		if(line[0] == '[') {
			section = trim(line.substr(1, line.find(']') - 1));
		}else if(section != "") {
			pos= line.find('=');
			fileContent[section][trim(line.substr(0, pos))] =  trim(line.substr(pos + 1));
		}
	}
	file.close();
	return;
}

vector<string> ConfigFile::explode(string const& str, string key) 
{
	vector<string> returnedVector;
	if(str.find(key) != string::npos) 
	{
		string buffer;
		size_t pos = 0, buffPos = 0;
		while((pos = str.find(key, pos+1)) != string::npos) {
			buffer.insert(0, str, buffPos, pos-buffPos);
            if(!buffer.empty())
                returnedVector.push_back(trim(buffer));
			buffer.clear();
			buffPos = pos+1;
		}
        buffer.insert(0, str, buffPos, str.length()-buffPos);
        if(!buffer.empty())
            returnedVector.push_back(trim(buffer));
		return returnedVector;
	}
	else 
	{
		returnedVector.push_back(str);
		return returnedVector;
	}
	return returnedVector;
}

map<string, string> ConfigFile::explodeToMap(string const& str, string key) 
{
	map<string, string> returnedMap;
	if(str.find(key) != string::npos) 
	{
		string buffer;
		size_t pos = 0, buffPos = 0;
		while((pos = str.find(key, pos+1)) != string::npos) {
			buffer.insert(0, str, buffPos, pos-buffPos);
            if(!buffer.empty())
                returnedMap[buffer] = trim(buffer);
			buffer.clear();
			buffPos = pos+1;
		}
        buffer.insert(0, str, buffPos, str.length()-buffPos);
        if(!buffer.empty())
            returnedMap[buffer] = trim(buffer);
		return returnedMap;
	}
	else 
	{
		returnedMap[str] = str;
		return returnedMap;
	}
	return returnedMap;
}