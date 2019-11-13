#include <iostream>
#include <chrono>
#include <ctime>   
#include <fstream>
#include "FileLogger.h"

using namespace std;

void log(const char* s, bool withTime = true) {
  logg(s, withTime, "\n");
}

void logg(const char* s, bool withTime = true, const char* sep = "") {
  const char* ss = s;
  if (withTime) {
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    const char* dt = std::ctime(&end_time);
    ss =  "[" + dt + "]: " + s + sep;
  }
  std::ofstream writer(file);
  writer << ss;
}
