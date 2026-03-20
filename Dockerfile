FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    pkg-config \
    protobuf-compiler \
    libprotobuf-dev \
    qt6-base-dev \
    qt6-httpserver-dev \
    qt6-websockets-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF \
    && cmake --build build

CMD ["sqlite3 capops.db < scripts/setup.sql"]
CMD ["./build/capops"]