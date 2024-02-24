#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  *lsb=(u_int8_t)(val & 0xFF);
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  *msb=(u_int8_t)((val >>8)& 0xFF);
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  if (value == NULL)
    return 1;
  uint32_t temp;
  if(sys_inb(port,&temp)!=0)
    return 1;
  *value=(u_int8_t)temp;
  return 0;
}
