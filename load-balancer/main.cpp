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

  const int INITIAL_SERVERS = 10;
  const int INITIAL_REQUESTS = INITIAL_SERVERS * 2;
  const double NEW_REQUEST_CHANCE = 1;
  const int RUNTIME = 10000;

  std::cout << "STARTING BALANCER" << std::endl;
  std::cout << "Number of Servers: " << INITIAL_SERVERS << std::endl;
  std::cout << "Percent chance of a new request: " << NEW_REQUEST_CHANCE << std::endl;
  std::cout << "Runtime: " << RUNTIME << " clock cycles" << std::endl;
  std::cout << "Starting Queue Size: " << INITIAL_REQUESTS << std::endl;
  std::cout << "Request time range: 1-500 clock cycles" << std::endl;

  RequestQueue q = RequestQueue(INITIAL_REQUESTS);
  std::vector<WebServer> servers = createWebServers(INITIAL_SERVERS);

  LoadBalancer l = LoadBalancer(servers, q, NEW_REQUEST_CHANCE, RUNTIME);
  l.balance();

  std::cout << "ENDING QUEUE SIZE: " << l.requestQueue.size() << std::endl;
  std::cout << l.filled << " still running" << std::endl;

  return 0;

}
