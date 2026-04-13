FROM --platform=linux/arm64 ubuntu:22.04
RUN apt-get update && apt-get install -y \
    gcc \
    g++ \
    make \
    valgrind \
    gdb \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /code
CMD ["/bin/bash"]
