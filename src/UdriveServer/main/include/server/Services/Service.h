#ifndef _SERVICE_H_
#define _SERVICE_H_

#include <string>

class Service{
public:
	virtual ~Service(){}
	virtual std::string execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const = 0;
        virtual const char* name() const = 0;
};

#endif
