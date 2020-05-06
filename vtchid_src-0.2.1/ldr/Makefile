#
# Makefile
#
# $Id: Makefile,v 1.2 2004/06/13 16:09:49 hos Exp $
#

include ../Makefile.comm

TARGET = $(MAIN_TARGET_NAME)ldr.exe

TARGET_INCLUDES = -I../sys
TARGET_CFLAGS = -DWINVER=0x0500 -D_WIN32_IE=0x0501 -DUNICODE -D_UNICODE
TARGET_LDFLAGS = -mwindows
LDLIBS = ../cpl/setting.o ../cpl/setting_data.o ../cpl/setting_file.o \
	 ../util/util.a \
	 -lsetupapi -lhid

SRCS = main.c
HEADERS = 
RSRC = resource.rc
RSRC_EX = 
OBJS = $(SRCS:%.c=%.o) $(RSRC:%.rc=%.o)
RESS = $(RSRC:%.rc=%.res)
STUB_DEFS = 
STUB_LIBS = $(STUB_DEFS:%.def=%.a)

GENFILES = $(TARGET) $(OBJS) $(RESS) $(STUB_LIBS)


all: $(TARGET)

$(TARGET): $(OBJS) $(STUB_LIBS)

$(OBJS): $(HEADERS)

pack-bin:
	$(INSTALL) -m 755 -s $(TARGET) $(TARGET_DIR)

pack-src:
	$(INSTALL) -m 755 -d $(TARGET_DIR)
	$(INSTALL) -m 644 $(SRCS) $(TARGET_DIR)
	$(INSTALL) -m 644 $(RSRC) $(TARGET_DIR)
	$(INSTALL) -m 644 Makefile $(TARGET_DIR)

clean:
	-$(RM) $(GENFILES) *.o
