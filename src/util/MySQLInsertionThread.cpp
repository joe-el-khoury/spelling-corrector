#include "MySQLInsertionThread.h"

/**
 * Goes through the queue and processes the queries.
 */
void MySQLInsertionThread::process_queries () {
    // The statement will be used a lot.
    sql::Statement* stmt = this->db_connection->createStatement();
    
    while (!(this->insertion_queue.empty())) {
        if (this->insertion_thread->joinable()) {
            // Lock the mutex only if the thread is joinable.
            {
                std::lock_guard<std::mutex> lock(this->insertion_queue_mutex);
                stmt->execute(this->insertion_queue.front());
                this->insertion_queue.pop();
            }
        
        } else {
            stmt->execute(this->insertion_queue.front());
            this->insertion_queue.pop();
        }
    }

    if (stmt) {
        delete stmt;
    }
}

/**
 * Monitors the insertion queue and executes insertions if needed.
 */
void MySQLInsertionThread::monitor_and_insert () {
    while (this->running) {
        if (this->get_insertion_queue_size() >= this->insert_every) {
            this->process_queries();
        }
    }

    // Process the last of the queries.
    this->process_queries();
}

/**
 * Stops the insertion thread and goes through the queue.
 */
void MySQLInsertionThread::stop () {
    this->running = false;
    this->insertion_thread->join();
}

/**
 * Launches the thread.
 */
MySQLInsertionThread::MySQLInsertionThread (sql::Connection* _db_connection) {
    this->insertion_thread = std::make_unique<std::thread>(&MySQLInsertionThread::monitor_and_insert, this);
    this->running          = true;

    this->db_connection = _db_connection;
}

void MySQLInsertionThread::add_to_insertion_queue (const std::string& _insert_query) {
    std::lock_guard<std::mutex> lock(this->insertion_queue_mutex);
    this->insertion_queue.push(_insert_query);
}

unsigned int MySQLInsertionThread::get_insertion_queue_size () {
    std::lock_guard<std::mutex> lock(this->insertion_queue_mutex);
    return this->insertion_queue.size();
}