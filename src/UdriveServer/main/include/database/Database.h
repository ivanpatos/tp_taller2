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
	Database();
	Database(const std::string& path);
	virtual ~Database();
	virtual void init();
	virtual std::string getValue(const std::string& key) const;
	virtual bool saveValue(const std::string& key, const std::string& value);
	virtual void deleteRecord(const std::string& key);
	virtual std::vector<std::string> getAllValues() const;

};


#endif
