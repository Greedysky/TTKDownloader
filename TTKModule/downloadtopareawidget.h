#ifndef DOWNLOADTOPAREAWIDGET_H
#define DOWNLOADTOPAREAWIDGET_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2025 Greedysky Studio

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
#include "ttkmoduleexport.h"

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
public:
    /*!
     * Object constructor.
     */
    explicit DownloadTopAreaWidget(QWidget *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadTopAreaWidget();

    /*!
     * Get class object instance.
     */
    static DownloadTopAreaWidget *instance();
    /*!
     * Set up app ui.
     */
    void setupUi(Ui::DownloadApplication *ui);

    /*!
     * Set background skin and alpha and list alpha parameter.
     */
    void setBackgroundParameter();
    /*!
     * Get background skin name.
     */
    inline QString backgroundPath() const noexcept { return m_backgroundImagePath; }
    /*!
     * Get background skin transparent.
     */
    inline int backgroundTransparent() const noexcept { return m_backgroundTransparent; }
    /*!
     * Get background skin pixmap.
     */
    const QPixmap& renderPixmap() const;

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
    void backgroundAnimationChanged(bool state);
    /*!
     * Show change background skin dialog.
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

private:
    /*!
     * Draw window background.
     */
    void drawWindowBackground();
    /*!
     * Draw window background rect.
     */
    void drawWindowBackground(const QImage &image);
    /*!
     * Draw window background rect by qimage.
     */
    void drawWindowBackgroundByImage();
    /*!
     * Draw window background rect by path.
     */
    void drawWindowBackgroundByPath(const QString &path);

    Ui::DownloadApplication *m_ui;

    DownloadRemoteWidget *m_remoteWidget;
    DownloadBackgroundSkinDialog *m_backgroundWidget;

    QImage m_backgroundImage;
    QString m_backgroundImagePath;
    int m_backgroundTransparent;

    static DownloadTopAreaWidget *m_instance;

};

#endif // DOWNLOADTOPAREAWIDGET_H
