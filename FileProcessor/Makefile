C:=gcc
SRCEXT:=c
SRCDIR:=src
OBJDIR:=obj
BIN:=fileprocessor

CFLAGS:=
LDFLAGS:=

DEBUGCFLAGS:=-g -D _DEBUG
DEBUGLDFLAGS:=-g

RELEASECFLAGS:=-O2
RELEASELDFLAGS:=

ifeq '$(OS)' 'Windows_NT'
	BIN:=$(BIN).exe
endif
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
$(BIN): $(OBJS)
	$(C) $(OBJS) -o $@ $(LDFLAGS)
$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(C) -c $< -o $@ -MMD $(CFLAGS)
dep: release
	mv ./$(BIN) ../$(BIN)
dirs:
	mkdir -p $(OBJDIR) $(dir $(BIN))
clean:
	rm -rf $(OBJDIR) $(BIN)
ifneq '$(OS)' 'Windows_NT'
	INSTALLPATH=/usr/local/bin/$(notdir $(BIN))
	.PHONY: install uninstall
	install: release
		install -m 755 $(BIN) $(INSTALLPATH)
	uninstall:
		rm -f $(INSTALLPATH)
endif
