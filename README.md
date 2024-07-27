# Fairy LED strip

Makes a bunch of fairies in the strip that bounce around. Based on double-pendulum approach to get a nicely chaotic system.

## Setup
```
git submodule init
mkdir build
cd build
cmake ../
cmake --build ./ --config Debug --target upload
```