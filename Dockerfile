FROM d0si/cmake-cpp-vortex-builder:alpine

RUN mkdir /vortex \
    && mkdir /vortex/build \
    && cd /vortex

ADD ./ /vortex/

WORKDIR /vortex

RUN cd /vortex/build \
    && cmake -DVORTEX_ENABLE_FEATURE_MONGO=ON \
        -DVORTEX_ENABLE_FEATURE_REDIS=ON \
        -DVORTEX_ENABLE_FEATURE_DUKTAPE=ON \
        -DVORTEX_ENABLE_FEATURE_CRYPTOPP=ON .. \
    && make -j8
