# How to build Tinuk

Tinuk's build system is basically the same one in the OSDev Meaty Skeleton Tutorial, but I stuck it all in Docker for protability.

## Dependecies:
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
