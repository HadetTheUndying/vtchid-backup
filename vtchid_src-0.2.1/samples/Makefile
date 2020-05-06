#
# Makefile
#
# $Id: Makefile,v 1.1 2004/06/12 11:42:37 hos Exp $
#

include ../Makefile.comm

TARGET = 

SAMPLES = $(wildcard *.sdp)


all:

pack-bin:
	$(INSTALL) -m 755 -d $(TARGET_DIR)/samples
	$(INSTALL) -m 644 $(SAMPLES) $(TARGET_DIR)/samples

pack-src:
	$(INSTALL) -m 755 -d $(TARGET_DIR)
	$(INSTALL) -m 644 $(SAMPLES) $(TARGET_DIR)
	$(INSTALL) -m 644 Makefile $(TARGET_DIR)

clean:
