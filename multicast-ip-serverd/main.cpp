#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <cstring>

#include "llog/llog.h"
#include "ip_query.h"

namespace {
const char *kGroupServerAddress = "224.0.0.88";
const int port = 7777;
}

int main (int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage : <multicast_ip_serverd interface>\n");
    return EXIT_FAILURE;
  }

  ins::log_to_stderr = true;
  ins::Configuration::GetInstance().Configure(ins::Configuration::LOG_FILE,
                                              "/tmp/multicast_ip_serverd.log");
  daemon(0, 1);
  char *interface = argv[1];

  auto sockfd = socket(AF_INET, SOCK_DGRAM, 0); // 建立套接字
  if (sockfd == -1) {
    perror("socket()");
    return -1;
  }

  struct sockaddr_in dest_addr; // 目标ip
  // 初始化目标 ip 信息
  bzero(&dest_addr, sizeof(dest_addr));
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_addr.s_addr = inet_addr(kGroupServerAddress); // 目的地址，为多播地址
  dest_addr.sin_port = htons(port); 	// 多播服务器的端口也是 8000

  // 向多播地址发送数据
  while(true){
    IpQuery query(interface);
    auto ip = query.Query();
    auto n = sendto(sockfd, ip.c_str(), ip.length(), 0,
                    (struct sockaddr*)&dest_addr, sizeof(dest_addr));
    if (n < 0) {
      LOG(INFO) << "send ip err:" << std::strerror(errno);
    } else {
      LOG(INFO) << "send ip :" << ip;
    }
    sleep(5);
  }
}
