#---------------------------------------------------
# "UltimateDailyWallpaper" Copyright (C) 2023 Patrice Coni
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#  
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.
#---------------------------------------------------

VERSION   = 3.1.2
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

QT       += core gui network xml concurrent sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET          = UltimateDailyWallpaper
TEMPLATE        = app
CONFIG          += warn_on
DESTDIR         = ../bin
MOC_DIR         = ../build/moc
RCC_DIR         = ../build/rcc
UI_DIR          = ../build/ui
unix:OBJECTS_DIR = ../build/o/unix
DIRS            = ../lang

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TRANSLATIONS = \
               ../language/UltimateDailyWallpaper_ca.po \
               ../language/UltimateDailyWallpaper_de.po \
               ../language/UltimateDailyWallpaper_fr.po \
               ../language/UltimateDailyWallpaper_it.po \
               ../language/UltimateDailyWallpaper_es.po \
               ../language/UltimateDailyWallpaper_fi.po \
               ../language/UltimateDailyWallpaper_ru.po \
               ../language/UltimateDailyWallpaper_uk.po \
               ../language/UltimateDailyWallpaper_ko.po \
               ../language/UltimateDailyWallpaper_pt.po \
               ../language/UltimateDailyWallpaper.pot

SOURCES += \
    about.cpp \
    main.cpp \
    mainwindow.cpp \
    photobrowser.cpp \
    settingswindow.cpp \
    setwallpaper.cpp

HEADERS += \
    about.h \
    connection.h \
    interfaces.h \
    itemdelegate.h \
    mainwindow.h \
    photobrowser.h \
    settingswindow.h \
    setwallpaper.h

FORMS += \
    about.ui \
    photobrowser.ui \
    settingswindow.ui

RESOURCES += \
    udw_ressource.qrc
