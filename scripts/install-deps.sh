#!/usr/bin/env bash

if [[ $EUID -ne 0 ]]; then
	echo "This script must be run as root" 
	exit 1
fi

apt install -y verilator libsystemc-dev >/dev/null 2>&1
exit 0
cd /opt

# Build scv
curl -L "https://accellera.org/images/downloads/standards/systemc/scv-2.0.1.tar.gz" | tar zxf -
pushd scv-2.0.1
./configure --prefix=/usr --sysconfdir=/etc --enable-static
make
make install
popd