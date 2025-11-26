# FinLite

C++ HTTP server with SQLite backend for financial reporting

![](https://github.com/user-attachments/assets/0194bbc5-9951-458f-8f81-46752cc74d7a)

## Tech Stack

**Language:** C++ (C++11)

**Database:** SQLite3 — embedded database for transaction storage and aggregation queries

**HTTP Server:** Custom implementation using raw BSD sockets (POSIX) with Windows Winsock2 compatibility

**Frontend:** Server-side rendered HTML with embedded CSS — no JavaScript frameworks or external dependencies

## Architecture

```
http_client.cc     → Application entry point
    ↓
server.cc/hh       → Socket-based HTTP server (cross-platform)
    ↓
generator.cc/hh    → HTML dashboard generator
    ↓
lite.cc/hh         → SQLite database abstraction layer
    ↓
finmart.h          → Transaction data model
```

## Build

```bash
./buils.cmake.sh
```
