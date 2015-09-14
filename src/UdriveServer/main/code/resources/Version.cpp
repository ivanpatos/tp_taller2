#include "../../include/resources/Version.h"

Version::Version(const std::string& id, const std::string& data){
	this->id = id;
	this->data = data;
}

Version::~Version(){
}

std::string Version::getData() const{
	return this->data;
}

std::string Version::getId() const{
	return this->id;
}
