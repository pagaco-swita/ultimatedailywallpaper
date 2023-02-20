/**
 * "UltimateDailyWallpaper" Copyright (C) 2023 Patrice Coni
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BING_WALLPAPER_DOWNLOADER_H
#define BING_WALLPAPER_DOWNLOADER_H

#include <QObject>
#include <QtPlugin>
#include <QStringList>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "interfaces.h"

class Bing_wallpaper_downloader : public QObject,
                                  public BasicInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "UltimateDailyWallpaper.BasicInterface" FILE "bing_wallpaper_downloader.json")
    Q_INTERFACES(BasicInterface)

public:
    Bing_wallpaper_downloader();
    ~Bing_wallpaper_downloader();

    bool SetExtendedFunctionInterface() override;
    bool SetAdditionalFunctionInterface() override;
    bool SetMenuInterface() override;
    bool SetSubMenuInterface() override;

    void get_picture(bool downloadthumb,
                     QString _picturedir,
                     QString lang,
                     int year,
                     int month,
                     int day) override;

    QString provider() override;
    QString pluginname() override;
    QString plugininfo() override;

signals:
    void download_successful(QString _description,
                             QString _copyright,
                             QString _provider,
                             QString _title_headline,
                             QString _filename,
                             QString _browser_url,
                             QString _thumb_filename,
                             int _size_height,
                             int _size_width,
                             int pageid,
                             bool tempdatabase,
                             QString potd_date) override;

private:
    QNetworkAccessManager dl_manager;
    QNetworkReply *reply;

    QString _reply;
    QString _urlBase, _picture_url, _titletext, _page_url, _thumb_url, _copyright, _description;
    QString filename;
    QString thumbfilename;
    int _picture_height, _picture_width;

    void parse(QString _lang);
    bool request_download_json(QString _targeturl);
    int download_picture(QString _dlurl, QString dlpath, bool _is_thumb);
    int check_exists();
};

#endif // BING_WALLPAPER_DOWNLOADER_H
