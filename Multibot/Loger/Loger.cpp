#include "Loger.hpp"

using namespace std;

bool dirIsset(const string dirName) {
	DIR *dir= opendir(dirName.c_str());
    closedir(dir);
    
	return (dir)? true : false;
}

void logerAddWarrning(const string &msg) {
	fstream plik;
	if(!dirIsset("logs") && (system("mkdir logs") == -1)) exit(3);
    
	plik.open("logs/multibot.log", ios::app);
    
	if(plik.good()) plik << "WARNING: "  << msg << endl;
    
    plik.close();
}

void logerAddError(const string &msg) {
	fstream plik;
	if(!dirIsset("logs") && (system("mkdir logs") == -1)) exit(3);

	plik.open("logs/multibot.log", ios::app);
	if(plik.good()) plik << "ERROR: " << msg << endl;
    
    plik.close();
	exit(2);
}

void logerAddInfo(const string &msg) {
	fstream plik;
	if(!dirIsset("logs") && (system("mkdir logs") == -1)) exit(3);
    
	plik.open("logs/multibot.log", ios::app);
	if(plik.good()) plik << "INFO: "  << msg << endl;
    
    plik.close();
}