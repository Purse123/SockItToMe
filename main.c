#include <sys/socket.h>

#define PORT 8080
#define BUFFERSIZE 2048

typedef uint32_t u32;
typedef int32_t s32;

int main() {
  s32 server_fd, client_fd;
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == -1) {
    perror ("Socket failed");
    exit (-1);
  }
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  
  struct sockaddr_in server_addr;
  server_addr.sin_family        = AF_INT;
  server_addr.sin_port          = htons(PORT);
  server_addr.sin_addr.s_addr   = htonl(INADDR_ANY);

  if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    perror("Socket bind failed");
    close (server_fd);
    exit (-1);
  }
  if (listen(server_fd, 1)) {
    perror("Listening Failed");
    close (server_fd);
    exit(-1);
  }

  // bind() : you provide you own IP + port
  // accept() : OS fills in client's IP + port
  // NOTE: we are using same sockaddr for bind and accept
  fprintf(stdout, "Listning on port %d\n", PORT);                    // vvvvvvv 32 bit
  client_fd = accept(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

  
  return 0;
}
