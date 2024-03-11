#include "KBD.h"

int kbd_hook_id=1;

int(kbd_subscribe_int)(uint8_t* bit_no){
  if(bit_no==NULL) return 1;
  *bit_no=BIT(kbd_hook_id); //guardo hoodId antes de o alterar
  if(sys_irqsetpolicy(IRQ_KBD, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbd_hook_id)==0)return 0;
  return 1;
}
int (kbd_unsubscribe_int)(){
  return sys_irqrmpolicy(&kbd_hook_id);
}


