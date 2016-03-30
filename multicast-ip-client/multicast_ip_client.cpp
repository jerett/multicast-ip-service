//
// Created by jerett on 16-3-30.
//

#include "multicast_ip_client.h"

#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

MulticastIpClient::MulticastIpClient() {
  udp_fd_ = socket(AF_INET, SOCK_DGRAM, 0);
}

MulticastIpClient::~MulticastIpClient() {
  close(udp_fd_);
}

bool MulticastIpClient::Open() noexcept {
  bzero(&local_addr_, sizeof(local_addr_));
  local_addr_.sin_family = AF_INET;
  local_addr_.sin_addr.s_addr = htonl(INADDR_ANY);
  local_addr_.sin_port = htons(kIpServerPort);

  auto ret = bind(udp_fd_,
                  reinterpret_cast<const sockaddr*>(&local_addr_),
                  sizeof(local_addr_));
  if (ret != 0) return false;

  struct ip_mreq mreq; // 多播地址结构体
  mreq.imr_multiaddr.s_addr = inet_addr(kIpServerAddress);
  mreq.imr_interface.s_addr = htonl(INADDR_ANY);
  // 加入多播组
  ret = setsockopt(udp_fd_, IPPROTO_IP, IP_ADD_MEMBERSHIP,&mreq, sizeof(mreq));
  if (ret != 0) return false;
  return true;
}

bool MulticastIpClient::SetTimeout(int timeout_ms) noexcept {
  struct timeval tv;
  tv.tv_sec = timeout_ms/1000;
  tv.tv_usec = (timeout_ms%1000) * 1000;
  auto ret = setsockopt(udp_fd_, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
  return ret == 0;
}

bool MulticastIpClient::QueryServerIp(std::string *ip) noexcept {
  char buff[1024] = {0};
  socklen_t  sock_len;
  // 接收数据
  auto n = recvfrom(udp_fd_, buff, sizeof(buff), 0,
                    (struct sockaddr*)&local_addr_, &sock_len);
  if (n == -1) {
    return false;
  } else {
    buff[n] = 0;
    *ip = buff;
    return true;
  }
}
