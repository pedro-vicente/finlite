#include "server.hh"
#include "generator.hh"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#define close closesocket
typedef int socklen_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////
// http_server
/////////////////////////////////////////////////////////////////////////////////////////////////////

http_server::http_server(int p, finmart_db& database) : port(p), db(database), server_fd(-1)
{
#ifdef _WIN32
  WSADATA wsa_data;
  if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
  {
  }
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// ~http_server
/////////////////////////////////////////////////////////////////////////////////////////////////////

http_server::~http_server()
{
  if (server_fd != -1)
  {
    close(server_fd);
  }
#ifdef _WIN32
  WSACleanup();
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// start
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool http_server::start()
{
  struct sockaddr_in address;
  int opt = 1;

  server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)))
  {
    return false;
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
  {
    return false;
  }

  if (listen(server_fd, 3) < 0)
  {
    return false;
  }

  std::cout << "Server running on: http://localhost:" << port << std::endl;

  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// run
/////////////////////////////////////////////////////////////////////////////////////////////////////

void http_server::run()
{
  while (true)
  {
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    int sock = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if (sock < 0)
    {
      continue;
    }

    char buf[30000] = { 0 };
    recv(sock, buf, 30000, 0);

    std::string request(buf);
    std::string html = html_generator::generate_dashboard(db);

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // make HTML response
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    std::stringstream ss;
    ss << "HTTP/1.1 200 OK\r\n";
    ss << "Content-Type: text/html; charset=UTF-8\r\n";
    ss << "Content-Length: " << html.length() << "\r\n";
    ss << "Connection: close\r\n";
    ss << "\r\n";
    ss << html;

    std::string str = ss.str();
    send(sock, str.c_str(), (int)str.length(), 0);

    close(sock);
  }
}

