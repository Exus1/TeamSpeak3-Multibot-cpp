#include "PokeBot.hpp"

using namespace std;

PokeBot::PokeBot(Ts3API &api) : api(api) 
{
	if(!dirIsset("configs/functions/PokeBot")) if(system("mkdir configs/functions/PokeBot") == -1) logerAddWarrning("Nie udało sie stworzyć folderu konfiguracyjnego funkcji PokeBot");
	
	if(!fileIsset("configs/functions/PokeBot/config.cfg")) createConfig();
}

bool PokeBot::run() 
{
	th = new thread(bind(&startFunctionInThread, this));
    return (th != NULL)? true : false;
}

bool PokeBot::stop() 
{
	if(isRuning() && !loopEnd) 
	{
		loopEnd = true;
		for(int i = 0; i <10; i++) {
			if(loopEnded) {
				loopEnded = false;
				loopEnd = false;
				return true;
			}
			//sleep(1);
		}
		return false;
	}
	else 
	{
		return false;
	}
}
	
string PokeBot::status() 
{
	return "TEST";
}
	
bool PokeBot::isRuning() 
{
	return (th != NULL)? true : false;
}
	
bool PokeBot::isEnabled() 
{
	return (configFile["general_config"]["enable"] == "true")? true : false;
}

void PokeBot::operator()() 
{
	map<string, string> ignoredGroups, adminGroups, clientGroups;
	vector<string> channelList = configFile.explode(configFile["general_config"]["channels"], ",");
	map<string, time_t> channelTimes;
	map<string, clientInfo> clientList, adminList;
    map<string, map<string, clientInfo>> channelUsers, pokedAdmins;
	bool poked = false, loopBreak = false, oneChannel = false;
	unsigned int clid;
    int timePoke;
    
    if((channelList.size() > 0) && (channelList[0] != "0"))
	while(true)
	{
		// Pętla wszystkich kanałów
		for(size_t i = 0; i < channelList.size(); i++) 
		{
            if(configFile["channel_"+channelList[i]]["enable"] == "false") continue;
            oneChannel = true;
            
			// Wczytanie ignorowanych grup
            ignoredGroups = configFile.explodeToMap(configFile["channel_"+channelList[i]]["ignored_groups"], ",");
            
			// Wczytywanie gup administratorów
			adminGroups = configFile.explodeToMap(configFile["channel_"+channelList[i]]["admin_groups"], ",");
			
			
			// Pobieranie administratorów
            for(map<string, string>::iterator it = adminGroups.begin(); it != adminGroups.end(); it++) {
                if(it->second != "0")
                    if(api.trystoi(it->second, clid)) api.getServerGroupClientList(adminList, clid, "cldbid", true);
            }
                    
			// Pobieranie listy użytkowników na serwerze
			api.getChannelClientList(clientList, channelList[i], "clid", "-groups");
			
			// Petla wszystkich użytkowników danego kanału
			for(map<string, clientInfo>::iterator it = clientList.begin(); it != clientList.end(); it++) 
			{
                //if(channelUsers[channelList[i]][it->first] == it->second) continue;
                    
				loopBreak = false;
				
                // Odczyt grup danego użytkownika
				clientGroups = configFile.explodeToMap(it->second["server_groups"], ",");
                
				// Wiadomość kanału
                if(!(channelUsers[channelList[i]][it->first] == it->second))
                    if(!it->second.sendMessage(configFile["channel_"+channelList[i]]["user_message_welcome"])) 
                        logerAddWarrning("Nie udało się wysłać wiadomości do użytkownika. (PokeBot)");
				
				// Pętla grup pojedyńczego użytkownika. Sprawdza czy ma ignorowaną lub jest jednym z adminów
				for(map<string, string>::iterator it1 = clientGroups.begin(); it1 != clientGroups.end(); it1++) 
                    if(!ignoredGroups[it1->second].empty() || !adminGroups[it1->second].empty()) loopBreak = true;

				// Przechodzi do następnej iteracji jeśli użytkownik posiada ignorowaną grupę
				if(loopBreak) continue;
				
				// Jeżli nie jest administratorem lub nie ma ignorowanej grupy
				
				// Pętla administratorów
				for(map<string, clientInfo>::iterator it1 = adminList.begin(); it1 != adminList.end(); it1++) 
				{
					if(it1->second.isOnline()) {
                        for(map<string, string>::iterator itt = it1->second.info.begin(); itt != it1->second.info.end(); itt++){
                            cout << "[ " << itt->first << " ] => " << itt->second << endl;
                        }
                        if(!pokedAdmins[channelList[i]][it1->first]["time_to_poke"].empty()) {
                            if(api.trystoi(pokedAdmins[channelList[i]][it1->first]["time_to_poke"], timePoke) && (timePoke > time(NULL))) {
                                poked = true;
                                continue;
                            }
                        }
                        
						if(!it1->second.poke(configFile["channel_"+channelList[i]]["admin_message"]))
                            logerAddWarrning("Nie udało się wysłać poke do administratora. (PokeBot");
                        else {
                            poked = true; 
                            pokedAdmins[channelList[i]][it1->first] = it1->second;
                            if(api.trystoi(configFile["channel_"+channelList[i]]["poke_time"], timePoke))
                                pokedAdmins[channelList[i]][it1->first]["time_to_poke"] = to_string(time(NULL) + 20);
                        }
					}
				}
				
                if(!(channelUsers[channelList[i]][it->first] == it->second)) {
                    if(poked) 
                    {
                        if(!it->second.sendMessage(configFile["channel_"+channelList[i]]["user_message_success"])) 
                            logerAddWarrning("Nie udało się wysłać wiadomości do użytkownika. (PokeBot)");
                    }
                    else 
                    {
                        if(!it->second.sendMessage(configFile["channel_"+channelList[i]]["user_message_failed"])) 
                            logerAddWarrning("Nie udało się wysłać wiadomości do użytkownika. (PokeBot)");
                    }
                }
				
                poked = false;
                channelUsers[channelList[i]].clear();
                channelUsers[channelList[i]] = clientList;
			}
			
		}
        
        if(!oneChannel) {
            logerAddWarrning("Pokebot został zatrzymany z powodu braku uruchomionych kanałów");
            loopEnd = true;
        }
		
		
		
		if(loopEnd) {
			loopEnded = true;
			return;
		}
	}
    logerAddInfo("Nie było żadnych kanałów do sprawdzania. Pokebot nie został uruchomiony");
}

void PokeBot::configureChannel(string id) 
{
	if(configFile["channel_"+id].empty()) 
	{
		configFile["channel_"+id]["user_message_failed"] = "Aktualnie nie ma żadengo administratora.";
		configFile["channel_"+id]["user_message_success"] = "Administrator został powiadomiony!";
		configFile["channel_"+id]["user_message_welcome"] = "Za chwilę administrator zostanie powiadomiony";
		configFile["channel_"+id]["admin_message"] = "Ktoś potrzebuje twojej pomocy!";
		configFile["channel_"+id]["ignored_groups"] = "0";
		configFile["channel_"+id]["admin_groups"] = "0";
		configFile["channel_"+id]["ignored_admin_groups"] = "0";
		//configFile["channel_"+id]["protect_time"] = "5";
		configFile["channel_"+id]["poke_time"] = "5";
		configFile["channel_"+id]["enable"] = "true";
		configFile.save();
	}
	
	while(true) 
	{
		cout << COLOR_BLUE;
		cout << "Konfiguracja kanału. id. " + id << endl;
		cout << COLOR_RESET;
	
		cout << "1. Ustaw wiadomość dla użytkowników kanale kiedy administrator nie został powiadomiony" << endl;
		cout << "2. Ustaw wiadomość dla użytkowników kanale kiedy administrator został powiadomiony" << endl;
		cout << "3. Ustaw wiadomość po wejściu na kanał" << endl;
		cout << "4. Ustaw wiadomość powiadamiającą administratorów" << endl;
		cout << "5. Dodaj ignorowane grupy. (Nie dostaje powiadomienia oraz nie wysyła poke)" << endl;
		cout << "6. Dodaj grupę administratora" << endl;
		//cout << "7. Ustaw czas zabezpieczenia przed spamem" << endl;
		cout << "7. Ustaw czas między kolejnymi powiadomieniami" << endl;
		cout << endl;
		
        cout << COLOR_GREEN;
		if(configFile["channel_"+id]["enable"] == "true")   cout << "8. Wyłącz powiadomienia z tego kanału" << endl;
		else                                                cout << "8. Włącz powiadomienia z tego kanału" << endl;
		cout << COLOR_RESET;
        
		cout << endl;
		cout << "0. Wyjdź" << endl;
	
		unsigned short input;
		cin >> input;
		checkCinError();
	
		if(input > 8) {
			cout << COLOR_RED << "Nie ma takiej opcji" << COLOR_RESET << endl;
			sleep(3);
			if(system("clear") == -1) logerAddWarrning("Nie udało się wyczyścić terminala");
		}
		
		string chose;
		switch(input) 
		{
			case 0: return; // Wyjście
			case 1: // Ustawianie wiadomości
			{
				cout << COLOR_BLUE << "Podaj wiadomość jaką dostanie użytkownik jeżeli żadnego administratora nie ma na serwerze" << COLOR_RESET << endl;
				cin >> chose;
				configFile["channel_"+id]["user_message_failed"] = chose;
				chose.clear();
				break;
			}
			case 2:
			{
				cout << COLOR_BLUE << "Podaj wiadomość jaką dostanie użytkownik kanału po powiadomieniu administratora" << COLOR_RESET << endl;
				cin >> chose;
				configFile["channel_"+id]["user_message_success"] = chose;
				chose.clear();
				break;
			}
			case 3:
			{
				cout << COLOR_BLUE << "Podaj wiadomość jaką dostanie użytkownik po wejściu na kanał" << COLOR_RESET << endl;
				cin >> chose;
				configFile["channel_"+id]["user_message_welcome"] = chose;
				chose.clear();
				break;
			}
			case 4: // Powiadmienie admina
			{
				cout << COLOR_BLUE << "Podaj wiadomość jaką dostanie administrator kiedy użytkownik będzie na kanale (poke)" << COLOR_RESET << endl;
				cin >> chose;
				configFile["channel_"+id]["admin_message"] = chose;
				chose.clear();
				break;
			}
			case 5: // Ignorowane grupy
			{
				cout << COLOR_BLUE << "Wpisz id grupy która ma być ignorowana" << COLOR_RESET << endl;
				map<string, string> ignoredGroups = configFile.explodeToMap(configFile["channel_"+id]["ignored_admin_groups"], ",");
				cin >> chose;
				if(ignoredGroups[chose].empty()) {
					cout << COLOR_RED << "Taka grupa jest już dodana" << COLOR_RESET << endl;
					break;
				}
                
				if(configFile["channel_"+id]["ignored_admin_groups"].empty() || (configFile["channel_"+id]["ignored_admin_groups"] == "0"))   
                    configFile["channel_"+id]["ignored_admin_groups"] = chose;
				else                                                            
                    configFile["channel_"+id]["ignored_admin_groups"] = "," + chose;
                
				chose.clear();
				break;
			}
			case 6: // Dodawanie grupy administratora
			{
				cout << COLOR_BLUE << "Wpisz id grupy administratora" << COLOR_RESET << endl;
				cin >> chose;
                
				if(configFile["channel_"+id]["admin_groups"].empty() || (configFile["channel_"+id]["admin_groups"] == "0"))   
                    configFile["channel_"+id]["admin_groups"] = chose;
				else                                                    
                    configFile["channel_"+id]["admin_groups"] = "," + chose;
                
				chose.clear();
				break;
			}
            /*
			case 7:
			{
				cout << COLOR_BLUE << "Wprowadź czas zabezpieczenia przed spamem. (Czas po wyjściu wszystkich użytkowników z kanału w którym administracja nie będzie powiadamiana)" << COLOR_RESET << endl;
				cin >> chose;
				configFile["channel_"+id]["protect_time"] = chose;
				chose.clear();
				break;
			}
             */
			case 7:
			{
				cout << COLOR_BLUE << "Wprowadź ilość sekund między kolejnymi powiadomieniami administratora (poke)" << COLOR_RESET << endl;
				cin >> chose;
				configFile["channel_"+id]["poke_time"] = chose;
				break;
			}
			case 8:
			{
				if(configFile["channel_"+id]["enable"] == "true") {
					configFile["channel_"+id]["enable"] = "false";
					cout << COLOR_GREEN << "Wyłączono powiadomienia z tego kanału" << COLOR_RESET << endl;
				}else {
					configFile["channel_"+id]["enable"] == "true";
					cout << COLOR_GREEN << "Włączono powiadomienia na tym kanale" << COLOR_RESET << endl;
				}
			}
			configFile.save();
		}
        if(system("clear") == -1) logerAddWarrning("Nie udało sięwyczyścić terminala");
	}
}



void PokeBot::config() 
{
	while(true) 
	{
		cout << COLOR_GREEN;
		cout << "Konfiguracja PokeBot'a" << endl;
		cout << endl;
        cout << COLOR_BLUE << "Skonfigurowane kanały: " << configFile["general_config"]["channels"] << COLOR_RESET << endl;
        cout << endl;
		cout << COLOR_GREEN << "Wybierz opcje której chcesz użyć:"<< endl;
		cout << COLOR_RESET;
		
		if(configFile["general_config"]["enable"] == "true")    cout << "1. Wyłącz" << endl;
		else                                                    cout << "1. Włącz" << endl;
		
		cout << "2. Dodaj kanał" << endl;
		cout << "3. Usuń nakanł" << endl;
		cout << endl;
		cout << "0. Wstecz" << endl;
		
		short input;
		cin >> input;
		checkCinError();
		
		if(input > 3) {
			cout << COLOR_RED << "Nie ma takiej opcji" << COLOR_RESET << endl;
			sleep(3);
			if(system("clear") == -1) logerAddWarrning("Nie udało się wyczyścić terminala");
		}
		
        
		switch(input) 
		{
			case 0: return; // WYjście
			case 1: // Włącz/Wyłącz
			{
				if(configFile["general_config"]["enable"] == "true") {
					configFile["general_config"]["enable"] = "false";
				}else {
					configFile["general_config"]["enable"] = "true";
				}
				configFile.save();
				break;
			}
			case 2: // Dodawanie kanału
			{
                string chose;
				cout << COLOR_GREEN;
				cout << "Wprowadź id kanału" << endl;
				cout << COLOR_RESET;
				cin >> chose;
                
                map<string, string> channelList = configFile.explodeToMap(configFile["general_config"]["channels"], ",");
                
                if(!channelList[chose].empty()) {
                    cout << COLOR_RED << "Kanał o podanym id już istnieje" << COLOR_RESET << endl;
                    sleep(3);
                    break;
                }
                
				if(configFile["general_config"]["channels"].empty() || (configFile["general_config"]["channels"] == "0,0")) 
                    configFile["general_config"]["channels"] = chose;
				else
					configFile["general_config"]["channels"] += "," + chose;
				
                if(system("clear") == -1) logerAddWarrning("Nie udało się wyczyścić terminala");
                
				configureChannel(chose);
				break;
			}
            //TODO: Usuwanie kanału
			case 3: // Usuwanie kanału
			{
				string chose; bool status = false;
                cout << COLOR_GREEN;
				cout << "Wprowadź id kanału do usunięcia" << endl;
				cout << COLOR_RESET;
				cin >> chose;
                
                if(!configFile["general_config"]["channels"].empty()) 
                {
                    vector<string> channelList = configFile.explode(configFile["general_config"]["channels"], ",");
                    if((channelList.size() == 1) && (channelList[0] != chose)) {
                        cout << COLOR_RED << "Nie ma takiego kanału" << endl;
                    }else {
                        configFile["general_config"]["channels"].clear();
                        for(size_t i = 0; i < channelList.size(); i++) {
                            if(channelList[i] == chose) {
                                status = true;
                                configFile.fileContent.erase("channel_"+chose);
                                continue;
                            }else if(configFile["general_config"]["channels"].empty()) {
                                configFile["general_config"]["channels"] = channelList[i];
                            }
                            else {
                                configFile["general_config"]["channels"] += ","+channelList[i];
                            }
                        }
                    }
                    if(status)
                        cout << COLOR_GREEN << "Pomyślnie usunięto kanał" << COLOR_RESET << endl;
                    else
                        cout << COLOR_RED << "Podany kanał nie istnieje" << COLOR_RESET << endl;

                    configFile.save();
                    sleep(3);
                    if(system("clear") == -1) logerAddWarrning("Nie udało się wyczyścić terminala");  
                }
                break;
            }
		}
        
		if(system("clear") == -1) logerAddWarrning("Nie udało się wyczyścić terminala");
	}
}

void PokeBot::createConfig() 
{
	configFile["general_config"]["enable"] = "false";
	configFile["general_config"]["channels"] = "0,0";
	configFile.save();
}