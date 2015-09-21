#ifndef _NON_EXISTENT_SERVICE_H_
#define _NON_EXISTENT_SERVICE_H_

#include <string>
#include "Service.h"


class NonExistentService : public Service{
public:
	NonExistentService();
	~NonExistentService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const;
};


#endif
