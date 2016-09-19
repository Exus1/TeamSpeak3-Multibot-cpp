#include "includes/Loger.hpp"

using namespace std;

namespace Loger {
    void addError(string content, int id) {
        sqlite3 *db;
        char *sqliteErr = 0;

        if(sqlite3_open("Database.db", &db) != SQLITE_OK) {
            cout << "Unable to open database and add new ERROR. " << content << endl;
            sqlite3_close(db);
            return;
        }

        string sql = "INSERT INTO `Logs`(`id`, `content`, `type`) VALUES('" + id + string("', '") + content + "', 'ERROR');";
        if(sqlite3_exec(db, sql.c_str(), NULL, NULL, &sqliteErr) != SQLITE_OK) {
            cout << "Unable to add new ERROR to database. " << content << " Mysql error: " << sqliteErr << endl;
            sqlite3_close(db);
            return;
        }

        sqlite3_close(db);
    }

    void addWarning(string content) {
        sqlite3 *db;
        char *sqliteErr = 0;

        if(sqlite3_open("Database.db", &db) != SQLITE_OK) {
            cout << "Unable to open database and add new WARNING. " << string(content) << endl;
            sqlite3_close(db);
            return;
        }

        string sql = "INSERT INTO `Logs`(`id`, `content`, `type`) VALUES('0', '"+ string(content) +"', 'WARNING');";
        if(sqlite3_exec(db, sql.c_str(), NULL, NULL, &sqliteErr) != SQLITE_OK) {
            cout << "Unable to add new WARNING to database. " << string(content) << " Mysql error: " << sqliteErr << endl;
            sqlite3_close(db);
            return;
        }

        sqlite3_close(db);
    }

    void addInfo(string content) {
        sqlite3 *db;
        char *sqliteErr = 0;

        if(sqlite3_open("Database.db", &db) != SQLITE_OK) {
            cout << "Unable to open database and add new INFO. " << content << endl;
            sqlite3_close(db);
            return;
        }
        string sql = "INSERT INTO `Logs`(`id`, `content`, `type`) VALUES('0', '"+ string(content) +"', 'INFO');";
        if(sqlite3_exec(db, sql.c_str(), NULL, NULL, &sqliteErr) != SQLITE_OK) {
            cout << "Unable to add new INFO to database. " << string(content) << " Mysql error: " << sqliteErr << endl;
            sqlite3_close(db);
            return;
        }

        sqlite3_close(db);
    }
}
