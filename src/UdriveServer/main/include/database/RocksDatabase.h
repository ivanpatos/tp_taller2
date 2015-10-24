/*
 * RocksDatabase.h
 *
 *  Created on: Oct 21, 2015
 *      Author: tomrea
 */

#ifndef INCLUDE_DATABASE_ROCKSDATABASE_H_
#define INCLUDE_DATABASE_ROCKSDATABASE_H_

#include <string>
#include <vector>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
#include "Database.h"

class RocksDatabase: public Database {

private:
	std::string path;
	rocksdb::DB *database;

public:
	RocksDatabase();
	RocksDatabase(const std::string& path);
	virtual ~RocksDatabase();
	virtual void init();
	virtual std::string getValue(const std::string& key) const;
	virtual bool saveValue(const std::string& key, const std::string& value);
	virtual void deleteRecord(const std::string& key);
	virtual std::vector<std::string> getAllValues() const;
};



#endif /* INCLUDE_DATABASE_ROCKSDATABASE_H_ */
