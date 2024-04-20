#include "KBC.h"

int(KBC_read_status)(uint8_t* curr_status){
  //ler config do status atráves do util sys_inb
  return util_sys_inb(STATUS_PORT,curr_status);
}

int (KBC_read_output)(uint8_t port, uint8_t *output,uint8_t aux){
  uint8_t curr_status;
  uint8_t attemps=10;
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
        if (aux && !(curr_status & BIT(5))) {          
            return 1;
        } 
        if (!aux && (curr_status & BIT(5))) {        
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

int (KBC_write_comm)(uint8_t port,uint8_t comm){
  uint8_t tries=10;
  uint8_t status;
  while (tries>0){
    if(KBC_read_status(&status)!=0)
      return 1;

    if ((status & INPT_BUF_FULL)==0){
      if(sys_outb(port,comm)!=0)
        return 1;

      return 0;
    }

    tickdelay(micros_to_ticks(20000));
    tries--; 
  }

return 1;
  
}
