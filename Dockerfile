FROM ubuntu:latest
ARG CMAKE_VERSION=3.26.1
ARG SONAR_SCANNER_VERSION=4.8.0.2856 

RUN apt-get update && apt-get install -y wget software-properties-common
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt-get install -y gcc-12 g++-12 build-essential
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 100 --slave /usr/bin/g++ g++ /usr/bin/g++-12 --slave /usr/bin/gcov gcov /usr/bin/gcov-12

RUN echo gcc --version

RUN apt-get install -y ninja-build
RUN apt-get install -y default-jdk 
RUN apt-get install -y git python3 python3-pip python3-virtualenv
RUN wget https://github.com/Kitware/CMake/releases/download/v$CMAKE_VERSION/cmake-$CMAKE_VERSION-linux-x86_64.sh \ 
  && mkdir -p /opt/cmake \
  && sh ./cmake-$CMAKE_VERSION-linux-x86_64.sh --skip-license --prefix=/opt/cmake \
  && rm cmake-$CMAKE_VERSION-linux-x86_64.sh \
  && update-alternatives --install /usr/bin/cmake cmake /opt/cmake/bin/cmake 60
RUN apt-get install unzip
RUN cd /opt \
  && wget https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-$SONAR_SCANNER_VERSION-linux.zip \
  && unzip sonar-scanner-cli-$SONAR_SCANNER_VERSION-linux.zip -d sonar_scanner \
  && rm -rf sonar-scanner-cli-$SOANR_SCANNER_VERSION-linux.zip
ENV PATH=$PATH:/opt/sonar_scanner/sonar-scanner-$SONAR_SCANNER_VERSION-linux/bin
RUN echo $PATH
RUN apt-get install -y clang-14 clang-tidy-14
RUN update-alternatives --install /usr/bin/clang clang-14 /usr/bin/clang-14 100 --slave /usr/bin/clang++ clang++14 /usr/bin/clang++-14 --slave /usr/bin/clang-tidy clang-tidy-14 /usr/bin/clang-tidy-14 --slave /usr/bin/run-clang-tidy run-clang-tidy-14 /usr/bin/run-clang-tidy-14 
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get install -y gcovr
RUN apt-get clean
