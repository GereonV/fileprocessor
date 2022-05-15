C:=gcc
SRCEXT:=c
SRCDIR:=src
OBJDIR:=obj
LIB:=libds.a

CFLAGS:=-std=c11 -Wpedantic -Wall
DEBUGCFLAGS:=-g -D _DEBUG
RELEASECFLAGS:=-O2

.PHONY: all debug release test dep dirs clean
all: CFLAGS+=$(DEBUGCFLAGS)
all: LDFLAGS+=$(DEBUGLDFLAGS)
all: $(LIB)
debug: dirs all
release: CFLAGS+=$(RELEASECFLAGS)
release: LDFLAGS+=$(RELEASELDFLAGS)
release: dirs $(LIB)
OBJS:=$(patsubst $(SRCDIR)/%.$(SRCEXT),$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.$(SRCEXT)))
-include $(OBJS:%.o=%.d)
test: $(LIB)
	$(C) test/main.c -I$(SRCDIR) -L$(dir $(LIB)) -lds
	./a
	rm ./a
$(LIB): $(OBJS)
	ar -cr $(LIB) $(OBJS)
$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(C) -c $< -o $@ -MMD $(CFLAGS)
dep: release
	cp $(SRCDIR)/*.h ../deps/lib/include/
	mv ./$(LIB) ../deps/lib/
dirs:
	mkdir -p $(OBJDIR) $(dir $(LIB))
clean:
	rm -rf $(OBJDIR) $(LIB)
ifneq '$(OS)' 'Windows_NT'
	INSTALLPATH=/usr/local/lib/$(notdir $(LIB))
	.PHONY: install uninstall
	install: release
		cp $(LIB) $(INSTALLPATH)
	uninstall:
		rm -f $(INSTALLPATH)
endif
