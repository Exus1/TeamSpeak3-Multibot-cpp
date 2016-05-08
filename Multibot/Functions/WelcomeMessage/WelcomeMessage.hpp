/**
 * @brief WelcomeMessage
 * @file WelcomeMessage.cpp
 */
#pragma once

#include <fstream>
#include <string>

#include "TeamSpeak3_API/Ts3API.hpp"
#include "Functions/Function.hpp"
#include "Extras/Menu/Menu.hpp" // badNumber(), dirIsset()

#define COLOR_RESET "\x1b[0m"
#define BOLD_ON "\x1b[1m"
#define BOLD_OFF "\x1b[22m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_BLUE "\x1b[34m"

using namespace std;

class WelcomeMessage : public Function {
private:
	/// Referencja do api serwerea TeamSpeak3
	Ts3API &api;
	/// Przechowuje wskaźnik na obiekt wątku w którym uruchomiony jest obiekt
	thread* th = NULL;
	/// Zmeinna determinującą zakończenie pętli
	bool loopEnd = false;
	/// Zmienna potwierdzająca zakończenie wątku
	bool loopEnded = false;
	/// Wskaźnik na obiekt przechowujący konfiguracje funkcji
	ConfigFile& configFile = *(new ConfigFile("configs/functions/WelcomeMessage/config.cfg"));
	// Przechowuje wiadomość powitalną
	string message;
public:
	
	/**
	 * Tworzy obiekt funkcji WelcomeMessage
	 * 
	 * @brief Konstruktor obiektu funkcji WelcomeMessage
	 * @param &api - Referencja do api TeamSpeak3.
	 */
	WelcomeMessage(Ts3API &api);
	
	/**
	 * @brief Operator wykonujący się po uruchomieniu funkcji w nowym wątku
	 */
	virtual void operator()();
	
	/**
	 * @brief Uruchamia nowy wątek z daną funkcją
	 * @return true/false
	 */
	virtual bool run();
	
	/**
	 * @brief Zatrzymuje główną pętle funkcji
	 * @return true/false
	 */
	virtual bool stop();
	
	/**
	 * @brief Sprawdza ostatni czas aktualizacji statusu i zwraca wartość
	 * @return Czas ostaniej aktualizacji
	 */
	virtual string status();
	
	/**
	 * @brief Sprawdza czy główna pętla jest uruchomiona
	 * @return true/false
	 */
	virtual bool isRuning();
	
	/**
	 * @brief Spradza czy fukcja jest przeznaczona do uruchomienia
	 * @return true/false
	 */
	virtual bool isEnabled();
	
	/**
	 * @brief Otwira menu konfiguracji funkcji
	 */
	virtual void config();
	
	/**
	 * @brief Tworzy foldery i pliki konfiguracyjne
	 */
	virtual void createConfig();
	
	/**
	 * @brief Generuje wiadomość powitalną dla danego użytkownika
	 * @param returned - Wiadomość dla użytkownika
	 * @param clInfo - Struktura z informacjami o użytkowniku
	 */
	void prepareMessage(string &returned, clientInfo &clInfo);
	
	/**
	 * @brief Pobiera wiadomość powitalną z pliku
	 */
	void getWelcomeMessage();
};