#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

#include <string>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
#include "../resources/User.h"
#include "../resources/Folder.h"
#include "../resources/File.h"
#include "../resources/Version.h"


class DataManager{

private:
	std::string path;
	rocksdb::DB *database;
	std::vector<rocksdb::ColumnFamilyHandle*> columnFamilyHandler;			//0: default, 1: users, 2: folders. 3:files

	DataManager();
	~DataManager();
	DataManager(const DataManager&);
	DataManager& operator=(const DataManager&);


public:

	static DataManager& Instance();

	User * getUser(const std::string& key);
	bool saveUser(const User& user);
	std::vector<User*> getAllUsers();

	Folder * getFolder(const std::string& key);
	bool saveFolder(const Folder& folder);
	void deleteFolder(const std::string& key);

	File * getFile(const std::string& key);
	bool saveFile(const File& file);

	Version * getVersion(const std::string& key);
	bool saveVersion(const Version& version);

};

#endif
