#include "../../include/database/DataManager.h"


DataManager::DataManager() : path("./database"), columnFamilyHandler(5){
	rocksdb::Options options;
	options.create_if_missing = true;
	rocksdb::Status status = rocksdb::DB::Open(options, this->path, &this->database);
	if (status.ok()){
		database->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), rocksdb::kDefaultColumnFamilyName, &this->columnFamilyHandler[0]);
		database->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), "users", &this->columnFamilyHandler[1]);
		database->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), "folders", &this->columnFamilyHandler[2]);
		database->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), "files", &this->columnFamilyHandler[3]);
		database->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), "data", &this->columnFamilyHandler[4]);
		for (rocksdb::ColumnFamilyHandle *columnFamiliy : this->columnFamilyHandler)
			delete columnFamiliy;
		delete this->database;
	}

	std::vector<rocksdb::ColumnFamilyDescriptor> columnFamiliesDescriptor;
	columnFamiliesDescriptor.push_back(rocksdb::ColumnFamilyDescriptor(rocksdb::kDefaultColumnFamilyName, rocksdb::ColumnFamilyOptions()));
	columnFamiliesDescriptor.push_back(rocksdb::ColumnFamilyDescriptor("users", rocksdb::ColumnFamilyOptions()));
	columnFamiliesDescriptor.push_back(rocksdb::ColumnFamilyDescriptor("folders", rocksdb::ColumnFamilyOptions()));
	columnFamiliesDescriptor.push_back(rocksdb::ColumnFamilyDescriptor("files", rocksdb::ColumnFamilyOptions()));
	columnFamiliesDescriptor.push_back(rocksdb::ColumnFamilyDescriptor("data", rocksdb::ColumnFamilyOptions()));
	rocksdb::DB::Open(rocksdb::DBOptions(), this->path, columnFamiliesDescriptor, &this->columnFamilyHandler, &this->database);
}

DataManager::~DataManager(){
	for (rocksdb::ColumnFamilyHandle *columnFamiliy : this->columnFamilyHandler)
		delete columnFamiliy;
	delete this->database;
}

DataManager& DataManager::Instance(){
	static DataManager instance;
	return instance;
}

User * DataManager::getUser(const std::string& key){
	std::string value = "";
	this->database->Get(rocksdb::ReadOptions(), this->columnFamilyHandler[1], key, &value);
	if (value != "")
		return new User(value);
	else
		return NULL;
}

bool DataManager::saveUser(const User& user){
	std::string key = user.getUsername();
	std::string value = user.getJsonString();
	rocksdb::Status status = this->database->Put(rocksdb::WriteOptions(), this->columnFamilyHandler[1], key, value);
	return status.ok();
}

std::vector<User*> DataManager::getAllUsers(){
	std::vector<User*> userList;
	rocksdb::Iterator* iterator = this->database->NewIterator(rocksdb::ReadOptions(), this->columnFamilyHandler[1]);
	for (iterator->SeekToFirst(); iterator->Valid(); iterator->Next()){
		User* user = new User(iterator->value().ToString());
		userList.push_back(user);
	}
	delete iterator;
	return userList;
}

Folder * DataManager::getFolder(const std::string& key){
	std::string value = "";
	this->database->Get(rocksdb::ReadOptions(), this->columnFamilyHandler[2], key, &value);
	if (value != "")
		return new Folder(value);
	else
		return NULL;
}

bool DataManager::saveFolder(const Folder& folder){
	std::string key = folder.getId();
	std::string value = folder.getJsonString();
	rocksdb::Status status = this->database->Put(rocksdb::WriteOptions(), this->columnFamilyHandler[2], key, value);
	return status.ok();
}

void DataManager::deleteFolder(const std::string& key){
	this->database->Delete(rocksdb::WriteOptions(), this->columnFamilyHandler[2], key);
}

File * DataManager::getFile(const std::string& key){
	std::string value = "";
	this->database->Get(rocksdb::ReadOptions(), this->columnFamilyHandler[3], key, &value);
	if (value != "")
		return new File(value);
	else
		return NULL;
}

bool DataManager::saveFile(const File& file){
	std::string key = file.getId();
	std::string value = file.getJsonString();
	rocksdb::Status status = this->database->Put(rocksdb::WriteOptions(), this->columnFamilyHandler[3], key, value);
	return status.ok();
}

Version * DataManager::getVersion(const std::string& key){
	std::string value = "";
	this->database->Get(rocksdb::ReadOptions(), this->columnFamilyHandler[4], key, &value);
	if (value != "")
		return new Version(key, value);
	else
		return NULL;
}

bool DataManager::saveVersion(const Version& version){
	std::string key = version.getId();
	std::string value = version.getData();
	rocksdb::Status status = this->database->Put(rocksdb::WriteOptions(), this->columnFamilyHandler[4], key, value);
	return status.ok();
}


