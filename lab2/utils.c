#include <lcom/lcf.h>

#include <stdint.h>

#include <lcom/utils.h>
int (util_sys_inb)(int port, uint8_t *byte){
  uint32_t temp;
  if(sys_inb(port,&temp)!=0)
    return 1;
  *byte= (temp & 0xFF);
  return 0;
}
int (util_get_LSB)(uint16_t val, uint8_t *lsb){
  return 1;
}
int (util_get_MSB)(uint16_t val, uint8_t *msb){
  return 1;
  
}








































/* 
int (util_sys_inb)(int port, uint8_t *byte){
  if(byte==NULL)
    return 1;
  uint32_t temp;
  if(sys_inb(port, &temp)!=0)
    return 1;
  *byte=(temp & 0xFF);
  return 0;
}
int (util_get_LSB)(uint16_t val, uint8_t *lsb){
  if(lsb==NULL)
    return 1;
  *lsb= val & 0xFF;
  return 0;
}
int (util_get_MSB)(uint16_t val, uint8_t *msb){
  if(msb==NULL)
    return 1;
  *msb= (val>>8) & 0xFF;
  return 0;
} */





































/* int (util_sys_inb)(int port, uint8_t *byte){
  if(byte==NULL)
    return 1;
  uint32_t temp;
  if(sys_inb(port,&temp)!=0)
    return 1;
  *byte=0xFF & temp;
  return 0;
}
int (util_get_LSB)(uint16_t val, uint8_t *lsb){
  if(lsb == NULL)
    return 1;
  *lsb=(val & 0xFF);
  return 0;
}

int (util_get_MSB)(uint16_t val, uint8_t *msb){
  if(msb == NULL)
    return 1;
  *msb=((val >>8)& 0xFF);
  return 0;
} */


































/* int (util_sys_inb)(int port, uint8_t *byte){
  if(byte==NULL)
    return 1;
  uint32_t temp;
  if(sys_inb(port, &temp)!=0)
    return 1;
  *byte=0xFF & temp;
  return 0;
}
int (util_get_LSB)(uint16_t val, uint8_t *lsb){
  if(lsb==NULL)
    return 1;
  val=val & 0xFF;
  *lsb=(uint8_t)val;
  return 0;
}
int (util_get_MSB)(uint16_t val, uint8_t *msb){
  if(msb==NULL)
    return 1;
  val=val >>8;
  val=val & 0xFF;
  *msb=(uint8_t)val;
  return 0;
} */





























/* int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if(lsb==NULL){
    return 1;
  }
  *lsb=(uint8_t)(val & 0xFF);
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if(msb==NULL){
    return 1;
  }
  *msb=(uint8_t)((val >>8)& 0xFF);
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  if (value == NULL)
    return 1;
  uint32_t temp;
  if(sys_inb(port,&temp)!=0)
    return 1;
  *value=(uint8_t)temp;
  return 0;
}
 */
