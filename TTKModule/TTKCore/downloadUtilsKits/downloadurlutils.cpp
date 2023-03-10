#include "downloadurlutils.h"

#include <QUrl>
#include <QProcess>
#include <QDesktopServices>
#ifdef Q_OS_WIN
#  include <Windows.h>
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
        p.replace('/', "\\");
        p = "/select," + p;
        ShellExecuteW(0, L"open", L"explorer.exe", p.toStdWString().c_str(), nullptr, SW_SHOWNORMAL);
        return true;
#endif
    }
    return QDesktopServices::openUrl(local ? QUrl::fromLocalFile(path) : QUrl(path, QUrl::TolerantMode));
}
