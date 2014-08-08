# Config.pri file version 2.0. Auto-generated by IDE. Any changes made by user will be lost!
BASEDIR = $$quote($$_PRO_FILE_PWD_)

device {
    CONFIG(debug, debug|release) {
        profile {
            CONFIG += \
                config_pri_assets \
                config_pri_source_group1
        } else {
            CONFIG += \
                config_pri_assets \
                config_pri_source_group1
        }

    }

    CONFIG(release, debug|release) {
        !profile {
            CONFIG += \
                config_pri_assets \
                config_pri_source_group1
        }
    }
}

simulator {
    CONFIG(debug, debug|release) {
        !profile {
            CONFIG += \
                config_pri_assets \
                config_pri_source_group1
        }
    }
}

config_pri_assets {
    OTHER_FILES += \
        $$quote($$BASEDIR/assets/About.qml) \
        $$quote($$BASEDIR/assets/Balloon.qml) \
        $$quote($$BASEDIR/assets/images/background.png) \
        $$quote($$BASEDIR/assets/images/balloon_left.png) \
        $$quote($$BASEDIR/assets/images/balloon_right.png) \
        $$quote($$BASEDIR/assets/images/ic_info.png) \
        $$quote($$BASEDIR/assets/images/ic_microphone.png) \
        $$quote($$BASEDIR/assets/images/ic_microphone_mute.png) \
        $$quote($$BASEDIR/assets/images/icon114x114.png) \
        $$quote($$BASEDIR/assets/main.qml)
}

config_pri_source_group1 {
    SOURCES += \
        $$quote($$BASEDIR/src/applicationui.cpp) \
        $$quote($$BASEDIR/src/main.cpp) \
        $$quote($$BASEDIR/src/net/network.cpp) \
        $$quote($$BASEDIR/src/net/session/client.cpp) \
        $$quote($$BASEDIR/src/net/session/connection.cpp) \
        $$quote($$BASEDIR/src/net/session/server.cpp) \
        $$quote($$BASEDIR/src/net/session/state.cpp)

    HEADERS += \
        $$quote($$BASEDIR/src/applicationui.hpp) \
        $$quote($$BASEDIR/src/net/network.h) \
        $$quote($$BASEDIR/src/net/session/client.h) \
        $$quote($$BASEDIR/src/net/session/connection.h) \
        $$quote($$BASEDIR/src/net/session/server.h) \
        $$quote($$BASEDIR/src/net/session/state.h)
}

INCLUDEPATH += $$quote($$BASEDIR/src/net) \
    $$quote($$BASEDIR/src/net/session) \
    $$quote($$BASEDIR/src)

CONFIG += precompile_header

PRECOMPILED_HEADER = $$quote($$BASEDIR/precompiled.h)

lupdate_inclusion {
    SOURCES += \
        $$quote($$BASEDIR/../src/*.c) \
        $$quote($$BASEDIR/../src/*.c++) \
        $$quote($$BASEDIR/../src/*.cc) \
        $$quote($$BASEDIR/../src/*.cpp) \
        $$quote($$BASEDIR/../src/*.cxx) \
        $$quote($$BASEDIR/../src/net/*.c) \
        $$quote($$BASEDIR/../src/net/*.c++) \
        $$quote($$BASEDIR/../src/net/*.cc) \
        $$quote($$BASEDIR/../src/net/*.cpp) \
        $$quote($$BASEDIR/../src/net/*.cxx) \
        $$quote($$BASEDIR/../src/net/session/*.c) \
        $$quote($$BASEDIR/../src/net/session/*.c++) \
        $$quote($$BASEDIR/../src/net/session/*.cc) \
        $$quote($$BASEDIR/../src/net/session/*.cpp) \
        $$quote($$BASEDIR/../src/net/session/*.cxx) \
        $$quote($$BASEDIR/../assets/*.qml) \
        $$quote($$BASEDIR/../assets/*.js) \
        $$quote($$BASEDIR/../assets/*.qs) \
        $$quote($$BASEDIR/../assets/images/*.qml) \
        $$quote($$BASEDIR/../assets/images/*.js) \
        $$quote($$BASEDIR/../assets/images/*.qs)

    HEADERS += \
        $$quote($$BASEDIR/../src/*.h) \
        $$quote($$BASEDIR/../src/*.h++) \
        $$quote($$BASEDIR/../src/*.hh) \
        $$quote($$BASEDIR/../src/*.hpp) \
        $$quote($$BASEDIR/../src/*.hxx)
}

TRANSLATIONS = $$quote($${TARGET}.ts)
