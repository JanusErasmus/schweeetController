#ifndef MENU_SELECT_PROBE_H_
#define MENU_SELECT_PROBE_H_
#include "menu.h"

class cMenuSelectProbe : public cMenu
{
	uint8_t mSelection;

	void setCursor(uint8_t probe);

public:
	cMenuSelectProbe(cMenuManager *manager);
	virtual ~cMenuSelectProbe();

	void handleButton(cButtonListner::eButtons button);
};

#endif /* MENU_SELECT_PROBE_H_ */
