/*
 * RocksDatabase.h
 *
 *  Created on: Oct 21, 2015
 *      Author: tomrea
 */

#ifndef INCLUDE_DATABASE_ROCKSDATABASE_H_
#define INCLUDE_DATABASE_ROCKSDATABASE_H_

#include <string>
#include <vector>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
#include "Database.h"

/**
 * Define el manejo de una base de datos generada con Rocksdb.
 */
class RocksDatabase: public Database {

private:
	std::string path;
	rocksdb::DB *database;

public:
	RocksDatabase();

	/**
	 * Inicializa la base de datos a partir del path.
	 * @param path Path de la base de datos a generar.
	 */
	RocksDatabase(const std::string& path);
	virtual ~RocksDatabase();

	/**
	 * Inicializa la base de datos a partir del path. Si existe la abre, sino la crea.
	 */
	virtual void init();
	virtual std::string getValue(const std::string& key) const;
	virtual bool saveValue(const std::string& key, const std::string& value);
	virtual void deleteRecord(const std::string& key);
	virtual std::vector<std::string> getAllValues() const;
};



#endif /* INCLUDE_DATABASE_ROCKSDATABASE_H_ */
