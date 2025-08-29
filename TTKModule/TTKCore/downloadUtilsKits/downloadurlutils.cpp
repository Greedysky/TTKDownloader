#include "downloadurlutils.h"
#include "ttkplatformsystem.h"

#include <QUrl>
#include <QProcess>
#include <QDesktopServices>
#ifdef Q_OS_WIN
#  define WIN32_LEAN_AND_MEAN
#  include <qt_windows.h>
#  include <shellapi.h>
#endif

bool TTK::Url::openUrl(const QString &path, bool local)
{
    if(path.isEmpty())
    {
        return false;
    }

    if(local)
    {
#ifdef Q_OS_WIN
        QString p = path;
        p.replace(TTK_SEPARATOR, TTK_WSEPARATOR);
        p = "/select," + p;
        ShellExecuteW(0, L"open", L"explorer.exe", p.toStdWString().c_str(), nullptr, SW_SHOWNORMAL);
        return true;
#elif defined Q_OS_UNIX
        if(TTKPlatformSystem::systemName() == TTKPlatformSystem::System::LinuxUbuntu)
        {
            return QProcess::startDetached("nautilus", {path});
        }
#endif
    }
    return QDesktopServices::openUrl(local ? QUrl::fromLocalFile(path) : QUrl(path, QUrl::TolerantMode));
}
