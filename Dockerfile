FROM ubuntu:latest
RUN apt-get update && apt-get install -y wget software-properties-common
RUN apt-get install -y gcc g++ 
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt-get install -y gcc-12 g++-12 build-essential
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 100 --slave /usr/bin/g++ g++ /usr/bin/g++-12 --slave /usr/bin/gcov gcov /usr/bin/gcov-12

RUN echo gcc --version

RUN apt-get install -y ninja-build
RUN apt-get install -y openjdk-17-jdk 
RUN apt-get install -y git python3 python3-pip python3-virtualenv
RUN wget https://github.com/Kitware/CMake/releases/download/v3.23.2/cmake-3.23.2-linux-x86_64.sh \ 
    && mkdir -p /opt/cmake \
    && sh ./cmake-3.23.2-linux-x86_64.sh --skip-license --prefix=/opt/cmake \
    && rm cmake-3.23.2-linux-x86_64.sh \
    && update-alternatives --install /usr/bin/cmake cmake /opt/cmake/bin/cmake 60
RUN apt-get clean
