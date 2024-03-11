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
extern uint32_t counter_KBC;

int(kbd_test_scan)() {
  uint8_t attemps = 10;
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
            KBC_read_output(KBD_CMD_BUF,&scancode,attemps);
            kbd_print_scancode(!(scancode & MAKE_CODE), scancode == IS_TWO_BYTES ? 2 : 1, &scancode);
          }
          
      }
    }
  }
  if (kbd_unsubscribe_int() != 0) return 1;
  if(kbd_print_no_sysinb(counter_KBC)==0) return 0;
  return 1;
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
