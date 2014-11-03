//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char **argv) {
  char *server;

  assert(argc == 2);

  asprintf(&server, "tcp://%s", argv[1]);

  printf ("Connecting to hello world server: %s\n", server);
  void *context = zmq_ctx_new();
  void *requester = zmq_socket(context, ZMQ_REQ);
  zmq_connect(requester, server);

    int request_nbr;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
      int n;
      char buffer [50];
      printf ("Sending Hello %d…\n", request_nbr);
      zmq_send (requester, "hello", 5, 0);
      n = zmq_recv (requester, buffer, sizeof(buffer), 0);
      printf("%d\n", n);
      printf("Received World %d '%.*s'\n", request_nbr, n, buffer);
    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}
