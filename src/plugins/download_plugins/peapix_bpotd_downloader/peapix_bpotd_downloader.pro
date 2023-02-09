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

VERSION     = 0.0.5
DEFINES     += PLUGIN_VERSION=\\\"$$VERSION\\\"
DESTDIR     = ../../../../plugins
QT          += core widgets sql xml network concurrent
TEMPLATE    = lib
DEFINES += PEAPIX_BPOTD_DOWNLOADER_LIBRARY
CONFIG      += c++17 plugin
TARGET      = peapix_bpotd_downloader_$$VERSION

INCLUDEPATH += ../../../../src

FILES = peapix_bpotd_downloader.json

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    peapix_bpotd_downloader.cpp

HEADERS += \
    peapix_bpotd_downloader.h
