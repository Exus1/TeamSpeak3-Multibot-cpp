#pragma once
/**
 * @author Karol Krupa
 * @date 04/03/16
 * @brief Zawiera klasę służącą do obsługi socketu serwera TeamSpeak3
 * @file Ts3Socket.hpp
 */

#include <string>
#include <iostream>

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include <mutex>
#include <regex>
#include <map>
#include <cstring>

#define BUFFLEN 512
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#define COLOR_RESET "\x1b[0m"
#define BOLD_ON "\x1b[1m"
#define BOLD_OFF "\x1b[22m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_BLUE "\x1b[34m"

using namespace std;

/**
 * Służy do konfiguracji połączenia socketu z serwerem TeamSpeak3.
 * ip - Adres ipv4 serwera TeamSpeak3. (Domyślnie 127.0.0.1)
 * server_port - Port instancji serwera która ma zostać wybrana do połączenia. (Domyślnie 9987)
 * query_port - Port sewrwera TeamSpeak3. (Domyślnie 10011)
 * login - Login użytownika query. (Domyślnie serveradmin)
 * password - Hasło użytkownika query.
 *
 * @class serverConfig
 * @author Karol Krupa
 * @date 04/03/16
 * @brief Służy do konfiguracji połączenia
 */
struct serverConfig {
	string ip = "127.0.0.1";
	string server_port = "9987";
	string query_port = "10011";
	string login = "serveradmin";
	string password = "";
    string nickname = "ExMultibot";
};

/**
 * @class Ts3Socket
 * @author Karol Krupa
 * @date 04/03/16
 * @brief Klasa służąca do obługi socketu TeamSpeak3
 */
class Ts3Socket {
private:
	int sock = -1;
	serverConfig config;
	mutex* mtx;

public:
	/**
	 * Konstuktor obieku socketu. Tworzy socket oraz łączy go z instancją serwera TeamSpeak3.
	 *
	 * @brief Łączy socket z obiektem
	 * @author Karol Krupa
	 * @date 04/03/16
	 * @param &config - Struktura zawierająca konfigurację połączenia.
	 * @return Brak.
	 */
	Ts3Socket(struct serverConfig const &config);

	bool serverConnect();

	/**
	 * @brief Sprawdza czy socket jest aktualnie używany.
	 * @return true - Jeżeli wolny. false - Jeżeli zajęty.
	 */
	bool checkStatus();

	/**
	 * @brief Wysyła polecenie do serwera ts3 i zwraca odpowiedź.
	 * @param recv_message - Zmienna string w której zostanie zapisana odpowiedź.
	 * @param message - Wiadomość do wysłania.
	 * @return true - Jeśli powodzenie, false - Jeśli niepowodzenie.
	 */
	bool sendMessage(string &recv_message, string const message);

	/**
	 * Zamienia białe znaki itp. na odpowiedznie znaczniki.
	 *
	 * @brief Służy do dekodowania wiadomości otrzymanych od serwera TeamSpeak3.
	 * @param message - Wiadomość do deszyfracji.
	 */
	void stringDecode(string& message);

	/**
	 *  Zamienia białe znaki na odpowiadające im znacznikia.
	 *
	 *  @brief Służy do kodowania wiadomości wysyłanych przez socket do serwera TeamSpeak3
	 *  @param message - Wiadomość do zakodowania.
	 */
	void stringEncode(string& message);
};
