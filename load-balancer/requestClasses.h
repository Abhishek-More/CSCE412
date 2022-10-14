#include <string>
#include <queue>
#include <iostream>


/**
 * Contains Request data
*/
class Request {
public:
  int time; //!< Length of time the request needs to complete. Upon construction, it will be a random integer from 1-500 
  int startTime; //!< Clock cycle when the request began
  std::string toIP; //!< Destination IP
  std::string fromIP; //!< Origin IP

  Request()
  {
    this->time = rand() % 500 + 1;
    this->toIP = this->generateIP();
    this->fromIP = this->generateIP();
  }

  Request(int time, int startTime, std::string toIP, std::string fromIP)
  {
    this->time = time;
    this->startTime = startTime;
    this->toIP = toIP;
    this->fromIP = fromIP;
  }

  /**
   * Generates random IP address for origin or destination  
  */
  std::string generateIP()
  {
    std::string ip = "";
    ip += std::to_string(rand() % 256) + ".";
    ip += std::to_string(rand() % 256) + ".";
    ip += std::to_string(rand() % 256) + ".";
    ip += std::to_string(rand() % 256);

    return ip;
  }
};

/**
 * Class to store request pointers in a queue
*/
class RequestQueue
{
public:
  std::queue<Request*> requestQueue;

  RequestQueue()
  {

  }

  /**
   * Generates specified number of requests upon creation.
  */
  RequestQueue(int requestNum)
  {
    std::cout << "STARTING REQUESTS" << std::endl;
    for (int i = 0; i < requestNum; i++) {
      Request* req = new Request();
      std::cout << std::to_string(req->time) << " " << req->fromIP << " " << req->toIP << std::endl;
      requestQueue.push(req);
    }
  }

  /**
   * Pops from the front of the queue, and returns the popped request
  */
  Request* pop()
  {
    Request* front = requestQueue.front();
    requestQueue.pop();
    return front;
  }

  /**
   * Returns the request at the front of the queue
  */
  Request* front()
  {
    if (requestQueue.size() == 0)
    {
      return nullptr;
    }
    return this->requestQueue.front();
  }

  /**
   * Returns the size of the queue
  */
  int size() {
    return requestQueue.size();
  }

  /**
   * Adds to the queue
  */
  void push(Request* req)
  {
    return requestQueue.push(req);
  }
};
