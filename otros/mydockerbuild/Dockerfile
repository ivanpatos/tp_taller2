FROM ubuntu:14.04

WORKDIR /opt/

RUN echo "Instalando librerias" \
	&& apt-get update \
	&& apt-get install -y \
    libgflags-dev \
    libsnappy-dev \
    zlib1g-dev \
	libbz2-dev \
	cmake \
	google-mock \
	lcov \
	git \
	g++

RUN echo "Descargando RocksDB" \
	&& git clone https://github.com/facebook/rocksdb.git \
	&& echo "fin descarga" \
	&& cd rocksdb \
	&& echo "creando libreria estatica (tarda aprox 5 min)" && make static_lib \
	&& echo "instalando" && make install

RUN echo "Instalando gmock" \
	&& cd /usr/src/gmock \
	&& sudo cmake . \
	&& sudo make \
	&& sudo cp -a *.a /usr/lib \
	&& cd /usr/src/gmock/gtest \
	&& sudo cp -a *.a /usr/lib

RUN echo "Descargando codigo del servidor" \
	&& git clone https://github.com/ivanpatos/tp_taller2.git \
	&& echo "fin descarga" \
	&& mkdir build_tptaller2 \
	&& cd build_tptaller2 \
	&& cmake /opt/tp_taller2/src/UdriveServer/main \
	&& make

COPY conf.conf "/opt/build_tptaller2/"

##################### INSTALLATION END #####################

WORKDIR /opt/build_tptaller2/

RUN cat conf.conf

# Expose the default port
EXPOSE 8080

# Set default container command
CMD ["/opt/build_tptaller2/udrive_server"]

RUN echo "server up and running in port 8080"