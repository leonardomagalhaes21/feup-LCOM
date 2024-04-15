#include "ms.h"

int ms_hook_id=3;
uint8_t curr_byte; 
uint8_t byte_idx = 0;
struct packet ms_packet; 
uint8_t ms_bytes[3]; 



int(ms_subscribe_int)(uint8_t *bit){
  if(bit==NULL)
    return 1;
  *bit=BIT(ms_hook_id);
  return sys_irqsetpolicy(IRQ_MS,IRQ_REENABLE | IRQ_EXCLUSIVE, &ms_hook_id);
}
int(ms_unsubscribe_int)(){
  return sys_irqrmpolicy(&ms_hook_id);
}
void (mouse_ih)(){
  KBC_read_output(0x60, &curr_byte, 1);
}
void ms_sync_bytes() {
  if (byte_idx == 0 && (curr_byte & FIRST_BYTE)) { // é o byte CONTROL, o bit 3 está ativo
    ms_bytes[byte_idx]= curr_byte;
    byte_idx++;
  }
  else if (byte_idx > 0) {                            // recebe os deslocamentos em X e Y
    ms_bytes[byte_idx] = curr_byte;
    byte_idx++;
  }
}
void (ms_bytes_to_packet)(){

  for (int i = 0 ; i < 3 ; i++) {
    ms_packet.bytes[i] = ms_bytes[i];
  }

  ms_packet.lb = ms_bytes[0] & MS_LB;
  ms_packet.mb = ms_bytes[0] & MS_MB;
  ms_packet.rb = ms_bytes[0] & MS_RB;
  ms_packet.x_ov = ms_bytes[0] & MS_X_OVERFLOW;
  ms_packet.y_ov = ms_bytes[0] & MS_Y_OVERFLOW;
  ms_packet.delta_x = (ms_bytes[0] & MS_X_SIGNAL) ? (0xFF00 | ms_bytes[1]) : ms_bytes[1];
  ms_packet.delta_y = (ms_bytes[0] & MS_Y_SIGNAL) ? (0xFF00 | ms_bytes[2]) : ms_bytes[2];
}
int (ms_write)(uint8_t command) {

  uint8_t attemps = 10;
  uint8_t mouse_response;

  do {
    attemps--;
    if (KBC_write_comm(0x64,WRITE_BYTE_MOUSE)) 
      return 1;
    if (KBC_write_comm(0x60,command)) 
      return 1;
    tickdelay(micros_to_ticks(20000));
    if (util_sys_inb(0x60, &mouse_response)) 
      return 1;
    if (mouse_response == ACK) 
      return 0;
  } while (mouse_response != ACK && attemps);

  return 1;
}
