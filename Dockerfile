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
    yaml-cpp-dev

EXPOSE 17912
