-include Makefile.rules
DIR=src
LOGIN_L=boissi_f
PROJET=-MQExample
CLASSICS=AUTHORS TODO README ChangeLog
SUPPLEMENTS=

all:
	cd $(DIR) && $(MAKE)

$(TARGET):
	cd $(DIR) && $(MAKE)

clean:
	rm -f *~
	rm -rf *#*
	rm -rf *.core
	rm -f $(LOGIN_L)$(PROJET).tar.bz2
	rm -rf $(LOGIN_L)$(PROJET)
	cd $(DIR) && $(MAKE) clean distclean
	rm -f Makefile.rules

distclean: clean
	./configure
	rm -f Makefile.rules

dist: distclean
	mkdir $(LOGIN_L)$(PROJET)
	cp -r $(CLASSICS) $(SUPPLEMENTS) configure Makefile src check \
	$(LOGIN_L)$(PROJET)
	tar cvjf $(LOGIN_L)$(PROJET).tar.bz2 $(LOGIN_L)$(PROJET)
	rm -rf $(LOGIN_L)$(PROJET)
	$(MD5) $(LOGIN_L)$(PROJET).tar.bz2


distcheck: dist
	tar xvjf $(LOGIN_L)$(PROJET).tar.bz2
	cd $(LOGIN_L)$(PROJET) && sh check
	rm -rf $(LOGIN_L)$(PROJET)

.PHONY: check

check:
	cd check && sh check.sh

cafe:
	@echo "                       "
	@echo "    \ | ( | ) / /      "
	@echo "  _________________    "
	@echo "  |               |    "
	@echo "  |               |    "
	@echo "  |               /--\ "
	@echo "  |               |  | "
	@echo "   \             /\--/ "
	@echo "    \___________/      "
	@echo "                       "

coffee: cafe
