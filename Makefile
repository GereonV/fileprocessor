TARGETS:=FileProcessor MakeMake

.PHONY: all clean
all:
	$(foreach dir,$(TARGETS),"$(MAKE)" -C $(dir) dep;)
clean:
	$(foreach dir,$(TARGETS),"$(MAKE)" -C $(dir) clean;)
ifneq '$(OS)' 'Windows_NT'
	.PHONY: install uninstall
	install: all
		$(foreach dir,$(TARGETS),"$(MAKE)" -C $(dir) install;)
	uninstall:
		$(foreach dir,$(TARGETS),"$(MAKE)" -C $(dir) uninstall;)
endif
