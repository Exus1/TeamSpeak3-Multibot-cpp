#include <iostream>
#include <Ts3API.hpp>
#include <Loger.hpp>
#include <sqlite3.h>
#include <string>
#include <fstream>


#include <ModulesLoader.hpp>

using namespace std;

int main() {
    /* Creating sqlite DB */
    fstream dbFile("Database.db");
    if(!dbFile.is_open())
    {
        dbFile.close();
        sqlite3 *db;
        if(sqlite3_open("Database.db", &db) != SQLITE_OK) {
            cout << "Unable to create sqlite database! Check permissions!";
            sqlite3_close(db);
            return 1;
        }

        string query;
        query = "CREATE TABLE `Logs`(`id` int(4), `content` varchar(255), `type` varchar(7));";
        char *sqliteErr = 0;
        if(sqlite3_exec(db, query.c_str(), NULL, 0, &sqliteErr) != SQLITE_OK) {
            cout << "Unable to create table (Logs) in sqlite database! Mysql error: " << sqliteErr << endl;
            sqlite3_close(db);
            return 1;
        }

        sqlite3_close(db);
    } else {
        dbFile.close();
    }

    /* Connecting to ts3 server */
    struct serverConfig conf;
    conf.ip = "exus.ovh";
  	conf.password = "u++5RvMV";
    conf.nickname = "ExMultibot";

    Ts3API ts3(conf);
    if(!ts3.connect()) {
      return 1;
    }

    ModulesLoader Mloader("libs", "ts3M", ts3);
    Mloader.loadAll();

    

    return 0;
}
