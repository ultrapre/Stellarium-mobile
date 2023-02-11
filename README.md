**Stellarium Mobile  v1.30.2**



**New feature:**

- [x] Online update comets (in Advance Panel)
- [x] Checkbox for telrad circle
- [x] Checkbox for toast layout
- [x] Checkbox for flip view
- [x] Select observing list include DSO ID, show filter for observing session
- [x] Add some UI panels
- [x] update DSO catalog v3.x



***how to use observing function***

Add multi lines of DSO-id in observingList.txt and copy it to sdcard. Select observing list *.txt file and apply filter, only set observing in catalog filter.



**Build me:**

Source of fork: https://www.stellarium-labs.com/stellarium-mobile/

Archive Version of v1.29.6: https://github.com/ultrapre/Stellarium-mobile/releases/tag/v1.29.6

This also can be compiled to Windows Version, see release. (add `LIBS += -lWinmm -LG:\Qt\5.15.2\mingw81_32\bin -lGLESv2 -lEGL` into .pro)

IOS build Kits: macOS 10.13.6 + XCode 10.1 + 5.12.3, please use original 1.29.6 code but not newest.

[fixing way here](https://github.com/ultrapre/stellarium_lite)

If build error, remove AndroidManifest.xml and change sdk version in project.
