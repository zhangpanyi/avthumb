FROM alpine:3.10

RUN apk add --update --no-cache \
    bash \
    build-base \
    ca-certificates \
    cmake \
    freetype-dev \
    ffmpeg-dev \
    ffmpeg-libs \
    git \
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
    yaml-cpp-dev \
    unzip \
    zlib-dev

# COPY app /avthumb/app
# COPY proto /avthumb/proto
# COPY third_party /avthumb/third_party
# COPY .gitmodules /avthumb/.gitmodules
# COPY CMakeLists.txt /avthumb/CMakeLists.txt

# RUN rm -rf /avthumb

EXPOSE 17912
