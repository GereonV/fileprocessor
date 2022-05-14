TARGETS:=FileProcessor MakeMake

.PHONY: all clean
all:
	$(foreach dir,$(TARGETS),make -C $(dir) dep;)
clean:
	$(foreach dir,$(TARGETS),make -C $(dir) clean;)
ifneq '$(OS)' 'Windows_NT'
	.PHONY: install uninstall
	install: all
		$(foreach dir,$(TARGETS),make -C $(dir) install;)
	uninstall:
		$(foreach dir,$(TARGETS),make -C $(dir) uninstall;)
endif
