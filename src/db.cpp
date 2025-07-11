#include "db.h"
#include <sqlite3.h>
#include <iostream>

sqlite3* db;

// intialize sqlite database and create table for contacts
bool initDatabase() {
    int rc = sqlite3_open("contacts.db", &db);
    if (rc) return false;

    const char* sql = "CREATE TABLE IF NOT EXISTS contacts (name TEXT PRIMARY KEY, phone INTEGER);";
    char* errMsg = nullptr;
    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);

    return rc == SQLITE_OK;
}

// add new contact to databse
bool addContactToDB(const std::string& name, long long phone) {
    std::string sql = "INSERT INTO contacts (name, phone) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 2, phone);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool updateContactInDB(const std::string& name, long long newPhone) {
    std::string sql = "UPDATE contacts SET phone = ? WHERE name = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int64(stmt, 1, newPhone);
    sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_TRANSIENT);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool deleteContactFromDB(const std::string& name) {
    std::string sql = "DELETE FROM contacts WHERE name = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool clearAllContactsFromDB() {
    const char* sql = "DELETE FROM contacts;";
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    return rc == SQLITE_OK;
}

void searchContactsInDB(const std::string& query) {
    auto results = getContactsMatching(query);
    for (const auto& contact : results)
        std::cout << contact.first << " : " << contact.second << "\n";
}

void displayAllContacts() {
    auto all = getAllContacts();
    for (const auto& contact : all)
        std::cout << contact.first << " : " << contact.second << "\n";
}

bool contactExists(const std::string& name) {
    std::string sql = "SELECT name FROM contacts WHERE name = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return exists;
}

// sort contacts by name or phone
void sortContactsInDB(int sortBy) {
    if (sortBy != 1 && sortBy != 2) {
        std::cerr << "Invalid sort option\n";
        return;
    }

    std::string sql = (sortBy == 1)
        ? "SELECT name, phone FROM contacts ORDER BY name COLLATE NOCASE;"
        : "SELECT name, phone FROM contacts ORDER BY phone;";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout << sqlite3_column_text(stmt, 0) << " : " << sqlite3_column_int64(stmt, 1) << "\n";
    }
    sqlite3_finalize(stmt);
}
// fetch all contacts from db
std::vector<std::pair<std::string, long long>> getAllContacts() {
    std::vector<std::pair<std::string, long long>> results;
    std::string sql = "SELECT name, phone FROM contacts;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            long long phone = sqlite3_column_int64(stmt, 1);
            results.emplace_back(name, phone);
        }
        sqlite3_finalize(stmt);
    }

    return results;
}
// search contacts by name with wildcard matching
std::vector<std::pair<std::string, long long>> getContactsMatching(const std::string& query) {
    std::vector<std::pair<std::string, long long>> results;
    std::string sql = "SELECT name, phone FROM contacts WHERE name LIKE ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        std::string wildcard = "%" + query + "%";
        sqlite3_bind_text(stmt, 1, wildcard.c_str(), -1, SQLITE_TRANSIENT);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            long long phone = sqlite3_column_int64(stmt, 1);
            results.emplace_back(name, phone);
        }

        sqlite3_finalize(stmt);
    }

    return results;
}
