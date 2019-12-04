#!/usr/bin/env bash

if [[ $EUID -ne 0 ]]; then
	echo "This script must be run as root" 
	exit 1
fi

apt install -y build-essential git cmake verilator libsystemc-dev curl libgtest-dev >/dev/null 2>&1
exit 0
cd /opt

# Build UVM for SystemC
curl -L "http://accellera.org/images/downloads/standards/systemc/uvm-systemc-1.0-beta1.tar.gz" | tar zxf -
pushd uvm-systemc-1.0-beta1
config/bootstrap
mkdir -p objdir
cd objdir
../configure --prefix=/usr --with-systemc=/usr --with-arch-suffix="" --with-layout=unix
make
make install
popd

# Build scv
curl -L "https://accellera.org/images/downloads/standards/systemc/scv-2.0.1.tar.gz" | tar zxf -
pushd scv-2.0.1
./configure --prefix=/usr --sysconfdir=/etc --with-systemc=/usr --enable-static
make
make install
popd