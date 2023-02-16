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
#include <QDomElement>
#include <QDomDocument>

#include "bing_wallpaper_downloader.h"

Bing_wallpaper_downloader::Bing_wallpaper_downloader()
{
}

Bing_wallpaper_downloader::~Bing_wallpaper_downloader()
{
}

bool Bing_wallpaper_downloader::SetExtendedFunctionInterface()
{
    return false;
}

bool Bing_wallpaper_downloader::SetAdditionalFunctionInterface()
{
    return false;
}

bool Bing_wallpaper_downloader::SetMenuInterface()
{
    return false;
}

bool Bing_wallpaper_downloader::SetSubMenuInterface()
{
    return false;
}

QString Bing_wallpaper_downloader::SubMenuTitle()
{
}

QStringList Bing_wallpaper_downloader::SubMenuTriggers()
{
}

QStringList Bing_wallpaper_downloader::SubMenuEmitStrings()
{
}

void Bing_wallpaper_downloader::SubMenuFunction(QString anything)
{
    QSettings _settings(QDir::homePath()+"/.UltimateDailyWallpaper/settings.conf", QSettings::IniFormat);
    _settings.beginGroup("PROVIDER_SETTINGS");
    _settings.setValue("lang", anything);
    _settings.endGroup();
    _settings.sync();
}

void Bing_wallpaper_downloader::get_picture(bool downloadthumb,
                                         QString _picturedir,
                                         QString lang,
                                         int year,
                                         int month,
                                         int day)
{
    _picture_height=0;
    _picture_width=0;

    parse(lang);

    if(!(check_exists()==255))
    {
        if(!(download_picture("https://www.bing.com"+_urlBase+"_"+"UHD.jpg", _picturedir, false)==255))
        {
            QImage img(_picturedir+"/"+filename);
            _picture_height=img.size().height();
            _picture_width=img.size().width();
            if(!(download_picture("https://www.bing.com"+_urlBase+"_"+"400x240.jpg", QDir::homePath()+"/.UltimateDailyWallpaper/thumbnails", true)==255))
            {                
                emit download_successful(_description,
                                         _copyright,
                                         provider(),
                                         _titletext,
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

QString Bing_wallpaper_downloader::pluginname()
{
    return tr("Daily Bing wallpaper Downloader");
}

QString Bing_wallpaper_downloader::provider()
{
    return tr("Bing");
}

QString Bing_wallpaper_downloader::plugininfo()
{
    QString info;
    info.append("Name: "+pluginname());
    info.append("\n");
    info.append("Description: Bing wallpaper of the day\n");
    info.append("License: GPL-3.0+\n");
    info.append("Author: Patrice Coni\n");
    info.append("Version: ");
    info.append("v");
    info.append(PLUGIN_VERSION);

    return info;
}

void Bing_wallpaper_downloader::parse(QString _lang)
{
    QString baseURL="https://www.bing.com/HPImageArchive.aspx?format=xml&idx=0&n=1&mkt=";
    QString _language;

    if(_lang.contains("de"))
    {
        _language="de-DE";
    }
    else if(_lang.contains("fr"))
    {
        _language="fr-FR";
    }
    else if(_lang.contains("it"))
    {
        _language="it-IT";
    }
    else if(_lang.contains("es"))
    {
        _language="es-ES";
    }
    else
    {
        _language="en-US";
    }

    if(request_download_json(baseURL+_language)==true)
    {
        QDomDocument basefile;

        basefile.setContent(_reply);

        QDomElement element= basefile.documentElement().firstChild().firstChild().toElement();

        while(!element.isNull()) {
              if(element.tagName()=="urlBase")
              {
                  _urlBase = element.firstChild().toText().data();
              }
              if(element.tagName()=="copyright")
              {
                  _description = element.firstChild().toText().data();
              }
              if(element.tagName()=="copyrightlink")
              {
                  _page_url = element.firstChild().toText().data();
              }
              if(element.tagName()=="headline")
              {
                  _titletext = element.firstChild().toText().data();
              }
              element = element.nextSibling().toElement();
        }
    }

    filename.clear();
    filename.append(_urlBase+"_UHD.jpg");
    filename.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_â€”+=|:;<>Â«Â»,.?/{}\'\"\\\[\\\]\\\\]")));

    thumbfilename.clear();
    thumbfilename.append("_thumb_"+_urlBase+".jpg");
    thumbfilename.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_â€”+=|:;<>Â«Â»,.?/{}\'\"\\\[\\\]\\\\]")));
}

bool Bing_wallpaper_downloader::request_download_json(QString _targeturl)
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

int Bing_wallpaper_downloader::download_picture(QString _dlurl, QString dlpath, bool _is_thumb)
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

int Bing_wallpaper_downloader::check_exists()
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
