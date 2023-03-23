#include <stdio.h>
#include <sqlite/sqlite3.h>

int main(int argc, char* argv[])
{
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    printf("La base de datos se ha creado o abierto con éxito.\n");
    sqlite3_close(db);
    return 0;
}