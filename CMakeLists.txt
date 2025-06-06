cmake_minimum_required(VERSION 3.16)

project(Baza_Kontaktow VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        baza_kontaktow.cpp
        baza_kontaktow.h
        baza_kontaktow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Baza_Kontaktow
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}


        registration.h registration.cpp registration.ui
        user.h user.cpp
        logged.h logged.cpp logged.ui
        database_manager.h database_manager.cpp
        hash.h hash.cpp
        dashboard.h dashboard.cpp dashboard.ui
        createcontact.h createcontact.cpp createcontact.ui
        styles/style.qss


        contactswidget.h contactswidget.cpp contactswidget.ui
        groupswidget.h groupswidget.cpp groupswidget.ui
        editcontact.h editcontact.cpp editcontact.ui
        creategroup.h creategroup.cpp creategroup.ui
        editgroup.ui
        editgroup.h editgroup.cpp editgroup.ui













    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Baza_Kontaktow APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Baza_Kontaktow SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Baza_Kontaktow
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Baza_Kontaktow PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Baza_Kontaktow)
endif()
set_target_properties(Baza_Kontaktow PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Baza_Kontaktow
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Baza_Kontaktow)
endif()
