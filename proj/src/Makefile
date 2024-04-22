PROG=proj

.PATH: ${.CURDIR}/devices/timer
.PATH: ${.CURDIR}/devices
.PATH: ${.CURDIR}/devices/graphics
.PATH: ${.CURDIR}/devices/keyboard
.PATH: ${.CURDIR}/devices/mouse

.PATH: ${.CURDIR}/controllers/serialPort
.PATH: ${.CURDIR}/game
.PATH: ${.CURDIR}/game/modes
.PATH: ${.CURDIR}/sprites

SRCS = 	main.c timer.c utils.c graphics.c keyboard.c mouse.c 

# ./controllers/keyboardMouse/KBC.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_

DPADD += ${LIBLCF}
LDADD += -llcf -lxpm -llm

.include <minix.lcom.mk>


