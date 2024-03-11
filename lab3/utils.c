#include <lcom/lcf.h>

#include <stdint.h>

uint32_t counter_KBC = 0;


int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if(lsb==NULL){
    return 1;
  }
  *lsb=(u_int8_t)(val & 0xFF);
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if(msb==NULL){
    return 1;
  }
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
