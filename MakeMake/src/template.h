#define TEMPLATE_MK \
"C:=%s\n" \
"SRCEXT:=%s\n" \
"SRCDIR:=src\n" \
"OBJDIR:=obj\n" \
"BIN:=program\n" \
"\n" \
"CFLAGS:=\n" \
"LDFLAGS:=\n" \
"\n" \
"DEBUGCFLAGS:=-g -D _DEBUG\n" \
"DEBUGLDFLAGS:=-g\n" \
"\n" \
"RELEASECFLAGS:=-O2\n" \
"RELEASELDFLAGS:=\n" \
"\n" \
"ifeq '$(OS)' 'Windows_NT'\n" \
"	BIN:=$(BIN).exe\n" \
"endif\n" \
".PHONY: all debug release dirs clean\n" \
"all: CFLAGS+=$(DEBUGCFLAGS)\n" \
"all: LDFLAGS+=$(DEBUGLDFLAGS)\n" \
"all: $(BIN)\n" \
"debug: dirs all\n" \
"release: CFLAGS+=$(RELEASECFLAGS)\n" \
"release: LDFLAGS+=$(RELEASELDFLAGS)\n" \
"release: dirs $(BIN)\n" \
"OBJS:=$(patsubst $(SRCDIR)/%%.$(SRCEXT),$(OBJDIR)/%%.o,$(wildcard $(SRCDIR)/*.$(SRCEXT)))\n" \
"-include $(OBJS:%%.o=%%.d)\n" \
"$(BIN): $(OBJS)\n" \
"	$(C) $(OBJS) -o $@ $(LDFLAGS)\n" \
"$(OBJDIR)/%%.o: $(SRCDIR)/%%.$(SRCEXT)\n" \
"	$(C) -c $< -o $@ -MMD $(CFLAGS)\n" \
"dirs:\n" \
"	mkdir -p $(OBJDIR) $(dir $(BIN))\n" \
"clean:\n" \
"	rm -rf $(OBJDIR) $(BIN)\n" \
"ifneq '$(OS)' 'Windows_NT'\n" \
"	INSTALLPATH=/usr/local/bin/$(notdir $(BIN))\n" \
"	.PHONY: install uninstall\n" \
"	install: release\n" \
"		install -m 755 $(BIN) $(INSTALLPATH)\n" \
"\n" \
"	uninstall:\n" \
"		rm -f $(INSTALLPATH)\n" \
"endif\n" \
""
