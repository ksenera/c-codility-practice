FROM --platform=linux/arm64 ubuntu:22.04
RUN apt-get update && apt-get install -y gcc make valgrind && rm -rf /var/lib/apt/lists/*
WORKDIR /code
CMD ["/bin/bash"]
