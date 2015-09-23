#ifndef _FOLDER_H_
#define _FOLDER_H_

#include <string>
#include "../../others/json/json.h"
#include "../database/Database.h"
#include "File.h"


class Folder{

private:
	std::string id;
	std::string name;
	std::vector<File*> fileChildren;
	std::vector<Folder*> folderChildren;

public:
	Folder(const Json::Value& json);
	Folder(const std::string& jsonString, Database &userDB, Database &folderDB, Database &fileDB);
	~Folder();

	std::string getId() const;
	std::string getName() const;
	std::vector<Folder*> getFolderChildren() const;
	std::vector<File*> getFileChildren() const;
	Json::Value getJson() const;
	std::string getJsonString() const;
	void addFolderChildren(Folder *folder);
	void addFileChildren(File *file);
	void removeFileChildren(File *file);
	bool hasFolder(const std::string& folderName) const;
	bool hasFile(const std::string& fileName, const std::string& fileExtension) const;

};


#endif
