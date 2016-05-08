#pragma once

#include "Functions/Function.hpp"

using namespace std;

#include <string>
#include <thread>
//#include <curl/curl.h>

#include "TeamSpeak3_API/Ts3API.hpp"
#include "Extras/ConfigReader/ConfigFile.hpp"
#include "Extras/Menu/Menu.hpp" // badNumber(), dirIsset()
#include "Extras/wwwReader/www.hpp"

#define COLOR_RESET "\x1b[0m"
#define BOLD_ON "\x1b[1m"
#define BOLD_OFF "\x1b[22m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_BLUE "\x1b[34m"


using namespace std;

/**
 * Zawiera wszystkie metody które musi zaimplementować każda nowa funkcja multibota aby mogła być prawidłowo obsługiwana.
 * W konstruktorze obiektu powinny być zawarte refuły sprawdzające czy istniją odpowiednie foldery oraz pliki koniguracyjne.
 * 
 * @class Function
 * @author Karol Krupa
 * @date 07/03/16
 * @brief Interfejs funkcji multibota
 */
class AntyVPN : public Function {
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
	ConfigFile& configFile = *(new ConfigFile("configs/functions/AntyVPN/config.cfg"));
	
	static int writer(char *data, size_t size, size_t nmemb, string *buffer);
	
	bool isVPN(clientInfo &clInfo);
public:


	AntyVPN(Ts3API &api);
	/**
	 * Implementacja tej metody odpowiada za wszystkie operacje wykonywane po przekazaniu obiektu do nowego wątku.
	 * 
	 * @brief Odpowiada za operacje wykonywane w nowym wątku
	 */
	virtual void operator()();
	
	/**
	 * Implementacja metody powinna uruchamiać dany obiekt w nowym wątku wykonawczym.
	 * 
	 * @brief Funkcja uruchamiająca obiekt w nowym wątku
	 * @return true - W przypadku powodzenia, false - W przypadku błędu.
	 */
	virtual bool run();
	
	/**
	 * Implementacja metody powinna zatrzymywać wątek danego obiektu i niszczyć go.
	 * @brief Zatrzymuje wątek danego obiektu i niszczy go.
	 * @return true - W przypadku powodzenia, false - W przypadku błędu
	 */
	virtual bool stop();
	
	/**
	 * Zwraca status obiektu na podsawie czasu ostatniej aktualizacji statusu wątku.
	 * 
	 * @brief Zwraca status aktualnie uruchomionego obiektu.
	 * @return 
	 */
	virtual string status();
	
	/**
	 * @brief Sprawdza czy obiekt jest już uruchomiony w nowym wątku wykonawczym
	 * @return true - Jeżeli uruchomiony, false - Jeżeli nie uruchomiony
	 */
	virtual bool isRuning();
	
	/**
	 * Sprawdza w odpowiednim pliku konfiguracyjnym czy funkcja powinna być uruchomiona.
	 * 
	 * @brief Sprawdza czy dana funkcja jest ustawiona do uruchomienia.
	 * @return true - Jeżeli jest do uruchomienia, false - Jeżeli nie ma byc uruchomiona.
	 */
	virtual bool isEnabled();
	
	/**
	 * @brief Wyświetla konfiguracje dotyczącą danej funkcji.
	 */
	virtual void config();
	
	/**
	 * @brief Implementacja metody powinna utworzyć plik konfiguracyjny danej funkcji
	 */
	virtual void createConfig();
};