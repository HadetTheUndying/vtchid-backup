#
# Makefile
#
# $Id: Makefile,v 1.21 2004/06/14 09:29:06 hos Exp $
#

include ../Makefile.comm

TARGET_INCLUDES = $(DDK_INCLUDES) -I../util
TARGET_CFLAGS =
TARGET_SYS_LDFLAGS = -Wl,-Map,$(@:%.sys=%.map) 
LDLIBS = ../util/util.a -lntoskrnl -lhal -lmingwex -lgcc

TARGET_NAME = $(MAIN_TARGET_NAME)
TARGET_SUFFIX = .sys
TARGET = $(TARGET_NAME)$(TARGET_SUFFIX)

SRCS = main.c pnp.c ioctl.c usb.c hid.c setting.c event.c
HEADERS = main.h report_data.h hid_port.h usbd_lib.h
RSRC = version.rc
OBJS = $(SRCS:%.c=%.o) $(RSRC:%.rc=%.o)
DEFS = libhidclass.def libusbd.def
STUB_LIBS = $(DEFS:%.def=%.a)

GENFILES = $(TARGET) $(OBJS) $(STUB_LIBS) $(TARGET_NAME).map


all: $(TARGET)

$(TARGET): $(OBJS) $(STUB_LIBS)

$(OBJS): $(HEADERS)

version.o: ../version.h

pack-bin:
	$(INSTALL) -m 755 -s $(TARGET) $(TARGET_DIR)

pack-src:
	$(INSTALL) -m 755 -d $(TARGET_DIR)
	$(INSTALL) -m 644 $(SRCS) $(TARGET_DIR)
	$(INSTALL) -m 644 $(HEADERS) $(TARGET_DIR)
	$(INSTALL) -m 644 $(RSRC) $(TARGET_DIR)
	$(INSTALL) -m 644 $(DEFS) $(TARGET_DIR)
	$(INSTALL) -m 644 Makefile $(TARGET_DIR)

clean:
	-$(RM) $(GENFILES) *.o *.sys *.map *.tmp *.a
