TARGETS:=DataStructures FileProcessor MakeMake

.PHONY: all clean
all:
	mkdir -p deps/bin deps/lib/include
	$(foreach dir,$(TARGETS),"$(MAKE)" -C $(dir) dep;)
clean:
	$(foreach dir,$(TARGETS),"$(MAKE)" -C $(dir) clean;)
reset: clean
	rm -rf deps MakeMake/src/template.h
ifneq '$(OS)' 'Windows_NT'
	.PHONY: install uninstall
	install: all
		$(foreach dir,$(TARGETS),"$(MAKE)" -C $(dir) install;)
	uninstall:
		$(foreach dir,$(TARGETS),"$(MAKE)" -C $(dir) uninstall;)
endif
