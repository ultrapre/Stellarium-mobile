########### install files ###############

INSTALL(FILES stellarium.ico ssystem.ini base_locations.bin.gz DejaVuSans.ttf default_config.ini DejaVuSansMono.ttf iso639-1.utf8 iso3166-1-alpha-2.utf8 countryCodes.dat DESTINATION share/${PACKAGE}/data)

IF (BUILD_FOR_MAEMO)
  INSTALL(FILES maemo/stellarium.desktop DESTINATION /usr/share/applications/hildon)
  INSTALL(FILES maemo/stellarium.png DESTINATION /usr/share/icons/hicolor/48x48/apps)
ENDIF()

IF(UNIX AND NOT APPLE)
  INSTALL(FILES stellarium.desktop DESTINATION share/applications)
  INSTALL(FILES stellarium.xpm DESTINATION share/pixmaps)
  INSTALL(FILES icons/16x16/stellarium.png DESTINATION share/icons/hicolor/16x16/apps)
  INSTALL(FILES icons/32x32/stellarium.png DESTINATION share/icons/hicolor/32x32/apps)
  INSTALL(FILES icons/48x48/stellarium.png DESTINATION share/icons/hicolor/48x48/apps)
  INSTALL(FILES icons/64x64/stellarium.png DESTINATION share/icons/hicolor/64x64/apps)
  INSTALL(FILES icons/128x128/stellarium.png DESTINATION share/icons/hicolor/128x128/apps)
  INSTALL(FILES icons/256x256/stellarium.png DESTINATION share/icons/hicolor/256x256/apps)
  INSTALL(FILES icons/512x512/stellarium.png DESTINATION share/icons/hicolor/512x512/apps)
ENDIF()

IF(MACOSX)
  INSTALL(FILES Icon.icns DESTINATION share )
  INSTALL(FILES Info.plist PkgInfo DESTINATION . )
ENDIF(MACOSX)

