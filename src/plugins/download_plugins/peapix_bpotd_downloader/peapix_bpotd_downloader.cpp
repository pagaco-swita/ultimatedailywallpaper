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

#include <QUrl>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QApplication>
#include <QDebug>
#include <QThread>
#include <QProcess>
#include <QDateTime>
#include <QImage>
#include <QSqlQuery>
#include <QSqlError>
#include <QSettings>

#include "peapix_bpotd_downloader.h"

Peapix_bpotd_downloader::Peapix_bpotd_downloader()
{
}

Peapix_bpotd_downloader::~Peapix_bpotd_downloader()
{
}

bool Peapix_bpotd_downloader::SetExtendedFunctionInterface()
{
    return false;
}

bool Peapix_bpotd_downloader::SetAdditionalFunctionInterface()
{
    return false;
}

bool Peapix_bpotd_downloader::SetMenuInterface()
{
    return false;
}

bool Peapix_bpotd_downloader::SetSubMenuInterface()
{
    return false;
}

QString Peapix_bpotd_downloader::SubMenuTitle()
{
}

QStringList Peapix_bpotd_downloader::SubMenuTriggers()
{
}

QStringList Peapix_bpotd_downloader::SubMenuEmitStrings()
{
}

void Peapix_bpotd_downloader::SubMenuFunction(QString anything)
{
    QSettings _settings(QDir::homePath()+"/.UltimateDailyWallpaper/settings.conf", QSettings::IniFormat);
    _settings.beginGroup("PROVIDER_SETTINGS");
    _settings.setValue("lang", anything);
    _settings.endGroup();
    _settings.sync();
}

void Peapix_bpotd_downloader::get_picture(bool downloadthumb,
                                         QString _picturedir,
                                         QString lang,
                                         int year,
                                         int month,
                                         int day)
{
    _picture_height=0;
    _picture_width=0;

    if(lang=="en")
    {
        lang.clear();
        lang.append("us");
    }

    parse(lang);

    if(!(check_exists()==255))
    {
        if(!(download_picture(_picture_url, _picturedir, false)==255))
        {
            QImage img(_picturedir+"/"+filename);
            _picture_height=img.size().height();
            _picture_width=img.size().width();
            if(!(download_picture(_thumb_url, QDir::homePath()+"/.UltimateDailyWallpaper/thumbnails", true)==255))
            {
                emit download_successful(_titletext,
                                         _copyright,
                                         provider(),
                                         "Peapix - Bing wallpaper of the day",
                                         filename,
                                         _page_url,
                                         thumbfilename,
                                         _picture_height,
                                         _picture_width,
                                         0,
                                         false,
                                         "");
            }
        }
    }
    else
    {
        qDebug() << "The most recent image is already stored.";
    }
}

QString Peapix_bpotd_downloader::pluginname()
{
    return tr("Bing wallpaper of the day Downloader");
}

QString Peapix_bpotd_downloader::provider()
{
    return tr("Peapix - Bing wallpaper of the day");
}

QString Peapix_bpotd_downloader::plugininfo()
{
    QString info;
    info.append("Name: "+pluginname());
    info.append("\n");
    info.append("Description: Bing wallpaper of the day from Peapix\n");
    info.append("License: GPL-3.0+\n");
    info.append("Author: Patrice Coni\n");
    info.append("Version: ");
    info.append("v");
    info.append(PLUGIN_VERSION);

    return info;
}

void Peapix_bpotd_downloader::parse(QString _lang)
{
    QString baseURL;

    if(_lang.contains("ca"))
    {
        baseURL="https://peapix.com/bing/feed?country="+_lang;
    }
    else if(_lang.contains("de"))
    {
        baseURL="https://peapix.com/bing/feed?country="+_lang;
    }
    else if(_lang.contains("fr"))
    {
        baseURL="https://peapix.com/bing/feed?country="+_lang;
    }
    else if(_lang.contains("ja"))
    {
        baseURL="https://peapix.com/bing/feed?country=jp";
    }
    else if(_lang.contains("es"))
    {
        baseURL="https://peapix.com/bing/feed?country="+_lang;
    }
    else
    {
        baseURL="https://peapix.com/bing/feed?country=us";
    }

    if(request_download_json(baseURL)==true)
    {
        QJsonDocument jsondoc = QJsonDocument::fromJson(_reply.toUtf8());
        QJsonArray _array = jsondoc.array();
        QJsonValue value = _array.at(0);
        QJsonObject obj = value.toObject();

        _picture_url = obj.value("imageUrl").toString();
        _page_url = obj.value("pageUrl").toString();
        _thumb_url = obj.value("thumbUrl").toString();
        _copyright = obj.value("copyright").toString();
         _titletext = obj.value("title").toString();

        filename.clear();
        filename.append(QUrl(_picture_url).fileName());

        thumbfilename.clear();
        thumbfilename.append(QUrl(_thumb_url).fileName());
    }
}

bool Peapix_bpotd_downloader::request_download_json(QString _targeturl)
{
    QEventLoop loop;
    QObject::connect(&dl_manager,&QNetworkAccessManager::finished,&loop,&QEventLoop::quit);
    QUrl targeturl=_targeturl;
    reply = dl_manager.get(QNetworkRequest(targeturl));
    loop.exec();
    if (reply->bytesAvailable())
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            _reply = reply->readAll();
            delete reply;
            reply=0;
        }
        else
        {
            qDebug() << reply->errorString();
            return false;
        }
    }

    loop.quit();
    loop.exit();

    return true;
}

int Peapix_bpotd_downloader::download_picture(QString _dlurl, QString dlpath, bool _is_thumb)
{
    QDir _picturedir(dlpath);
    if(!_picturedir.exists())
    {
        _picturedir.mkpath(dlpath);
    }

    QStringList arguments;

    if(_is_thumb==true)
    {
        arguments << _dlurl << "--output" << dlpath+"/"+thumbfilename;
    } else
    {
        arguments << _dlurl << "--output" << dlpath+"/"+filename;
    }

    QProcess proc;

    if(!arguments.isEmpty())
    {
        proc.start("curl", arguments);
        proc.waitForFinished();
        proc.close();
    }
    else
    {
        qDebug()<<"No arguments.";
    }

    return proc.exitCode();
}

int Peapix_bpotd_downloader::check_exists()
{
    QString content;
    QString _databaseFilePath=QDir::homePath()+"/.UltimateDailyWallpaper/udw_database.sqlite";

    QSqlDatabase udw_db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        udw_db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        udw_db = QSqlDatabase::addDatabase("QSQLITE");
    }

    udw_db.setDatabaseName(_databaseFilePath);
    udw_db.open();

    QSqlQuery uwp_query(udw_db);
    uwp_query.prepare("SELECT filename FROM udw_history WHERE filename=\'"+filename+"\'");
    uwp_query.exec();
    while(uwp_query.next())
    {
        if(uwp_query.last())
        {
            content = uwp_query.value(0).toString();
        }
    }

    if(!content.isEmpty())
    {
        if(filename==content)
        {
            return 255;
        }
        else
        {
            return 2;
        }
    }
    else
    {
        return 1;
    }
    return 100;
}
