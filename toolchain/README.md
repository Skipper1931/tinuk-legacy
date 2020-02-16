# How to build Tinuk

Tinuk's build system is basically the same one in the OSDev Meaty Skeleton Tutorial, but I stuck it all in Docker for protability.

## Dependecies
* Docker
* Git LFS

Docker is needed since all the build stuff runs in a docker container. Git LFS is needed for the tarball with the pre-compiled cross-compiler.

## Commands

You can check the scripts to see what they do, then pass them (only one tho) to docker run to run them in the container. You could set up the container's environment on your host machine but it's reccomended (obviously) to use docker.

*It's assumed that the source tree is located at /src/tinuk (You should probably put it somewhere else tbh)*

**Make the docker image**

`docker build /src/tinuk/toolchain -n tinuk-build-env`

**Build everything and run QEMU**

`docker run -it --rm -v /src/tinuk/:/tinuk tinuk-build-env ./qemu.sh`

**Delete all the object files, sysroot, .iso, etc**

`docker run -it --rm -v /src/tinuk/:/tinuk tinuk-build-env ./clean.sh`

**Build everything into an ISO**

`docker run -it --rm -v /src/tinuk/:/tinuk tinuk-build-env ./iso.sh`

## Debug with GDB

It's actually possible to use GDB to debug something running in QEMU. To do this, we open another shell into the container and run GDB from the shell. While it's technically possible to expose QEMU outside the container and run GDB on the host machine, it's better to run GDB directly in the container. You can name the container here whatever you want. You should probably stay in the GRUB menu in QEMU while you set up GDB, so you don't miss anything.


First we make the container

`docker run -it --rm -v /src/tinuk/:/tinuk --name tinuk-debug tinuk-build-env ./qemu.sh`

Then, we open a new terminal and open a bash shell on the container we made

`docker exec -it tinuk-debug /bin/bash`

These next commands are executed in the container bash shell we just made
```
cd /tinuk
gdb
```
These next commands are executed in GDB
```
symbol-file [path to binary (kernel/karyon.kernel or something else)]
target remote localhost:1234
break [wherever you want to break]
continue
```
QEMU will now break when you hit the function you broke at, and you can use the GDB shell to debug as usual.