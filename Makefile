CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi addc.cgi delc.cgi modc.cgi selc.cgi adds.cgi dels.cgi mods.cgi sels.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi

install:
		cp *.cgi /usr/lib/cgi-bin/sx

		#cp ~/cgi-stu/stu/index.html /var/www/html/index.html
		cp *.html /var/www/html
