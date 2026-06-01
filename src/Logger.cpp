#include "../include/Logger.h"
#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <mutex>
#include <sstream>

Logger::Logger(){

}

Logger::~Logger(){
    if(logFile_.is_open()){
        logFile_.close();
    }
}

Logger& Logger::getInstance(){
    static Logger instance;
    return instance;
}

void Logger::setLogFile(const  std::string& filename){
    std::lock_guard<std::mutex> lock(loggerMutex_);

    if(logFile_.is_open()){
        logFile_.close();
    }
    logFile_.open(filename, std::ios::app);
    if(!logFile_.is_open()){
        std::cerr<<"Failed to open log file: " << filename << std::endl;
    }
}

std::string Logger::levelToSring(LogLevel level){
    switch (level) {
            case LogLevel::DEBUG:   return "DEBUG";
            case LogLevel::INFO:    return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::ERROR:   return "ERROR";
            default:                return "UNKNOWN";
        }
}

std::string Logger::getTimeStamp(){
    auto now =  std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss<<std::put_time(std::localtime(&in_time_t),"%Y-%m-%d %X");
    return ss.str();
}

void Logger::log(LogLevel level, const std::string& message){
    std::lock_guard<std::mutex> lock(loggerMutex_);
    std::string logEntry = "["+getTimeStamp()+"] ["+levelToSring(level)+"] "+message+"\n";

    std::cout<<logEntry;
    if(logFile_.is_open()){
        logFile_<<logEntry;
        logFile_.flush();
    }
}
