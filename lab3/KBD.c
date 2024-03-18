#include "KBD.h"

int kbd_hook_id=1;
uint8_t scancode=0;
int(kbd_subscribe_int)(uint8_t* bit_no){
  if(bit_no==NULL) return 1;
  *bit_no=BIT(kbd_hook_id); //guardo hoodId antes de o alterar
  if(sys_irqsetpolicy(IRQ_KBD, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbd_hook_id)==0)return 0;
  return 1;
}
int (kbd_unsubscribe_int)(){
  return sys_irqrmpolicy(&kbd_hook_id);
}
void (kbc_ih)() {
    if (KBC_read_output(KBD_DATA_BUF,&scancode,0)!=0) printf("Error: Could not read scancode!\n");
}

int (keyboard_restore)(){
  uint8_t comm;
  if(KBC_write_comm(KB_FE,KBD_CMD_BUF)!=0)
    return 1;
  if(KBC_read_output(KBD_OUT_BUF,&comm,0)!=0)
    return 1;
  comm= comm | BIT(0);
  if(KBC_write_comm(KBD_OUT_BUF,KBD_CMD_BUF)!=0)
    return 1;
  if(KBC_write_comm(comm,KBD_OUT_BUF)!=0)
    return 1;
  return 0;
}


