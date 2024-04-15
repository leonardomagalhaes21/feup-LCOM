
#include "KBC.h"

//LER O STATUS DO STATUS(0X64)
int (KBC_read_status)(uint8_t* curr_status){ //passar por referencia para usar o sys_inb do util
  if(util_sys_inb(0x64,curr_status)!=0)
    return 1;
  return 0;
}

//LER O STATUS DO STATUS(0X64)
//VERIFICAR SE O BIT DO OUTPUT ESTÁ CHEIO E CONSIGO LER, VERIFICAR SE TEM ERROS DE PARIDADE OU TIMEOUT
//TENTAR ISSO DURANTE ALGUMAS VEZES COM INTERVALOS DE TEMPO
//FAZER ISTO COM O IH PARA MANTER O SCANCODE SEMPRE ATUALIZADO
int (KBC_read_output)(uint8_t port, uint8_t *output,uint8_t aux){
  uint8_t status;
  uint8_t tries=10;
  while(tries >0){
    if(KBC_read_status(&status)!=0)
      return 1;
    if((status & BIT(0))!=0){
      
      if(((status & BIT(6))!=0) |((status &BIT(7))!=0))
        return 1;
      if(util_sys_inb(port,output)!=0)
        return 1;
      return 0;
    }
    tickdelay(micros_to_ticks(20000));
    tries--;
  }
  return 1; 
}


//PARECIDA AO KBC_READ_OUTPUT, MAS PARA O INPUT BUFFER
//TENTAR ALGUMAS VEZES E VER SE É POSSIVEL ESCREVER NO BUFFER
int (KBC_write_comm)(uint8_t comm, uint8_t port){
  uint8_t status;
  uint8_t tries=10;
  while(tries >0){
    if(KBC_read_status(&status)!=0)
      return 1;
    if((status & BIT(1))==0){
      
      if(((status & BIT(6))!=0) |((status &BIT(7))!=0))
        return 1;
      if(util_sys_inb(port,&comm)!=0)
        return 1;
      return 0;
    }
    tickdelay(micros_to_ticks(20000));
    tries--;
  }
  return 1; 
}





































/* //LER O STATUS DO STATUS(0X64)
int (KBC_read_status)(uint8_t* curr_status){ //passar por referencia para usar o sys_inb do util
  if(util_sys_inb(0x64,curr_status)!=0)
    return 1;
  return 0;
}
//LER O STATUS DO STATUS(0X64)
//VERIFICAR SE O BIT DO OUTPUT ESTÁ CHEIO E CONSIGO LER, VERIFICAR SE TEM ERROS DE PARIDADE OU TIMEOUT
//TENTAR ISSO DURANTE ALGUMAS VEZES COM INTERVALOS DE TEMPO
//FAZER ISTO COM O IH PARA MANTER O SCANCODE SEMPRE ATUALIZADO
int (KBC_read_output)(uint8_t port, uint8_t *output,uint8_t aux){
  uint8_t status;
  
  uint8_t tries=10;
  while (tries>0){
    if(KBC_read_status(&status)!=0)
      return 1;
    if((status & BIT(0))!=0){
      if(util_sys_inb(port,output)!=0)
        return 1;
      if(((status &BIT(7))!=0) | ((status & BIT(6))!=0))
        return 1;
      return 0;
    }
    tickdelay(micros_to_ticks(20000));
    tries--;                                                     
  }
  return 1;
  
}


//PARECIDA AO KBC_READ_OUTPUT, MAS PARA O INPUT BUFFER
//TENTAR ALGUMAS VEZES E VER SE É POSSIVEL LER O QUE ESTÁ NO BUFFER
int (KBC_write_comm)(uint8_t comm, uint8_t port){
  uint8_t status;
  uint8_t tries=10;
  while (tries>0){

    if(KBC_read_status(&status)!=0)
      return 1;
    
    if((status & BIT(1))==0){
    
      if(sys_outb(port,comm)!=0)
        return 1;
    
      return 0;
    }
    tickdelay(micros_to_ticks(20000));
    tries--; 
  }
  return 1;
} */





/* int (KBC_read_status)(uint8_t* curr_status){
  if(util_sys_inb(STATUS_PORT,curr_status)!=0)
    return 1;
  return 0;
}
int (KBC_read_output)(uint8_t port, uint8_t *output,uint8_t aux){
  uint8_t curr_status;
  uint8_t tries =10;

  while (tries >0){
    if(KBC_read_status(&curr_status)!=0)
      return 1;
  
  if((curr_status & BIT(0))!=0){//está cheio, posso ler
    if(util_sys_inb(port, output)!=0)
      return 1;
    if(((curr_status & BIT(7)) != 0)|((curr_status & BIT(6)) != 0) )
      return 1;
        
    return 0;
  }
  tickdelay(micros_to_ticks(20000));
  tries--;
  }
  return 1;
}

int (KBC_write_comm)(uint8_t comm, uint8_t port){
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
  */












/* 
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
        
        
          
          return 0; // output lido sem erros de paridade e timeout
      }
      //dar uma delay de 20ms para voltar a tentar
      tickdelay(micros_to_ticks(20000));
      //tentar até ao max de atemps
      attemps--;
  }
  return 1; // ultrapassou as tentativas
} */
/*
int (KBC_write_comm)(uint8_t comm,uint8_t port){
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
  
} */
