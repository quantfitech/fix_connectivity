FROM ubuntu:22.04

# Install build tools and CMake
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gcc \
    g++ \
    git \
    python3 \
    python3-pip \
    python3-venv \
    && apt-get clean

RUN apt-get update && apt-get install -y \
    libssl-dev \
    libspdlog-dev \
    libhiredis-dev\
    libgtest-dev \ 
    libbenchmark-dev \
    nlohmann-json3-dev


RUN apt-get update && apt-get install -y ca-certificates
# Update the CA certificates in the container
RUN update-ca-certificates

RUN git clone https://github.com/redis/hiredis.git
WORKDIR /hiredis/build
RUN cmake ..
RUN cmake --build .

RUN ls /hiredis/build

WORKDIR /fix_connectivity/
COPY . . 

RUN ls /fix_connectivity/

RUN cmake -B build_docker && cmake --build build_docker

# Set the entry point for the container (modify as needed)
CMD ["/fix_connectivity/build_docker/coinbase_market_data/coinbase_md"]
