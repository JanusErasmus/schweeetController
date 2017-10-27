#include "nvm.h"

uint8_t eeprom_read_byte(uint8_t address)
{

    switch(address)
    {
    case ADDRES_CONTROLLING:
        return 1;

    case ADDRES_SETPOINT:
        return 12;
    }

    return 0;
}

void eeprom_write_byte(uint8_t , uint8_t )
{

}
