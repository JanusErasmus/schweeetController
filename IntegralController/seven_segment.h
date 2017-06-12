#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

class cSevenSegment
{
	void sendByte(uint8_t byte);
	uint8_t mDigits[4];
	uint8_t mPoint;

	void putDigit(uint8_t index, bool point);

public:
	cSevenSegment();
	virtual ~cSevenSegment();

	void run();


	void setNumber(float number);


};

extern cSevenSegment SevenSegment;

#endif /* SEVEN_SEGMENT_H_ */
