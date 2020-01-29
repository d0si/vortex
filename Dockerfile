FROM d0si/cmake-cpp-vortex-builder:alpine

RUN mkdir /vortex \
    && mkdir /vortex/build \
    && cd /vortex

ADD ./ /vortex/

WORKDIR /vortex

RUN cd /vortex/build \
    && cmake .. \
    && make -j8
