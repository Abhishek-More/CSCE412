#include <string>
#include <queue>
#include <iostream>


class Request {
public:
  int time;
  int origTime;
  int startTime;
  std::string toIP;
  std::string fromIP;

  Request()
  {
    this->time = rand() % 10 + 1;
    this->origTime = this->time;
    this->toIP = this->generateIP();
    this->fromIP = this->generateIP();
  }

  Request(int time, int startTime, std::string toIP, std::string fromIP)
  {
    this->time = time;
    this->origTime = time;
    this->startTime = startTime;
    this->toIP = toIP;
    this->fromIP = fromIP;
  }

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

class RequestQueue
{
public:
  std::queue<Request*> requestQueue;

  RequestQueue()
  {
  }

  RequestQueue(int requestNum)
  {
    for (int i = 0; i < requestNum; i++) {
      Request* req = new Request();
      std::cout << std::to_string(req->time) << " " << req->fromIP << " " << req->toIP << std::endl;
      requestQueue.push(req);
    }
  }

  Request* pop()
  {
    Request* front = requestQueue.front();
    requestQueue.pop();
    return front;
  }

  Request* front()
  {
    if (requestQueue.size() == 0)
    {
      return nullptr;
    }
    return this->requestQueue.front();
  }

  int size() {
    return requestQueue.size();
  }

  void push(Request* req)
  {
    return requestQueue.push(req);
  }
};
