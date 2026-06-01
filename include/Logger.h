#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <mutex>
#include <fstream>
#include <sstream>

class Logger{
    public :
        enum class LogLevel{
            DEBUG, INFO, WARNING, ERROR
        };

        static Logger& getInstance();

        Logger(const Logger&) = delete;
        Logger operator=(const Logger&) = delete;

        void  setLogFile(const std::string& filename);
        void log(LogLevel level, const std::string& message);

    private:
        Logger();
        ~Logger();

        std::string levelToSring(LogLevel level);
        std::string getTimeStamp();

        std::mutex loggerMutex_;
        std::ofstream logFile_;
};

#define LOG_DEBUG(msg) Logger::getInstance().log(Logger::LogLevel::DEBUG, msg)
#define LOG_INFO(msg) Logger::getInstance().log(Logger::LogLevel::INFO, msg)
#define LOG_WARNING(msg) Logger::getInstance().log(Logger::LogLevel::WARNING, msg)
#define LOG_ERROR(msg) Logger::getInstance().log(Logger::LogLevel::ERROR, msg)

#endif //LOGGER_H_
