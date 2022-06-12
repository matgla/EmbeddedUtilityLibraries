FROM ubuntu:latest
RUN apt-get update && apt-get install -y wget software-properties-common
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt install -y gcc-12 g++-12
# RUN wget https://github.com/Kitware/CMake/releases/download/v3.23.2/cmake-3.23.2-linux-x86_64.sh \ 
#     && chmod +x cmake-3.23.2-linux-x86_64.sh \ 
#     && sh ./cmake-3.23.2-linux-x86_64.sh --skip-license
