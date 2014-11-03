//  Hello World server

#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

int main (void)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:7313");
    assert (rc == 0);

    while (1) {
      char buffer [10];
      zmq_recv (responder, buffer, 10, 0);
      if (memcmp("hello", buffer, 5) == 0) {
	  printf ("Received Hello\n");
	  zmq_send (responder, "World", 5, 0);
	  sleep(1);
      } else {
	printf ("Received: '%s'\n", buffer);
      }
    }
    return 0;
}
