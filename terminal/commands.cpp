#include "terminal.h"

extern const dbg_entry mainEntry;
extern const dbg_entry backlightEntry;
extern const dbg_entry outputEntry;

const dbg_entry* dbg_entries[] =
{
		&helpEntry,
		&mainEntry,
		&backlightEntry,
		&outputEntry,
		0
};
