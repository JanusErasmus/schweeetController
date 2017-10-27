#ifndef CTEMPPROBE_H
#define CTEMPPROBE_H

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
    float mAnalog;

public:
    cTempProbe();

    void setTemp(float analog){ mAnalog = analog; }
    float getTemp(){ return mAnalog; }
};

#endif // CTEMPPROBE_H
