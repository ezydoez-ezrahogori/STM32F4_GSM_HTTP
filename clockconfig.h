
/*
 * clockconfig.h
 *
 *  Created on: Mar 30, 2023
 *      Author: Ezrah Buki
 */

#ifndef CLOCKCONFIG_H_
#define CLOCKCONFIG_H_

#include "stm32f4xx.h"

namespace custom_libraries {

class clock_config {
public:
	clock_config();
	~clock_config();
	void initialize();
};

} /* namespace custom_libraries */

#endif /* CLOCKCONFIG_H_ */
