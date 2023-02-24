![Icon](https://github.com/pagaco-swita/ultimatedailywallpaper/blob/main/src/icons/ultimatedesktopwallpaper_icon.png)

# UltimateDailyWallpaper
UltimateDailyWallpaper is a simple utility to use the daily picture of a provider as wallpaper on Linux and macOS operating systems. It saves images in a high quality. Further information about each picture can be obtained from the internet with a single click. It integrates with most desktop environments to provide automatically changing wallpaper. It allows a simple integration of external plugins, which allows downloading a daily wallpaper from any one provider.
<br>
## Features of the application: <br />
 * Allows download the daily picture of Wikimedia Commons (POTD) in a high quality
 * Allows download "pictures of the day" from past days of Wikimedia Commons
 * Allows download the daily wallpaper of Bing in a high quality
 * Allows a simple integration of external plugins to download a daily picture of any provider
 * Supports the most of desktop environments to provide automatically changing wallpaper
 * Allows automatically changing wallpaper on lockscreen of KDE Plasma 5 and GNOME

## Recomment: <br />
* gnome-shell-extension-appindicator - support for legacy tray icons on GNOME 3 -> https://github.com/ubuntu/gnome-shell-extension-appindicator
* gnome-shell-extension-top-icons-plus - https://github.com/phocean/TopIcons-plus

## Get the latest build (Linux and macOS):<br />
<a href="hhttps://github.com/pagaco-swita/ultimatedailywallpaper/releases">https://github.com/pagaco-swita/ultimatedailywallpaper/releases</a>

## How to build the Application:

```
$ sudo apt-get install libkf5filemetadata-dev locales qt5-qmake-bin libkf5coreaddons-dev libkf5config-dev qtbase5-dev tzdata qtchooser qt5-qmake libqt5opengl5-dev baloo-kf5-dev qtbase5-dev-tools sensible-utils curl libqt5gui5 libqt5widgets5 libqt5core5a qttools5-dev

$ cd ./src
$ qmake (or qmake -qt5)
$ make -f Makefile
``` 

## Screenshots: <br />

### Main Application
![Screenshot](https://github.com/pagaco-swita/ultimatedailywallpaper/blob/main/screenshots/newpicture_desktop_001.png)

### Application menu
![Screenshot](https://github.com/pagaco-swita/ultimatedailywallpaper/blob/main/screenshots/new_menu_001.png)

### Load stored picture
![Screenshot](https://github.com/pagaco-swita/ultimatedailywallpaper/blob/main/screenshots/load_existing_picture.png)
