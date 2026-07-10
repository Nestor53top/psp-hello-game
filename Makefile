TARGET = hello_psp
OBJS = main.o

INCDIR =
CFLAGS = -G0 -O2 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = -lpspgu -lpspdisplay -lpspctrl -lpspkernel -lpsppower -lpspdebug

EXTRA_TARGETS = $(PSP_EBOOT)
PSP_EBOOT = EBOOT.PBP

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
