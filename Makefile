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

# Create PARAM.SFO with correct values
PARAM_SFO = PARAM.SFO
$(PARAM_SFO):
	mksfo "HELLO PSP GAME" $(PARAM_SFO)

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
