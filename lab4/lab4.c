// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include "KBC.c"
#include "ms.h"
#include "timer.c"
#include "i8042.h"
#include "i8254.h"

extern uint8_t byte_idx;
extern struct packet ms_packet;
extern int count;
// Any header files included below this line should have been created by you
typedef enum {
  START,
  UP,
  VERTEX,
  DOWN,
  END
} SystemState;

SystemState state = START;
uint16_t x_len_total = 0;


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
  int ipc_status;
  message msg;
  uint8_t mask; 

  if (ms_write(ENABLE_DATA_REPORT) != 0) 
    return 1; 
  if (ms_subscribe_int(&mask) != 0) 
    return 1;


  while (cnt) { 

    if (driver_receive(ANY, &msg, &ipc_status) != 0){
      printf("Error");
        continue;
    }

    if (is_ipc_notify(ipc_status)){
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE: 
          if (msg.m_notify.interrupts & mask){  
            mouse_ih();                          
            ms_sync_bytes();                       
            if (byte_idx == 3) {                    
              ms_bytes_to_packet();            
              mouse_print_packet(&ms_packet);      
              byte_idx = 0;
              cnt--;
            }
          }
          break;
      }
    }
  }
  

  

  if (ms_unsubscribe_int() != 0) 
    return 1;
  if (ms_write(DISABLE_DATA_REPORT) != 0) 
    return 1;
  
  return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
    int ipc_status;
  message msg;
  uint8_t time = 0;
  uint8_t mask = 0, timer_mask = 0; 
  uint16_t frequency = sys_hz();

  if (ms_write(ENABLE_DATA_REPORT) != 0) 
    return 1;
  if (ms_subscribe_int(&mask) != 0) 
    return 1;
  if (timer_subscribe_int(&timer_mask) != 0) 
    return 1;

  while (time < idle_time) {

    if (driver_receive(ANY, &msg, &ipc_status) != 0){
      printf("Error");
      continue;
    }

    if (is_ipc_notify(ipc_status)){
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE: 

          if (msg.m_notify.interrupts & timer_mask) { 
            timer_int_handler();
            if (count % frequency == 0) 
              time++;
          }

          if (msg.m_notify.interrupts & mask){  
            mouse_ih();                               
            ms_sync_bytes();                       
            if (byte_idx == 3) {                    
              ms_bytes_to_packet();               
              mouse_print_packet(&ms_packet);      
              byte_idx = 0;
            }
            time = 0;
            count = 0;
          }
      }
    }
  }


  if (timer_unsubscribe_int() != 0) 
    return 1;
  if (ms_unsubscribe_int() != 0) 
    return 1;
  if (ms_write(DISABLE_DATA_REPORT) != 0) 
    return 1;

  return 0;
}



int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
     while (cnt) { 

        if (ms_write(MOUSE_READ_DATA) != 0) 
          return 1;
        mouse_ih();                                     
        ms_sync_bytes();                               
        if (byte_idx == 3) {                            
            ms_bytes_to_packet();                      
            mouse_print_packet(&ms_packet);           
            byte_idx = 0;
            cnt--;
            tickdelay(micros_to_ticks(period * 1000));    
        }
    }

    
  
    
    uint8_t command = minix_get_dflt_kbc_cmd_byte();             
    if (KBC_write_comm(0x64, 0x60) != 0) 
      return 1; 
    if (KBC_write_comm(0x60, command) != 0) 
      return 1;  
    return 0;
}

