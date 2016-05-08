//
// Created by jerett on 16-3-30.
//

#ifndef MULTICAST_IP_CLIENT_MULTICAST_IP_CLIENT_H
#define MULTICAST_IP_CLIENT_MULTICAST_IP_CLIENT_H

#include <string>
#include <netinet/in.h>

class MulticastIpClient {
public:
  MulticastIpClient();
  ~MulticastIpClient();
  MulticastIpClient(const MulticastIpClient&) = default;
  MulticastIpClient(MulticastIpClient&&) = default;

  bool Open() noexcept;

  bool SetTimeout(int timeout_ms) noexcept;
  /**
   * if no timeout, will block unitil get msg
   */
  bool QueryServerIp(const std::string &key, std::string *ip) noexcept;

private:
  bool CheckMsgIsValidIP(const std::string &msg,
                         const std::string &key,
                         std::string *ip) const noexcept;

private:
  int timeout_ms_ = -1;
  constexpr static const char * kIpServerAddress = "224.0.0.88";
  const static int kIpServerPort = 7777;
  struct sockaddr_in local_addr_; // 本地地址
  int udp_fd_;
};


#endif //MULTICAST_IP_CLIENT_MULTICAST_IP_CLIENT_H
