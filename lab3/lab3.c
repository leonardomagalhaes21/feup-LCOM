#include <lcom/lcf.h>

#include <lcom/lab3.h>
#include "KBC.c"
#include "KBD.h"
#include "timer.c"
#include "i8042.h"
#include "i8254.h"
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

extern uint8_t scancode;
uint32_t KBC_counter =0;
extern int count;

int(kbd_test_scan)() {
  int ipc_status;
  uint8_t irq_set;
  message msg;

  if(kbd_subscribe_int(&irq_set)!=0)return 1;
  // fechar ciclo ao clicar no esc
  while( scancode != CODE_ESC) { 
    
    if( (driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
      printf("driver_receive failed." );
      continue;
    }
    if (is_ipc_notify(ipc_status)) { 
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & irq_set) { 
            kbc_ih();
            kbd_print_scancode(!(scancode & MAKE_CODE), scancode == IS_TWO_BYTES ? 2 : 1, &scancode);
          }
          
      }
    }
  }
  if (kbd_unsubscribe_int() != 0) return 1;
  if(kbd_print_no_sysinb(KBC_counter)!=0) return 1;
  return 0;
}

int(kbd_test_poll)() {
  while( scancode != CODE_ESC) { 
    if(KBC_read_output(KBD_OUT_BUF,&scancode,0)==0){
      kbd_print_scancode(!(scancode & MAKE_CODE), scancode == IS_TWO_BYTES ? 2 : 1, &scancode);
    }
    
    
  }
  return keyboard_restore();
}

int(kbd_test_timed_scan)(uint8_t n) { 
  int ipc_status;
  uint8_t timer_irq_set, kbc_irq_set;
  message msg;
  int time=n;

  if(kbd_subscribe_int(&kbc_irq_set)!=0)return 1;
  if(timer_subscribe_int(&timer_irq_set)!=0) return 1;
  // fechar ciclo ao clicar no esc
  while( scancode != CODE_ESC && time >0) { 
    
    if( (driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
      printf("driver_receive failed." );
      continue;
    }
    if (is_ipc_notify(ipc_status)) { 
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & kbc_irq_set) {
            kbc_ih();
            kbd_print_scancode(!(scancode & MAKE_CODE), scancode == IS_TWO_BYTES ? 2 : 1, &scancode);
            time=n;
            count=0;
          }
          if(msg.m_notify.interrupts & timer_irq_set){
            timer_int_handler();
            if(count%60==0){
             time-=1;
            }
          }   
      }
    }
  }
  if(timer_unsubscribe_int()!=0)
    return 1;
  if (kbd_unsubscribe_int() != 0) 
    return 1;
  if(kbd_print_no_sysinb(KBC_counter)!=0) 
    return 1;
  return 0;
}
