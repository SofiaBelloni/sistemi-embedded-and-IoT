#ifndef __CONNECTION_MANAGER__
#define __CONNECTION_MANAGER__

class ConnectionManager{
public:
    
    ConnectionManager(char* ssid, char* password);
    int SendData(char* address, const char* message);
    
private:
    bool IsConnected();
};

#endif