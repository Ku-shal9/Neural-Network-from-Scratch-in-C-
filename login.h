#ifndef LOGIN_H
#define LOGIN_H

#include <sqlite3.h>
#include <iostream>
#include <string>

bool login_database(const std::string &db_path)
{
    sqlite3 *db;
    if (sqlite3_open(db_path.c_str(), &db))
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::string username, password;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    std::string sql = "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    bool success = false;
    if (rc == SQLITE_ROW)
    {
        int count = sqlite3_column_int(stmt, 0);
        if (count == 1)
        {
            std::cout << "Login successful!\n\n";
            success = true;
        }
        else
        {
            std::cout << "Invalid username or password.\n\n";
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return success;
}

#endif // LOGIN_H
