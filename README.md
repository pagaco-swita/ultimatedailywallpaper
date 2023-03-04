![Icon](https://github.com/pagaco-swita/ultimatedailywallpaper/blob/main/src/icons/ultimatedesktopwallpaper_icon.png)

# UltimateDailyWallpaper
UltimateDailyWallpaper is a utility to use the daily picture of a provider as wallpaper on Linux and macOS operating systems. It saves images in a high quality. Further information about each picture can be obtained from the internet with a single click. It integrates with most desktop environments to provide automatically changing wallpaper. It allows a simple integration of external plugins, which allows downloading a daily wallpaper from any one provider.
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

## Installation:

### Linux
UltimateDailyWallpaper is currently available in the repository of:
 * <a href="https://software.opensuse.org/package/UltimateDailyWallpaper?search_term=UltimateDailyWallpaper">OpenSUSE</a>

### macOS
Download the current release of UltimateDailyWallpaper for macOS: <br>
<a href="https://github.com/pagaco-swita/ultimatedailywallpaper/releases">https://github.com/pagaco-swita/ultimatedailywallpaper/releases</a>

## Build from source:
To build UltimateDailyWallpaper from source, you will need:

### Build requirements:
 * Qt 5.14+
 * Git
 * mesa-libGL
 * make
 * gcc/gcc-c++

### Required packages to use UltimateDailyWallpaper:
 * curl

### Build instructions:

```
$ git clone https://github.com/pagaco-swita/ultimatedailywallpaper.git
$ cd ultimatedailywallpaper
$ qmake (or qmake-qt5)
$ make -f Makefile
``` 
 
## Screenshots: <br />

### Main Application
![Screenshot](https://github.com/pagaco-swita/ultimatedailywallpaper/blob/main/screenshots/newpicture_desktop_001.png)

### Application menu
![Screenshot](https://github.com/pagaco-swita/ultimatedailywallpaper/blob/main/screenshots/new_menu_001.png)

### Load stored picture
![Screenshot](https://github.com/pagaco-swita/ultimatedailywallpaper/blob/main/screenshots/load_existing_picture.png)
