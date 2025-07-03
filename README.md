SDL3 Port for the Nintendo DS
Currently threads are broken witch breaks evrything
build using blocksds
``` bash
cmake -B build -S. --install-prefix /opt/wonderful/thirdparty/blocksds/external/SDL3 -DCMAKE_TOOLCHAIN_FILE=/opt/wonderful/thirdparty/blocksds/core/cmake/BlocksDS.cmake --fresh
cmake --build build && cmake --install build
```

---

Simple DirectMedia Layer (SDL for short) is a cross-platform library
designed to make it easy to write multi-media software, such as games
and emulators.

You can find the latest release and additional information at:
https://www.libsdl.org/

Installation instructions and a quick introduction is available in
[INSTALL.md](INSTALL.md)

This library is distributed under the terms of the zlib license,
available in [LICENSE.txt](LICENSE.txt).

Enjoy!

Sam Lantinga (slouken@libsdl.org)
