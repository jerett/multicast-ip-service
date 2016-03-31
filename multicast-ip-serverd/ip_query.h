//
// Created by jerett on 16-3-30.
//

#ifndef MULTICAST_IP_SERVERD_IP_QUERY_H
#define MULTICAST_IP_SERVERD_IP_QUERY_H

#include <string>

class IpQuery {
public:
  IpQuery(const std::string &interface);
  IpQuery(const IpQuery&) = default;
  IpQuery(IpQuery&&) = default;
  IpQuery& operator=(const IpQuery&) = default;

  std::string Query();
  ~IpQuery();

private:
  int udp_fd_;
  std::string interface_;
};


#endif //MULTICAST_IP_SERVERD_IP_QUERY_H
