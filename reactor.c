#include <stdlib.h>
#include <sys/select.h>
#include "reactor.h"

#define MAXHANDLERS 100

struct reactor_ {
  int nhandlers;
  eh_t* handlers[MAXHANDLERS];
};

int eh_handle_read (eh_t* eh){
  if (eh->handle_read != NULL)
    return eh->handle_read(eh);
  return 0;
}

reactor_t* reactor_new (){
  reactor_t* r = (reactor_t*) malloc (sizeof (reactor_t));
  r->nhandlers = 0;
  return r;
}

void reactor_register_eh (reactor_t* r, eh_t* eh){

	r->handlers[r->nhandlers++] = eh;
	eh->reactor = r;
}

void reactor_handle_events (reactor_t* r){
  int i = 0;
  fd_set rd_set;
  int max_fd = 0;


  //XXX Inicializamos el set de lectura a 0
  FD_ZERO(&rd_set);

  for (;;) { //Recorremos todos los handlers
    eh_t* eh = r->handlers[i];
    if (eh->fd > max_fd)
      max_fd = eh->fd;
    FD_SET(0,&rd_set);
    //Añadimos con FD_SET para lectura
  }

  while (select(max_fd + 1, &rd_set, NULL,NULL,NULL) > 0) { //Espero eventos con select()
    for (i = r->nhandlers - 1; i >= 0; --i) {
      if (eh_handle_read (r->handlers[i]))
	break;
    }
  }
}
