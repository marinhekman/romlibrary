[![Build Status](https://travis-ci.org/maximilianvoss/romlibrary.svg?branch=master)](https://travis-ci.org/maximilianvoss/romlibrary)

# ROM Library

ROM Library is helps you to download ROMs from well-known webpages.   
Following ROM databases are supported:

* https://romsmania.cc/
* https://wowroms.com/
* https://roms-download.com/
* https://romsemulator.net/
* https://romhustler.org/

Please note: This software is using the mentioned sites to download ROMs. You are responsible to have valid licenses to
use the software. Rom Library does not hold, provide, sell or distribute licenses.

## Installing the latest version from source

### Fetching Dependencies

```bash
sudo apt-get update
sudo apt-get -y install libcurl4-openssl-dev libsqlite3-dev libcurl4-openssl-dev
```

### Compiling the latest code

```bash
git clone --recurse-submodules https://github.com/maximilianvoss/romlibrary.git
cd romlibrary
cmake -G "Unix Makefiles"
make
make test
sudo make install
```