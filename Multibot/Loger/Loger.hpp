/**
 * @brief Zawiera deklaracje funkcji logera
 * @file Loger.hpp 
 */
#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <dirent.h>
#include <stdlib.h>

using namespace std;

/**
 * @brief Sprawdza czy podany katalog istnieje
 * @param dirName
 * @return true - Jeśli istnieje, false - Jeśli nie istnieje
 */
bool dirIsset(const string dirName);

/**
 * @brief Dodaje ostrzeżenia do logów
 * @param msg - Wiadomość
 */
void logerAddWarrning(const string &msg);

/**
 * @brief Dodaje błąd do logów i zakańcza wykonywania programu
 * @param msg - Wiadomość błędu
 */
void logerAddError(const string &msg);

/**
 * @brief Dodaje informacje do logów
 * @param msg - Wiadomość
 */
void logerAddInfo(const string &msg);