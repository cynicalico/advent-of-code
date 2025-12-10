set windows-shell := ["pwsh.exe", "-NoLogo", "-Command"]

cog:
    cog -r CMakeLists.txt
    cog -r src/solution_map.cpp
    cog -r solutions/prototypes.hpp

config $preset:
    cmake --preset {{ preset }}

build $preset:
    cmake --build --preset {{ preset }}

clean $preset:
    cmake --build --preset {{ preset }} --target clean

[windows]
purge:
    rm -Force -Recurse .build

[linux]
purge:
    rm -rf .build
