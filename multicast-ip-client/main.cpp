#include <iostream>
#include "multicast_ip_client.h"

int main(int argc, char*argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage : <multicast_ip_client key(required)>\n");
    return EXIT_FAILURE;
  }
  MulticastIpClient ip_client;
  ip_client.Open();
  std::string ip;

  ip_client.SetTimeout(5000);
//  while (true) {
  std::cout << ip_client.QueryServerIp(argv[1], &ip) << ":" << ip << std::endl;
//  }
  return EXIT_SUCCESS;
}
