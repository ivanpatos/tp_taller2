#ifndef _VERSION_H_
#define _VERSION_H_

#include <string>
#include "../../others/json/json.h"


class Version{

private:
	std::string id;
	std::string data;

public:
	Version(const std::string& id, const std::string& data);
	~Version();

	std::string getData() const;
	std::string getId() const;
};


#endif
