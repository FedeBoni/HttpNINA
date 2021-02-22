#include "HttpNINA.h"

HttpNINA::HttpNINA()
{
}

void HttpNINA::init(int port)
{
	_port = port;
	_server = new WiFiServer(port);
}

void HttpNINA::start()
{
	_server->begin();
}

void HttpNINA::stop()
{
	delete _server;
}

bool HttpNINA::listen(bool wait)
{
	bool onListen = true;
	while (onListen)
	{
		_client = _server->available();
		if (_client)
		{
			raw = "";
			//_client.read();
			method = _client.readStringUntil(' ');
			raw += method;
			String w_path = _client.readStringUntil('\n');
			raw += w_path;
			if (method == "GET")
			{
				int q_index = w_path.indexOf('?');
				if (q_index > 0)
				{
					path = w_path.substring(0, q_index);
					readParam(w_path.substring(q_index + 1, w_path.indexOf(' ')));
				}
				else
				{
					path = w_path.substring(0, w_path.indexOf(' '));
				}
				while (_client.available())
				{
					_client.read();
				}
			}
			else if (method == "POST")
			{
				path = w_path.substring(0, w_path.indexOf(' '));
				bool isBlankLine = false;
				while (!isBlankLine)
				{
					String c_line = _client.readStringUntil('\n');
					if (c_line.length() == 1)
					{
						isBlankLine = true;
					}
				}
				//_client.setTimeout(50);
				String q_string = _client.readStringUntil('\n');
				raw += q_string;
				char c;
				while (_client.available())
				{
					c = _client.read();
				}
				readParam(q_string);
			}
			onListen = false;
			return true;
		}
		else
		{
			if (!wait)
			{
				return false;
			}
		}
	}
}

String HttpNINA::getQueryValue(String key)
{
	for (int i = 0; i < 5; i++)
	{
		if (_key[i] == key)
		{
			return _val[i];
		}
	}
	return "-1";
}

void HttpNINA::sendHeader(int cod)
{
	switch (cod)
	{
	case 200:
		_client.println("HTTP/1.1 200 OK");
		_client.println("Content-type:text/html");
		_client.println();
		break;
	case 404:
		_client.println("HTTP/1.1 404 Not Found");
		_client.println();
		break;
	case 405:
		_client.println("HttpNINA/1.1 405 Method Not Allowed");
		_client.println();
		break;
	}
}

void HttpNINA::sendResponse(String resp)
{
	_client.print(resp);
}

void HttpNINA::endResponse()
{
	_client.stop();
}

void HttpNINA::readParam(String w_path)
{
	int next_begin_index = 0;
	int position = 0;
	int next_concat_index = 0;
	//inizializzo i valori a -1
	for (int i = 0; i < 5; i++)
	{
		_val[i] = -1;
	}
	do
	{
		next_concat_index = w_path.indexOf("&", next_begin_index);
		int next_eq_index = w_path.indexOf('=', next_begin_index);
		_key[position] = w_path.substring(next_begin_index, next_eq_index);
		next_begin_index = next_eq_index + 1;
		if (next_concat_index > 0)
		{
			_val[position] = w_path.substring(next_begin_index, next_concat_index);
		}
		else
		{
			_val[position] = w_path.substring(next_begin_index);
		}
		next_begin_index = next_concat_index + 1;
		//next_concat_index = w_path.indexOf('&', next_concat_index + 1);
		position++;
	} while (next_concat_index > 0);
}
