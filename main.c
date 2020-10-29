#include <stdio.h>
#include <memory.h>
#include "duckdb.h"

static void
fatal(const char *msg) {
  fputs(msg, stderr);
  exit(2);
}

int
main(int argc, char* argv[]) {
  duckdb_database db;
  duckdb_connection con;

  if (duckdb_open(NULL, &db) == DuckDBError) {
    fatal("cannot open db");
  }
  if (duckdb_connect(db, &con) == DuckDBError) {
    fatal("cannot connect db");
  }
  // create a table
  if (duckdb_query(con, "CREATE TABLE integers(i INTEGER, j INTEGER);", NULL) == DuckDBError) {
    fatal("cannot create table");
  }
  // insert three rows into the table
  if (duckdb_query(con, "INSERT INTO integers VALUES (3, 4), (5, 6), (7, NULL);", NULL) == DuckDBError) {
    fatal("cannot insert record");
  }

  duckdb_result result;
  // query rows again
  if (duckdb_query(con, "SELECT * FROM integers", &result) == DuckDBError) {
    fatal("cannot query table");
  }
  for (size_t row_idx = 0; row_idx < result.row_count; row_idx++) {
    for (size_t col_idx = 0; col_idx < result.column_count; col_idx++) {
      int64_t v = duckdb_value_int64(&result, col_idx, row_idx);
      printf("%d ", v);
    }
    printf("\n");
  }
  duckdb_destroy_result(&result);
  duckdb_disconnect(&con);
  duckdb_close(&db);
  return 0;
}
