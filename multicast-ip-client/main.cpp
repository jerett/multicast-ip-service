#include <iostream>
#include "multicast_ip_client.h"

int main(int argc, char*argv[]) {
  MulticastIpClient ip_client;
  ip_client.Open();
  std::string ip;
  ip_client.SetTimeout(5000);
  ip_client.QueryServerIp(&ip);
  std::cout << "ip::" << ip << std::endl;
  return EXIT_SUCCESS;
}
