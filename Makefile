webdir=/var/www
htmldir=html
scriptdir=scripts
targets=$(webdir)/html/* led_server $(webdir)/cgi-bin/*

all: $(targets)

$(webdir)/html/%: $(htmldir)/%
	cp $< $@

$(webdir)/cgi-bin/send-to-screen.cgi: $(scriptdir)/send-to-screen-py.py
	cp $< $@
led_server: src/* include/*
	$(MAKE) -C src
