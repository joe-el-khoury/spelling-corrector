#include "MySQLInsertionThread.h"

/**
 * Goes through the queue and processes the queries.
 */
void MySQLInsertionThread::process_queries () {
    // The statement will be used a lot.
    sql::Statement* stmt = this->db_connection->createStatement();
    
    while (!(this->insertion_queue.empty())) {
        // Keep in new scope so the mutex becomes unlocked when the lock_guard is destroyed!
        {
            std::lock_guard<std::mutex> lock(this->insertion_queue_mutex);
            stmt->execute(_sql_query);
            this->insertion_queue.pop();
        }
    }

    delete stmt;
}

/**
 * Monitors the insertion queue and executes insertions if needed.
 */
void MySQLInsertionThread::monitor_and_insert () {
    while (this->running) {
        if (this->get_insert_queue_size() >= this->insert_every) {
            this->process_queries();
        }
    }

    // Process the last of the queries.
    this->process_queries();
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

void MySQLInsertionThread::add_to_insertion_queue (const std::string& _insert_query) {
    std::lock_guard<std::mutex> lock(this->insertion_queue_mutex);
    this->insertion_queue.push(_insert_query);
}

unsigned int MySQLInsertionThread::get_insertion_queue_size () {
    std::lock_guard<std::mutex> lock(this->insertion_queue_mutex);
    return this->insertion_queue.size();
}