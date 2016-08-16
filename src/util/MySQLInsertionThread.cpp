#include "MySQLInsertionThread.h"

/**
 * Monitors the insertion queue and executes insertions if needed.
 */
void MySQLInsertionThread::monitor_and_insert () {
    while (this->running) {
        if (this->get_insert_queue_size() >= this->insert_every) {
            // Pop from the queue and process the query until it's empty.
            while (!(this->insertion_queue.empty())) {
                // Keep in new scope so the mutex becomes unlocked when the lock_guard is destroyed!
                {
                    std::lock_guard<std::mutex> lock(this->insertion_queue_mutex);
                    this->exec_insert_query(this->insert_queue.front());
                    this->insert_queue.pop();
                }
            }
        }
    }

    // The thread is no longer running, so process the last of the queries.
    while (!(this->insertion_queue.empty())) {
        {
            std::lock_guard<std::mutex> lock(this->insertion_queue_mutex);
            this->exec_insert_query(this->insertion_queue.front());
            this->insertion_queue.pop();
        }
    }
}

/**
 * Launches the thread.
 */
MySQLInsertionThread::MySQLInsertionThread (sql::Connection* _db_connection) {
    this->running = true;
    this->db_connection = _db_connection;
}

/**
 * Stop the thread.
 */
MySQLInsertionThread::~MySQLInsertionThread () {
    this->running = false;
}

void MySQLInsertionThread::exec_insert_query (const std::string _insert_query) {
    sql::Statement* stmt = this->db_connection->createStatement();
    bool returned_result = stmt->execute(_sql_query);
}

void MySQLInsertionThread::add_to_insert_queue (const std::string& _insert_query) {
    std::lock_guard<std::mutex> lock(this->insertion_queue_mutex);
    this->insert_queue.push(_insert_query);
}

unsigned int MySQLInsertionThread::get_insert_queue_size () {
    std::lock_guard<std::mutex> lock(this->insertion_queue_mutex);
    return this->insert_queue.size();
}