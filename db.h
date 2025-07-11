#pragma once
#include <string>
#include <vector>

//database function declarations for contact management
bool initDatabase();
bool addContactToDB(const std::string& name, long long phone);
bool updateContactInDB(const std::string& name, long long newPhone);
bool deleteContactFromDB(const std::string& name);
void searchContactsInDB(const std::string& query);
void displayAllContacts();
bool contactExists(const std::string& name);
void sortContactsInDB(int sortBy); // 1- name, 2- phone
bool clearAllContactsFromDB();

std::vector<std::pair<std::string, long long>> getAllContacts();
std::vector<std::pair<std::string, long long>> getContactsMatching(const std::string& query);
