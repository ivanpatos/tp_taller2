#include "../../include/database/Database.h"


Database::Database(const std::string& path): path(path){
	rocksdb::Options options;
	options.create_if_missing = true;
	rocksdb::Status status = rocksdb::DB::Open(options, this->path, &this->database);
}

Database::~Database(){
	delete this->database;
	this->database = NULL;
}

std::string Database::getValue(const std::string& key) const{
	std::string value = "";
	this->database->Get(rocksdb::ReadOptions(), key, &value);
	return value;
}

bool Database::saveValue(const std::string& key, const std::string& value){
	rocksdb::Status status = this->database->Put(rocksdb::WriteOptions(), key, value);
	return status.ok();
}

void Database::deleteRecord(const std::string& key){
	this->database->Delete(rocksdb::WriteOptions(), key);
}

std::vector<std::string> Database::getAllValues(){
	std::vector<std::string> vector;
	rocksdb::Iterator* iterator = this->database->NewIterator(rocksdb::ReadOptions());
	for (iterator->SeekToFirst(); iterator->Valid(); iterator->Next())
		vector.push_back(iterator->value().ToString());
	delete iterator;
	return vector;
}
