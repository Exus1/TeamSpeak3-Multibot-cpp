#include "Menu.hpp"

using namespace std;

bool demonize() 
{
	// Sprawdzanie czy multibot jest już uruchomiony
	int lockfileInt = open("mutlbit.pid", O_RDWR | O_CREAT, 0640);
	if(lockf(lockfileInt, F_TLOCK, 0) < 0) {
		cout << COLOR_RED;
		cout << "Multibot jest już uruchomiony!" << endl;
		cout << COLOR_RESET;
		return false;
	}
	
	int pid = fork();       // Tworzenie prosecu potomnego
	if(pid > 0) exit(0);    // Zamykanie procesu głównego
	
	if(system("clear") == -1) logerAddWarrning("Nie udało się wyczyścić terminala"); // Czyści wiadomość o wciśnięciu ENTER
	setsid(); // Tworzenie grupy procesów (potomny)
	
	// Tworzenie "lockfile"
	fstream lockfile;
	lockfile.open("multibot.pid", ios::out);
	if(lockfile.fail()) {
		cout << COLOR_RED;
		cout << "Prawdopodobnie multibot jest już uruchomiony. (Nie udało utworzyć się pliku multibot.pid)" << endl;
		cout << COLOR_RESET;
		lockfile.close();
		return false;
	}
	
	lockfile << getpid(); // Blokowanie pliku w procesie potomnym 
	if(lockf(lockfileInt, F_TLOCK, 0)); // Neutralizowanie otrzeżenia kompilatora
	return true;
}

void dropStdIO() {
	ofstream devnull;
	devnull.open("/dev/null");
	cout.rdbuf(devnull.rdbuf());    // Przekierowanie standardowych strumieni I/O na /dev/null
	cin.rdbuf(devnull.rdbuf());     // Przekierowanie standardowych strumieni I/O na /dev/null
	devnull.close();
	return;
}

bool checkCinError()  
{
	if(cin.fail()) { // Jeżeli wystąpił błąd przy wprowadzaniu danych
		cout << "\x1b[31mMusisz wprowadzić numer polecenia!\x1b[0m" << endl;
		cin.clear(); // Czyści strumień
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Czyści strumień
		return true;
	}else {
		return false;
	}
}

bool fileIsset(string name) 
{
	fstream file;
	file.open(name); // Otwiera plik
	
	if(!file.good())    return false;
	else                file.close();
    return true;
}

Menu::Menu(map<string, Function*> &functionsMap) : functionsMap(functionsMap) 
{
	while(true) 
	{
		showHeader();
        
		if(showFunctions()) return;
        
		if(system("clear") == -1) logerAddWarrning("Nie udało się wyczyścić terminala");
		cout << COLOR_RESET;
	}
}

bool Menu::multibotStatus() 
{
	int lockfileInt = open("mutlbit.pid", O_RDWR | O_CREAT, 0640);
    
	return (lockf(lockfileInt, F_TLOCK, 0) != 0)? true : false;
}

void Menu::restartMultibot() 
{
	stopMultibot(); // Wyłącza wszystkie funkcje multibota
	cout << endl;
	startMultibot(); // Włącza wszystkie funkcje multibota
}

void Menu::stopMultibot() 
{
	if(fileIsset("multibot.pid") && multibotStatus()) 
	{
		cout << COLOR_BLUE;
		cout << "Zatrzymywanie multibota. Może to potrwać do 10 sekund." << endl;
		cout << COLOR_RESET;
		fstream pidf;
		pidf.open("multibot.pid", ios::in);
		string pid;
		pidf >> pid;
		if(system(string("kill " + pid).c_str()) == -1) logerAddWarrning("Nie udało się zabić procesu. pid=" + pid);
		int lockfileInt = open("mutlbit.pid", O_RDWR | O_CREAT, 0640);
		for(int i = 0; i < 10; i++) {
			if(lockf(lockfileInt, F_TLOCK, 0) == 0) {
				cout << COLOR_GREEN;
				cout << "Multibot wyłączony" << endl;
				cout << COLOR_RESET;
				return;
			}
			sleep(1);
		}
		cout << COLOR_RED;
		cout << "Nie udało się zarejestrować zmaknięcia multibota w ciągu 10 sekund. Możliwe że zaraz sam się włączy." << endl;
		cout << COLOR_RESET;
	}
	else 
	{
		cout << COLOR_RED;
		cout << "Multibot nie jest uruchomiony." << endl;
		cout << COLOR_RESET;
	}
}

bool Menu::startMultibot() 
{
	if(!demonize()) return false;
    
	bool status; // Zawiera informacje czy jakakolwiek funkcja została uruchamiana
	for(map<string, Function*>::iterator it = functionsMap.begin(); it != functionsMap.end(); it++) // Iteruje po wszystkich funkcjach umieszczonych w mapie
	{ 
		if(it->second->isEnabled()) // Jeżeli funkcja jest ustawiona na rozruch
		{ 
			cout << COLOR_BLUE;
			cout << "Uruchamianie " << it->first << endl;
			cout << COLOR_RESET;
			if(it->second->run()) 
			{ // Jeżeli udało się uruchomić
				cout << COLOR_GREEN;
				cout << "Pomyślnie uruchomiono " << it->first << endl;
				cout << COLOR_RESET;
			}
			else // Jeżeli wystąpił błąd przy uruchamianiu
			{ 
				cout << COLOR_RED;
				cout << "Wystąpił błąd przy uruchamianiu " << it->first << endl;
				cout << COLOR_RESET;
			}
			status = true; // Uruchomiano przynajmniej jedną funkcję
			cout << endl;
		}
	}
	cout << BOLD_ON;
	if(!status) 
	{ // Jeżeli nic nie uruchamiano
		cout << COLOR_RED;
		cout << "Nie było żadnych funkcji do uruchomienia." << endl;
		cout << COLOR_RESET;
		return false;
	}
	else // Jeżeli uruchamiano jakąś funkcję
	{ 
		cout << COLOR_GREEN;
		cout << "Uruchamianie funkcji zostało zakończone." << endl;
		cout << COLOR_BLUE << BOLD_OFF;
		cout << "Jeżeli program nie powrócił do normalnego terminala naciśnij ENTER" << endl;
		cout << COLOR_RESET;
	}
	cout << BOLD_OFF;
    
	dropStdIO();
	return true;
}

void Menu::showHeader() 
{
		cout << COLOR_GREEN;
		cout <<  BOLD_ON << "ExMultibot - Multibot dla serwerów TeamSpeak3" << BOLD_OFF << endl;
        
		if(multibotStatus())    cout << "Status multibota: " << BOLD_ON << "Uruchominy" << BOLD_OFF << endl;
		else                    cout << "Status multibota: " << BOLD_ON << COLOR_RED << "Zatrzymany" << BOLD_OFF <<endl;
        
        cout << COLOR_RESET;
		
		cout << endl;
		cout << COLOR_BLUE;
		cout << "Wybierz numer opcji do wykonania." << endl;
		cout << COLOR_RESET;
}

bool Menu::showFunctions() 
{
	map<int, Function*> functionList; // Mapa przechowująca wskaźniki na fukncje i odpowiadające im id z listy
	bool runable = false;
	
	// Wyświetla standardowe menu
	cout << "1. Uruchom multibota" << endl;
	cout << "2. Wyłącz multibota" << endl;
	cout << "3. Zrestartuj multibota" << endl;
    cout << "4. Ustaw nazwę bota" << endl;
	cout << endl;
	cout << COLOR_BLUE << "Konfiguruj wybraną funkcje: (zielony - funkcja do uruchomienia)" << COLOR_RESET <<  endl;
	
	// Iteruje po każdej funkcji z tablicy funkcji i przypisuje jej id
	int i = 5;
	for(map<string, Function*>::iterator it = functionsMap.begin(); it != functionsMap.end(); it++) 
	{
		functionList[i] = it->second;
		cout << i << ". ";
		if(it->second->isEnabled()) 
		{
			cout << COLOR_GREEN; 
			cout << it->first << endl;
			cout << COLOR_RESET;
			runable = true;
		}
		else 
		{
			cout << COLOR_RED; 
			cout << it->first << endl;
			cout << COLOR_RESET;
		}
		i++;
	}
	
	// Wyświtla ostatnią opcje menu
	cout << COLOR_BLUE <<  endl;
	cout << "0. Wyjdź" << endl;
	cout << COLOR_RESET;
	
	// Pobiera numer opcji od użytkownika
	int chose;
	cin >> chose;
	if(checkCinError()) { // Jeżeli błąd wyświetla odpowiedni komunikat
		sleep(3);
		return false;
	}
	if(chose > i) {
		cout << COLOR_RED;
		cout << "Nie ma takiej opcji!" << endl;
		cout << COLOR_RESET;
		return false;
	}
	if(system("clear") == -1) logerAddWarrning("Nie udało się wyczyścić terminala");
	// -- Pobiera numer opcji od użytkownika
	
	
	// Wybiera odpowiednią opcje
	if(chose < 5) 
	{
		switch(chose) 
		{
			case 0: exit(0); // Wyjście
			case 1: // Uruchomienie multibota
			{
				if(!runable) {
					cout << COLOR_RED;
					cout << "Nie ma żadnych funckji do uruchomienia!" << endl;
					cout << COLOR_RESET;
					break;
				}
				
				return startMultibot();
			}
			break;
			case 2: stopMultibot(); // Zatrzymywanie multibota
            break;
			case 3: // Restart multibota
            {
				if(!runable) 
				{
					cout << COLOR_RED;
					cout << "Nie ma żadnych funckji do uruchomienia!" << endl;
					cout << COLOR_RESET;
					break;
				}
				restartMultibot();
			break;
            }
            case 4:
            {
                string chose1;
                ConfigFile configFile("configs/config.cfg");
                cout << COLOR_GREEN << "Wprowadź nazwę dla bota: " << COLOR_RESET << endl;
                cin >> chose1;
                configFile["general_config"]["nickname"] = chose1;
                configFile.save();
            }
		}
		sleep(3);
		return false;
	}
	else // Jeżeli wybrano konfigurację funkcji
	{ 
		functionList[chose]->config();
		return false;
	}
}

