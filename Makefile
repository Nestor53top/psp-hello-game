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

PARAM_SFO = PARAM.SFO
SFO_TITLE = Hello PSP Game
SFO_CATEGORY = UG
SFO_DISC_ID = UCJS10041
SFO_DISC_VERSION = 1.00
SFO_PARENTAL_LEVEL = 1

$(PARAM_SFO): $(OBJS)
	mksfoex -d MEMSIZE=1 -s CATEGORY=$(SFO_CATEGORY) -s DISC_ID=$(SFO_DISC_ID) -s DISC_VERSION=$(SFO_DISC_VERSION) -d PARENTAL_LEVEL=$(SFO_PARENTAL_LEVEL) '$(SFO_TITLE)' $(PARAM_SFO)

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
