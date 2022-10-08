C:=%s
SRCEXT:=%s
SRCDIR:=src
OBJDIR:=obj
BIN:=bin/program
ifeq '$(OS)' 'Windows_NT'
BIN:=$(BIN).exe
endif

CFLAGS:=-Wpedantic -Wall -Wextra -Wconversion
LDFLAGS:=

DEBUGCFLAGS:=-g -D _DEBUG
DEBUGLDFLAGS:=-g

RELEASECFLAGS:=-O3
RELEASELDFLAGS:=

.PHONY: debug release dirs clean
debug: CFLAGS+=$(DEBUGCFLAGS)
debug: LDFLAGS+=$(DEBUGLDFLAGS)
debug: $(BIN)
release: CFLAGS+=$(RELEASECFLAGS)
release: LDFLAGS+=$(RELEASELDFLAGS)
release: dirs $(BIN)
OBJS:=$(patsubst $(SRCDIR)/%%.$(SRCEXT),$(OBJDIR)/%%.o,$(wildcard $(SRCDIR)/*.$(SRCEXT)))
-include $(OBJS:%%.o=%%.d)
$(BIN): $(OBJS)
	$(C) $(OBJS) -o $@ $(LDFLAGS)
$(OBJDIR)/%%.o: $(SRCDIR)/%%.$(SRCEXT)
	$(C) -c $< -o $@ -MMD $(CFLAGS)
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
