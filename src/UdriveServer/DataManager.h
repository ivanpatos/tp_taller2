#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
#include "User.h"

using namespace rocksdb;
using namespace std;

class DataManager{

private:
	string path;
	DB *database;
	vector<ColumnFamilyHandle*> columnFamilyHandler;			//0: default, 1: users, 2: documents

	DataManager();
	~DataManager();
	DataManager(const DataManager&);
	DataManager& operator=(const DataManager&);


public:

	static DataManager& Instance();

	User * getUser(const string& key);
	bool saveUser(const User& user);


};


#endif
