#include <iostream>
#include "balancer.h"

std::vector<WebServer> createWebServers(int size) {
  std::vector<WebServer> list;
  for(int i = 0; i < size; i++) {
    list.push_back(WebServer());
  }

  return list;
}

int main() {

  const int INITIAL_SERVERS = 5;

  const int INITIAL_REQUESTS = INITIAL_SERVERS * 2;

  const int RUNTIME = 100;

  RequestQueue q = RequestQueue(INITIAL_REQUESTS);
  std::vector<WebServer> servers = createWebServers(INITIAL_SERVERS);

  LoadBalancer l = LoadBalancer(servers, q, RUNTIME);
  l.balance();

  return 0;

}
