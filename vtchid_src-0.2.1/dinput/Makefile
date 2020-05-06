#
# Makefile
#
# $Id: Makefile,v 1.2 2004/01/09 08:51:40 hos Exp $
#

include ../Makefile.comm

INCLUDES = -I.
TARGET_CFLAGS = -DINITGUID

TARGET = dinput_util.a

SRCS = dinput_util.c
HEADERS = dinput_util.h dinputd.h
OBJS = $(SRCS:%.c=%.o)

GENFILES = $(OBJS) $(TARGET)


all: $(TARGET)

$(TARGET): $(OBJS)

clean:
	-$(RM) $(GENFILES) *.o

pack-bin:

pack-src:
	$(INSTALL) -m 755 -d $(TARGET_DIR)
	$(INSTALL) -m 644 $(SRCS) $(TARGET_DIR)
	$(INSTALL) -m 644 $(HEADERS) $(TARGET_DIR)
	$(INSTALL) -m 644 Makefile $(TARGET_DIR)
