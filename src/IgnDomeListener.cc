#include "Listener.hh"

#include <iomanip>
#include <fstream>
#include <memory>
#include <mutex>
#include <string>

#include <ignition/msgs.hh>
#include <ignition/transport.hh>

class Listener::ListenerPrivate
{
  public: ListenerPrivate(std::shared_ptr<std::ofstream> _logFile,
              std::shared_ptr<std::mutex> _fileMutex);

  public: void cb(const ignition::msgs::WorldStatistics &_msg);

  public: ignition::transport::Node node;

  public: std::shared_ptr<std::ofstream> logFile{nullptr};

  public: std::shared_ptr<std::mutex> fileMutex{nullptr};
};

Listener::Listener(const std::string &_topic,
    std::shared_ptr<std::ofstream> _logFile,
    std::shared_ptr<std::mutex> _fileMutex) :
  topic(_topic),
  dataPtr(std::make_unique<ListenerPrivate>(_logFile, _fileMutex))
{
}

Listener::~Listener() = default;

bool Listener::Listen()
{
  return this->dataPtr->node.Subscribe(this->topic,
      &ListenerPrivate::cb,
      this->dataPtr.get());
}

Listener::ListenerPrivate::ListenerPrivate(
    std::shared_ptr<std::ofstream> _logFile,
    std::shared_ptr<std::mutex> _fileMutex) :
  logFile(_logFile),
  fileMutex(_fileMutex)
{
}

void Listener::ListenerPrivate::cb(const ignition::msgs::WorldStatistics &_msg)
{
  std::lock_guard<std::mutex> guard(*(this->fileMutex));

  if (this->logFile->is_open())
  {
    *(this->logFile) << std::fixed << std::setprecision(2)
      << _msg.real_time_factor() << std::endl;
  }
}
