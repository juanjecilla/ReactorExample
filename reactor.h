#ifndef REACTOR_H
#define REACTOR_H

struct reactor_;
typedef struct reactor_ reactor_t;

struct eh_ {
  int fd;
  int (*handle_read) (struct eh_*);
  reactor_t* reactor;
};
typedef struct eh_ eh_t;

int eh_handle_read (eh_t* eh);

reactor_t* reactor_new (void);
void reactor_register_eh (reactor_t* r, eh_t* eh);
void reactor_handle_events (reactor_t* r);

#endif
