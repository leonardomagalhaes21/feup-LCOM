#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>
#include "i8254.h"
//CONSTRUIR COMANDO RBC
//MANDAR CODIGO PARA O CONTROLADOR
//LER A CONFIGURAÇÃO DO TIMER EM ESPECIFICO
int (timer_get_conf)(uint8_t timer, uint8_t *st){
  if(st==NULL)
    return 1;
  uint8_t control_word=0x00;
  control_word=(TIMER_RB_CMD | BIT(5)| BIT(timer +1));
  if(sys_outb(0x43,control_word)!=0)
    return 1;
  if(util_sys_inb(0x40+timer,st)!=0)
    return 1;
  return 0;
}
//SWITCH COM CADA UM DOS FIELDS ESPECIFICOS
int (timer_display_conf)(uint8_t timer, uint8_t conf, enum timer_status_field field){
  union timer_status_field_val data;
  switch (field)
  {
  case tsf_all:
    data.byte=conf;
    break;
  case tsf_initial:
    conf=conf >>4;
    conf=conf & 0x03;
    if(conf==1)
      data.in_mode=LSB_only;
    else if(conf==2)
      data.in_mode=MSB_only;
    else if(conf==3)
      data.in_mode=MSB_after_LSB;
    else
      data.in_mode=INVAL_val;
    
    break;
  case tsf_mode:
    conf=conf >>1;
    conf=conf & 0x07;
    if(conf==6)
      data.count_mode=2;
    else if(conf==7)
      data.count_mode=3;
    else 
      data.count_mode=conf;
    break;
  case tsf_base:
    conf=conf & 0x01;
    data.bcd=conf;
    break;
  
  default:
    return 1;
    break;
  }
  if(timer_print_config(timer, field, data)!=0)
    return 1;
  return 0;


}



//IR BUSCAR A CONFIGURAÇÃO AO TIMER
//DEIXAR APENAS O ULTIMOS 4 BITS E ACIONAR OS BITS DE MSB_AFTER_LSB
//FAZER A FREQ(TIMER_FREQ/freq) E IR BUSCAR O MSB E LSB
//FAZER SWITCH COM OS TIMERS E GUARDAR O TIMER ESCOLHIDO(ENDEREÇO) E ATIVAR NO CONTROLADOR O TIMER RESPETIVO
//MANDAR O CONTROLADOR PARA O TIMER_CTRL PARA AVISAR QUE VAI ESCREVER EM MSB_AFTER_LSB NO TIMER ESPECIFICO
//MANDAR O LSB E DEPOIS O MSB PARA O TIMER SELECIONADO
int (timer_set_frequency)(uint8_t timer, uint32_t freq){
  if(freq > TIMER_FREQ| freq <19| timer>2)
    return 1;
  uint8_t word;
  if(timer_get_conf(timer,&word)!=0)
    return 1;
  word=word & 0x0F;
  word|=TIMER_LSB_MSB;
  switch (timer)
  {
  case 0:
    word |=TIMER_SEL0;
    break;
  case 1:
    word|=TIMER_SEL1;
    break;
  case 2:
    word |=TIMER_SEL2;
    break;
  default:
    return 1;
    break;
  }
  uint8_t LSB, MSB;
  uint16_t frequency;
  frequency=TIMER_FREQ /freq;
  LSB=( frequency & 0xFF);
  MSB=((frequency >>8) & 0xFF);
  if(sys_outb(0x43,word)!=0)
    return 1;
  if(sys_outb(0x40+timer,LSB)!=0)
    return 1;
  if(sys_outb(0x40+timer, MSB)!=0)
    return 1;
  return 0;
  
}

void (timer_int_handler)(){
  
}

int (timer_subscribe_int)(uint8_t *bit_no){
  return 1;
}

int (timer_unsubscribe_int)(){
  return 1;
}







































/* 

//SWITCH COM CADA UM DOS FIELDS ESPECIFICOS
int (timer_display_conf)(uint8_t timer, uint8_t conf, enum timer_status_field field){
  union timer_status_field_val data;
  switch (field)
  {
  case tsf_all:
    data.byte=conf;
    break;
  case tsf_initial:
    conf=conf >>4;
    conf=conf & 0x03;
    if(conf==1)
      data.in_mode=LSB_only;
    else if(conf==2)
      data.in_mode=MSB_only;
    else if(conf==3)
      data.in_mode=MSB_after_LSB;
    else
      data.in_mode=INVAL_val;
    
    break;
  case tsf_mode:
    conf=conf >>1;
    conf=conf & 0x07;
    if(conf==6)
      data.count_mode=2;
    else if(conf==7)
      data.count_mode=3;
    else 
      data.count_mode=conf;
    break;
  case tsf_base:
    conf=conf & 0x01;
    data.bcd=conf;
    break;
  
  default:
    return 1;
    break;
  }
  if(timer_print_config(timer, field, data)!=0)
    return 1;
  return 0;

}

//IR BUSCAR A CONFIGURAÇÃO AO TIMER
//DEIXAR APENAS O ULTIMOS 4 BITS E ACIONAR OS BITS DE MSB_AFTER_LSB
//FAZER A FREQ(TIMER_FREQ/freq) E IR BUSCAR O MSB E LSB
//FAZER SWITCH COM OS TIMERS E GUARDAR O TIMER ESCOLHIDO(ENDEREÇO) E ATIVAR NO CONTROLADOR O TIMER RESPETIVO
//MANDAR O CONTROLADOR PARA O TIMER_CTRL PARA AVISAR QUE VAI ESCREVER EM MSB_AFTER_LSB NO TIMER ESPECIFICO
//MANDAR O LSB E DEPOIS O MSB PARA O TIMER SELECIONADO
int (timer_set_frequency)(uint8_t timer, uint32_t freq){
  if(freq > TIMER_FREQ| freq <19| timer>2)
    return 1;
  uint8_t word;
  if(timer_get_conf(timer, &word)!=0)
    return 1;
  word= word & 0xFF;
  word |= TIMER_LSB_MSB;
  uint16_t initial_freq;
  initial_freq=TIMER_FREQ/freq;
  uint8_t LSB, MSB;
  if(util_get_LSB(initial_freq,&LSB)!=0)
    return 1;
  if(util_get_MSB(initial_freq, &MSB)!=0)
    return 1;
  uint8_t maria;
  switch (timer)
  {
  case 0:
    word|=TIMER_SEL0;
    maria=TIMER_0;
    break;
  case 1: 
    word|=TIMER_SEL1;
    maria=TIMER_1;
    break;
  case 2:
    word|=TIMER_SEL2;
    maria=TIMER_2;
    break;
  default:
    return 1;
    break;
  }
  if(sys_outb(TIMER_CTRL,word)!=0)
    return 1;
  if(sys_outb(0x40+timer,LSB)!=0)
    return 1;
  if(sys_outb(0x40+ timer,MSB)!=0)
    return 1;
  return 0;
}



void (timer_int_handler)(){
  count++;
}

int (timer_subscribe_int)(uint8_t *bit_no){
  if(bit_no ==NULL)
    return 1;
  *bit_no=BIT(hook_id);
  if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id)!=0)
    return 1;
  return 0;
}

int (timer_unsubscribe_int)(){
  if(sys_irqrmpolicy(&hook_id)!=0)
    return 1;
  return 0;
}
 */
































/* int count=0;
int hook_id=0;
//CONSTRUIR COMANDO RBC
//MANDAR CODIGO PARA O CONTROLADOR
//LER A CONFIGURAÇÃO DO TIMER EM ESPECIFICO
int (timer_get_conf)(uint8_t timer, uint8_t *st){
  if(st==NULL)
    return 1;
  uint8_t RBC=(TIMER_RB_CMD| TIMER_RB_COUNT_ | BIT(1+timer));
  if(sys_outb(TIMER_CTRL, RBC)!=0)
    return 1;
  if(util_sys_inb(TIMER_0+timer,st)!=0)
    return 1;
  return 0;
}

//SWITCH COM CADA UM DOS FIELDS ESPECIFICOS

int (timer_display_conf)(uint8_t timer, uint8_t conf, enum timer_status_field field){
  union timer_status_field_val temp;
  switch (field)
  {
  case tsf_all:
    temp.byte=conf;
    break;
  
  case tsf_initial:
    conf=conf >>4;
    conf = conf & 0x03;
    if(conf== 1)
      temp.in_mode= LSB_only;
    else if (conf==2)
      temp.in_mode=MSB_only;
    else if (conf==3)
      temp.in_mode=MSB_after_LSB;
    else
      temp.in_mode=INVAL_val;
    break;
  case tsf_mode:  
    conf=(conf >>1) & 0x07;
    if(conf==6)
      temp.count_mode=2;
    else if(conf==7)
      temp.count_mode=3;
    else
      temp.count_mode = conf;
    break;
  case tsf_base:
    conf=conf & BIT(0);
    temp.bcd=conf;
    break;
  
  default:
    return 1;
    break;
  }
  if(timer_print_config(timer,field,temp)!=0)
    return 1;
  return 0;
}

void (timer_int_handler)(){
  
}

int (timer_subscribe_int)(uint8_t *bit_no){
  return 1;
}

int (timer_unsubscribe_int)(){
  return 1;
}


//IR BUSCAR A CONFIGURAÇÃO AO TIMER
//DEIXAR APENAS O ULTIMOS 4 BITS E ACIONAR OS BITS DE MSB_AFTER_LSB
//FAZER A FREQ(TIMER_FREQ/freq) E IR BUSCAR O MSB E LSB
//FAZER SWITCH COM OS TIMERS E GUARDAR O TIMER ESCOLHIDO(ENDEREÇO) E ATIVAR NO CONTROLADOR O TIMER RESPETIVO
//MANDAR O CONTROLADOR PARA O TIMER_CTRL PARA AVISAR QUE VAI ESCREVER EM MSB_AFTER_LSB NO TIMER ESPECIFICO
//MANDAR O LSB E DEPOIS O MSB PARA O TIMER SELECIONADO
 
int (timer_set_frequency)(uint8_t timer, uint32_t freq){
  if(freq>TIMER_FREQ | freq <19 | timer >2)
    return 1;
  uint8_t controlador;
  if(timer_get_conf(timer, &controlador)!=0)
    return 1;
  controlador =controlador & 0x0F;
  controlador |= MSB_after_LSB;
  uint32_t initial_freq= TIMER_FREQ /freq;
  uint8_t MSB, LSB;
  util_get_LSB(initial_freq,&LSB);
  util_get_MSB(initial_freq, &MSB);

  uint8_t selected;  
  switch (timer){
  case 0:
    selected=TIMER_0;
    controlador |=TIMER_SEL0;
    break;
  case 1:
    selected=TIMER_1;
    controlador |=TIMER_SEL1;
    break;
  case 2:
    selected=TIMER_2;
    controlador|=TIMER_SEL2;
    break;
  default:
    return 1;
    break;
  }
  if(sys_outb(TIMER_CTRL, controlador)!=0)
    return 1;
  if(sys_outb(selected, LSB)!=0)
    return 1;
  if(sys_outb(selected, MSB)!=0)
    return 1;
  return 0;
}
void (timer_int_handler)(){
  count++;
}
int (timer_subscribe_int)(uint8_t *bit_no){
  if(bit_no==NULL)
    return 1;
  *bit_no=BIT(hook_id);
  if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id)!=0)
    return 1;
  return 0;
}
int (timer_unsubscribe_int)(){
  if(sys_irqrmpolicy(&hook_id)!=0)
    return 1;
  return 0;
}
 */



























/* 
int hook_id=0;
int count=0;
int (timer_get_conf)(uint8_t timer, uint8_t *st){
  if(st==NULL | timer>2)
    return 1;
  uint8_t RBC=(TIMER_RB_CMD | TIMER_RB_COUNT_ | BIT(timer+1));
  if(sys_outb(TIMER_CTRL, RBC)!=0)
    return 1;
  if(util_sys_inb(TIMER_0+timer,st)!=0)
    return 1;
  return 0;
}


int (timer_display_conf)(uint8_t timer, uint8_t conf, enum timer_status_field field){
  union timer_status_field_val temp;

  switch (field){
  case tsf_all:
    temp.byte=conf;
    break;


  case tsf_base:
    temp.bcd= conf & BIT(0);
    break;


  case tsf_initial:
    conf=( conf >>4)& 0x03;
    if(conf==1)
      temp.in_mode= LSB_only;
    else if(conf==2)
      temp.in_mode=MSB_only;
    else if(conf==3)
      temp.in_mode=MSB_after_LSB;
    else 
      temp.in_mode=INVAL_val;
    break;


  case tsf_mode:
    conf=(conf>>1)& 0x07;
    if(conf==6)
      temp.count_mode=2;
    else if(conf==7)
      temp.count_mode=3;
    else  
      temp.count_mode=conf;
    break;


  default:
    return 1;
    break;
  }

  if(timer_print_config(timer,field,temp)!=0)
    return 1;
  return 0;
}

int (timer_set_frequency)(uint8_t timer, uint32_t freq){
  if(freq >TIMER_FREQ || freq<19 || timer >2)
    return 1;
  uint8_t controlador;
  if(timer_get_conf(timer, & controlador)!=0)
    return 0;
  //preparar para por os bits de lsb followed by msb
  controlador = controlador &0xF;
  controlador |= TIMER_LSB_MSB;
  uint8_t MSB, LSB;
  uint32_t freq_initial= TIMER_FREQ/freq;
  util_get_LSB(freq_initial, &LSB);
  util_get_MSB(freq_initial, &MSB);

  uint8_t select;
  switch (timer)
  {
  case 0:
    controlador|=TIMER_SEL0;
    select =TIMER_0;
    break;
  case 1:
    controlador |= TIMER_SEL1;
    select =TIMER_1;
    break;
  case 2:
    controlador |= TIMER_SEL2;
    select =TIMER_2;
    break;
  
  default:
    break;
  }
  if(sys_outb(TIMER_CTRL, controlador)!=0)
    return 1;
  if(sys_outb(select, LSB)!=0)
    return 1;
  if(sys_outb(select, MSB)!=0)
    return 1;
  return 0;
  
}
void (timer_int_handler)(){
  count ++;
}
int (timer_subscribe_int)(uint8_t *bit_no){
  if(bit_no==NULL)
    return 1;
  *bit_no=BIT(hook_id);
  if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id)!=0)
    return 1;
  return 0;
}
int (timer_unsubscribe_int)(){
  if(sys_irqrmpolicy(&hook_id)!=0)
    return 1;
  return 0;
} */








































/* int count=0;
int hookId=0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if (freq<19 || freq>TIMER_FREQ  || timer>2) return 1;

  //Write control word to configure Timer 0:
  uint8_t control;
  if(timer_get_conf(timer, &control)!=0) return 1;
  //ativa bits de LSB followed by MSB e retira os de read-back
  control=(control | 0x30) & 0x3F;

  //configura a control de acordo com o timer escolhido
  uint32_t option;
  switch (timer) {
    case 0:
      option= 0x40;
      control = control | TIMER_SEL0;
      break;
    
    case 1:
      option=0x41;
      control = control | TIMER_SEL1;
      break;

    case 2:
      option=0x42;
      control = control | TIMER_SEL2;
      break;
    default:
      return 1;
  }

  Load timer’s register with the value of the divisor to
    generate the frequency corresponding to the desired
    rate
  uint32_t start= TIMER_FREQ/ freq;
  // os 16 bits do meio são perdidos, mas não serão usados pela configuração do sistema
  uint8_t LSB, MSB;
  util_get_LSB(start,&LSB);
  util_get_MSB(start,&MSB);

  if(sys_outb(0x43, control)!=0) return 1;
  if(sys_outb(option, LSB)!=0) return 1;
  if(sys_outb(option, MSB)!=0) return 1;
  
  return 0;
}


//adiciona a subscrição à interrupção
int (timer_subscribe_int)(uint8_t *bit_no) {
  if(bit_no!=NULL){
    *bit_no=BIT(hookId); //guardo hoodId antes de o alterar
    if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hookId)==0){
      return 0;
    }
  }
  printf("Erro ao estabelecer a interrupção\n");
  return 1;
}

//remove a subscrição à interrupção
int (timer_unsubscribe_int)() {
  if(sys_irqrmpolicy(&hookId)==0)return 0;
  printf("Erro ao remover a interrupção\n");
  return 1;
}

void (timer_int_handler)() {
  count ++;
}


//dá a config de acordo com o timer dado
int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if(st==NULL || timer>2){
    return 1;
  }
  uint8_t temp=BIT(timer + 1);
  uint8_t rb_cmd= (TIMER_RB_CMD | TIMER_RB_COUNT_ | temp);
  if(sys_outb(0x43,rb_cmd)!=0) return 1;
  if( util_sys_inb(0x40 + timer,st)) return 1;
  return 0;
}


//dá display à config de acordo com a variável field
int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  if (timer>2) return 1;
  union timer_status_field_val result;
  uint8_t temp;

  switch (field)
  {

  case tsf_base:
    result.bcd= st & 0x01;
    break;
  
  case tsf_mode:
    temp=st & 0x0E;
    temp=temp>>1;
    if(temp==7) result.count_mode =3;
    else if(temp==6) result.count_mode=2;
    else result.count_mode=temp;
    break;
  
  case tsf_initial:
    temp= st & 0x30;
    temp= temp>>4;
    if(temp==3){
      result.in_mode=MSB_after_LSB;
    }
    else if (temp==2)
    {
      result.in_mode=MSB_only;
    }
    else if(temp==1){
      result.in_mode=LSB_only;
    } 
    else result.in_mode=INVAL_val;
    break;

  case tsf_all:
    result.byte=st;
    break;


  default:
    return 1;
  }
  if (timer_print_config(timer, field, result)==0) return 0;
  return 1;
}
 */
