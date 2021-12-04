#include "downloadurlutils.h"

#include <QUrl>
#include <QProcess>
#include <QDesktopServices>
#ifdef Q_OS_WIN
#  include <Windows.h>
#  include <shellapi.h>
#endif

bool DownloadUtils::Url::openUrl(const QString &exe, const QString &path)
{
#ifdef Q_OS_WIN
    ShellExecuteW(0, exe.toStdWString().c_str(), path.toStdWString().c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    return true;
#else
    Q_UNUSED(exe);
    return QProcess::startDetached(path, QStringList());
#endif
}

bool DownloadUtils::Url::openUrl(const QString &path, bool local)
{
#ifdef Q_OS_WIN
    if(path.isEmpty())
    {
        return false;
    }

    if(local)
    {
        QString p = path;
        p.replace('/', "\\");
        p = "/select," + p;
        ShellExecuteW(0, L"open", L"explorer.exe", p.toStdWString().c_str(), nullptr, SW_SHOWNORMAL);
        return true;
    }
#else
    Q_UNUSED(local);
#endif
    return QDesktopServices::openUrl(QUrl(path, QUrl::TolerantMode));
}
