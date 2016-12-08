#ifndef ANALOG_H_
#define ANALOG_H_

class cAnalog
{
	uint8_t mChannel;


public:
	cAnalog(uint8_t channel);
	virtual ~cAnalog();

	uint16_t sample();
};

#endif /* ANALOG_H_ */
