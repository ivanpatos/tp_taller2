#ifndef _FOLDER_H_
#define _FOLDER_H_

#include <string>
#include "../../others/json/json.h"
#include "File.h"

class Folder{

private:
	std::string id;
	std::string name;
	std::vector<File*> fileChildren;
	std::vector<Folder*> folderChildren;

public:
	Folder(const Json::Value& json);
	Folder(const std::string& jsonString);
	~Folder();

	std::string getId() const;
	std::string getName() const;
	Json::Value getJson() const;
	std::string getJsonString() const;
	void addFolderChildren(Folder *folder);
	void addFileChildren(File *file);
	bool hasFolder(const std::string& folderName) const;
	bool hasFile(const std::string& fileName, const std::string& fileExtension) const;

};


#endif
