APP_NAME = Ayvu
DEVICE_TARGET = bb10

CONFIG += qt warn_on cascades10
QT += network
LIBS += -laudio_manager -lasound -lbbmultimedia -lbbsystem -lbbdevice

include(config.pri)
