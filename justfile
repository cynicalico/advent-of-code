set windows-shell := ["pwsh.exe", "-NoLogo", "-Command"]

cog:
    cog -r CMakeLists.txt
    cog -r solutions/prototypes.hpp
    cog -r src/solution_map.cpp

config preset: cog
    cmake --preset {{ preset }}

[windows]
build preset cores="4":
    cmake --build --preset {{ preset }} --parallel {{ cores }}

[linux]
build preset cores="4":
    cmake --build --preset {{ preset }} -j {{ cores }}

[windows]
reset-cache:
    rm ./.build/CMakeCache.txt
    rm -Force -Recurse ./.build/CMakeFiles

[linux]
reset-cache:
    rm ./.build/CMakeCache.txt
    rm -rf ./.build/CMakeFiles

clean:
    cmake --build ./.build/ --target clean

[windows]
purge:
    rm -Force -Recurse .build
    rm -Force -Recurse bin

[linux]
purge:
    rm -rf .build
    rm -rf bin
