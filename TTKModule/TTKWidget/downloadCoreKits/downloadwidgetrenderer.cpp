#include "downloadwidgetrenderer.h"
#include "downloadextractwrapper.h"
#include "downloadbackgroundmanager.h"
#include "downloadbackgroundconfigmanager.h"

DownloadWidgetRenderer::DownloadWidgetRenderer()
    : m_background(nullptr)
{

}

void DownloadWidgetRenderer::setBackgroundPixmap(const QSize &size)
{
    if(!m_background)
    {
        return;
    }

    DownloadBackgroundImage image;
    if(DownloadExtractWrapper::outputSkin(&image, G_BACKGROUND_PTR->backgroundUrl()))
    {
        m_background->setPixmap(image.m_pix.scaled(size));
    }
    else
    {
        m_background->setPixmap(QPixmap(G_BACKGROUND_PTR->backgroundUrl()).scaled(size));
    }
}
