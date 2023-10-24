# A C++ SFML based space fighting/whatever game!
This is a project I made for my c++ course, it's supposed to have a Starfield-like ship editor (in 2D not 3D, so much simpler), and gameplay will consist of fighting enemies, possibly foraging materials and other goals. The goal is also to have it working on linux and windows.

How to build:
- quick setup a cmake project in vs code via extenson
- use the supplied CMakeLists or copy it over the generated one blocks the configuration

In case of Linux dependencies might need to be installed first. Here's a rough command to install them and probably some more on Fedora distro, probably just the devel libs are needed:
```
sudo dnf install libglvnd libglvnd-core-devel libglvnd-devel libglvnd-egl libglvnd-gles openal-soft-devel openal-soft-examples openal-soft-qt openal-soft flac flac-devel flac-libs vorbis-tools
```
In windows I used chocolatey:
```
choco install git, make, cmake
```
I installed the mingw manually from the link on SFML website but this should work too:
```
choco install mingw--version 13.1.0 --force
```
Have fun!
