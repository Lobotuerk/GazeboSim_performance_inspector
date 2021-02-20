#ifndef LISTENER_HH_
#define LISTENER_HH_

#include <fstream>
#include <memory>
#include <mutex>
#include <string>

class Listener
{
  public: Listener(const std::string &_topic,
              std::shared_ptr<std::ofstream> _logFile,
              std::shared_ptr<std::mutex> _fileMutex);

  public: ~Listener();

  public: bool Listen();

  private: std::string topic;

  // forward declaration of a class that should have a node with a
  // Subscribe(...) method
  private: class ListenerPrivate;

  // using PImpl to allow for an Ignition or Gazebo classic implementation
  // (the dependencies are determined at compile-time)
  private: std::unique_ptr<ListenerPrivate> dataPtr;
};

#endif
