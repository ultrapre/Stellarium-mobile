SET(glues_lib_SRCS
	core/external/glues_stel/source/glues_error.c
	core/external/glues_stel/source/glues_error.h
	core/external/glues_stel/source/glues.h
	core/external/glues_stel/source/libtess/dict.h
	core/external/glues_stel/source/libtess/dict.c
	core/external/glues_stel/source/libtess/dict-list.h
	core/external/glues_stel/source/libtess/geom.c
	core/external/glues_stel/source/libtess/geom.h
	core/external/glues_stel/source/libtess/memalloc.c
	core/external/glues_stel/source/libtess/memalloc.h
	core/external/glues_stel/source/libtess/mesh.c
	core/external/glues_stel/source/libtess/mesh.h
	core/external/glues_stel/source/libtess/normal.c
	core/external/glues_stel/source/libtess/normal.h
	core/external/glues_stel/source/libtess/priorityq.c
	core/external/glues_stel/source/libtess/priorityq.h
	core/external/glues_stel/source/libtess/priorityq-heap.h
	core/external/glues_stel/source/libtess/priorityq-heap.i
	core/external/glues_stel/source/libtess/priorityq-sort.h
	core/external/glues_stel/source/libtess/render.c
	core/external/glues_stel/source/libtess/render.h
	core/external/glues_stel/source/libtess/sweep.c
	core/external/glues_stel/source/libtess/sweep.h
	core/external/glues_stel/source/libtess/tess.c
	core/external/glues_stel/source/libtess/tess.h
	core/external/glues_stel/source/libtess/tessmono.c
	core/external/glues_stel/source/libtess/tessmono.h
	)

SET(stellarium_lib_SRCS
	core/StelAudioMgr.hpp
	core/StelAudioMgr.cpp
	core/StelVideoMgr.hpp
	core/StelVideoMgr.cpp
	core/StelGeodesicGrid.cpp
	core/StelGeodesicGrid.hpp
	core/StelMovementMgr.cpp
	core/StelMovementMgr.hpp
	core/StelObserver.cpp
	core/StelObserver.hpp
	core/StelLocation.hpp
	core/StelLocation.cpp
	core/StelLocationMgr.hpp
	core/StelLocationMgr.cpp
	core/StelProjector.cpp
	core/StelProjector.hpp
	core/StelProjectorClasses.cpp
	core/StelProjectorClasses.hpp
	core/StelProjectorType.hpp
	core/StelSkyDrawer.cpp
	core/StelSkyDrawer.hpp
	core/StelPainter.hpp
	core/StelPainter.cpp
	core/MultiLevelJsonBase.hpp
	core/MultiLevelJsonBase.cpp
	core/StelSkyImageTile.hpp
	core/StelSkyImageTile.cpp
	core/StelSkyPolygon.hpp
	core/StelSkyPolygon.cpp
	core/SphericMirrorCalculator.cpp
	core/SphericMirrorCalculator.hpp
	core/StelApp.cpp
	core/StelApp.hpp
	core/StelCore.cpp
	core/StelCore.hpp
	core/StelFileMgr.cpp
	core/StelFileMgr.hpp
	core/StelLocaleMgr.cpp
	core/StelLocaleMgr.hpp
	core/StelModule.cpp
	core/StelModule.hpp
	core/StelModuleMgr.cpp
	core/StelModuleMgr.hpp
	core/StelObject.cpp
	core/StelObject.hpp
	core/StelObjectMgr.cpp
	core/StelObjectMgr.hpp
	core/StelObjectModule.cpp
	core/StelObjectModule.hpp
	core/StelObjectType.hpp
	core/StelPluginInterface.hpp
	core/StelSkyCultureMgr.cpp
	core/StelSkyCultureMgr.hpp
	core/StelTextureMgr.cpp
	core/StelTextureMgr.hpp
	core/StelTexture.cpp
	core/StelTexture.hpp
	core/StelTextureTypes.hpp
	core/StelToneReproducer.cpp
	core/StelToneReproducer.hpp
	core/StelSkyLayerMgr.cpp
	core/StelSkyLayerMgr.hpp
	core/StelSkyLayer.hpp
	core/StelSkyLayer.cpp
	core/StelFader.hpp
	core/StelSphereGeometry.cpp
	core/StelSphereGeometry.hpp
	core/OctahedronPolygon.cpp
	core/OctahedronPolygon.hpp
	core/StelIniParser.cpp
	core/StelIniParser.hpp
	core/StelUtils.cpp
	core/StelUtils.hpp
	core/StelTranslator.cpp
	core/StelTranslator.hpp
	core/VecMath.hpp
	core/StelJsonParser.hpp
	core/StelJsonParser.cpp
	core/SimbadSearcher.hpp
	core/SimbadSearcher.cpp
	core/StelSphericalIndex.hpp
	core/StelSphericalIndex.cpp
	core/StelVertexArray.hpp
	core/StelVertexArray.cpp
	core/StelGuiBase.hpp
	core/StelGuiBase.cpp
	core/StelViewportEffect.hpp
	core/StelViewportEffect.cpp
	core/TrailGroup.hpp
	core/TrailGroup.cpp
	core/RefractionExtinction.hpp
	core/RefractionExtinction.cpp
	core/StelActionMgr.hpp
	core/StelActionMgr.cpp
	core/StelProgressController.hpp

	${gl_lib_SRCS}

	${glues_lib_SRCS}

	core/planetsephems/calc_interpolated_elements.c
	core/planetsephems/calc_interpolated_elements.h
	core/planetsephems/elliptic_to_rectangular.c
	core/planetsephems/elliptic_to_rectangular.h
	core/planetsephems/elp82b.c
	core/planetsephems/elp82b.h
	core/planetsephems/gust86.c
	core/planetsephems/gust86.h
	core/planetsephems/l1.c
	core/planetsephems/l1.h
	core/planetsephems/marssat.c
	core/planetsephems/marssat.h
	core/planetsephems/pluto.c
	core/planetsephems/pluto.h
	core/planetsephems/sideral_time.c
	core/planetsephems/sideral_time.h
	core/planetsephems/stellplanet.c
	core/planetsephems/stellplanet.h
	core/planetsephems/tass17.c
	core/planetsephems/tass17.h
	core/planetsephems/vsop87.c
	core/planetsephems/vsop87.h

	core/modules/Atmosphere.cpp
	core/modules/Atmosphere.hpp
	core/modules/Constellation.cpp
	core/modules/Constellation.hpp
	core/modules/ConstellationMgr.cpp
	core/modules/ConstellationMgr.hpp
	core/modules/GridLinesMgr.cpp
	core/modules/GridLinesMgr.hpp
	core/modules/LabelMgr.hpp
	core/modules/LabelMgr.cpp
	core/modules/Landscape.cpp
	core/modules/Landscape.hpp
	core/modules/LandscapeMgr.cpp
	core/modules/LandscapeMgr.hpp
	core/modules/Meteor.cpp
	core/modules/Meteor.hpp
	core/modules/MeteorMgr.cpp
	core/modules/MeteorMgr.hpp
	core/modules/MilkyWay.cpp
	core/modules/MilkyWay.hpp
	core/modules/Nebula.cpp
	core/modules/Nebula.hpp
	core/modules/NebulaMgr.cpp
	core/modules/NebulaMgr.hpp
	core/modules/Orbit.cpp
	core/modules/Orbit.hpp
	core/modules/Planet.cpp
	core/modules/Planet.hpp
	core/modules/MinorPlanet.cpp
	core/modules/MinorPlanet.hpp
	core/modules/Comet.cpp
	core/modules/Comet.hpp
	core/modules/Skybright.cpp
	core/modules/Skybright.hpp
	core/modules/Skylight.cpp
	core/modules/Skylight.hpp
	core/modules/SolarSystem.cpp
	core/modules/SolarSystem.hpp
	core/modules/Solve.hpp
	core/modules/Star.cpp
	core/modules/Star.hpp
	core/modules/StarMgr.cpp
	core/modules/StarMgr.hpp
	core/modules/StarWrapper.cpp
	core/modules/StarWrapper.hpp
	core/modules/ZoneArray.cpp
	core/modules/ZoneArray.hpp
	core/modules/ZoneData.hpp
	StelMainView.hpp
	StelMainView.cpp
	StelLogger.hpp
	StelLogger.cpp
	CLIProcessor.hpp
	CLIProcessor.cpp
	translations.h
)

# On windows, QZipReader is already included in the lib
IF(!WIN32)
	SET(stellarium_lib_SRCS ${stellarium_lib_SRCS}
		core/external/qtcompress/qzip.cpp
		core/external/qtcompress/qzipreader.h
		core/external/qtcompress/qzipwriter.h
	)
ENDIF()

IF(ENABLE_SCRIPTING)
	SET(stellarium_lib_SRCS ${stellarium_lib_SRCS}
		scripting/StelScriptMgr.cpp
		scripting/StratoscriptPreprocessor.cpp
		scripting/StelScriptMgr.hpp
		scripting/ScreenImageMgr.hpp
		scripting/ScreenImageMgr.cpp
		scripting/StelMainScriptAPI.cpp
		scripting/StelMainScriptAPI.hpp
		scripting/StelMainScriptAPIProxy.cpp
		scripting/StelMainScriptAPIProxy.hpp
	)
ENDIF()

SET(stellarium_exe_SRCS main.cpp)

################# compiles resources files ############
SET(stellarium_RES ${CMAKE_SOURCE_DIR}/data/mainRes.qrc)
QT5_ADD_RESOURCES(stellarium_RES_CXX ${stellarium_RES})


#############################################################################################
############################# Standard GUI plugin compilation ###############################
#############################################################################################
IF (GUI_MODE STREQUAL "Standard")
	SET(stellarium_gui_SRCS
		gui/StelGui.hpp
		gui/StelGui.cpp
		gui/SkyGui.hpp
		gui/SkyGui.cpp
		gui/StelStyle.hpp
		gui/StelGuiItems.hpp
		gui/StelGuiItems.cpp
		gui/HelpDialog.hpp
		gui/HelpDialog.cpp
		gui/ShortcutLineEdit.hpp
		gui/ShortcutLineEdit.cpp
		gui/ShortcutsDialog.hpp
		gui/ShortcutsDialog.cpp
		gui/Dialog.hpp
		gui/Dialog.cpp
		gui/MapLabel.hpp
		gui/MapLabel.cpp
		gui/AngleSpinBox.hpp
		gui/AngleSpinBox.cpp
		gui/LocationDialog.hpp
		gui/LocationDialog.cpp
		gui/DateTimeDialog.hpp
		gui/DateTimeDialog.cpp
		gui/ViewDialog.hpp
		gui/ViewDialog.cpp
		gui/SearchDialog.hpp
		gui/SearchDialog.cpp
		gui/ConfigurationDialog.hpp
		gui/ConfigurationDialog.cpp
		gui/AddRemoveLandscapesDialog.hpp
		gui/AddRemoveLandscapesDialog.cpp
		gui/AtmosphereDialog.hpp
		gui/AtmosphereDialog.cpp
		gui/CustomDeltaTEquationDialog.hpp
		gui/CustomDeltaTEquationDialog.cpp
		gui/StelDialog.hpp
		gui/StelDialog.cpp)

	################# compiles .ui files ############
	SET(stellarium_UIS
	gui/locationDialogGui.ui
	gui/helpDialogGui.ui
	gui/shortcutsDialog.ui
	gui/dateTimeDialogGui.ui
	gui/viewDialog.ui
	gui/searchDialogGui.ui
	gui/configurationDialog.ui
	gui/AtmosphereDialog.ui
	gui/CustomDeltaTEquationDialog.ui
	gui/addRemoveLandscapesDialog.ui)

        IF(ENABLE_SCRIPTING)
            IF(ENABLE_SCRIPT_CONSOLE)
		SET(stellarium_gui_SRCS ${stellarium_gui_SRCS}
			gui/ScriptConsole.hpp
			gui/ScriptConsole.cpp
			gui/StelScriptSyntaxHighlighter.hpp
			gui/StelScriptSyntaxHighlighter.cpp)
		SET(stellarium_UIS ${stellarium_UIS}
			gui/scriptConsole.ui)
            ENDIF(ENABLE_SCRIPT_CONSOLE)
        ENDIF(ENABLE_SCRIPTING)

	QT5_WRAP_UI(stellarium_UIS_H ${stellarium_UIS})

	# compiles resources files
	SET(stellarium_gui_RES ${CMAKE_SOURCE_DIR}/data/gui/guiRes.qrc)
	QT5_ADD_RESOURCES(stellarium_gui_RES_CXX ${stellarium_gui_RES})

	SET(extLinkerOption ${QT_QTSCRIPT_LIBRARY} ${OPENGL_LIBRARIES})

	# Compile the static library
	ADD_LIBRARY(StelGuiLib STATIC ${stellarium_gui_SRCS} ${stellarium_UIS_H} ${stellarium_gui_RES_CXX})
	TARGET_LINK_LIBRARIES(StelGuiLib ${StelMain} ${extLinkerOption})
	QT5_USE_MODULES(StelGuiLib Core Gui Widgets Network OpenGL Script Declarative)
	SET_TARGET_PROPERTIES(StelGuiLib PROPERTIES COMPILE_FLAGS "-DQT_STATICPLUGIN")
	SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} ${CMAKE_BINARY_DIR}/src/${CMAKE_CFG_INTDIR}/libStelGuiLib.a)
	ADD_DEPENDENCIES(AllStaticPlugins StelGuiLib)
ENDIF()

#############################################################################################
################################ No GUI plugin compilation ##################################
#############################################################################################
IF (GUI_MODE STREQUAL "None")
	SET(stellarium_nogui_SRCS
		noGui/StelNoGui.hpp
		noGui/StelNoGui.cpp)
	ADD_LIBRARY(StelNoGuiLib STATIC ${stellarium_nogui_SRCS})
	TARGET_LINK_LIBRARIES(StelNoGuiLib ${extLinkerOption})
	SET_TARGET_PROPERTIES(StelNoGuiLib PROPERTIES COMPILE_FLAGS "-DQT_STATICPLUGIN")
	SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} ${CMAKE_BINARY_DIR}/src/libStelNoGuiLib.a)
	ADD_DEPENDENCIES(AllStaticPlugins StelNoGuiLib)
ENDIF()


#############################################################################################
############################# External GUI plugin compilation ###############################
#############################################################################################
IF (GUI_MODE STREQUAL "External")
	SET(EXTERNAL_GUI_SRC_PATH "../../MyGui/" CACHE PATH "The location of the plugin main directory i.e. the one containing the top level CMakeLists.txt")
	ADD_SUBDIRECTORY( ${EXTERNAL_GUI_SRC_PATH} externalGui )
	SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} ${CMAKE_BINARY_DIR}/src/externalGui/src/libExternalGui.a)
	SET(EXTERNAL_GUI_PLUGIN_EXTRALIBS CACHE STRING "Additionnal link options needed for the GUI plugin")
	SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${EXTERNAL_GUI_PLUGIN_EXTRALIBS})
ENDIF()


###############################################################################################
################## Static plugins need to be known by the file StelMainView.cpp at compilation time
################## so add the definitions to the compilation.
################## Also add the full path to the .a libraries at compilation time.

### demo plugins ###

IF (USE_PLUGIN_HELLOSTELMODULE)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/HelloStelModule/src/${CMAKE_CFG_INTDIR}/libHelloStelModule.a")
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_HELLOSTELMODULE)
ENDIF()

IF (USE_PLUGIN_SIMPLEDRAWLINE)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/SimpleDrawLine/src/${CMAKE_CFG_INTDIR}/libSimpleDrawLine.a")
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_SIMPLEDRAWLINE)
ENDIF()
	
### work plugins ###

IF (USE_PLUGIN_ANGLEMEASURE)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/AngleMeasure/src/${CMAKE_CFG_INTDIR}/libAngleMeasure.a")
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_ANGLEMEASURE)
ENDIF()

IF (USE_PLUGIN_COMPASSMARKS)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/CompassMarks/src/${CMAKE_CFG_INTDIR}/libCompassMarks.a")
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_COMPASSMARKS)
ENDIF()

IF (USE_PLUGIN_EXOPLANETS)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/Exoplanets/src/${CMAKE_CFG_INTDIR}/libExoplanets.a")
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_EXOPLANETS)
ENDIF()

IF (USE_PLUGIN_LOGBOOK)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/LogBook/src/${CMAKE_CFG_INTDIR}/libLogBook.a")
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_LOGBOOK)
        SET(QT_USE_QTSQL TRUE)
ENDIF()

IF (USE_PLUGIN_NOVAE)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/Novae/src/${CMAKE_CFG_INTDIR}/libNovae.a")
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_NOVAE)
ENDIF()

IF (USE_PLUGIN_OBSERVABILITY)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/Observability/src/${CMAKE_CFG_INTDIR}/libObservability.a")
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_OBSERVABILITY)
ENDIF()

IF (USE_PLUGIN_OCULARS)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/Oculars/src/${CMAKE_CFG_INTDIR}/libOculars.a")
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_OCULARS)
ENDIF()

IF (USE_PLUGIN_PULSARS)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/Pulsars/src/${CMAKE_CFG_INTDIR}/libPulsars.a")
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_PULSARS)
ENDIF()

IF (USE_PLUGIN_QUASARS)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/Quasars/src/${CMAKE_CFG_INTDIR}/libQuasars.a")
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_QUASARS)
ENDIF()

IF (USE_PLUGIN_SATELLITES)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/Satellites/src/${CMAKE_CFG_INTDIR}/libSatellites.a")
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_SATELLITES)
ENDIF()

IF (USE_PLUGIN_SOLARSYSTEMEDITOR)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/SolarSystemEditor/src/${CMAKE_CFG_INTDIR}/libSolarSystemEditor.a")
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_SOLARSYSTEMEDITOR)
ENDIF()

IF (USE_PLUGIN_SUPERNOVAE)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/Supernovae/src/${CMAKE_CFG_INTDIR}/libSupernovae.a")
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_SUPERNOVAE)
ENDIF()

IF (USE_PLUGIN_SVMT)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} ${CMAKE_BINARY_DIR}/plugins/svmt/src/${CMAKE_CFG_INTDIR}/libSVMT.a)
        IF(APPLE)
                SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "-framework QtDeclarative")
        ELSE(APPLE)
                SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} ${QT_LIBRARY_DIR}/libQtDeclarative.so)
        ENDIF(APPLE)
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_SVMT)
ENDIF()

IF (USE_PLUGIN_TELESCOPECONTROL)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/TelescopeControl/src/${CMAKE_CFG_INTDIR}/libTelescopeControl.a")
        IF(WIN32)
                SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} libwsock32.a)
        ENDIF(WIN32)
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_TELESCOPECONTROL)
ENDIF()

IF (USE_PLUGIN_TEXTUSERINTERFACE)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/TextUserInterface/src/${CMAKE_CFG_INTDIR}/libTextUserInterface.a")
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_TEXTUSERINTERFACE)
ENDIF()

IF (USE_PLUGIN_TIMEZONECONFIGURATION)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} "${CMAKE_BINARY_DIR}/plugins/TimeZoneConfiguration/src/${CMAKE_CFG_INTDIR}/libTimeZoneConfiguration.a")
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_TIMEZONECONFIGURATION)
ENDIF()

IF (USE_PLUGIN_VIRGO)
        SET(STELLARIUM_STATIC_PLUGINS_LIBRARIES ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} ${CMAKE_BINARY_DIR}/plugins/VirGO/src/${CMAKE_CFG_INTDIR}/libVirGO.a ${CFITSIO_LIBRARIES})
        ADD_DEFINITIONS(-DUSE_STATIC_PLUGIN_VIRGO)
ENDIF()

#############################################################################################
################################ Build main program #########################################
#############################################################################################

SET(extLinkerOption ${OPENGL_LIBRARIES} ${ZLIB_LIBRARIES})
IF(WIN32)
	SET(extLinkerOption ${extLinkerOption} libwinmm.a -lws2_32)
ENDIF()

IF(WIN32 AND ENABLE_WINDOWS_EXE_ICON)
  IF(RC_COMPILER_PATH)
    ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_BINARY_DIR}/stellarium-rc.o
                       COMMAND ${RC_COMPILER_PATH} ${CMAKE_SOURCE_DIR}/data/stellarium.rc ${CMAKE_BINARY_DIR}/stellarium-rc.o
                       WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/data)
    SET(stellarium_exe_SRCS ${stellarium_exe_SRCS} ${CMAKE_BINARY_DIR}/stellarium-rc.o)
  ENDIF(RC_COMPILER_PATH)
ENDIF(WIN32 AND ENABLE_WINDOWS_EXE_ICON)

IF(GENERATE_STELMAINLIB)
 ADD_LIBRARY(stelMain SHARED ${stellarium_lib_SRCS} ${stellarium_RES_CXX})
 TARGET_LINK_LIBRARIES(stelMain ${extLinkerOption} ${STELLARIUM_STATIC_PLUGINS_LIBRARIES})
 QT5_USE_MODULES(stelMain Core Concurrent Declarative Gui Network OpenGL Script Widgets)
 IF(ENABLE_SOUND)
   QT5_USE_MODULES(stelMain Multimedia)
 ENDIF()
 INSTALL(TARGETS stelMain DESTINATION lib)
 ADD_EXECUTABLE(stellarium ${stellarium_exe_SRCS})
 #stelMain should be after the plug-ins, otherwise the build crashes
 TARGET_LINK_LIBRARIES(stellarium ${STELLARIUM_STATIC_PLUGINS_LIBRARIES} stelMain ${extLinkerOption})
ELSE()
 ADD_EXECUTABLE(stellarium ${stellarium_lib_SRCS} ${stellarium_RES_CXX} ${stellarium_exe_SRCS})
 TARGET_LINK_LIBRARIES(stellarium ${extLinkerOption} ${STELLARIUM_STATIC_PLUGINS_LIBRARIES})
 QT5_USE_MODULES(stellarium Core Concurrent Declarative Gui Network OpenGL Script Widgets)
 IF(ENABLE_SOUND)
   QT5_USE_MODULES(stellarium Multimedia)
 ENDIF()

 IF(APPLE)
  SET_TARGET_PROPERTIES(stellarium PROPERTIES LINK_FLAGS " -framework Cocoa -framework OpenGL")
 ENDIF()

ENDIF()

ADD_DEPENDENCIES(stellarium AllStaticPlugins)

INSTALL(TARGETS stellarium DESTINATION bin)



#############################################################################################
################################## Build unit tests #########################################
#############################################################################################

SET(extLinkerOptionTest ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} ${QT_QTTEST_LIBRARY} ${QT_QTGUI_LIBRARY} ${ZLIB_LIBRARIES})

# Custom target used to build all tests at once
ADD_CUSTOM_TARGET(buildTests)

SET(tests_testDates_SRCS
	core/StelUtils.cpp
	core/StelUtils.hpp
	tests/testDates.cpp)
ADD_EXECUTABLE(testDates EXCLUDE_FROM_ALL ${tests_testDates_SRCS})
QT5_USE_MODULES(testDates Core Gui Widgets OpenGL Script Declarative Test)
TARGET_LINK_LIBRARIES(testDates ${extLinkerOptionTest})
ADD_DEPENDENCIES(buildTests testDates)

SET(tests_testStelFileMgr_SRCS
	core/StelFileMgr.cpp
	core/StelFileMgr.hpp
	tests/testStelFileMgr.cpp)
ADD_EXECUTABLE(testStelFileMgr EXCLUDE_FROM_ALL ${tests_testStelFileMgr_SRCS})
QT5_USE_MODULES(testStelFileMgr Core Gui Widgets OpenGL Script Declarative Test)
TARGET_LINK_LIBRARIES(testStelFileMgr ${extLinkerOptionTest})
ADD_DEPENDENCIES(buildTests testStelFileMgr)

SET(tests_testStelSphereGeometry_SRCS
	tests/testStelSphereGeometry.hpp
	tests/testStelSphereGeometry.cpp
	core/StelSphereGeometry.hpp
	core/StelSphereGeometry.cpp
	core/StelVertexArray.hpp
	core/StelVertexArray.cpp
	core/OctahedronPolygon.hpp
	core/OctahedronPolygon.cpp
	core/StelJsonParser.hpp
	core/StelJsonParser.cpp
	core/StelUtils.cpp
	core/StelUtils.hpp
	core/StelProjector.cpp
	core/StelProjector.hpp
	core/StelFileMgr.cpp
	core/StelFileMgr.hpp
	core/StelTranslator.cpp
	core/StelTranslator.hpp
	${glues_lib_SRCS})
ADD_EXECUTABLE(testStelSphereGeometry EXCLUDE_FROM_ALL ${tests_testStelSphereGeometry_SRCS})
QT5_USE_MODULES(testStelSphereGeometry Core Gui OpenGL Test)
TARGET_LINK_LIBRARIES(testStelSphereGeometry ${extLinkerOptionTest} ${QT_QTOPENGL_LIBRARY})
ADD_DEPENDENCIES(buildTests testStelSphereGeometry)

#SET(tests_testStelSphericalIndex_SRCS
#	tests/testStelSphericalIndex.hpp
#	tests/testStelSphericalIndex.cpp
#	core/StelSphericalIndex.hpp
#	core/StelSphericalIndex.cpp
#	core/StelSphereGeometry.hpp
#	core/StelSphereGeometry.cpp
#	core/StelVertexArray.hpp
#	core/StelVertexArray.cpp
#	core/OctahedronPolygon.hpp
#	core/OctahedronPolygon.cpp
#	core/StelJsonParser.hpp
#	core/StelJsonParser.cpp
#	core/StelUtils.cpp
#	core/StelUtils.hpp
#	core/StelProjector.cpp
#	core/StelProjector.hpp
#	core/StelTranslator.cpp
#	core/StelTranslator.hpp
#	${glues_lib_SRCS})
#ADD_EXECUTABLE(testStelSphericalIndex EXCLUDE_FROM_ALL ${tests_testStelSphericalIndex_SRCS})
#QT5_USE_MODULES(testStelSphericalIndex Core Gui Widgets OpenGL Script Declarative Test)
#TARGET_LINK_LIBRARIES(testStelSphericalIndex ${extLinkerOptionTest} ${QT_QTOPENGL_LIBRARY})
#ADD_DEPENDENCIES(buildTests testStelSphericalIndex)

SET(tests_testStelJsonParser_SRCS
	tests/testStelJsonParser.hpp
	tests/testStelJsonParser.cpp
	core/StelJsonParser.hpp
	core/StelJsonParser.cpp)
ADD_EXECUTABLE(testStelJsonParser EXCLUDE_FROM_ALL ${tests_testStelJsonParser_SRCS})
QT5_USE_MODULES(testStelJsonParser Core Gui Widgets OpenGL Script Declarative Test)
TARGET_LINK_LIBRARIES(testStelJsonParser ${extLinkerOptionTest})
ADD_DEPENDENCIES(buildTests testStelJsonParser)

#SET(tests_testStelVertexArray_SRCS
#  tests/testStelVertexArray.hpp
#  tests/testStelVertexArray.cpp
#  core/StelVertexArray.hpp)
#QT5_WRAP_CPP(tests_testStelVertexArray_MOC_SRCS tests/testStelVertexArray.hpp)
#ADD_EXECUTABLE(testStelVertexArray EXCLUDE_FROM_ALL ${tests_testStelVertexArray_SRCS} ${tests_testStelVertexArray_MOC_SRCS})
#QT5_USE_MODULES(testStelVertexArray Core Gui Test)
#TARGET_LINK_LIBRARIES(testStelVertexArray ${extLinkerOptionTest})
#ADD_DEPENDENCIES(buildTests testStelVertexArray)

SET(tests_testDeltaT_SRCS
  tests/testDeltaT.hpp
  tests/testDeltaT.cpp
  core/StelUtils.cpp
  core/StelUtils.hpp)
ADD_EXECUTABLE(testDeltaT EXCLUDE_FROM_ALL ${tests_testDeltaT_SRCS})
QT5_USE_MODULES(testDeltaT Core Gui Widgets OpenGL Script Declarative Test)
TARGET_LINK_LIBRARIES(testDeltaT ${extLinkerOptionTest})
ADD_DEPENDENCIES(buildTests testDeltaT)

SET(tests_testConversions_SRCS
	core/StelUtils.cpp
	core/StelUtils.hpp
	tests/testConversions.hpp
	tests/testConversions.cpp)
ADD_EXECUTABLE(testConversions EXCLUDE_FROM_ALL ${tests_testConversions_SRCS})
QT5_USE_MODULES(testConversions Core Gui Widgets OpenGL Script Declarative Test)
TARGET_LINK_LIBRARIES(testConversions ${extLinkerOptionTest})
ADD_DEPENDENCIES(buildTests testConversions)


ADD_CUSTOM_TARGET(tests COMMENT "Run the Stellarium unit tests")
#ADD_CUSTOM_COMMAND(TARGET tests POST_BUILD COMMAND ./testDates WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/)
ADD_CUSTOM_COMMAND(TARGET tests POST_BUILD COMMAND ./testStelFileMgr WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/)
ADD_CUSTOM_COMMAND(TARGET tests POST_BUILD COMMAND ./testStelSphereGeometry WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/)
#ADD_CUSTOM_COMMAND(TARGET tests POST_BUILD COMMAND ./testStelSphericalIndex WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/)
#ADD_CUSTOM_COMMAND(TARGET tests POST_BUILD COMMAND ./testStelVertexBuffer WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/)
ADD_CUSTOM_COMMAND(TARGET tests POST_BUILD COMMAND ./testStelJsonParser WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/)
#ADD_CUSTOM_COMMAND(TARGET tests POST_BUILD COMMAND ./testStelVertexArray WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/)
ADD_CUSTOM_COMMAND(TARGET tests POST_BUILD COMMAND ./testDeltaT WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/)
ADD_CUSTOM_COMMAND(TARGET tests POST_BUILD COMMAND ./testConversions WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/)
ADD_DEPENDENCIES(tests buildTests)

