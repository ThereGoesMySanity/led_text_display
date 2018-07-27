webdir=/var/www
htmldir=html
scriptdir=scripts
targets=$(webdir)/html led_server $(webdir)/cgi-bin/send-to-screen.cgi

all: $(targets)

$(webdir)/html: $(htmldir)
	rsync -rupiE --delete $(htmldir) $(webdir)

$(webdir)/cgi-bin/%.cgi: $(scriptdir)/%.py
	cp $< $@

led_server: src/* include/*
	$(MAKE) -C src

.PHONY: $(webdir)/html
