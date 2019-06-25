FROM alpine:3.10

RUN echo 'http://dl-cdn.alpinelinux.org/alpine/edge/testing' >> /etc/apk/repositories

RUN apk add --update --no-cache \
    bash \
    build-base \
    ca-certificates \
    cmake \
    ffmpeg-dev \
    ffmpeg-libs \
    freetype-dev \
    git \
    grpc-dev \
    lcms2-dev \
    libavc1394-dev \
    libffi-dev \
    # Wrapper for libjpeg-turbo
    libjpeg \
    # accelerated baseline JPEG compression and decompression library
    libjpeg-turbo-dev \
    # Portable Network Graphics library
    libpng-dev \
    # A software-based implementation of the codec specified in the emerging JPEG-2000 Part-1 standard (development files)
    jasper-dev \
    # Provides support for the Tag Image File Format or TIFF (development files)
    tiff-dev \
    # Libraries for working with WebP images (development files)
    libwebp-dev \
    libressl-dev \
    linux-headers \
    python \
    yaml-cpp-dev

# Copy project
COPY app /avthumb/app
COPY proto /avthumb/proto
COPY protocol /avthumb/protocol
COPY server.py /avthumb/server.py
COPY third_party /avthumb/third_party
COPY CMakeLists.txt /avthumb/CMakeLists.txt
RUN chmod +x /avthumb/server.py

# Build OpenCV
RUN cd /avthumb/third_party/opencv \
    && mkdir build && cd build \
    && cmake -D CMAKE_BUILD_TYPE=RELEASE -D BUILD_EXAMPLES=NO -D BUILD_ANDROID_EXAMPLES=NO -D INSTALL_PYTHON_EXAMPLES=NO -D BUILD_DOCS=NO .. \
    && make -j4 && make install \
    && rm -rf /avthumb/third_party/opencv

# Build project
RUN cd /avthumb \
    && mkdir build && cd build \
    && cmake .. && make -j4 \
    && rm -rf /avthumb/build

EXPOSE 17912

WORKDIR /avthumb/bin

VOLUME [ "/avthumb/config" ]

ENTRYPOINT [ "/avthumb/server.py" ]