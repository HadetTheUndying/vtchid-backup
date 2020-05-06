#
# Makefile
#
# $Id: Makefile,v 1.4 2006/06/23 02:27:42 hos Exp $
#

include Makefile.comm

GENFILES = version.h

TARGET_NAME = $(MAIN_TARGET_NAME)

TARGET_INF = $(TARGET_NAME).inf

VERSION = `cat VERSION`

READMES = README.txt README.ja.txt VERSION
INST_BIN_ADD_FILES = $(TARGET_INF) $(READMES)
INST_SRC_FILES = Makefile Makefile.comm $(TARGET_INF) vidpid.h $(READMES)

SUBDIRS = util sys dinput cpl ldr samples

all: version.h
	for d in $(SUBDIRS); do \
	  (cd $$d && $(MAKE) all) || \
	  exit 1 ; \
	done

clean: pack-clean
	-$(RM) $(GENFILES)
	-for d in $(SUBDIRS); do \
	  (cd $$d; $(MAKE) clean) || \
	  exit 1 ; \
	done

version.h: VERSION
	echo "#define VERSION_STR \"`cat $<`.0\"" > $@
	echo "#define VERSION_ID `tr . , < $<`,0" >> $@


## misc rules

pack: pack-bin pack-src

pack-bin: all
	-$(RM) -r $(TARGET_NAME)-$(VERSION)
	$(INSTALL) -m 755 -d $(TARGET_NAME)-$(VERSION)
	VERSION=$(VERSION) ; \
	TARGET_DIR=`pwd`/$(TARGET_NAME)-$$VERSION/ ; \
	for d in $(SUBDIRS); do \
          (cd $$d && \
           $(MAKE) pack-bin TARGET_DIR="$$TARGET_DIR") || \
	  exit 1 ; \
        done
	$(INSTALL) -m 644 $(INST_BIN_ADD_FILES) $(TARGET_NAME)-$(VERSION)
	$(ZIP) -r $(TARGET_NAME)-$(VERSION).zip $(TARGET_NAME)-$(VERSION)
	-$(RM) -r $(TARGET_NAME)-$(VERSION)

pack-src:
	-$(RM) -r $(TARGET_NAME)_src-$(VERSION)
	$(INSTALL) -m 755 -d $(TARGET_NAME)_src-$(VERSION)
	VERSION=$(VERSION) ; \
	TARGET_DIR=`pwd`/$(TARGET_NAME)_src-$$VERSION ; \
	for d in $(SUBDIRS); do \
          (cd $$d && \
           $(MAKE) pack-src TARGET_DIR="$$TARGET_DIR/$$d") || \
	  exit 1 ; \
        done
	$(INSTALL) -m 644 $(INST_SRC_FILES) $(TARGET_NAME)_src-$(VERSION)
	$(GTAR) -zcf $(TARGET_NAME)_src-$(VERSION).tar.gz \
                     $(TARGET_NAME)_src-$(VERSION)
	-$(RM) -r $(TARGET_NAME)_src-$(VERSION)

pack-clean:
	-$(RM) $(TARGET_NAME)_src-*.tar.gz $(TARGET_NAME)-*.zip
	-$(RM) -r $(TARGET_NAME)-*/ $(TARGET_NAME)_src-*/


PUT_DIR = /t/www/data/www.tamanegi.org/prog/$(TARGET_NAME)/p

put: pack
	$(INSTALL) -m 755 -d $(PUT_DIR)/
	$(INSTALL) -m 644 $(TARGET_NAME)-$(VERSION).zip $(PUT_DIR)/
	$(INSTALL) -m 644 $(TARGET_NAME)_src-$(VERSION).tar.gz \
	                  $(PUT_DIR)/
	$(INSTALL) -m 644 $(READMES) $(PUT_DIR)/../
