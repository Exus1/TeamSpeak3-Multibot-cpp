/**
 * @author Karol Krupa
 * @date 18/03/16
 * @file Ts3API.hpp
 * @brief Zawiera obiekt obsługujący serwer TeamSpeak3 oraz pomocnicze struktury
 */
#pragma once

#include <iostream>
#include <map>
#include <time.h>

#include "Ts3Socket.hpp"
#include "Ts3Structs.hpp"

using namespace std;

// Deklaracje struktur
struct clientInfo;
struct serverInfo;
struct timeStruct;

/**
 * @class Ts3API
 * @author Karol Krupa
 * @date 18/03/16
 * @brief Obiekt obsługujący serwer TeamSpeak3
 */
class Ts3API {
private:
	/// Strutktura zwierająca konfiguracje połączenia
	struct serverConfig config;
	/// Referencja do obiektu Ts3Socket
	Ts3Socket &sock = *(new Ts3Socket(config));

	/**
	 * Przykładowy ciąg znaków:
	 * clid=12 cid=2
	 *
	 * @brief Zwija ciąg znaków do mapy <string, string>
	 * @param returnedMap - Zwracana mapa
	 * @param input - Ciąg znaków do konwersji
	 */
	void split(map<string, string>& returnedMap, string &input);

	/**
	 * Przykładowy ciąg znaków:
	 * clid=12 cid=2
	 *
	 * @brief Zwija ciąg znaków do struktury clientInfo
	 * @param returnedStruct - Zwracana struktura
	 * @param input - Ciąg znaków do konwersji
	 */
	void split(clientInfo &returnedStruct, string &input);

	/**
	 * Przykładowy ciąg znaków:
	 * clid=12 cid=2|clid=32 cid=2
	 *
	 * @brief Zwija ciąg znaków do mapy <string, map<string, string>>
	 * @param returnedMap - Zwracana struktura
	 * @param input - Ciąg znaków do konwersji
	 */
	void split(map<string, map<string, string>>& returnedMap, string mapIndex, string &input);

	/**
	 * Przykładowy ciąg znaków:
	 * clid=12 cid=2|clid=32 cid=2
	 *
	 * @brief Zwija ciąg znaków do mapy <string, struct clientInfo>
	 * @param returnedStruct - Zwracana struktura
	 * @param input - Ciąg znaków do konwersji
	 */
	void split(map<string, struct clientInfo>& returnedMap, string mapIndex, string &input);

	/**
	 * @brief Wykonuje bezzwrotną komendę na serwerze
	 * @param command - Nazwa komendy
	 * @return true/false
	 */
	bool executeCommand(const string &command);

	/**
	 * @brief Wykonuje komendę na serwerze i zwraca jej wartość w postaci mapy
	 * @param returnedMap - Zwracana mapa
	 * @param returnedMap - Zwracana mapa
	 * @param command - Komenda do wykoania
	 * @return true/false
	 */
	bool executeCommand(map<string, string>& returnedMap, const string &command);

	/**
	 * @brief Wykonuje komendę na serwerze i zwraca jej wynik w postaci mapy
	 * @param returnedMap - Zwracana mapa
	 * @param command - Komenda do wykonania
	 * @param mapIndex - Indeks z jakim ma być stworzona mapa
	 * @return true/false
	 */
	bool executeCommand(map<string, map<string, string>> &returnedMap, string mapIndex, const string &command);

	/**
	 * @brief Wykonuje komendę na serwerze i zwraca jej wynik w postaci mapy
	 * @param returnedMap - Zwracana mapa
	 * @param command - Komenda do wykonania
	 * @param mapIndex - Indeks z jakim ma być stworzona mapa
	 * @return true/false
	 */
	bool executeCommand(map<string, struct clientInfo> &returnedMap, string mapIndex, const string &command);

	/**
	 * @brief Wykonuje komendę na serwerze i zwraca jej wynik w postaci struktury clientInfo
	 * @param returnedStruct - Zwracana struktura
	 * @param command - Komenda do wykonania
	 * @return true/false
	 */
	bool executeCommand(clientInfo &returnedStruct, const string &command);


public:
	/**
	 * @brief Konwertuje ilość sekund na strukturę zawierająca informacje o czasie
	 * @param time - Ilość sekund
	 * @return Struktura zawierająca czasy
	 */
	timeStruct convertTime(string time);

	/**
	 * @brief Konwertuje czas z formatu timestamp
	 * @param timestamp - Czas w formacie timestamp
	 * @return format: d.m.y h.m
	 */
	string convertTimestampTime(string timestamp);

	/**
	 * @brief Konwetuje ilość sekund do słownego wupisania czasu (PL)
	 * @param time - Ilość sekund
	 * @return true/false
	 */
	string convertTimeToStr(timeStruct tStruct);

	/**
	 * Łączy się z serwerem TeamSpeak3 oraz tworzy podsawowe obiekty i ustawienia.
	 *
	 * @brief Konstruktor klasy Ts3API
	 * @param config - Struktura zawierająca konfigurację połaczenia z serwerem.
	 */
	Ts3API(struct serverConfig config);

	bool connect();

	/**
	 * Próbuje zamienić ciąg znaków na liczbę całkowitą i zwraca odpowiedzią wartość w przyadku powodzenia lub błędu.
	 * Zapobiega przed nagłym zakończeniem programu poprzez wyłapywanie wyjątku "invalid_argument"
	 *
	 * @brief Zamienia ciąg znaków na wartość liczbową
	 * @param str - Ciąg znaków do zamiany.
	 * @param returnedValue - Zwracana wartość liczbowa.
	 * @return true - Gdzy powodzenie, false - Gdy błąd.
	 */
	bool trystoi(string str, int& returnedValue);

	bool trystoi(string str, unsigned int& returnedValue);

	/**
	 * @brief Zwraca listę użytkowników serwera
	 * @param mapIndex - Indeks z jakim zostanie utworzona mapa
	 * @param flags - Flagi komendy "clientlist"
	 * @return true/false
	 */
	bool getServerClientList(map<string, map<string, string>> &returnedMap, const string &mapIndex = "auto", const string &flags = "");

	/**
	 * @brief Zwraca listę użytkowników serwera (zawira strukturę clientInfo)
	 * @param mapIndex - Indeks z jakim zostanie utworzona mapa
	 * @param flags - Flagi komendy "clientlist"
	 * @return true/false
	 */
	bool getServerClientList(map<string, struct clientInfo> &returnedMap, const string &mapIndex = "auto", const string &flags = "");

	/**
	 * @brief Zwraca mapę z użytkownikami z danego kanału
	 * @param returnedStruct - Lista użytkowników danego kanału
	 * @param channelId - Id kanału
	 * @param mapIndex - Indeks z jakim ma być utworzona mapa
	 * @param falgs - Flagi z "clientlist"
	 * @return ture/false
	 */
	bool getChannelClientList(map<string, clientInfo> &returnedStruct, string const &channelId, string const &mapIndex = "auto", string const &flags = "");

	/**
	 * targetmode 1 - client, 2- channel, 3 - server
	 */
	bool sendMessage(string message, int target, short targetmode = 1);

	/**
	 * @brief Pobiera informacje o wybranym użytkowniku
	 * @param returnedStruct - Zwracana struktura
	 * @param clid - Id użytkownika
	 * @return true/false
	 */
	bool getClientInfo(clientInfo &returnedStruct, unsigned int clid);

	/**
	 * @brief Pobiera informacje o wybranym użytkowniku
	 * @param returnedStruct - Zwracana struktura
	 * @param clid - Id użytkownika
	 * @return true/false
	 */
	bool getClientInfo(map<string, string> &returnedMap, unsigned int clid);

	/**
	 * @brief Zwraca informacje o serwerze
	 * @param returnedStruct - Zwracana struktura
	 * @return true/false
	 */
	bool getServerInfo(serverInfo &returnedStruct);

	/**
	 * @brief Wyrzuca danego użytkownika z serwera
	 * @param clid - Id użytkownika
	 * @param message - Wiadomość porzegnalna
	 * @return true/false
	 */
	bool clientKickFromServer(unsigned int clid, string message);

	/**
	 * @brief Wyrzuca użytkownika z kanału
	 * @param clid - Id użytkownika
	 * @param message - Wiadomość porzegnalna
	 * @return true/false
	 */
	bool clientKickFromChannel(unsigned int clid, string message);

	/**
	 * @brief Wysyła poke do użytkownika
	 * @param id - Identyfikator użytkownika
	 * @param msg - Wiadomość
	 * @return true/false
	 */
	bool pokeClient(unsigned int id, string msg);

	/**
	 * @brief Zwraca listę użytkowników danej grupy
	 * @param &returnedStruct - Zwracana struktura
	 * @param mapIndex - Indeks z jakim zostanie utworzona mapa
	 * @param id - Id grupy
	 * @names - Czy używać parametru -names
	 */
	bool getServerGroupClientList(map<string, clientInfo> &returnedStruct, unsigned int id, string mapIndex = "auto", bool names = false);

	/**
	 * @brief Zwraca strukturę zawierająca id użytkownika. Można sprawdzić czy jest online oraz wysyłać wiadomości lub pobrać szczegółowe dane
	 * @param returnedStruct - Zwracana struktura
	 * @param uid - Uid użytkownika
	 * @return true/false
	 */
	bool clientGetIds(struct clientInfo &returnedStruct, string uid);

	/**
	 * @brief Zwraca strukturę zawierająca id użytkownika. Można sprawdzić czy jest online oraz wysyłać wiadomości lub pobrać szczegółowe dane
	 * @param returnedMap - Zwracana mapa
	 * @param uid - Uid użytkownika
	 * @return true/false
	 */
	bool clientGetIds(map<string, string> &returnedMap, string uid);

	/**
	 * @brief Zwraca strukturę zawierająca uid i database id. Można wysyłać wiadomości oraz sprawdzać czy jest online i pobrać szczegółowe dane
	 * @param returnedStruct - Zwracana struktura
	 * @param uid - Uid użytkownika
	 * @return true/ false
	 */
	bool getClientNameFromUid(struct clientInfo &returnedStruct, string uid);

	bool getClientNameFromDbid(struct clientInfo &returnedStruct, unsigned int dbid);

	bool getClientNameFromDbid(map<string, string> &returnedMap, unsigned int dbid);

    bool whoAmi(map<string, string> &returnedMap);

    bool setName(string name);
};





/**
 * @class clientInfo
 * @author Karol Krupa
 * @date 18/03/16
 * @brief Przechowuje informacje o wybranym użytkowniku
 */
struct clientInfo {
private:
	/**
	 * @brief Zwraca clid użytkownika
	 * @return clid
	 */
	unsigned int getClid();

	/**
	 * @brief Zwraca uid użytkownika
	 * @return uid
	 */
	string getUid();

	bool checkApi();
public:
	/// Wskaźnik na api serwera
	Ts3API *api;
	/// Mapa przechowująca wszystkie informacje
	map<string, string> info;

	/**
	 * @brief Wysyła wiadomość do użytkownika
	 * @param message - Treść wiadomości
	 * @return true/false
	 */
	bool sendMessage(const string &message);

	/**
	 * @brief Sprawdza czy struktura jest pusta
	 * @return true/false
	 */
	bool empty();

	/**
	 * @brief Czyści strukturę
	 */
	void clear();

	/**
	 * @brief Zwraca wartość mapy info
	 * @param name - Klucz mapy info
	 */
	string& operator[](const string &name);

    bool operator==(struct clientInfo clientStruct);

	/**
	 * @brief Wyrzuca użytkonika z serwera i czyści strukturę
	 * @param msg - Wiadomość porzegnalna
	 * @return true/false
	 */
	bool kickFromServer(const string& msg);

	/**
	 * @brief Wyrzuca użytkownika z kanału
	 * @param msg - Wiadomość porzegnalna
	 * @return true/false
	 */
	bool kickFromChannel(const string& msg);

	/**
	 * @brief Zwraca strutkurę z czesem po konwetsji z wybranego klucza
	 * @return Struktura czasu
	 */
	timeStruct getTime(string key);

	/**
	 * @brief Zwraca czas wyrażony w zdaniu
	 * @param key - Nazwa klucza mapy z zapisaną ilością sekund
	 * @return np. 2 godziny 34 minuty 5 sekund
	 */
	string getStrTime(string key);

	/**
	 * @brief Konwertuje czas z formatu timestamp
	 * @param key - Czas w formacie timestamp
	 * @return format: d.m.y h.m
	 */
	string getTimestampTime(string key);

	/**
	 * @brief Aktualizuje informacje o użytkowniku na podstawie informacji z mapy info
	 * @return true/false
	 */
	bool infoUpdate();

	/**
	 * @brief Aktualizuje informacje o użytkowniku na podstawie podanego Identyfikatora
	 * @param uid - UID użytkownika
	 * @return true/false
	 */
	bool infoUpdate(string uid);

	/**
	 * @brief Przypisuje obiekt api do struktury
	 * @param api - Obiekt api połączony z serwerem
	 */
	void setAPI(Ts3API &api);

	/**
	 * @brief Sprawdza czy użytkownik jest online
	 * @return true/false
	 */
	bool isOnline();

	/**
	 * @brief Wysyła poke do użytkownika
	 * @param message - Wiadomość
	 * @return true/false
	 */
	bool poke(string message);
};






/**
 * @class serverInfo
 * @author Karol Krupa
 * @date 18/03/16
 * @file Ts3API.hpp
 * @brief Struktura przechowująca informacje o serwerze
 */
struct serverInfo {
private:
	bool checkApi();
public:
	/// Mapa przechowująca wszystkie informacje
	map<string, string> info;
	/// Wskaźnik na api serwera
	Ts3API *api;

	/**
	 * @brief Zwraca wartość mapy info
	 * @param name - Klucz mapy info
	 */
	string& operator[](const string &name);

	/**
	 * @brief Czyści strukturę z wyłączeniem wskaźnika do api
	 */
	void clear();

	/**
	 * @brief Zwraca strutkurę z czesem po konwetsji z wybranego klucza
	 * @return Struktura czasu
	 */
	timeStruct getTime(string key);

	/**
	 * @brief Zwraca czas wyrażony w zdaniu
	 * @param key - Nazwa klucza mapy z zapisaną ilością sekund
	 * @return np. 2 godziny 34 minuty 5 sekund
	 */
	string getStrTime(string key);

	/**
	 * @brief Konwertuje czas z formatu timestamp
	 * @param key - Czas w formacie timestamp
	 * @return format: d.m.y h.m
	 */
	string getTimestampTime(string key);
};






/**
 * @class timeStruct
 * @author Karol Krupa
 * @date 18/03/16
 * @brief Struktura przechowująca informacje o czesie po konwersji
 */
struct timeStruct {
public:
	/// Ilość lat
	int years = 0;
	/// Ilość miesięcy
	int months = 0;
	/// Ilość dni
	int days = 0;
	/// Ilość godzin
	int hours = 0;
	/// Ilość minut
	int minutes = 0;
	/// Ilosć sekund
	int seconds = 0;

	/**
	 * @brief Ustawia wszystkie wartości na 0;
	 */
	void clear();
};
