#include "../../main/others/json/json.h"

Json::Value getJsonUser(std::string username,std::string pass, std::string mail ){
	Json::Value valueInput(Json::objectValue);
	valueInput["username"] = username;
	valueInput["password"] = pass;
	valueInput["mail"] = mail;
	valueInput["profilePicture"] = "";
	valueInput["location"] = "";
	valueInput["token"] = "";
	return valueInput;
}

Json::Value getJsonFile(std::string id, std::string name, std::string extension, int version) {
	Json::Value valueInput(Json::objectValue);
	valueInput["id"]= id;
	valueInput["name"] = name;
	valueInput["deleted"] = "";
    valueInput["extension"] = extension;
	valueInput["lastModified"] = "";
	valueInput["username"] = "";
	std::stringstream ss;
	ss << version;
	valueInput["version"] = std::string(ss.str());
	return valueInput;
}

Json::Value getJsonFolder(std::string id, std::string name){
	Json::Value inputValue;
	inputValue["id"] = id;
	inputValue["name"] = name;
	return inputValue;
}

template <typename T>
bool compareVectors(std::vector<T> a, std::vector<T> b)
{
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    return (a == b);
}
