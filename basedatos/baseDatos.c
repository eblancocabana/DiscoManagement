#include <stdio.h>
#include <sqlite/sqlite3.h>

int db_existe(char *nombrearch) {
    FILE *arch = fopen(nombrearch,"r");
    if (arch) {
        fclose(arch);
        return 1;
    }
    return 0;
}


int main(int argc, char* argv[])
{
    sqlite3 *db;
    int db_exists = db_existe("basedatos.db");
    int rc = sqlite3_open("basedatos.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    printf("La base de datos se ha creado o abierto con éxito.\n");
    if (!db_exists) {
        // Implementacion de importacion de datos CSV
    }
    sqlite3_close(db);
    return 0;
}