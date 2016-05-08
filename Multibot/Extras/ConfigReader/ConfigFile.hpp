#pragma once

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <vector>

#include "Loger/Loger.hpp"

using namespace std;

class ConfigFile {
private:
	/// Przechowuje ścieżkę do pliku
	string fileName;
	
	/**
	 * @brief Pobiera zawartość pliku w odpowiednim formacie i zapisuje ją do mapy fileContent.
	 */
	void getContent();
	
	/**
	 * @brief Usuwa białe znaki z początku i końca ciągu
	 * @param source - Ciąg do usunięcia buałych znaków
	 * @param delims - Znaki które powinny być usunięte
	 * @return Ciąg bez białych znaków na początku i końcu
	 */
	string trim(string const& source, char const* delims = " \t\r\n");

public:
	/// Przechowuje wczytany plik konfiguracyjny
	map<string, map<string, string>> fileContent;
	
	/**
	 * @breif Konstruktor obiektu ConfigFile
	 */
	ConfigFile(string const file);
	
	/**
	 * @brief Zapisuje zmienioną konfiguracje do pliku
	 */
	void save();
	
	/**
	 * Pozwala na używanie obiektu tak jak zwykłej mapy
	 * 
	 * @brief Przeładowanie operatora []
	 * @param name - Nazwa sekcji w pliku konfiguracyjnym
	 * @return map<string, string> - Zawartość sekcji pliku konfiguracyjnego
	 */
	map<string, string>& operator[](string name);
	
	vector<string> explode(string const& str, string key);
	
	map<string, string> explodeToMap(string const& str, string key);
};