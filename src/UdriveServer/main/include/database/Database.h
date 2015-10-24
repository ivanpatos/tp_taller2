#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <string>
#include <vector>

class Database {

public:
	virtual ~Database(){};
	virtual void init()=0;
	virtual std::string getValue(const std::string& key) const=0;
	virtual bool saveValue(const std::string& key, const std::string& value)=0;
	virtual void deleteRecord(const std::string& key)=0;
	virtual std::vector<std::string> getAllValues() const=0;
};


#endif
