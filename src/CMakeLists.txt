if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected, default to Release")
	set(CMAKE_BUILD_TYPE "Release")
endif()

if(CMAKE_COMPILER_IS_GNUCC)
	message(STATUS "GNU C compiler detected")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O0 -g")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O0 -g")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O2 -pipe -fstack-protector --param=ssp-buffer-size=4")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O2 -pipe -fstack-protector --param=ssp-buffer-size=4")
	set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELEASE} -g -Wall -O2 -pipe -fstack-protector --param=ssp-buffer-size=4")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} -g -Wall -O2 -pipe -fstack-protector --param=ssp-buffer-size=4")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(APP_VERSION)
	message(STATUS "Building as custom version ${APP_VERSION}")
	add_definitions(-DAPP_VERSION=${APP_VERSION})
endif()

add_definitions(${QT_DEFINITIONS} -fexceptions) # -DHAVE_CONFIG_H
add_definitions(-D_DEFAULT_SOURCE)

find_package(FFmpeg REQUIRED)

set(divvydroid_INC
	${CMAKE_CURRENT_BINARY_DIR} # so files can find autogenerated files
	${CMAKE_CURRENT_SOURCE_DIR} # so that we can refer to our files starting at src dir
	${FFMPEG_INCLUDE_DIR}
	${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS}
	CACHE INTERNAL EXPORTEDVARIABLE
)

set(divvydroid_LIBS
	Qt5::Core Qt5::Gui Qt5::Network Qt5::Widgets
	CACHE INTERNAL EXPORTEDVARIABLE
)

set(divvydroid_SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/input/devicetouchhandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/input/devicebuttonhandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/input/input_to_adroid_keys.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/input/inputhandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/input/monkeyhandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/input/shellkeyboardhandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/device/adbclient.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/device/deviceinfo.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/device/videothread.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/initthread.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui
	${CMAKE_CURRENT_SOURCE_DIR}/aboutdialog.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/aboutdialog.ui
	CACHE INTERNAL EXPORTEDVARIABLE
)

if(MINGW)
	# add windows icon
	add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/divvydroidrc.obj
		COMMAND ${CMAKE_RC_COMPILER}
			-D GCC_WINDRES
			-I ${CMAKE_CURRENT_SOURCE_DIR}
			-I ${CMAKE_CURRENT_BINARY_DIR}
			-o ${CMAKE_CURRENT_BINARY_DIR}/divvydroidrc.obj
			-i ${CMAKE_CURRENT_SOURCE_DIR}/../res/divvydroid.rc)
	set(divvydroid_SRCS ${divvydroid_SRCS} ${CMAKE_CURRENT_BINARY_DIR}/divvydroidrc.obj)
endif()

set(divvydroid_LIBS
	${FFMPEG_LIBRARIES}
	Qt5::Core
	Qt5::Network
	Qt5::Widgets
	CACHE INTERNAL EXPORTEDVARIABLE
)

# do the configuration of config.h at the end, so all the necessary variables have been set
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h)

add_executable(divvydroid WIN32 ${divvydroid_SRCS} ${divvydroid_RES})
target_include_directories(divvydroid PUBLIC ${divvydroid_INC})
target_link_libraries(divvydroid ${divvydroid_LIBS})

install(TARGETS divvydroid DESTINATION ${CMAKE_INSTALL_BINDIR})
