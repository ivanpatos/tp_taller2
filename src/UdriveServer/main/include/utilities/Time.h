#ifndef _TIME_H_
#define _TIME_H_

#include <string>

/**
 * Clase que devuelve el tiempo actual.
 */
class Time{

public:
	/**
	 * @return Devuelve el tiempo actual.
	 */
	static std::string getCurrentTime();
};

#endif
