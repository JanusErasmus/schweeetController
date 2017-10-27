#ifndef NVM_H
#define NVM_H
#include <QDebug>

#include <stdint.h>
#define printp(_X, ...) qDebug(_X, ##__VA_ARGS__)


#define ADDRES_SETPOINT     0
#define ADDRES_CONTROLLING  1

uint8_t eeprom_read_byte(uint8_t);
void eeprom_write_byte(uint8_t, uint8_t);

#endif // NVM_H
