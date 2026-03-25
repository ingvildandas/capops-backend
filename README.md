# CapOps Backend API
A C++17 / Qt6 service that ingests protobuf-encoded flight data from Redis, groups and stores risk event data, and exposes REST + WebSocket interfaces for frontend consumers.

> Important: CapOps API must be connected to a Redis server with an active publisher. The publisher component is CapOps Processor, maintained in its own repository.
> 
> Without CapOps Processor running and publishing to Redis, CapOps API will not receive or process any flight data.

## Table of Contents
1. Architecture Overview
2. Prerequisites
3. Local Development
   1. Clone
   2. Configure and Build
   3. Run
   4. Run Tests
4. Environment Variables
5. Running from DockerHub
6. Redis Dependency

## Architecture Overview
CapOps API provides:
- REST HTTP server (Qt HttpServer)
- WebSocket server (Qt WebSockets)
- SQLite persistent storage
- Redis subscriber (redis-plus-plus)
- Protobuf message ingestion

Publish–subscribe communication is strictly inbound: CapOps API subscribes to Redis channels—it does not publish.
All real-time flight data originates from CapOps Processor, which must be deployed separately.

## Prerequisites
Toolchain (must be preinstalled and available to CMake):
- C++17 capable compiler (GCC ≥ 9, Clang ≥ 10, or MSVC equivalent)
- CMake ≥ 3.5
- Qt6:
    - Qt6Core
    - Qt6Network
    - Qt6WebSockets
    - Qt6HttpServer
- Protobuf (compiler + headers)
- Ninja (recommended)
- Redis server accessible on the network
- Git

The CMake build automatically fetches:
- Catch2 (unit test framework)
- SQLite3 (CMake wrapper project)
- hiredis
- redis-plus-plus

## Local Development

### Clone
```bash
git clone https://github.com/<your-org>/capops-api.git
cd capops-api
```

### Configure and build
Full build:
```bash
cmake -S . -B build
cmake --build build
```

For a slimmer build not including testing:
```bash
cmake --build build -DBUILD_TESTING=OFF
```

### Run
After building, run the service from the build directory:
```bash
./build/capops
```
CapOps API requires connectivity to a functional Redis instance.
If Redis is not reachable, the service will exit. If Redis is reachable, but CapOps Processor is not actively publishing, the service will start but no flight data will ever arrive.

### Run Tests
After building, you can run the tests from the build directory:
```bash
./build/tests
```

## Environment Variables 
| Variable | Description | Default Value |
| ----------- | ----------- | ----------- |
| HTTP_PORT | HTTP REST server port | 8080 |
| WEBSOCKET_PORT | WebSocket server port | 8081 |
| DATABASE_FILE_PATH | Path to SQLite DB file | ./capops.db |
| REDIS_HOST | Redis host to subscribe to | localhost |
| REDIS_PORT | Redis port | 6379 |
| PROTOBUF_CONTRACT_VERSION | Expected protobuf schema version | 1 |
| REST_JSON_CONTRACT_VERSION | REST/JSON schema version | 1 |

## Running from DockerHub
A prebuilt image is pushed automatically on each commit to main.

Pull the image:
```bash
docker pull jacobg431/capops-api:latest
```

Run the container:
```bash
docker run -d \
    --name capops-api \
    --network capops-network \
    -p 8080:8080 \
    -p 8081:8081 \
    -e DATABASE_FILE_PATH=./capops.db \
    -e HTTP_PORT=8080 \
    -e WEBSOCKET_PORT=8081 \
    -e REDIS_HOST=redis-server \
    -e REDIS_PORT=6379 \
    -e PROTOBUF_CONTRACT_VERSION=2 \
    -e REST_JSON_CONTRACT_VERSION=4 \
    jacobg431/capops-api:latest
```

The above may fail if you haven't already created the network:
```bash
docker network create capops-network 
```

## Redis Dependency
CapOps API cannot operate standalone.

Requirements:
- A reachable Redis server
- A running deployment of CapOps Processor
- CapOps Processor must be actively publishing to the channels - consumed by CapOps API

If the API is running without a live Redis connection:
- The API will exit.

If the API is running with a live Redis connection but CapOps Processor is offline:
- No flight data is processed
- No risk events are generated
- REST/WebSocket endpoints return empty or stale data
