#include "Listener.hh"

#include <iomanip>
#include <fstream>
#include <memory>
#include <mutex>
#include <string>

#include <gazebo/common/common.hh>
#include <gazebo/gazebo_client.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/transport/transport.hh>

class Listener::ListenerPrivate
{
  public: ListenerPrivate(std::shared_ptr<std::ofstream> _logFile,
              std::shared_ptr<std::mutex> _fileMutex);

  public: void cb(ConstWorldStatisticsPtr &_msg);

  public: gazebo::transport::NodePtr node;

  public: gazebo::transport::SubscriberPtr sub;

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

Listener::~Listener()
{
  gazebo::client::shutdown();
}

bool Listener::Listen()
{
  this->dataPtr->sub =
    this->dataPtr->node->Subscribe(this->topic,
        &ListenerPrivate::cb, this->dataPtr.get());

  return nullptr != this->dataPtr->sub;
}

Listener::ListenerPrivate::ListenerPrivate(
    std::shared_ptr<std::ofstream> _logFile,
    std::shared_ptr<std::mutex> _fileMutex) :
  node(new gazebo::transport::Node()),
  logFile(_logFile),
  fileMutex(_fileMutex)
{
  gazebo::client::setup();
  this->node->Init();
}

void Listener::ListenerPrivate::cb(ConstWorldStatisticsPtr &_msg)
{
  std::lock_guard<std::mutex> guard(*(this->fileMutex));

  if (this->logFile->is_open())
  {
    auto simTime = gazebo::msgs::Convert(_msg->sim_time());
    auto realTime = gazebo::msgs::Convert(_msg->real_time());
    auto rtf = simTime.Double() / realTime.Double();

    *(this->logFile) << std::fixed << std::setprecision(2)
      << rtf << std::endl;
  }
}
