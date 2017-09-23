#include <stdio.h>
#include <stdlib.h>
#include "reactor.h"


struct light_eh_ {

	eh_t eh;
};
typedef struct light_eh_ light_eh_t;


static int light_eh_handle_read (eh_t* eh){

	char c;
	printf("Recibo presencia\n");
	c = getchar();
	getchar();
	if (c == '0') {
		printf("Apago las luces\n");
	    return 1;
	}
	else if (c == '1') {
	    printf("Enciendo las luces\n");
	    return 1;
	}
	else {
		printf("Dato incorrecto\n");
		return 1;
	}

	return 0;
}

eh_t* light_eh_new (int fd){

	light_eh_t* eh = (light_eh_t*) malloc(sizeof(light_eh_t));

	eh->eh.fd = fd;
	eh->eh.handle_read = light_eh_handle_read;

	return eh;
}

