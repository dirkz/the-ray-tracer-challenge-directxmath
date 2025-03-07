# The Ray Tracer Challenge with C++ and DirectXMath

Based on [this book](http://raytracerchallenge.com/).

## Dependencies

This project uses git submodules for dependencies (google test).

```
git clone --recurse-submodules <git-ssh-url>
```

If you checked out without taking submodules into account and want to correct this, or just want
to bring versions to the up-stream state (e.g. after having changed branches):

```
git submodule update --init --recursive
```

## Scope

Until about chapter 15, so triangles as primitive are implemented.
But no OBJ parser, no smooth triangles (rest of chapter 15),
and no CSG (chapter 16). Also no bounding-box optimizations.

I didn't bother to write unit tests
to cover the basics (which are handled by DirectXMath anyways),
and didn't unit test things that can be
easily verified visually.

There is a parallel renderer using close to all available cores in the system, and a Win32 window callback
implementation for this renderer that puts pixels on the screen as they are traced, so you can
visually trace the progress.
