// #include <iostream>
// #include <sqlite3.h>


// int main() {
//   sqlite3 * DB;
//   std::string create_table = "CREATE TABLE IF NOT EXISTS HIGHSCORES("
//                              "Id INT PRIMARY KEY NOT NULL"
//                              "Name CHAR(5)"
//                              "Score NOT NULL";
//   std::string create_index = "CREATE INDEX ScoreIndex ON HIGHSCORES (Score)";
//   int exists = 0;
//   exists = sqlite3_open("dodgy_blocks.db", &DB);
//   char * err;
//   exists = sqlite3_exec(DB, create_table.c_str(), NULL, 0, &err);

//   if (exists != SQLITE_OK) {
//     std::cerr << "Error Create Table" << std::endl;
//     sqlite3_free(err);
//   } else {
//     std::cout << "Table created Successfully" << std::endl;
//     sqlite3_close(DB);
//     return (0);
//   }
// }

// Create a callback function
int callback(void *NotUsed, int argc, char **argv, char **azColName)
{

  // Return successful
  return 0;
}

#include <iostream>
#include <sqlite3.h>
#include <string>

int main()
{
  sqlite3 *db;
  char * errMsg = 0;
  int rc;
  std::string sql;
  rc = sqlite3_open("dodgy_blocks.db", &db);

  if (rc) {
    std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_close(db);
    return (1);
  }
  sql = "CREATE TABLE IF NOT EXISTS HIGHSCORES ("
        "ID INT PRIMARY KEY     NOT NULL,"
        "NAME           TEXT    NOT NULL,"
        "SCORE          INT     NOT NULL);";
  rc = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
  sqlite3_close(db);
}
