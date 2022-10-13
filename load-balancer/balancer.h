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

/**
* The LoadBalancer class keeps track of the webservers and the request queue and automatically balances the request load.
*/
class LoadBalancer {
  public:
    int runtime; //!< Max runtime for the program
    int filled; //!< Number of servers that are currently running a request
    int chance; //!< Percent chance of generating a new request per clock cycle
    std::vector<WebServer> servers;
    RequestQueue requestQueue;

    LoadBalancer(std::vector<WebServer> servers, RequestQueue requestQueue, double newReqChance, int runtime)
    {
      this->servers = servers;
      this->requestQueue = requestQueue;
      this->chance = newReqChance;
      this->runtime = runtime;
    }

    /**
    * Runs the balancing algorithm for the servers and request queue.
    * For each clock cycle, only one new request can be allocated.
    */
    void balance()
    {
      int clock = 0;
      bool action = false;
      filled = 0;

      while((this->requestQueue.front() != nullptr || filled != 0) && clock < runtime)
      {
        action = false;
        //std::cout << clock << "|" << std::endl;

        // 1% chance of creating a new request every clock cycle
        if(rand() % 100 < this->chance) {
           std::cout << clock << "| New request added to Queue" << std::endl;
           this->requestQueue.push(new Request());
        }

        for(int i = 0; i < servers.size(); i++) {

          //if the server's request is finished, clear the request
          if(servers[i].checkRequest(clock)) {
            std::cout << clock << "| Server " << i << " has finished a process from " << servers[i].currentRequest->fromIP << " to " << servers[i].currentRequest->toIP << " that took " << servers[i].currentRequest->time << std::endl;
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

      /*
      while(clock < this->runtime) {
        std::cout << clock << std::endl;
        clock++;
      }
      */
  }
};
