game:
	make -f cliente.mk
	make -f server.mk

clean:
	make clean -f cliente.mk
	make clean -f server.mk