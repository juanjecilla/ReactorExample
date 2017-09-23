#include <stdio.h>
#include <stdlib.h>
#include "reactor.h"


struct interruptor_eh_ {

	eh_t eh;
};
typedef struct interruptor_eh_ interruptor_eh_t;


static int interruptor_eh_handle_read (eh_t* eh){

	char c;
	printf("Leo interruptor del aire\n");
	c = getchar();
	getchar();
	if (c == 'A') {
		printf("Aire apagado\n");
	    return 1;
	}
	else if (c == 'E') {
	    printf("Aire encendido\n");
	    return 1;
	}
	else {
		printf("Dato incorrecto\n");
		return 1;
	}

	return 0;
}

eh_t* interruptor_eh_new (int fd){

	interruptor_eh_t* eh = (interruptor_eh_t*) malloc(sizeof(interruptor_eh_t));

	eh->eh.fd = fd;
	eh->eh.handle_read = interruptor_eh_handle_read;

	return eh;
}

