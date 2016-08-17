#ifndef MYSQLINSERTIONTHREAD_H
#define MYSQLINSERTIONTHREAD_H

#include <connection.h>
#include <statement.h>

#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

class MySQLInsertionThread {
public:
    MySQLInsertionThread (sql::Connection*);

    void stop ();
    void add_to_insertion_queue (const std::string&);
private:
    std::queue<std::string> insertion_queue;
    unsigned int get_insertion_queue_size ();
    // How often to run the insert queries.
    const unsigned int insert_every = 1000;

    void process_queries ();
    void monitor_and_insert ();
    bool running;
    std::unique_ptr<std::thread> insertion_thread;
    std::mutex insertion_queue_mutex;

    sql::Connection* db_connection;
};

#endif /* MYSQLINSERTIONTHREAD_H */