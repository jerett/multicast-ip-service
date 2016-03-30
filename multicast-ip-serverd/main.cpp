#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main (int argc, char *argv[]) {
  int sockfd; // 套接字文件描述符
  struct sockaddr_in dest_addr; // 目标ip
  char buf[] = "192.168.2.79";

  sockfd = socket(AF_INET, SOCK_DGRAM, 0); // 建立套接字
  if (sockfd == -1) {
    perror("socket()");
    return -1;
  }

  // 初始化目标 ip 信息
  memset(&dest_addr, 0, sizeof(dest_addr));
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_addr.s_addr = inet_addr("224.0.0.88"); // 目的地址，为多播地址
  dest_addr.sin_port = htons(7777); 	// 多播服务器的端口也是 8000

  // 向多播地址发送数据
  while(true){
    int n = sendto(sockfd, buf, strlen(buf), 0,(struct sockaddr*)&dest_addr, sizeof(dest_addr));
    if (n < 0) {
      perror("sendto()");
      return -2;
    }
    sleep(1);
  }
}
