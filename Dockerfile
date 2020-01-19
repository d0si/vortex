FROM zigabobnar/cmake-cpp-vortex-builder:alpine

RUN mkdir /vortex \
    && mkdir /vortex/build \
    && cd /vortex

ADD ./ /vortex/

WORKDIR /vortex
