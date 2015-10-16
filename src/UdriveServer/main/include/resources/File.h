#ifndef _FILE_H_
#define _FILE_H_

#include <string>
#include "../../others/json/json.h"
#include "../database/Database.h"
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
	File(const Json::Value& json, Database &userDB);
	File(const std::string& jsonString, Database &userDB);
	~File();

	std::string getId() const;
	std::string getName() const;
	std::string getExtension() const;
	bool getDeleted() const;
	int getVersion() const;
	User* getOwner() const;
	std::vector<User*> getUsers() const;
	bool isOwner(const User& user) const;
	void increaseVersion();
	bool hasAnyLabel(const std::vector<std::string>& labels) const;
	bool hasPermission(const User& user) const;
	void setDeleted(const bool& state);
	void setName(const std::string& name);
	void setExtension(const std::string& extension);
	void setLabels(const std::vector<std::string> &labels);
	void addUser(User *user);
	void removeUser(const User& user);
	Json::Value getJson() const;
	std::string getJsonString() const;

};


#endif
