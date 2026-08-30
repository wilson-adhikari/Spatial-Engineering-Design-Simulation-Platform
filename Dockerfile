FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
    cmake=3.29* ninja-build g++-12 clang-tidy cppcheck \
    nodejs npm git curl \
    && curl -fsSL https://deb.nodesource.com/setup_20.x | bash - \
    && apt-get install -y nodejs \
    && node --version && npm --version && cmake --version && g++ --version

WORKDIR /app
COPY . .
RUN scripts/bootstrap.sh

EXPOSE 5173 4173
CMD ["bash"]
