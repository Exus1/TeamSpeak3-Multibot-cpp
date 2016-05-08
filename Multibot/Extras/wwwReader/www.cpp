#include "www.hpp"

using namespace std;


bool getWebsiteContent(string website, string &websiteContent) {
    int sock, result;
    string url, urlRest, recvMsg;
    char recvbuff[512];
    addrinfo serverInfo, *cServerInfo = NULL;
    
    memset(&serverInfo, 0, sizeof(addrinfo));
    serverInfo.ai_family = AF_UNSPEC;
    serverInfo.ai_socktype = SOCK_STREAM;
    serverInfo.ai_protocol = IPPROTO_TCP;
    
    
    
    url.insert(0, website, 0, website.find("/"));
    urlRest.insert(0, website, website.find("/"), website.length()-website.find("/"));
    
    getaddrinfo(url.c_str(), string("80").c_str(), &serverInfo, &cServerInfo);
    
    sock = socket(cServerInfo->ai_family, cServerInfo->ai_socktype, cServerInfo->ai_protocol);
    connect(sock, cServerInfo->ai_addr, cServerInfo->ai_addrlen);
    freeaddrinfo(cServerInfo);
    
    string toSend = "GET " + urlRest + " HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";
    
    if(send(sock, toSend.c_str(), toSend.length(), 0) < 1) {
        logerAddWarrning("Nie udało sie wysłać nagłówka http. " + url);
        return false;
    }
    
    
    do {
        result = recv(sock, recvbuff, 511, 0);
        if(result < 0) {
            logerAddWarrning("Nie udało się odebrać danych od serwera www. " + url);
            return false;
        }
        recvMsg += recvbuff;
        memset(&recvbuff, 0, sizeof(recvbuff));
    }while(result > 0);
    
    recvMsg.erase(0, recvMsg.find("\r\n\r\n")+4);
    
    url.clear();
    websiteContent.insert(0, recvMsg, recvMsg.find("\r\n")+2, stoi(url.insert(0, recvMsg, 0, recvMsg.find("\r\n")), nullptr, 16));
    
    return true;
}
 
 