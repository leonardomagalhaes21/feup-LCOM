#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>
#include "i8254.h"

int count=0;
int hookId=0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if (freq<19 || freq>TIMER_FREQ/*1193182*/ || timer>2) return 1;

  //Write control word to configure Timer 0:
  u_int8_t control;
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

  /*Load timer’s register with the value of the divisor to
    generate the frequency corresponding to the desired
    rate*/
  uint32_t start= TIMER_FREQ/ freq;
  // os 16 bits do meio são perdidos, mas não serão usados pela configuração do sistema
  u_int8_t LSB, MSB;
  util_get_LSB(start,&LSB);
  util_get_MSB(start,&MSB);

  if(sys_outb(0x43, control)==0){
    if(sys_outb(option, LSB)!=1) return 1;
    if(sys_outb(option, MSB)!=1) return 1;
  }
  return 1;
}


//adiciona a subscrição à interrupção
int (timer_subscribe_int)(uint8_t *bit_no) {
  if(bit_no!=NULL){
    if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hookId)==0){
      *bit_no=BIT(hookId);
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
