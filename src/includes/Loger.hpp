#pragma once

#include <string.h>
#include <iostream>
#include <sqlite3.h>

using namespace std;

/**
 *  @brief Przestrzeń nazw zawierająca metody Logera
 *
 *  Znajdują się tu wszystkie metody służące do odczytywania/dodawania
 *  błędów/powiadomień wykonania
*/
namespace Loger {
    /**
     *  @brief Dodaje Błąd
     *  @param content[in] Zwiera tresć błędu
     *  @param id Zawiera ID błędu
     *
     *  Dodaje błąd do tabeli błędów
    */
    void addError(string content, int id);

    /**
     *  @brief Dodaje ostrzeżenie
     *  @param content[in] Zawiera treść ostrzeżenia
     *
     *  Dodaje ostrzeżenie do tabeli ostrzeżeń
    */
    void addWarning(string content);

    /**
     *  @brief Dodanie powiadomienie
     *  @param content[in] Zawiera treść powiadomienia
    */
    void addInfo(string content);
}
