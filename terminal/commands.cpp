#include "terminal.h"

extern const dbg_entry mainEntry;
extern const dbg_entry backlightEntry;

const dbg_entry* dbg_entries[] =
{
		&helpEntry,
		&mainEntry,
		&backlightEntry,
		0
};
