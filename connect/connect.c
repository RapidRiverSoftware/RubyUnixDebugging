#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void die(char* format, ...) {
  va_list(ap);
  va_start(ap, format);
  vfprintf(stderr, format, ap);
  exit(1);
}

int main(int argc, char* argv[]) {

  const char* me       = argv[0];
  const char* port     = argv[1];
  const char* hostname = argv[2];

  if(port == NULL) {
    die("Usage: %s port [hostname]\n", me);
  }

  if(hostname == NULL) {
    hostname = "127.0.0.1";
  }

  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));

  hints.ai_family      = AF_UNSPEC;
  hints.ai_socktype    = SOCK_STREAM;
  hints.ai_protocol    = 0;
  hints.ai_flags       = AI_ADDRCONFIG;
  struct addrinfo* res = 0;

  int err = getaddrinfo(hostname, port, &hints, &res);

  if (err != 0) {
    die("failed to resolve remote socket address (err=%d)\n",err);
  }

  int fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (fd == -1) {
    die("Failed to create socket: %s", strerror(errno));
  }

  if(connect(fd, res->ai_addr, res->ai_addrlen)==-1) {
    die("Unable to connect to %s:%s: %s", hostname, port, strerror(errno));
  }

  while(1) {
    sleep(10000);
  }
}
