# DiscoManagement

Client-server nightclub and event management project built with C/C++,
Winsock sockets, and SQLite.

The system models a small event-management workflow for "Sound Strategy
Partners": user login, ticket purchase, local reservations, event listings,
DJ/RRPP data, and administrator operations. The client communicates with the
server over TCP on `127.0.0.1:6000`.

## What It Contains

- Console client for user login, ticket purchase, and reservations.
- TCP server that dispatches client requests to database operations.
- SQLite-backed persistence layer.
- CSV seed data for users, DJs, events, party days, and RRPP records.
- Domain models for tickets, events, DJs, RRPP, and local reservations.

## Project Structure

```text
SOCKETS/
+-- Cliente/              # Console client and client-side domain classes
`-- Servidor/
    +-- administrador/    # Administrator menu flow
    +-- basedatos/        # SQLite integration and database operations
    +-- clases/           # Server-side domain classes
    +-- estructuras/      # C structs and helpers
    `-- ficheros/         # CSV seed data
```

## Build Notes

This project targets Windows because it uses Winsock and links against
`ws2_32`.

Build the server from `SOCKETS/Servidor`:

```bash
gcc -c basedatos/baseDatos.c -o bd.o
gcc -c basedatos/sqlite/sqlite3.c -o sqlite.o
g++ -c administrador/inicio_servidor.cpp -o inicio.o
g++ -c main.cpp -o main.o
g++ main.o inicio.o sqlite.o bd.o -o servidor.exe -lWs2_32
```

Build the client from `SOCKETS/Cliente`:

```bash
g++ main.cpp comprar_entradas.cpp inicio.cpp reservar_local.cpp seleccion_entradas.cpp clases/entrada.cpp clases/reservalocal.cpp -o cliente.exe -lWs2_32
```

Run the server first, then start the client.
