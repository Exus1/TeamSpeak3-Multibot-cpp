/**
 * @author Karol Krupa
 * @date 18/03/16
 * @file Function.hpp
 * @brief Deklaracja interfejsu klasy funkcji multibota
 */
#pragma once

#include <string>
#include <thread>
#include "Extras/ConfigReader/ConfigFile.hpp"
#include "TeamSpeak3_API/Ts3API.hpp"

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
class Function {
public:

	/// Przechowuje wskaźnik na obiekt wątku w którym uruchomiony jest obiekt
	thread* th = NULL;
	/// Zmeinna determinującą zakończenie pętli
	bool loopEnd = false;
	/// Zmienna potwierdzająca zakończenie wątku
	bool loopEnded = false;
	/// Przechowuje wskaźnik na obiekt api
    Ts3API* api;
    /// Przechowuje wskaźnik na obiekt z konfiguracją funkcji
    ConfigFile* configFile;
    
	/**
	 * Implementacja tej metody odpowiada za wszystkie operacje wykonywane po przekazaniu obiektu do nowego wątku.
	 * 
	 * @brief Odpowiada za operacje wykonywane w nowym wątku
	 */
	virtual void operator()()=0;
	
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
	virtual void config()=0;
	
	/**
	 * @brief Implementacja metody powinna utworzyć plik konfiguracyjny danej funkcji
	 */
	virtual void createConfig()=0;
};

/**
 * @brief Funkcja uruchamiające obiekt ze wskaźnika w nowym wątku
 * @param func - Wskaźnik na obiekt do uruchomienia
 */
void startFunctionInThread(Function *func);