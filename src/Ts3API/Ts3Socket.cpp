/**
 * @brief Zawiera wystąpienia metod obiektu Ts3Socket
 * @file Ts3Socket.cpp
 */
#include "includes/Ts3Socket.hpp"
#include <string>

using namespace std;

Ts3Socket::Ts3Socket(struct serverConfig const &config) : config(config) {

}

bool Ts3Socket::serverConnect()
{
	char recvbuf[512] = "";
	string tempRecv;
	int iResult; // Zmienna przechowująca wyniki funkcji
	addrinfo serverInfo, *cServerInfo = NULL;

	mtx = new mutex();

  // Tworzenie struktury z informacjami o serwerze
  memset(&serverInfo, 0, sizeof(addrinfo));
  serverInfo.ai_family = AF_UNSPEC;
  serverInfo.ai_socktype = SOCK_STREAM;
  serverInfo.ai_protocol = IPPROTO_TCP;

  iResult = getaddrinfo(config.ip.c_str(),
                        config.query_port.c_str(),
                        &serverInfo,
                        &cServerInfo); // Konwersja z kolejności bitów hosta na kolejność sieciową


  if (iResult != 0) {
		cout << "[ERROR] Błąd przy konwersji adresu serwera" << endl;
		return false;
	}


  sock = socket(cServerInfo->ai_family, cServerInfo->ai_socktype, cServerInfo->ai_protocol); // Tworzenie socketu
  if (sock == INVALID_SOCKET) {
		cout << "[ERROR] Nie udało się utworzyć socketu" << endl;
		return false;
	}


  iResult = connect(sock, cServerInfo->ai_addr, cServerInfo->ai_addrlen); // Łączenie z serwerem
  if (iResult == SOCKET_ERROR) {
		close(sock);
		sock = INVALID_SOCKET;
		cout << COLOR_RED;
		cout << "[ERROR] Nie udało się połączyć z serwerem " << config.ip << " Sprawdź plik configs/config.cfg." << endl;
		cout << COLOR_RESET;
		return false;
  }
  freeaddrinfo(cServerInfo); // Uwalnianie pamięci


  cout << "[SUCCESS] Pomyślnie połączono z serwerem " << config.ip << endl; // Wiadomość Statusu


  do // Zbiera wiadomość powitalną wysyłaną przez serwer ts3
	{
		iResult = recv(sock, recvbuf, 511, 0);
		if (iResult == 0)
		{
			cout << COLOR_RED;
			cout << "[ERROR] Nie udało się połączyć z instancją serwera TeamSpeak3. Połączenie zostało zerwane przez serwer." << endl;
			cout << COLOR_RESET;
			return false;
		}
		else if (iResult < 0)
		{
			cout << COLOR_RED;
			cout << "[ERROR] Wystąpił błąd przy łączeniu się z instancją serwera TeamSpeak3." << endl;
			cout << COLOR_RESET;
			return false;
		}
	}while (iResult < 10);

  if (sendMessage(tempRecv, "login " + config.login + " " + config.password))
	{
        cout << "[SUCCESS] Pomyślnie zalogowano do serwera TeamSpeak3" << endl;
	}
  else
  {
		cout << COLOR_RED;
		cout << "[ERROR] Nie udało zalogować się do serwera TeamSpeak3. Sprawdź plik configs/config.cfg." << endl;
		cout << COLOR_RESET;
		return false;
  }

  if (sendMessage(tempRecv, "use port=" + config.server_port))
	{
		cout << "[SUCCESS] Pomyślne wybrano serwer o porcie " + config.server_port << endl;
  }
	else
	{
		cout << COLOR_RED;
		cout << "Nie udało się wybrać serwera o porcie " << config.server_port << " Sprawdź plik configs/config.cfg." << endl;
		cout << COLOR_RESET;
		return false;
  }

	cout << "[SUCCESS] Pomyślnie zakończono łączenie z serwerem TeamSpeak3" << endl;
	return true;
}

bool Ts3Socket::checkStatus()
{
	if(mtx->try_lock()) mtx->unlock();
	else return false;
	return true;
}

bool Ts3Socket::sendMessage(string &recv_message, string const message)
{
	recv_message = "";

	int iResult;

	fd_set sock_set;
	struct timeval time; time.tv_sec = 2; time.tv_usec = 0;

	string buff_message = "";
	char recv_buff[BUFFLEN] = ""; string return_buffer;
	regex error_pattern("error id=(.*) msg=(.*)"); smatch result;

	int selectSock = sock;
	selectSock++;

	mtx->lock();


	do
	{

		if(buff_message != "")  iResult = send(sock, buff_message.c_str(), message.length(), 0);
		else                    iResult = send(sock, message.c_str(), message.length(), 0);

		if(iResult == SOCKET_ERROR) {
			cout << "Nie udało się wysłać danych do serwera";
			return false;
		}

		if(unsigned(iResult) >= message.length()) {
			break;
		}else {
			buff_message = message;
			buff_message.erase(0, iResult);
		}

	}while(true);


	iResult = send(sock, "\n", 1, 0);
	if(iResult == SOCKET_ERROR) {
		cout << "Nie udało się wysłać danych do serwera";
		return false;
	}


	do
	{
		FD_ZERO(&sock_set);
		FD_SET(sock, &sock_set);

		iResult = recv(sock, recv_buff, BUFFLEN - 1, 0);

		if(iResult == 0) // Serwer zamknął połączenia
		{
			cout << "Serwer TeamSpeak3 zamknął połączenie";
			return false;
		}
		else if(iResult < 0) // Błąd przy odbieraniu danych
		{
			cout << "Wystąpł błąd przy odbieraniu danych";
		}
		else // Sukces
		{
			recv_message += recv_buff;
			memset(recv_buff, 0, sizeof(recv_buff));

			if(regex_search(recv_message, result, error_pattern)) // Wszystkie dane zostały odebrane
			{
				break;
			}
			else // Jakieś dane powinny czekać na odebranie
			{
				select(selectSock, &sock_set, NULL, NULL, &time);
				if(FD_ISSET(sock, &sock_set)) {
					continue;
				}else {
					cout << "Nie udało odebrać się wszystkich danych z serwera";
					return false;
				}
			}

		}
	}while(true);


	mtx->unlock();



	if((result[2] == "ok") && (recv_message.length() == size_t((result[0].length() +2))))   return true;
	else if((result[2] == "ok") && (recv_message.length() > size_t(result[0].length())))    recv_message.erase(recv_message.length() - (result[0].length() + 4), result[0].length() +4);
	else if(result[2] == "ok")                                                              return true;
	else
	{
		string error_msg = result[2];
		stringDecode(error_msg);
		cout << "Wystąpił błąd przy wykonywaniu polecenia na serwerze. msg=" + error_msg + " id=" + string(result[1]);
		return false;
	}
	return true;
}

void Ts3Socket::stringDecode(string& message)
{
	size_t pos = 0;
    char zn1[2] = { char(7) };
    char zn2[2] = { char(11) };
    string wartosci[11] = { " ", "/", "|", "\b", "\f", "\n", "\r", "\t", zn1, zn2, "\\" };
    string znaki[11] = { "\\s", "\\/", "\\p", "\\b", "\\f", "\\n", "\\r", "\\t", "\\a", "\\v", "\\\\" };

    for (int i = 0; i < 11; i++)
	{
		if ((pos = message.find(znaki[i])) != string::npos) {
			message.erase(pos, 2);
			message.insert(pos, wartosci[i]);

			while ((pos = message.find(znaki[i], pos + 2)) != string::npos) {
				message.erase(pos, 2);
				message.insert(pos, wartosci[i]);
			}
		}
    }
}

void Ts3Socket::stringEncode(string& message)
{
	size_t pos = 0;
	char zn1[2] = { char(7) };
	char zn2[2] = { char(11) };
	string wartosci[11] = { "\\", " ", "/", "|", "\b", "\f", "\n", "\r", "\t", zn1, zn2 };
	string znaki[11] = { "\\\\", "\\s", "\\/", "\\p", "\\b", "\\f", "\\n", "\\r", "\\t", "\\a", "\\v" };

	for (int i = 0; i < 11; i++)
	{
		if ((pos = message.find(wartosci[i])) != string::npos) {
			message.erase(pos, 1);
			message.insert(pos, znaki[i]);

			while ((pos = message.find(wartosci[i], pos + 2)) != string::npos) {
				message.erase(pos, 1);
				message.insert(pos, znaki[i]);
			}
		}
	}
}
