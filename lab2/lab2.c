#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>

#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}
//LER UMA CONFIGURAÇÃO E DAR DISPLAY A ESSA MESMA CONFIGURAÇÃO
int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  uint8_t conf;
  if(timer_get_conf(timer,&conf)!=0)
    return 1;
  if(timer_display_conf(timer,conf,field)!=0)
    return 1;
  return 0;
}
//DAR SET A UMA FREQUENCIA ESPECIFICA
int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  if(timer_set_frequency(timer, freq)!=0)
    return 1;
  return 0;
}

//DAR UM PRINT DE UM SEGUNDO EM UM SEGUNDO DURANTE UM TIME ESPECIFICO
int(timer_test_int)(uint8_t time) {
  return 1;
}























/* 
//LER UMA CONFIGURAÇÃO E DAR DISPLAY A ESSA MESMA CONFIGURAÇÃO
int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  uint8_t conf;
  if(timer_get_conf(timer,&conf)!=0)
    return 1;
  if(timer_display_conf(timer,conf,field)!=0)
    return 1;
  return 0;
}

//DAR SET A UMA FREQUENCIA ESPECIFICA
int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  if(timer_set_frequency(timer,freq)!=0)
    return 1;
  return 0;
}

extern int count;
extern int hook_id;
//DAR UM PRINT DE UM SEGUNDO EM UM SEGUNDO DURANTE UM TIME ESPECIFICO
int(timer_test_int)(uint8_t time) {
  int ipc_status;
  message msg;
  int r;
  uint8_t irq_set;
  if(timer_subscribe_int(&irq_set)!=0)
    return 1;
  while( time>0 ) { 
      
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
          printf("driver_receive failed with: %d", r);
          continue;
      }
      if (is_ipc_notify(ipc_status)) { 
          switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE:			
                  if (msg.m_notify.interrupts & irq_set) {
                    timer_int_handler();
                    if(count%60==0){
                      time--;
                      timer_print_elapsed_time();
                    }
                      
                  }
                  break;
              default:
                  break; 
          }
      } 
      else { 
        
      }
  }
  if(timer_unsubscribe_int()!=0)
    return 1;
  return 0; 
} */





























/* extern int count;

//LER UMA CONFIGURAÇÃO E DAR DISPLAY A ESSA MESMA CONFIGURAÇÃO
int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  uint8_t conf;
  if(timer_get_conf(timer,&conf)!=0)
    return 1;
  if(timer_display_conf(timer,conf,field)!=0)
    return 1;
  return 0;
}

//DAR SET A UMA FREQUENCIA ESPECIFICA
int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  if(timer_set_frequency(timer,freq)!=0)
    return 1;
  return 0;
}

//DAR UM PRINT DE UM SEGUNDO EM UM SEGUNDO DURANTE UM TIME ESPECIFICO
int(timer_test_int)(uint8_t time) {
  int ipc_status;
  message msg;
  int r;
  uint8_t irq_set;
  if(timer_subscribe_int(&irq_set)!=0)
    return 1;
  while( time>0 ) { 
      
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
          printf("driver_receive failed with: %d", r);
          continue;
      }
      if (is_ipc_notify(ipc_status)) { 
          switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE:			
                  if (msg.m_notify.interrupts & irq_set) {
                    timer_int_handler();
                    if(count%60==0){
                      timer_print_elapsed_time();
                      time--;
                    }
                  }
                  break;
              default:
                  break; 
          }
      } 
      else { 
        
      }
  }
  if(timer_unsubscribe_int()!=0)
    return 1;
  return 0;
} */



























/* extern int hook_id;
extern int count;
int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  uint8_t conf;
  if(timer_get_conf(timer,&conf)!=0)
    return 0;
  if(timer_display_conf(timer, conf, field)!=0)
    return 1;
  return 0;
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  if(timer_set_frequency(timer,freq)!=0)
    return 1;
  return 0;
}

int(timer_test_int)(uint8_t time) {
  uint8_t irq_set;
  int ipc_status;
  message msg;
  int r;
  if(timer_subscribe_int(&irq_set)!=0)
    return 1;
  while( time >0) { 
    
    if( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { 
      switch (_ENDPOINT_P(msg.m_source)) {
      case HARDWARE: 
        if (msg.m_notify.interrupts & irq_set) { 
          timer_int_handler();
          if(count%60==0){
             timer_print_elapsed_time();
             time-=1;
          }
        }
          break;
      default:
        break; 
      }
    } else {
      
    }
  }
  if(timer_unsubscribe_int()!=0)
    return 1;
  return 0;
}
 */






































/* 
extern int count; //usado para contar ciclos
int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  uint8_t temp;
  if(timer_get_conf(timer, &temp)==0){
    if(timer_display_conf(timer, temp,field)==0){
      return 0;
    }
  }
  return 1;
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  if(timer_set_frequency(timer,freq)==0)return 0;
  return 1;
}

int(timer_test_int)(uint8_t time) {
  int ipc_status;
  uint8_t irq_set;
  int r;
  message msg;

  if(timer_subscribe_int(&irq_set)!=OK)return 1;
  while( time >0) { 
    
    if( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { 
      switch (_ENDPOINT_P(msg.m_source)) {
      case HARDWARE: 
        if (msg.m_notify.interrupts & irq_set) { 
          //aumentar o count(+1ciclo)
          timer_int_handler();
          // freq do timer 0 é 60hz/s
          if(count%60==0){
             timer_print_elapsed_time();
             time-=1;
          }
        }
          break;
      default:
        break; 
      }
    } else {
      
    }
  }

  //preciso de libertar a subscrição (apaga pointer para o hood_id)
  if(timer_unsubscribe_int() ==0) return 0;
  return 1;
}
 */
