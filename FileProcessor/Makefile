CEXT=.c
CC=gcc
SRC=src
ASM=asm
OBJ=obj
DIRS=$(SRC) $(OBJ) $(ASM)
SRCS=$(wildcard $(SRC)/*$(CEXT))
ASMS=$(patsubst $(SRC)/%$(CEXT),$(ASM)/%.s,$(SRCS))
OBJS=$(patsubst $(SRC)/%$(CEXT),$(OBJ)/%.o,$(SRCS))
EXT=
ifeq ($(OS),Windows_NT)
	EXT=.exe
endif
BINDEBUG=fileprocessor-debug$(EXT)
BINRELEASE=fileprocessor$(EXT)
INSTALLPATH=/usr/local/bin/$(notdir $(BINRELEASE))

CFLAGS=
LDFLAGS=
BIN=$(BINDEBUG)
all: debug

.PHONY: debug release install uninstall clean cleandebug cleanrelease installdirs

debug: CFLAGS+= -g -D _DEBUG
debug: LDFLAGS+= -g
debug: installdirs cleanrelease $(BIN)

release: CFLAGS+= -O2
release: LDFLAGS+=
release: BIN=$(BINRELEASE)
release: installdirs cleandebug $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(BIN)

$(OBJ)/%.o: $(ASM)/%.s
	$(CC) $(CFLAGS) -c $< -o $@

$(ASM)/%.s: $(SRC)/%$(CEXT)
	$(CC) $(CFLAGS) -S $< -o $@

.SECONDARY: $(ASMS)

install: release
ifneq ($(OS),Windows_NT)
	install -m 755 $(BINRELEASE) $(INSTALLPATH)
else
	$(info Windows-installation needs to be done manually)
endif

uninstall:
ifneq ($(OS),Windows_NT)
	rm -f $(INSTALLPATH)
endif

clean:
	rm -rf $(BINDEBUG) $(BINRELEASE) $(OBJ) $(ASM)

cleandebug:
ifeq ($(wildcard $(BINDEBUG)),$(BINDEBUG))
	rm -f $(BINDEBUG) $(OBJS) $(ASMS)
endif

cleanrelease:
ifeq ($(wildcard $(BINRELEASE)),$(BINRELEASE))
	rm -f $(BINRELEASE) $(OBJS) $(ASMS)
endif

installdirs:
ifneq ($(wildcard $(DIRS:=/.)),$(DIRS:=/.))
	mkdir -p $(DIRS)
endif
