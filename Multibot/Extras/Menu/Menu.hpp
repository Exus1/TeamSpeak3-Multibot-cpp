/**
 * @brief Zawiera deklaracje obiektu menu
 * @file Menu.hpp
 */
#pragma once

#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <unistd.h>
#include <dirent.h>
#include <fstream>

#include <fcntl.h>
//#include <stdio.h>
//#include <signal.h> 
//#include <csignal>

#include "Functions/Function.hpp"
#include "Loger/Loger.hpp"

#define COLOR_RESET "\x1b[0m"
#define BOLD_ON "\x1b[1m"
#define BOLD_OFF "\x1b[22m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_BLUE "\x1b[34m"

using namespace std;

/**
 * @brief Przekazuje wykonanie programu do nowego procesu
 * @return true/false
 */
bool demonize();

/**
 * @brief Przekazuje standardowe strumienie I/O do /dev/null
 */
void dropStdIO();

/**
 * @brief Sprawdza czy wprowadzono poprawne dane do strumienia wejścia
 */
bool checkCinError();

/**
 * @brief Sprawdza czy dany plik istnieje
 * @param name - Nazwa pliku
 * @return true - jeżeli istnieje, false - jeżeli nie istnieje
 */
bool fileIsset(string name);

/**
 * @class Menu
 * @author Karol Krupa
 * @date 08/03/16
 * @brief Obiekt odpowiadający za wyświetlanie menu multibota
 */
class Menu {
private:
	/// Mapa przechowująca referencje do obiektów wszystkich funkcji
	map<string, Function*> &functionsMap;
	
	/**
	 * @brief Sprawdza czy multibot jest już uruchomiony
	 * @return true - Jeżeli uruchomiony, false - Jeżeli nie jest uruchomiony
	 */
	bool multibotStatus();
	
	/**
	 * @brief Wyświetla nagłówek menu multibota
	 */
	void showHeader();
	
	/**
	 * @brief Wyświetla listę funkcji wraz z ich statusami
	 * @return true - W przypadku uruchomienia multibota, false - W przypadku braku uruchomienia
	 */
	bool showFunctions();
	
	/**
	 * Pobiera pid procesu multibota i go zabija
	 * 
	 * @brief Wyłącza multibota
	 */
	void stopMultibot();
	
	/**
	 * @brief Restartue multibota
	 */
	void restartMultibot();
	
	/**
	 * @brief Uruchamia wątki ze wszystkimi funkcjami
	 */
	bool startMultibot();
	
public:
	/**
	 * Tworzy obiekt menu.
	 * 
	 * @brief Konstruktor obiektu menu
	 * @param &functionsMap - Referencja do mapy przechowującej referencje do obiektów wszystkich funkcji.
	 */
	Menu(map<string, Function*> &functionsMap);
};