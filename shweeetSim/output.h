#ifndef COUTPUT_H
#define COUTPUT_H


class cOutput
{

    bool mState;

public:
    cOutput();

    void set(){ mState = true; }
    void reset(){ mState = false; }

    bool getState(){ return mState; }
};

#endif // COUTPUT_H
