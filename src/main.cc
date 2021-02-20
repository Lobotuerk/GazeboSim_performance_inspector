#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <mutex>
#include <memory>
#include <string>
#include <thread>
#include <tuple>

#include <boost/program_options.hpp>

#include "Listener.hh"

// TODO have a sigint handler?
// (can close the file and call the Listener destructor)

std::tuple<std::string, unsigned int, std::string> parseArgs(const int _argc,
    const char* const *_argv)
{
  namespace po = boost::program_options;

  std::string topic;
  unsigned int time;
  std::string file;

  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "Produce help message")
    ("topic", po::value<std::string>(&topic)->default_value("/stats"),
      " The topic to subscribe to that contains performance metrics")
    ("time", po::value<unsigned int>(&time)->default_value(10),
      "How long to record metrics for, in seconds")
    ("file", po::value<std::string>(&file)->default_value(
      "metrics.log"), "The file to log metrics to");

  po::variables_map vm;
  po::store(po::parse_command_line(_argc, _argv, desc), vm);
  po::notify(vm);

  if (vm.count("help"))
  {
    std::cout << desc << std::endl;
    std::exit(0);
  }

  return {topic, time, file};
}

int main (int argc, char* argv[])
{
  auto params = parseArgs(argc, argv);
  std::string topic = std::get<0>(params);
  unsigned int recordLength = std::get<1>(params);
  std::string fileName = std::get<2>(params);

  auto logFile = std::make_shared<std::ofstream>();
  auto fileMutex = std::make_shared<std::mutex>();

  // open a "fresh" log file for writing
  // (delete any content that already exists in the log file before writing)
  logFile->open(fileName, std::ofstream::out | std::ostream::trunc);
  if (!logFile->is_open())
  {
    std::cerr << "Error creating log file " << fileName << std::endl;
    return -1;
  }

  Listener listener(topic, logFile, fileMutex);
  if (!listener.Listen())
  {
    std::cerr << "Error subscribing to topic " << topic << std::endl;
    logFile->close();
    return -1;
  }
  std::cout << "Saving data from " << topic << " to " << fileName << std::endl;

  std::cout << "Recording RTF for " << recordLength << " seconds..." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(recordLength));
  std::cout << "Done recording RTF." << std::endl;

  std::lock_guard<std::mutex> guard(*fileMutex);
  logFile->close();

  return 0;
}
