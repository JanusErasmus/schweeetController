#ifndef TEMP_PROBE_H_
#define TEMP_PROBE_H_
#include <analog.h>
#include <float.h>

class cTempProbe
{
public:
	enum eType
	{
		LM335,
		PT100
	};

private:
	eType mType;
	cAnalog *mAnalog;

public:
	cTempProbe(eType type, cAnalog *analog);
	virtual ~cTempProbe();

	float getTemp();
};

#endif /* TEMP_PROBE_H_ */
