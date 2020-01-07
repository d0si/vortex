FROM ubuntu:16.04

RUN apt-get update \
    && apt-get install -y build-essential \
    sudo \
    wget \
    git \
    python3 \
    python3-pip

RUN add-apt-repository ppa:mhier/libboost-latest \
    && apt-get update \
    && apt-get install libboost-latest

RUN cd /usr/local/src \
    && wget https://github.com/Kitware/CMake/releases/download/v3.16.2/cmake-3.16.2.tar.gz \
    && tar xvf cmake-3.16.2.tar.gz \
    && cd cmake-3.16.2.tar.gz \
    && ./bootstrap \
    && make \
    && make install \
    && cd .. \
    && rm -rf cmake*
