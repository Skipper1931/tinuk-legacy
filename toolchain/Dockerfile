# I used arch since it's lightweight and since I use arch btw.
# I'll change the version tag thingy as new updates come out; I just don't wanna break anything.
FROM archlinux:20200205

# Install packages
RUN pacman -Sy
RUN pacman -S --noconfirm tar binutils gcc make bison flex gmp mpc mpfr texinfo nasm grub xorriso qemu qemu-arch-extra mtools

# Set up cross-compiler (32 and 64 bit). cross-compiler.tar.gz should have these two pre-compiled and should be in the
# same folder as this Dockerfile. It's in the GitHub Repo so if you don't have it then check there. At some point
# i'll re-do the compiler stuff so the docker image pulls it from the GNU repo and compiles the latest verion but
# for now I'll go with the pre-compiled stuff (especially since it'll be quicker to make the image lol)
WORKDIR /opt
COPY ./cross-compiler.tar.gz .
RUN tar xvf cross-compiler.tar.gz
RUN rm cross-compiler.tar.gz

# Mount tinuk source dir. into the container
VOLUME /tinuk
WORKDIR /tinuk/toolchain

# Since we're in the toolchain dir the user can pass the different build scripts to docker run depending on what
# they want to do