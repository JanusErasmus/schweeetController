#ifndef INPUT_H_
#define INPUT_H_
#include "port.h"

class cInput : public cPort
{
public:
	cInput(uint8_t pin_definition);
	virtual ~cInput();

	bool get();
};

#endif /* INPUT_H_ */
