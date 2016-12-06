#ifndef BUTTON_H_
#define BUTTON_H_

class cButtons
{
	uint8_t mPressed;

public:
	cButtons();
	virtual ~cButtons();

	void handleButton(uint8_t button);

	void run();
};

extern cButtons Buttons;

#endif /* BUTTON_H_ */
