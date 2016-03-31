#Intrudution
muticast-ip-service provides service that client can obtain server's ip by multicasting .

#usage
##server
* Server run a dameon process which multicast ip every 5 seconds 
* usage: multicast_ip_serverd interface

##client
* Client attemp to get server ip via multicasting , and you can set a timeout.
* a few lines of code.
```
 MulticastIpClient ip_client;
  ip_client.Open();
  std::string ip;
  ip_client.SetTimeout(5000);
  ip_client.QueryServerIp(&ip);
 ```
 
 #plaform:
 unix like system