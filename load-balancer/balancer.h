#include <__nullptr>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <queue>
#include <string>
#include <vector>

#include "requestClasses.h"


class WebServer {
  public:
    Request *currentRequest;

    WebServer()
    {
      currentRequest = nullptr;
    }

    void setCurrentRequest(Request *req)
    {
      this->currentRequest = req;
    }

    bool checkRequest(int currTime)
    {
      if (this->currentRequest != nullptr)
      {
        if(currTime - this->currentRequest->startTime >= this->currentRequest->time) {
          return true;
        }
        return false;
      }
      return false;
    }
};

class LoadBalancer {
  public:
    int runtime;
    std::vector<WebServer> servers;
    RequestQueue requestQueue;

    LoadBalancer(std::vector<WebServer> servers, RequestQueue requestQueue, int runtime)
    {
      this->servers = servers;
      this->requestQueue = requestQueue;
      this->runtime = runtime;
    }

    void balance()
    {
      int clock = 0;
      bool action = false;
      int filled = 0;
      
      for (int i = 0; i < servers.size(); i++) {
        std::cout << servers[i].currentRequest << std::endl;
      }

      while(this->requestQueue.front() != nullptr || filled != 0)
      {
        action = false;
        std::cout << clock << std::endl;

        for(int i = 0; i < servers.size(); i++) {

          //if the server's request is finished, clear the request
          if(servers[i].checkRequest(clock)) {
            std::cout << clock << "| Server " << i << " has finished a process that took" << servers[i].currentRequest->time << std::endl;
            servers[i].currentRequest = nullptr;
            filled--;
          };

          //If a new request has not been assigned in this clock cycle, and a server is empty, then put the request into the server.
          if(!action && servers[i].currentRequest == nullptr && requestQueue.size() != 0) {
            Request* r = requestQueue.pop();
            r->startTime = clock;
            servers[i].setCurrentRequest(r);
            std::cout << clock << "| Server " << i << " has a new process that will take " << r->time << std::endl;
            filled++;
            action = true;
          }
        }

        clock++;
      }

      while(clock < this->runtime) {
        std::cout << clock << std::endl;
        clock++;
      }
  }
};