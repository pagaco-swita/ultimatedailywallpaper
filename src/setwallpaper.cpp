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

#include "setwallpaper.h"

#include <QProcess>
#include <QDebug>
#include <QPixmap>
#include <QApplication>
#include <QFile>
#include <QSettings>
#include <QTextStream>
#include <QDir>
#include <QThread>

setWallpaper::setWallpaper()
{
}

void setWallpaper::_set_wallpaper(QString _wallpaperfile, int _Parameter, int _change_lockscreen_wallpaper)
{
    if(_wallpaperfile.contains("\'"))
    {
        _wallpaperfile.replace("\'", "\'\\'\'");
    }

    if(_wallpaperfile.contains("\x22"))
    {
        _wallpaperfile.replace("\x22", "\x5C\x22");
    }

    if(!_wallpaperfile.isEmpty())
    {
        QString command;
        QString content;

        switch(_Parameter)
        {

#if defined(Q_OS_LINUX)
        case 0:
            //Budgie
            command="gsettings set org.gnome.desktop.background picture-uri \"file://"+_wallpaperfile+"\"";
            break;
        case 1:
            //Cinnamon
            command="gsettings set org.cinnamon.desktop.background picture-uri \"file://"+_wallpaperfile+"\"";
            break;
        case 2:
            //XFCE
            if(!(_xfce4_detect_monitors()==255))
            {
                for (int i = 0; i < _detected_monitors.size(); i++)
                {                    
                    command="xfconf-query --channel xfce4-desktop --property "+_detected_monitors.at(i)+" --set \""+_wallpaperfile+"\"";
                    if(doProcess(command)==255)
                    {
                        qDebug() << tr("Error - Failed to set wallpaper.");
                    }                    
                }
            }
            break;
        case 3:
            //LXDE
            command="pcmanfm --set-wallpaper=\""+_wallpaperfile+"\"";
            break;
        case 4:
            //MATE
            command="gsettings set org.mate.background picture-filename \""+_wallpaperfile+"\"";
            break;
        case 5:
            //Trinity Desktop Environment (TDE)
            command="dcop kdesktop KBackgroundIface setWallpaper \""+_wallpaperfile+"\" 8";
            break;
        case 6:
            //KDE Plasma 5
            content =
                    "#!/bin/bash\n"
                    " \n"
                    "dbus-send --session --dest=org.kde.plasmashell --type=method_call /PlasmaShell org.kde.PlasmaShell.evaluateScript 'string: \n"
                    "var Desktops = desktops(); \n"
                    "print (Desktops); \n"
                    "for (i=0;i<Desktops.length;i++) {\n"
                    "        d = Desktops[i];\n"
                    "        d.wallpaperPlugin = \"org.kde.image\";\n"
                    "        d.currentConfigGroup = Array(\"Wallpaper\",\n"
                    "                                    \"org.kde.image\",\n"
                    "                                    \"General\");\n"
                    "        d.writeConfig(\"Image\", \"file://"+_wallpaperfile+"\");\n"
                    "}'";

            _set_wallpaper_script(QDir::homePath()+"/.UltimateDailyWallpaper/spw.sh", content);

            if(_change_lockscreen_wallpaper==2)
            {
                command="kwriteconfig5 --file kscreenlockerrc --group Greeter --group Wallpaper --group org.kde.image --group General --key Image \""+_wallpaperfile+"\"";
            }

            break;
        case 7:
            //LXQt
            command="pcmanfm-qt --set-wallpaper=\""+_wallpaperfile+"\" --wallpaper-mode=stretch";
            break;
        case 8:
            //Deepin Desktop Environment (DDE)
            command="gsettings set com.deepin.wrap.gnome.desktop.background picture-uri \"file://"+_wallpaperfile+"\"";
            break;
        case 9:
            //GNOME 3 or GNOME-Classic

            QStringList color_schemes = {"picture-uri","picture-uri-dark"};

            for(int i=0; i<color_schemes.size();i++)
            {
                command="gsettings set org.gnome.desktop.background "+color_schemes.at(i)+" \"file://"+_wallpaperfile+"\"";
                if(doProcess(command)==255)
                {
                    qDebug() << tr("Error - Failed to set wallpaper.");
                }
                command.clear();
            }

            if(_change_lockscreen_wallpaper==2)
            {
                for(int i=0; i<color_schemes.size();i++)
                {
                    command="gsettings set org.gnome.desktop.screensaver "+color_schemes.at(i)+" \"file://"+_wallpaperfile+"\"";
                    if(doProcess(command)==255)
                    {
                        qDebug() << tr("Error - Failed to set wallpaper.");
                    }
                    command.clear();
                }
            }
            break;

#elif defined(Q_OS_MACOS)
        case 0:
            content =
                    "#!/bin/bash\n"
                    " \n"
                    "osascript -e 'tell application \"System Events\" to tell every desktop to set picture to \""+_wallpaperfile+"\"'";

            _set_wallpaper_script(QDir::homePath()+"/.UltimateDailyWallpaper/cw.sh", content);

            break;
#endif
        }

        if(!(_Parameter==2) && !(_Parameter==8))
        {
            if(doProcess(command)==255)
            {
                qDebug() << tr("Error - Failed to set wallpaper.");
            }
            command.clear();
        }
    }
}

int setWallpaper::_xfce4_detect_monitors()
{
    QProcess _list_monitors;

    _list_monitors.start("xfconf-query -c xfce4-desktop -l | grep \"last-image\" ");
    _list_monitors.waitForFinished();

    out = _list_monitors.readAllStandardOutput();
    _detected_monitors = out.split("\n");

    _list_monitors.close();

    return _list_monitors.exitCode();
}

void setWallpaper::_set_wallpaper_script(QString _scriptfile, QString content)
{
    QFile set_wallpaper_plasma(_scriptfile);
    if(!set_wallpaper_plasma.exists(_scriptfile))
    {
        if (set_wallpaper_plasma.open(QIODevice::Append))
        {
            QTextStream stream(&set_wallpaper_plasma);
            stream <<content<<Qt::endl;
        }
    }

    if(doProcess("/bin/bash "+_scriptfile)==255)
    {
        qDebug() << tr("Error - Failed to set wallpaper.");
    }
    QThread::msleep(100);
    content.clear();
    set_wallpaper_plasma.remove();
}

int setWallpaper::doProcess(QString command)
{
    QProcess proc;
    proc.start(command);
    proc.waitForFinished();
    proc.close();    

    return proc.exitCode();
}
