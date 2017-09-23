#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "reactor.h"

eh_t* light_eh_new (int fd);
eh_t* interruptor_eh_new (int fd);

static int global_eh_handle_read (eh_t* eh){
 	char c;
	switch ((c = getchar())) {

	  	case 'q':
	    	exit (0);
	    	break;
	}
  	
  	return 1; // siempre consume (evita loops)
}

eh_t* global_eh_new (int fd){

	eh_t* eh = (eh_t*) malloc(sizeof(eh_t));

	eh->fd = fd;
	eh->handle_read = global_eh_handle_read;

	return eh;
}

int main (){

	reactor_t* r = reactor_new();


	eh_t* global_eh = global_eh_new (0);
	eh_t* light_eh = light_eh_new(0);
	eh_t* interruptor_eh = interruptor_eh_new(0);

	reactor_register_eh (r, global_eh);
	reactor_register_eh (r, light_eh);
	reactor_register_eh (r, interruptor_eh);


	while (1) {
		reactor_handle_events(r);
	}
}
