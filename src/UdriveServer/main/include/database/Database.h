#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <string>
#include <vector>

/**
 * Clase que define el manejo de una base de datos del tipo key-value.
 */
class Database {

public:
	virtual ~Database(){};

	/**
	 * Inicializa la base de datos.
	 */
	virtual void init()=0;

	/**
	 * Obtiene el value a partir de la key.
	 * @param key Key del value a obtener.
	 * @return Value del key pasado.
	 */
	virtual std::string getValue(const std::string& key) const=0;

	/**
	 * Guarda el par key-value.
	 * @param key Key.
	 * @param value Value.
	 * @return Bool indicando si el registro fue grabado con éxito.
	 */
	virtual bool saveValue(const std::string& key, const std::string& value)=0;

	/**
	 * Elimina el registro a partir de la key pasada.
	 * @param key Key del registro a borrar.
	 */
	virtual void deleteRecord(const std::string& key)=0;

	/**
	 * Devuelve todos los values de la base de datos.
	 * @return Vector con todos los values de la base de datos.
	 */
	virtual std::vector<std::string> getAllValues() const=0;
};


#endif
