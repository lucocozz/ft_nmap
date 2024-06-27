FROM debian

RUN apt-get update && apt-get install -y \
	libpcap-dev \
	meson \
	clang \
	ninja-build \
	make


WORKDIR /root

COPY . ./ft_nmap/

RUN make -C ft_nmap

ENTRYPOINT [ "tail", "-f", "/dev/null" ]