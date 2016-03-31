//
// Created by jerett on 16-3-30.
//

#include "ip_query.h"
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

IpQuery::IpQuery(const std::string &interface): interface_(interface) {
  udp_fd_ = socket(AF_INET, SOCK_DGRAM, 0);
}

std::string IpQuery::Query() {
  struct ifreq ifr;
  ifr.ifr_addr.sa_family = AF_INET;
  strncpy(ifr.ifr_name, interface_.c_str(), IFNAMSIZ-1);
  ioctl(udp_fd_, SIOCGIFADDR, &ifr);

  sockaddr_in *ip_addr = reinterpret_cast<sockaddr_in*>(&ifr.ifr_addr);
  std::string ip(inet_ntoa(ip_addr->sin_addr));
  return std::move(ip);
//  std::string ip(inet_ntoa((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr)));
}

IpQuery::~IpQuery() {
  close(udp_fd_);
}
