#ifndef _SERVICE_MANAGER_H_
#define _SERVICE_MANAGER_H_

#include "json/json.h"
#include "User.h"
#include "DataManager.h"
#include "HttpResponse.h"

using namespace std;

class ServiceManager{

private:
	bool authenticateRequest(const User& user, const string& token);

public:
	ServiceManager();
	~ServiceManager();

	string createUser(const string& data);
	string getUser(const string& username, const string& token, const string& queryUsername);

};

#endif
