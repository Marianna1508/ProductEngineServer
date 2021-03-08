#include <iostream>
#include <chrono>
#include <thread>
#include "CServer.h"

#define MAX_CONNECCTION 5
void error(const char *msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[])
{
  std::cout << "Test server started..." << std::endl;

  int clientSocket;
  socklen_t clientAdrLen;
  char buffer[256];
  struct sockaddr_in clientAddr;
  int n;
  if (argc < 2)
  {
    fprintf(stderr, "ERROR, no port provided\n");
    exit(1);
  }
  int portno = atoi(argv[1]);
  CServer server(portno);
  int sockfd = server.socket();
  if (sockfd < 0)
    error("ERROR opening socket");
  
  if (server.bind(sockfd) < 0)
    error("ERROR on binding");

  server.listen(sockfd, MAX_CONNECCTION);

  clientAdrLen = sizeof(clientAddr);

for (;;)
{
  clientSocket = accept(sockfd,
                     (struct sockaddr *)&clientAddr,
                     &clientAdrLen);
  if (clientSocket < 0)
    error("ERROR on accept");
  bzero(buffer, 256);
  n = read(clientSocket, buffer, 255);
  if (n < 0)
    error("ERROR reading from socket");

  printf("Here is the message:\n %s", buffer);

  // take data from stdout and make text/html format
  char output_buffer[1024];
  std::string response = "\r\nHTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-length: ";
  std::string result = "";
  FILE *pipe = popen("../../src/run_some_command.sh", "r");
  if (!pipe)
    throw std::runtime_error("popen() failed!");
  try
  {
    while (fgets(output_buffer, sizeof output_buffer, pipe) != NULL)
    {
      result += output_buffer;
    }
  }
  catch (...)
  {
    pclose(pipe);
    throw;
  }
  pclose(pipe);
  response += std::to_string(result.length()) + "\r\n\r\n<h1>" + result +"</h1>";
  const char *res = result.c_str();

  // send result to the client
  n = write(clientSocket, res, result.length());

  if (n < 0)
    error("ERROR writing to socket");

  close(clientSocket);
}
  server.close(sockfd);

  std::this_thread::sleep_for(std::chrono::seconds(2));

  return 0;
}
