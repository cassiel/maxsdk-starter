# SETUP

- Get rid of old Xcode installations in `/Developer`.

- Clone the Max SDK into the top level of this project:

        git submodule add git://github.com/Cycling74/max6-sdk.git max6-sdk

# NOTES

The example projects in the SDK have a few directory-relative references (in the case of Xcode, these are relative to the directory containing the `.xcodeproj` bundle, not the project text file in the bundle itself):

- `../../maxmspsdk.xcconfig`

From `maxmspsdk.xcconfig` itself:

        C74SUPPORT = $(SRCROOT)/../../../c74support
        DSTROOT = $(SRCROOT)/../../../sdk-build

So, add some symlinks:

        $ (cd examples; ln -s ../max6-sdk/examples/maxmspsdk.xcconfig ./)
        $ ln -s max6-sdk/c74support ./
