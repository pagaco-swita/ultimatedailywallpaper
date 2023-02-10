SUBDIRS += src \
           src/plugins/download_plugins/wikimedia_commons_potd \
           src/plugins/download_plugins/bing_wallpaper_downloader
TEMPLATE = subdirs
CONFIG += ordered warn_on qt debug_and_release
