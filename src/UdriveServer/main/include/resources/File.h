#ifndef _FILE_H_
#define _FILE_H_

#include <string>
#include "../../others/json/json.h"
#include "User.h"



class File{

private:
	std::string id;
	std::string name;
	bool deleted;
	User *owner;
	std::string lastModified;
	User *lastUser;
	std::vector<User*> users;
	std::vector<std::string> labels;
	std::string extension;
	int version;

public:
	File(const Json::Value& json);
	File(const std::string& jsonString);
	~File();

	std::string getId() const;
	std::string getName() const;
	std::string getExtension() const;
	Json::Value getJson() const;
	std::string getJsonString() const;
};


#endif
