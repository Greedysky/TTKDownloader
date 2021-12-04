#ifndef DOWNLOADTOPAREAWIDGET_H
#define DOWNLOADTOPAREAWIDGET_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2022 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <QWidget>
#include <QTimer>
#include "ttkglobaldefine.h"

class DownloadRemoteWidget;
class DownloadBackgroundSkinDialog;

namespace Ui {
    class DownloadApplication;
}

/*! @brief The class of the app top area widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadTopAreaWidget : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadTopAreaWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadTopAreaWidget(QWidget *parent = nullptr);
    ~DownloadTopAreaWidget();

    /*!
     * Get class object instance.
     */
    static DownloadTopAreaWidget *instance();
    /*!
     * Set up app ui.
     */
    void setupUi(Ui::DownloadApplication* ui);

    /*!
     * Set background skin and alpha and list alpha parameter.
     */
    void setParameters(const QString &skin, int alpha);
    /*!
     * Get background skin name.
     */
    inline QString backgroundPath() const { return m_backgroundImagePath; }
    /*!
     * Get background skin alpha.
     */
    inline int backgroundAlpha() const { return m_backgroundAlpha; }
    /*!
     * Get background skin pixmap.
     */
    QPixmap rendererPixmap() const;

public Q_SLOTS:
    /*!
     * Show remote speed widget.
     */
    void showRemoteSpeedWidget();
    /*!
     * Close remote speed widget.
     */
    void closeRemoteSpeedWidget();
    /*!
     * Update remote speed text.
     */
    void updateRemoteSpeedText(int value);
    /*!
     * Current slider state changed.
     */
    void backgroundSliderStateChanged(bool state);
    /*!
     * Show change background skin dailog.
     */
    void showSkinChangedWindow();
    /*!
     * Current background transparent changed.
     */
    void backgroundTransparentChanged();
    /*!
     * Current background transparent changed by index.
     */
    void backgroundTransparentChanged(int index);
    /*!
     * Current background transparent changed by string.
     */
    void backgroundTransparentChanged(const QString &fileName);
    /*!
     * Resize current background skin when geometry changed.
     */
    void backgroundThemeChangedByResize();
    /*!
     * Current background skin changed by new path.
     */
    void backgroundSkinChanged(const QString &fileName);

protected:
    /*!
     * Draw window background rect.
     */
    void drawWindowBackgroundRect();
    /*!
     * Draw window background rect.
     */
    void drawWindowBackgroundRect(const QImage &image);
    /*!
     * Draw window background rect by qimage.
     */
    void drawWindowBackgroundRectString();
    /*!
     * Draw window background rect by picture.
     */
    void drawWindowBackgroundRectString(const QString &path);

    Ui::DownloadApplication *m_ui;

    DownloadRemoteWidget *m_remoteWidget;
    DownloadBackgroundSkinDialog *m_backgroundWidget;

    QImage m_backgroundImage;
    QString m_backgroundImagePath;
    int m_backgroundAlpha;

    static DownloadTopAreaWidget *m_instance;
};

#endif // DOWNLOADTOPAREAWIDGET_H
