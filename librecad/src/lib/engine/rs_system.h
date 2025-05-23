/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2021 A. Stebich (librecad@mail.lordofbikes.de)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software 
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!  
**
**********************************************************************/


#ifndef RS_SYSTEM_H
#define RS_SYSTEM_H


#define RS_SYSTEM RS_System::instance()
#include <QList>
#include <QSharedPointer>

class RS_Locale;
/**
 * Class for some system methods such as file system operations.
 * Implemented as singleton. Use init to Initialize the class
 * before you use it.
 *
 * @author Andrew Mustun
 */
class RS_System {

public:
    /**
     * @return Instance to the unique system object.
     */
    static RS_System *instance();

    void init(const QString& appName,
              const QString& appVersion,
              const QString& appDirName,
              const char *arg0);

    void init(const QString& appName,
              const QString& appVersion,
              const QString& appDirName,
              const QString& arg0);
    void initLanguageList();
    void initAllLanguagesList();

    bool checkInit();
    bool createPaths(const QString& p);

    /**
     * @return Users home directory.
     */
    static QString getHomeDir();
    /**
     * @return Users home directory.
     */
    static QString getTempDir();
    /**
     * @return Current directory.
     */
    static QString getCurrentDir();

    /**
     * @return Application Data directory.
     */
    QString getAppDataDir();

    /**
     * @return A list of absolute paths to all font files found.
     */
    QStringList getFontList() {
        QStringList ret = getFileList("fonts", "cxf");
        return ret;
    }

    /**
     * @return A list of absolute paths to all NEW font files found.
     */
    QStringList getNewFontList() {
        QStringList ret = getFileList("fonts", "lff");
        return ret;
    }

    /**
     * @return A list of absolute paths to all hatch pattern files found.
     */
    QStringList getPatternList() {
        QStringList ret = getFileList("patterns", "dxf");
        return ret;
    }

    /**
     * @return A list of absolute paths to all script files found.
     */
    QStringList getScriptList() {
        QStringList ret = getFileList("scripts/qsa", "qs");
        return ret;
    }

    /**
     * @return A list of absolute paths to all machine configuration files found.
     */
    QStringList getMachineList() {
        QStringList ret = getFileList("machines", "cxm");
        return ret;
    }

    /**
     * @return Absolute path to the documentation.
     */
    QString getDocPath() {
        QStringList lst = getDirectoryList("doc");

        if( !lst.isEmpty()) {
            return lst.first();
        }
        else {
            return QString();
        }
    }

    /**
     * @return The application name.
     */
    QString getAppName() {
        return appName;
    }

    /**
     * @return The application version.
     */
    QString getAppVersion() {
        return appVersion;
    }

    QStringList getFileList(const QString& subDirectory,
                            const QString& fileExtension);

    QStringList getDirectoryList(const QString& subDirectory);

    QStringList getLanguageList() {
        return languageList;
    }

    static QString languageToSymbol(const QString& lang);
    static QString symbolToLanguage(const QString& symb);

    static QString getEncoding(const QString& str);

    void loadTranslation(const QString& lang, const QString& langCmd);

    static bool test();

    /** Returns ISO code for given locale. Needed for win32 to convert
     *  from system encodings.
     */
    static QByteArray localeToISO(const QByteArray& locale);

private:
    RS_System() = default;
    void addLocale(RS_Locale *locale);
protected:
    QString appName;
    QString appVersion;
    QString appDirName;
    QString appDir;

    QStringList languageList;   //< List of available translations
    bool initialized {false};
    bool externalAppDir {false};
    QList<QSharedPointer<RS_Locale>> allKnownLocales;
};

#endif
