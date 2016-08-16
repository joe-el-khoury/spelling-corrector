#ifndef MYSQLINSERTIONTHREAD_H
#define MYSQLINSERTIONTHREAD_H

#include <connection.h>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

class MySQLInsertionThread {
public:
    MySQLInsertionThread (sql::Connection*);
    ~MySQLInsertionThread ();

    void add_to_insert_queue (const std::string&);
private:
    std::queue<std::string> insert_queue;
    unsigned int get_insert_queue_size ();

    bool running;
    std::unique_ptr<std::thread> insertion_thread;
    std::mutex queue_mutex;

    sql::Connection* db_connection;
};

#endif /* MYSQLINSERTIONTHREAD_H */