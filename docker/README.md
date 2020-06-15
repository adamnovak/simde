# SIMDe Development Container

## WORK IN PROGRESS

This isn't fully functional yet.  Here is a list of builds which don't
work yet:

 - aarch64-clang-*
 - ppc64le-gcc-* — build works, [qemu is buggy](https://bugs.launchpad.net/qemu/+bug/1883784)
 - emscripten — works, but still using CMake

The basic idea is to set up a Debian system with lots of different
compilers and emulators for different architectures and configure
multiple builds in different directories.

Note that there are also several docker files in the test/
subdirectory.  These can be used to test other operating systems,
especially older compilers which aren't supported on Debian testing
anymore.

In addition to normal development, there is a `simde-check-all.sh`
script which can be used to attempt to compile SIMDe on all the
platforms supported by this container, and run the tests.  It will
take a rather long time to run.

I use Podman not Docker, but Podman is compatible with Docker so at
the very least the commands should be similar.  My biggest concern is
the z option on the volume argument, which I'm not sure Docker
supports.  If someone who uses Docker can test I'd be grateful.

I build with:

```sh
podman build -t 'simde-dev' -f Dockerfile ..
```

That last `..` should be the path to the SIMDe source directory, so if
you're running it from somewhere other than docker/ you may need to
change the path.

Run with:

```sh
podman run -v ..:/usr/local/src/simde:z -it --rm simde-dev /bin/bash
```

This will bind the parent directory (the root of the SIMDe checkout)
to /usr/local/src/simde; any changes to either will propogate to the
other, meaning you can continue using your normal development
environment.

When you run the second command you should be dropped into bash shell
in the /usr/local/src/simde-build directory inside of the container.
Inside of that directory are lots of different subdirectories which
are pre-configured to build SIMDe with different compilers, targeting
different architectures, etc.  To build, just `cd` into one of them,
then run `ninja`.  To run the tests, `ninja test`.

The `--rm` argument causes all data (except for /usr/local/src/simde,
since that is bound to the host directory) to be removed when you exit
the bash shell.

You can also just run `simde-dev.sh` (in this directory), but you
won't be able to modify the default options.
