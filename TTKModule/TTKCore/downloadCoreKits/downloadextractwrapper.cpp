#include "downloadextractwrapper.h"
#include "downloadbackgroundconfigmanager.h"
#include "downloadotherdefine.h"
#include "downloadimageutils.h"
#include "ttknumberdefine.h"

#include "ttkzip/zip.h"
#include "ttkzip/unzip.h"

#include <QFile>

#define WIN_NAME_MAX_LENGTH     256

bool DownloadExtractWrapper::outputThunderSkin(QPixmap &image, const QString &path)
{
    unzFile zFile = unzOpen64(path.toLocal8Bit().constData());
    if(nullptr == zFile)
    {
        return false;
    }

    unz_file_info64 fileInfo;
    unz_global_info64 gInfo;
    if (unzGetGlobalInfo64(zFile, &gInfo) != UNZ_OK)
    {
        return false;
    }

    for(ZPOS64_T i = 0; i < gInfo.number_entry; ++i)
    {
        char file[WIN_NAME_MAX_LENGTH] = {0};
        char ext[WIN_NAME_MAX_LENGTH] = {0};
        char com[MH_KB] = {0};

        if(unzGetCurrentFileInfo64(zFile, &fileInfo, file, sizeof(file), ext, WIN_NAME_MAX_LENGTH, com, MH_KB) != UNZ_OK)
        {
            break;
        }

        if(unzOpenCurrentFile(zFile) != UNZ_OK)
        {
            break;
        }

        char dt[MH_KB] = {0};
        int size = 0;

        QByteArray arrayData;
        if(QString(file).toLower().contains("image/bkg"))
        {
            while(true)
            {
                size= unzReadCurrentFile(zFile, dt, sizeof(dt));
                if(size <= 0)
                {
                    break;
                }
                arrayData.append(dt, size);
            }
            image.loadFromData(arrayData);
        }

        unzCloseCurrentFile(zFile);

        if(i < gInfo.number_entry - 1 && unzGoToNextFile(zFile) != UNZ_OK)
        {
            return false;
        }
    }
    unzClose(zFile);

    return true;
}

bool DownloadExtractWrapper::outputSkin(DownloadBackgroundImage *image, const QString &path)
{
    unzFile zFile = unzOpen64(path.toLocal8Bit().constData());
    if(nullptr == zFile)
    {
        return false;
    }

    unz_file_info64 fileInfo;
    unz_global_info64 gInfo;
    if (unzGetGlobalInfo64(zFile, &gInfo) != UNZ_OK)
    {
        return false;
    }

    for(ZPOS64_T i = 0; i < gInfo.number_entry; ++i)
    {
        char file[WIN_NAME_MAX_LENGTH] = {0};
        char ext[WIN_NAME_MAX_LENGTH] = {0};
        char com[MH_KB] = {0};

        if(unzGetCurrentFileInfo64(zFile, &fileInfo, file, sizeof(file), ext, WIN_NAME_MAX_LENGTH, com, MH_KB) != UNZ_OK)
        {
            break;
        }

        if(unzOpenCurrentFile(zFile) != UNZ_OK)
        {
            break;
        }

        char dt[MH_KB] = {0};
        int size = 0;

        QByteArray arrayData;
        if(QString(file).toLower().contains(SKN_FILE))
        {
            while(true)
            {
                size= unzReadCurrentFile(zFile, dt, sizeof(dt));
                if(size <= 0)
                {
                    break;
                }
                arrayData.append(dt, size);
            }

            QPixmap pix;
            pix.loadFromData(arrayData);
            image->m_pix = pix;
        }
        else if(QString(file).toLower().contains(XML_FILE))
        {
            while(true)
            {
                size= unzReadCurrentFile(zFile, dt, sizeof(dt));
                if(size <= 0)
                {
                    break;
                }
                arrayData.append(dt, size);
            }

            DownloadSkinConfigManager manager;
            DownloadSkinConfigItem item;
            if(manager.fromByteArray(arrayData))
            {
                manager.readSkinXMLConfig(item);
                image->m_item = item;
            }
        }

        unzCloseCurrentFile(zFile);

        if(i < gInfo.number_entry - 1 && unzGoToNextFile(zFile) != UNZ_OK)
        {
            return false;
        }
    }
    unzClose(zFile);

    return true;
}

bool DownloadExtractWrapper::inputSkin(DownloadBackgroundImage *image, const QString &path)
{
    zipFile zFile = zipOpen64(path.toLocal8Bit().constData(), 0);
    if(nullptr == zFile)
    {
        return false;
    }

    QString nPrefix = QFileInfo(path).baseName();
    int level = 5;

    zip_fileinfo fileInfo;
    memset(&fileInfo, 0, sizeof(fileInfo));

    zipOpenNewFileInZip(zFile, (nPrefix + SKN_FILE).toLocal8Bit().constData(), &fileInfo, nullptr, 0, nullptr, 0, nullptr, Z_DEFLATED, level);
    QByteArray data = DownloadUtils::Image::generatePixmapData(image->m_pix);
    zipWriteInFileInZip(zFile, data.constData(), data.length());
    zipCloseFileInZip(zFile);

    DownloadSkinConfigManager manager;
    manager.writeSkinXMLConfig(image->m_item, DOWNLOAD_IMAGE_FILE);
    data = manager.toByteArray();

    zipOpenNewFileInZip(zFile, (nPrefix + XML_FILE).toLocal8Bit().constData(), &fileInfo, nullptr, 0, nullptr, 0, nullptr, Z_DEFLATED, level);
    zipWriteInFileInZip(zFile, data.constData(), data.length());
    zipCloseFileInZip(zFile);
    QFile::remove(DOWNLOAD_IMAGE_FILE);

    zipClose(zFile, 0);

    return true;
}

bool DownloadExtractWrapper::outputText(QByteArray &data, const QString &path)
{
    unzFile zFile = unzOpen64(path.toLocal8Bit().constData());
    if(nullptr == zFile)
    {
        return false;
    }

    unz_file_info64 fileInfo;
    unz_global_info64 gInfo;
    if (unzGetGlobalInfo64(zFile, &gInfo) != UNZ_OK)
    {
        return false;
    }

    for(ZPOS64_T i = 0; i < gInfo.number_entry; ++i)
    {
        char file[WIN_NAME_MAX_LENGTH] = {0};
        char ext[WIN_NAME_MAX_LENGTH] = {0};
        char com[MH_KB] = {0};

        if(unzGetCurrentFileInfo64(zFile, &fileInfo, file, sizeof(file), ext, WIN_NAME_MAX_LENGTH, com, MH_KB) != UNZ_OK)
        {
            break;
        }

        if(unzOpenCurrentFile(zFile) != UNZ_OK)
        {
            break;
        }

        char dt[MH_KB] = {0};
        int size = 0;

        while(true)
        {
            size= unzReadCurrentFile(zFile, dt, sizeof(dt));
            if(size <= 0)
            {
                break;
            }
            data.append(dt, size);
        }

        unzCloseCurrentFile(zFile);

        if(i < gInfo.number_entry - 1 && unzGoToNextFile(zFile) != UNZ_OK)
        {
            return false;
        }
    }
    unzClose(zFile);

    return true;
}

bool DownloadExtractWrapper::inputText(const QByteArray &data, const QString &path)
{
    zipFile zFile = zipOpen64(path.toLocal8Bit().constData(), 0);
    if(nullptr == zFile)
    {
        return false;
    }

    QString nPrefix = QFileInfo(path).baseName();
    int level = 5;

    zip_fileinfo fileInfo;
    memset(&fileInfo, 0, sizeof(fileInfo));

    zipOpenNewFileInZip(zFile, nPrefix.toLocal8Bit().constData(), &fileInfo, nullptr, 0, nullptr, 0, nullptr, Z_DEFLATED, level);
    zipWriteInFileInZip(zFile, data.constData(), data.length());
    zipCloseFileInZip(zFile);

    zipClose(zFile, 0);

    return true;
}
