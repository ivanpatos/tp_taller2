#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

#include <string>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
#include "../resources/User.h"


class DataManager{

private:
	std::string path;
	rocksdb::DB *database;
	std::vector<rocksdb::ColumnFamilyHandle*> columnFamilyHandler;			//0: default, 1: users, 2: documents

	DataManager();
	~DataManager();
	DataManager(const DataManager&);
	DataManager& operator=(const DataManager&);


public:

	static DataManager& Instance();

	User * getUser(const std::string& key);
	bool saveUser(const User& user);


};


#endif
