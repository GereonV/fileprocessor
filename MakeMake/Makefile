C:=gcc
SRCEXT:=c
SRCDIR:=src
OBJDIR:=obj
BIN:=makemake
FP:=../deps/bin/fileprocessor # path to executable
ifeq '$(OS)' 'Windows_NT'
BIN:=$(BIN).exe
endif

CFLAGS:=-std=c11 -Wpedantic -Wall -Wextra -Wconversion
LDFLAGS:=

DEBUGCFLAGS:=-g -D _DEBUG
DEBUGLDFLAGS:=-g

RELEASECFLAGS:=-O3
RELEASELDFLAGS:=

.PHONY: all debug release dep dirs clean
all: CFLAGS+=$(DEBUGCFLAGS)
all: LDFLAGS+=$(DEBUGLDFLAGS)
all: $(BIN)
debug: dirs all
release: CFLAGS+=$(RELEASECFLAGS)
release: LDFLAGS+=$(RELEASELDFLAGS)
release: dirs $(BIN)
OBJS:=$(patsubst $(SRCDIR)/%.$(SRCEXT),$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.$(SRCEXT)))
-include $(OBJS:%.o=%.d)
$(BIN): src/template.h $(OBJS)
	$(C) $(OBJS) -o $@ $(LDFLAGS)
$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(C) -c $< -o $@ -MMD $(CFLAGS)
src/template.h: Template.mk
	$(FP) -O$@ $<
dep: release
	mv ./$(BIN) ../deps/bin/
dirs:
	mkdir -p $(OBJDIR) $(dir $(BIN))
clean:
	rm -rf $(OBJDIR) $(BIN) src/template.h

ifneq '$(OS)' 'Windows_NT'
INSTALLPATH=/usr/local/bin/$(notdir $(BIN))
.PHONY: install uninstall
install: release
	install -m 755 $(BIN) $(INSTALLPATH)
uninstall:
	rm -f $(INSTALLPATH)
endif
