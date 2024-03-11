#include "KBC.h"
uint8_t scancode=0;
int(KBC_read_status)(uint8_t* curr_status){
  //ler config do status atráves do util sys_inb
  return util_sys_inb(STATUS_PORT,curr_status);
}

int (KBC_read_output)(uint8_t port, uint8_t *output, uint8_t attemps){
  uint8_t curr_status;
  
  while (attemps>0) {
      if (KBC_read_status(&curr_status) != 0) {
          return 1;
      }

      if ((curr_status & BIT(0)) != 0) { //output cheio, posso ler
          if(util_sys_inb(port, output) != 0){
              return 1;
          }
          if((curr_status & BIT(7)) != 0){
              printf("Parity error!\n");
              return 1;
          }
          if((curr_status & BIT(6)) != 0){
              printf("Timeout error!\n");
              return 1;
          }
          
          return 0; // output lido sem erros de paridade e timeout
      }
      //dar uma delay de 20ms para voltar a tentar
      tickdelay(micros_to_ticks(20000));
      //tentar até ao max de atemps
      attemps--;
  }
  return 1; // ultrapassou as tentativas
}
