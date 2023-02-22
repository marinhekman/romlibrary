[![Build Status](https://travis-ci.org/maximilianvoss/romlibrary.svg?branch=master)](https://travis-ci.org/maximilianvoss/romlibrary)

# ROM Library

ROM Library is helps you to download ROMs from well-known webpages.   
Following ROM databases are available:

* https://wowroms.com/
* https://roms-download.com/
* https://romsemulator.net/
* https://romhustler.org/
* https://www.reroms.com/

Please note: This software is using the mentioned sites to download ROMs. You are responsible to have valid licenses to
use the software. Rom Library does not hold, provide, sell or distribute licenses.

## Installing the latest version from source

### Fetching Dependencies

```bash
sudo apt-get update
sudo apt-get -y install libcurl4-openssl-dev libsqlite3-dev libcurl4-openssl-dev
```

### Other project dependencies

```bash
(git clone https://github.com/maximilianvoss/csafestring.git && cd csafestring && cmake -G "Unix Makefiles" && make && sudo make install)
(git clone https://github.com/maximilianvoss/casserts.git && cd casserts && cmake -G "Unix Makefiles" && make && sudo make install)
(git clone https://github.com/maximilianvoss/clogger.git && cd clogger && cmake -G "Unix Makefiles" && make && sudo make install)
(git clone https://github.com/maximilianvoss/chttp.git && cd chttp && cmake -G "Unix Makefiles" && make && sudo make install)
(git clone https://github.com/maximilianvoss/acll.git && cd acll && cmake -G "Unix Makefiles" && make && sudo make install)
(git clone https://github.com/lexbor/lexbor.git && cd lexbor && cmake -G "Unix Makefiles" && make && sudo make install)
```

### Compiling the latest code

```bash
git clone https://github.com/maximilianvoss/romlibrary.git
cd romlibrary
cmake -G "Unix Makefiles"
make
make test
sudo make install
```