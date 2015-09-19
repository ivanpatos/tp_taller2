#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <string>
#include <vector>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"


class Database{

private:
	std::string path;
	rocksdb::DB *database;

public:
	Database(const std::string& path);
	~Database();
	std::string getValue(const std::string& key) const;
	bool saveValue(const std::string& key, const std::string& value);
	void deleteRecord(const std::string& key);
	std::vector<std::string> getAllValues();

};


#endif
