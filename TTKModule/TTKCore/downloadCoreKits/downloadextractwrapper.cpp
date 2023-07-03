#include "downloadextractwrapper.h"
#include "downloadbackgroundconfigmanager.h"
#include "downloadotherdefine.h"
#include "downloadimageutils.h"
#include "ttknumberdefine.h"

#include "ttkzip/zip.h"
#include "ttkzip/unzip.h"

#include <QFile>

#define WIN_NAME_MAX_LENGTH 256
#ifndef FILE_ATTRIBUTE_DIRECTORY
#define FILE_ATTRIBUTE_DIRECTORY 0x00000010
#endif

bool DownloadExtractWrapper::outputThunderSkin(QPixmap &image, const QString &input)
{
    const unzFile &zFile = unzOpen64(qPrintable(input));
    if(!zFile)
    {
        return false;
    }

    unz_file_info64 fInfo;
    unz_global_info64 gInfo;
    if(unzGetGlobalInfo64(zFile, &gInfo) != UNZ_OK)
    {
        unzClose(zFile);
        return false;
    }

    for(ZPOS64_T i = 0; i < gInfo.number_entry; ++i)
    {
        char com[MH_KB] = {0};
        char name[WIN_NAME_MAX_LENGTH] = {0};
        char ext[WIN_NAME_MAX_LENGTH] = {0};

        if(unzGetCurrentFileInfo64(zFile, &fInfo, name, sizeof(name), ext, WIN_NAME_MAX_LENGTH, com, MH_KB) != UNZ_OK ||
           unzOpenCurrentFile(zFile) != UNZ_OK)
        {
            break;
        }
		
        int size = 0;
        char dt[MH_KB] = {0};

        QByteArray buffer;
        if(QString(name).toLower().contains("image/bkg"))
        {
            while(true)
            {
                size= unzReadCurrentFile(zFile, dt, sizeof(dt));
                if(size <= 0)
                {
                    break;
                }
                buffer.append(dt, size);
            }
            image.loadFromData(buffer);
        }

        unzCloseCurrentFile(zFile);

        if(i < gInfo.number_entry - 1 && unzGoToNextFile(zFile) != UNZ_OK)
        {
            unzClose(zFile);
            return false;
        }
    }

    unzClose(zFile);
    return true;
}

bool DownloadExtractWrapper::outputSkin(DownloadBackgroundImage *image, const QString &input)
{
    const unzFile &zFile = unzOpen64(qPrintable(input));
    if(!zFile)
    {
        return false;
    }

    unz_file_info64 fInfo;
    unz_global_info64 gInfo;
    if(unzGetGlobalInfo64(zFile, &gInfo) != UNZ_OK)
    {
        unzClose(zFile);
        return false;
    }

    for(ZPOS64_T i = 0; i < gInfo.number_entry; ++i)
    {
        char com[MH_KB] = {0};
        char name[WIN_NAME_MAX_LENGTH] = {0};
        char ext[WIN_NAME_MAX_LENGTH] = {0};

        if(unzGetCurrentFileInfo64(zFile, &fInfo, name, sizeof(name), ext, WIN_NAME_MAX_LENGTH, com, MH_KB) != UNZ_OK ||
           unzOpenCurrentFile(zFile) != UNZ_OK)
        {
            break;
        }

        int size = 0;
        char dt[MH_KB] = {0};

        QByteArray buffer;
        if(QString(name).toLower().contains(SKN_FILE))
        {
            while(true)
            {
                size= unzReadCurrentFile(zFile, dt, sizeof(dt));
                if(size <= 0)
                {
                    break;
                }
                buffer.append(dt, size);
            }

            QPixmap pix;
            pix.loadFromData(buffer);
            image->m_pix = pix;
        }
        else if(QString(name).toLower().contains(XML_FILE))
        {
            while(true)
            {
                size= unzReadCurrentFile(zFile, dt, sizeof(dt));
                if(size <= 0)
                {
                    break;
                }
                buffer.append(dt, size);
            }

            DownloadSkinConfigManager manager;
            if(manager.fromByteArray(buffer))
            {
                DownloadSkinConfigItem item;
                manager.readBuffer(item);
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

bool DownloadExtractWrapper::inputSkin(DownloadBackgroundImage *image, const QString &output)
{
    const zipFile &zFile = zipOpen64(qPrintable(output), 0);
    if(!zFile)
    {
        return false;
    }

    const QString &prefix = QFileInfo(output).baseName();
    const int level = 5;

    zip_fileinfo fileInfo;
    memset(&fileInfo, 0, sizeof(fileInfo));

    zipOpenNewFileInZip(zFile, qPrintable(prefix + SKN_FILE), &fileInfo, nullptr, 0, nullptr, 0, nullptr, Z_DEFLATED, level);
    QByteArray data = TTK::Image::generatePixmapData(image->m_pix);
    zipWriteInFileInZip(zFile, data.constData(), data.length());
    zipCloseFileInZip(zFile);

    DownloadSkinConfigManager manager;
    manager.writeBuffer(image->m_item, TTK_IMAGE_FILE);
    data = manager.toByteArray();

    zipOpenNewFileInZip(zFile, qPrintable(prefix + XML_FILE), &fileInfo, nullptr, 0, nullptr, 0, nullptr, Z_DEFLATED, level);
    zipWriteInFileInZip(zFile, data.constData(), data.length());
    zipCloseFileInZip(zFile);
    QFile::remove(TTK_IMAGE_FILE);

    zipClose(zFile, nullptr);

    return true;
}
