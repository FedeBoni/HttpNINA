#ifndef HTTPNINA_H
#define HTTPNINA_H

#include "Arduino.h"
#include <WiFiNINA.h>

class HttpNINA
{

private:
  WiFiServer *_server;
  WiFiClient _client;
  int _port;
  String _key[5];
  String _val[5];
  void readParam(String w_path);

public:
  HttpNINA();
  void init(int port);
  String getQueryValue(String key);
  void sendHeader(int cod);
  void sendResponse(String resp);
  void sendRaw(String raw);
  bool listen(bool wait = true);
  void start();
  void stop();
  String method;
  String path;
  String host;
  String raw;
};

#endif
