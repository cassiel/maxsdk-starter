`-*- word-wrap: t; -*-`

# Introduction

This is a project containing the source for some example C externals for MaxMSP. The project is laid out so that Cycling '74's Max 6 SDK can be fetched as a Git submodule (as opposed to starting with the SDK and then creating new external source trees inside it).

Feel free to fork this project and add, copy or modify the examples (read the _Setup_ section below). Alternatively, copy this project to start a new external (see the section _From Scratch_).

So far this is tested with Xcode 4. Windows requires a bit of work (mainly because the symbolic links in the source tree won't work); that's at the top of the to-do list.

# Setup

- If you have an old (3.x or older) Xcode installation in `/Developer`,
  remove it. (The MaxSDK erroneously refers to this directory, which
  messes up builds.)

- Having checked out this project, type the following into a Terminal at
  the top level:

        git submodule update --init

  For some reason, GitHub checkouts don't check out submodules; this
  will populate the `max6-sdk` directory.

# From Scratch

- Clone the Max SDK into the top level of a new project:

        git submodule add git://github.com/Cycling74/max6-sdk.git max6-sdk

- Link the support directory:

        $ ln -s max6-sdk/c74support ./

- Create an `examples` folder and create symbolic links for it:

        $ mkdir examples
        $ cd examples
        $ ln -s ../max6-sdk/examples/maxmspsdk.xcconfig ./
        $ ln -s ../max6-sdk/examples/Info.plist ./

  (The name `examples` isn't obligatory - feel free to use something
  else for "serious" development - but the source tree for actual
  externals needs to be two levels below the main project, whether it's
  something like `examples/basics/myobj` or
  `externals-src/main-externals/myobj`.) Should you care, these relative
  paths are in `maxmspsdk.xcconfig` in the SDK directory, which is
  itself located via a relative path in each Xcode project file. (TODO:
  document for Windows.)

# Building

In Xcode, builds are placed in various intermediate directories called `build`, and finally in the directory `sdk-build` in the top level of this project. (All of these are in `.gitignore`.)
