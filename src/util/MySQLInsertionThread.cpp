#include "MySQLInsertionThread.h"

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
    std::lock_guard<std::mutex> lock(this->queue_mutex);
    this->insert_queue.push(_insert_query);
}

unsigned int MySQLInsertionThread::get_insert_queue_size () {
    std::lock_guard<std::mutex> lock(this->queue_mutex);
    return this->insert_queue.size();
}