#include "downloadsettingwidget.h"
#include "ui_downloadsettingwidget.h"
#include "downloadsettingmanager.h"
#include "downloadhotkeymanager.h"

#include <QFileDialog>
#include <QButtonGroup>
#include <QStyledItemDelegate>

DownloadFunctionTableWidget::DownloadFunctionTableWidget(QWidget *parent)
    : DownloadAbstractTableWidget(parent),
      m_listIndex(0)
{
    QHeaderView *headerview = horizontalHeader();
    headerview->resizeSection(0, 20);
    headerview->resizeSection(1, 20);
    headerview->resizeSection(2, 85);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setRowCount(3);
}

void DownloadFunctionTableWidget::addFunctionItems(int index, const DownloadFunctionItemList &items)
{
    m_listIndex = index;
    for(int i = 0; i < items.count(); ++i)
    {
        const DownloadFunctionItem &v = items[i];

        QTableWidgetItem *item = nullptr;
        setItem(i, 0, item = new QTableWidgetItem);

                      item = new QTableWidgetItem(QIcon(v.m_icon), {});
        QtItemSetTextAlignment(item, Qt::AlignCenter);
        setItem(i, 1, item);

                      item = new QTableWidgetItem(v.m_name);
        item->setForeground(QColor(80, 80, 80));
        QtItemSetTextAlignment(item, Qt::AlignLeft | Qt::AlignVCenter);
        setItem(i, 2, item);

        setRowHeight(i, 28);
    }
}

void DownloadFunctionTableWidget::itemCellClicked(int row, int column)
{
    Q_UNUSED(column);
    Q_EMIT currentIndexChanged(row + m_listIndex);
    selectRow(currentRow());
}

void DownloadFunctionTableWidget::leaveEvent(QEvent *event)
{
    QTableWidget::leaveEvent(event);
    itemCellEntered(-1, -1);
}


DownloadSettingWidget::DownloadSettingWidget(QWidget *parent)
    : DownloadAbstractMoveDialog(parent),
      m_ui(new Ui::DownloadSettingWidget)
{
    m_ui->setupUi(this);
    setBackgroundLabel(m_ui->background);

    ////////////////////////////////////////////////
    m_ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_delete_normal"));
    m_ui->topTitleCloseButton->setStyleSheet(TTK::UI::ToolButtonStyle03);
    m_ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->topTitleCloseButton->setToolTip(tr("Close"));
    connect(m_ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));

    ////////////////////////////////////////////////
    DownloadFunctionItemList items;
    items << DownloadFunctionItem(":/contextMenu/btn_setting", tr("Normal"))
          << DownloadFunctionItem(":/contextMenu/btn_keyboard", tr("Hotkey"))
          << DownloadFunctionItem(":/contextMenu/btn_download", tr("Dwonload"))
          << DownloadFunctionItem(":/contextMenu/btn_window", tr("Outlook"));
    m_ui->normalFunTableWidget->setRowCount(items.count());
    m_ui->normalFunTableWidget->addFunctionItems(0, items);

    m_ui->confirmButton->setStyleSheet(TTK::UI::PushButtonStyle03);
    m_ui->cancelButton->setStyleSheet(TTK::UI::PushButtonStyle03);
    m_ui->confirmButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->cancelButton->setCursor(QCursor(Qt::PointingHandCursor));
#ifdef Q_OS_UNIX
    m_ui->confirmButton->setFocusPolicy(Qt::NoFocus);
    m_ui->cancelButton->setFocusPolicy(Qt::NoFocus);
#endif
    connect(m_ui->normalFunTableWidget, SIGNAL(currentIndexChanged(int)), m_ui->stackedWidget, SLOT(setCurrentIndex(int)));
    connect(m_ui->normalFunTableWidget, SIGNAL(currentIndexChanged(int)), SLOT(clearFunctionTableSelection()));
    connect(m_ui->confirmButton, SIGNAL(clicked()), SLOT(saveParameterSettings()));
    connect(m_ui->cancelButton, SIGNAL(clicked()), SLOT(close()));

    ////////////////////////////////////////////////
    initNormalSettingWidget();
    initDownloadSettingWidget();
    initSkinSettingWidget();
    ////////////////////////////////////////////////
    selectFunctionTableIndex(0, 0);
}

DownloadSettingWidget::~DownloadSettingWidget()
{
    delete m_ui;
}

void DownloadSettingWidget::initialize()
{
    m_ui->downloadDirEdit->setText(G_SETTING_PTR->value(DownloadSettingManager::DownloadPathDir).toString());

    if(!G_SETTING_PTR->value(DownloadSettingManager::CloseEventMode).toBool())
    {
        m_ui->minimumRadioBox->setChecked(true);
    }
    else
    {
        m_ui->quitRadioBox->setChecked(true);
    }

    m_ui->startupCheckBox->setChecked(G_SETTING_PTR->value(DownloadSettingManager::StartUpMode).toBool());
    m_ui->startupRunCheckBox->setChecked(G_SETTING_PTR->value(DownloadSettingManager::StartUpRunMode).toBool());
    m_ui->slienceRunCheckBox->setChecked(G_SETTING_PTR->value(DownloadSettingManager::SlienceRunMode).toBool());

    //
    QStringList hotkeys = G_SETTING_PTR->value(DownloadSettingManager::HotkeyValue).toString().split(TTK_SPLITER);
    if(hotkeys.count() != G_HOTKEY_PTR->count())
    {
        hotkeys = G_HOTKEY_PTR->defaultKeys();
    }

    m_ui->item_S01->setText(hotkeys[0]);
    m_ui->item_S02->setText(hotkeys[1]);
    m_ui->item_S03->setText(hotkeys[2]);
    m_ui->globalHotkeyBox->setChecked(G_SETTING_PTR->value(DownloadSettingManager::HotkeyEnable).toBool());
    globalHotkeyBoxChanged(m_ui->globalHotkeyBox->isChecked());

    ///////////////////////////////////////////////////////////////////////////
    G_SETTING_PTR->value(DownloadSettingManager::DownloadLimit).toBool() ?
                         m_ui->downloadLimitRadioBox->click() : m_ui->downloadFullRadioBox->click();
    m_ui->defaultDownloadModeBox->setCurrentIndex(G_SETTING_PTR->value(DownloadSettingManager::DownloadMode).toInt());
    m_ui->downloadMaxCountBox->setCurrentIndex(G_SETTING_PTR->value(DownloadSettingManager::DownloadMaxCount).toInt());

    ///////////////////////////////////////////////////////////////////////////
    m_ui->effectLevelBox->setCurrentIndex(G_SETTING_PTR->value(DownloadSettingManager::SkinEffectLevel).toInt());

    m_ui->suspensionVisiableBox->setChecked(G_SETTING_PTR->value(DownloadSettingManager::SkinSuspension).toBool());
    m_ui->suspensionShowPerBox->setChecked(G_SETTING_PTR->value(DownloadSettingManager::SkinSuspensionValue).toBool());

}

void DownloadSettingWidget::clearFunctionTableSelection()
{
    m_ui->normalFunTableWidget->clearSelection();
}

void DownloadSettingWidget::globalHotkeyBoxChanged(bool state)
{
    m_ui->item_S01->setHotKeyEnabled(state);
    m_ui->item_S02->setHotKeyEnabled(state);
    m_ui->item_S03->setHotKeyEnabled(state);
}

void DownloadSettingWidget::downloadDirSelected()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setViewMode(QFileDialog::Detail);
    if(dialog.exec())
    {
        QString path = dialog.directory().absolutePath();
        if(!path.isEmpty())
        {
            m_ui->downloadDirEdit->setText(path + TTK_SEPARATOR);
        }
    }
}

void DownloadSettingWidget::downloadGroupSpeedLimit(int index)
{
    m_ui->downloadLimitSpeedComboBox->setEnabled(index);
    m_ui->uploadLimitSpeedComboBox->setEnabled(index);
}

void DownloadSettingWidget::saveParameterSettings()
{
    const bool hotkeyEnabled = m_ui->globalHotkeyBox->isChecked();
    G_SETTING_PTR->setValue(DownloadSettingManager::HotkeyEnable, hotkeyEnabled);

    if(hotkeyEnabled)
    {
        G_HOTKEY_PTR->setHotKey(0, m_ui->item_S01->text());
        G_HOTKEY_PTR->setHotKey(1, m_ui->item_S02->text());
        G_HOTKEY_PTR->setHotKey(2, m_ui->item_S03->text());

        G_HOTKEY_PTR->setEnabled(true);
        G_SETTING_PTR->setValue(DownloadSettingManager::HotkeyValue, G_HOTKEY_PTR->keys().join(TTK_SPLITER));
    }
    else
    {
        G_HOTKEY_PTR->unsetShortcut();
    }


    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadPathDir, m_ui->downloadDirEdit->text());
    G_SETTING_PTR->setValue(DownloadSettingManager::CloseEventMode, m_ui->quitRadioBox->isChecked());
    G_SETTING_PTR->setValue(DownloadSettingManager::StartUpMode, m_ui->startupCheckBox->isChecked());
    G_SETTING_PTR->setValue(DownloadSettingManager::StartUpRunMode, m_ui->startupRunCheckBox->isChecked());
    G_SETTING_PTR->setValue(DownloadSettingManager::SlienceRunMode, m_ui->slienceRunCheckBox->isChecked());


    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadLimit, m_ui->downloadLimitRadioBox->isChecked());
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadMode, m_ui->defaultDownloadModeBox->currentIndex());
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadMaxCount, m_ui->downloadMaxCountBox->currentIndex());


    G_SETTING_PTR->setValue(DownloadSettingManager::SkinEffectLevel, m_ui->effectLevelBox->currentIndex());
    G_SETTING_PTR->setValue(DownloadSettingManager::SkinSuspension, m_ui->suspensionVisiableBox->isChecked());
    G_SETTING_PTR->setValue(DownloadSettingManager::SkinSuspensionValue, m_ui->suspensionShowPerBox->isChecked());

    Q_EMIT parameterSettingChanged();
    close();
}

void DownloadSettingWidget::selectFunctionTableIndex(int row, int col)
{
    clearFunctionTableSelection();
    switch(row)
    {
        case 0:
            m_ui->normalFunTableWidget->selectRow(col); break;
        default: break;
    }
}

void DownloadSettingWidget::initNormalSettingWidget()
{
    m_ui->downloadDirEdit->setStyleSheet(TTK::UI::LineEditStyle01);
    m_ui->downloadDirButton->setStyleSheet(TTK::UI::PushButtonStyle03);
    m_ui->downloadDirButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->downloadDirEdit->setText(TDDOWNLOAD_DIR_FULL);

    m_ui->quitRadioBox->setStyleSheet(TTK::UI::RadioButtonStyle01);
    m_ui->minimumRadioBox->setStyleSheet(TTK::UI::RadioButtonStyle01);

    m_ui->startupCheckBox->setStyleSheet(TTK::UI::CheckBoxStyle01);
    m_ui->startupRunCheckBox->setStyleSheet(TTK::UI::CheckBoxStyle01);

    m_ui->slienceRunCheckBox->setStyleSheet(TTK::UI::CheckBoxStyle01);

#ifdef Q_OS_UNIX
    m_ui->downloadDirButton->setFocusPolicy(Qt::NoFocus);
    m_ui->quitRadioBox->setFocusPolicy(Qt::NoFocus);
    m_ui->minimumRadioBox->setFocusPolicy(Qt::NoFocus);
    m_ui->startupCheckBox->setFocusPolicy(Qt::NoFocus);
    m_ui->startupRunCheckBox->setFocusPolicy(Qt::NoFocus);
    m_ui->slienceRunCheckBox->setFocusPolicy(Qt::NoFocus);
#endif
    connect(m_ui->downloadDirButton, SIGNAL(clicked()), SLOT(downloadDirSelected()));

    m_ui->globalHotkeyBox->setStyleSheet(TTK::UI::CheckBoxStyle01);
#ifdef Q_OS_UNIX
    m_ui->globalHotkeyBox->setFocusPolicy(Qt::NoFocus);
#endif
    connect(m_ui->globalHotkeyBox, SIGNAL(clicked(bool)), SLOT(globalHotkeyBoxChanged(bool)));
}

void DownloadSettingWidget::initDownloadSettingWidget()
{
    m_ui->downloadFullRadioBox->setStyleSheet(TTK::UI::RadioButtonStyle01);
    m_ui->downloadLimitRadioBox->setStyleSheet(TTK::UI::RadioButtonStyle01);
#ifdef Q_OS_UNIX
    m_ui->downloadFullRadioBox->setFocusPolicy(Qt::NoFocus);
    m_ui->downloadLimitRadioBox->setFocusPolicy(Qt::NoFocus);
#endif
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(m_ui->downloadFullRadioBox, 0);
    buttonGroup->addButton(m_ui->downloadLimitRadioBox, 1);
    QtButtonGroupConnect(buttonGroup, this, downloadGroupSpeedLimit);

    m_ui->defaultDownloadModeBox->setItemDelegate(new QStyledItemDelegate(m_ui->defaultDownloadModeBox));
    m_ui->defaultDownloadModeBox->setStyleSheet(TTK::UI::ComboBoxStyle01 + TTK::UI::ItemView01);
    m_ui->defaultDownloadModeBox->view()->setStyleSheet(TTK::UI::ScrollBarStyle01);
    m_ui->downloadMaxCountBox->setItemDelegate(new QStyledItemDelegate(m_ui->downloadMaxCountBox));
    m_ui->downloadMaxCountBox->setStyleSheet(TTK::UI::ComboBoxStyle01 + TTK::UI::ItemView01);
    m_ui->downloadMaxCountBox->view()->setStyleSheet(TTK::UI::ScrollBarStyle01);
    m_ui->downloadLimitSpeedComboBox->setItemDelegate(new QStyledItemDelegate(m_ui->downloadLimitSpeedComboBox));
    m_ui->downloadLimitSpeedComboBox->setStyleSheet(TTK::UI::ComboBoxStyle01 + TTK::UI::ItemView01);
    m_ui->downloadLimitSpeedComboBox->view()->setStyleSheet(TTK::UI::ScrollBarStyle01);
    m_ui->uploadLimitSpeedComboBox->setItemDelegate(new QStyledItemDelegate(m_ui->uploadLimitSpeedComboBox));
    m_ui->uploadLimitSpeedComboBox->setStyleSheet(TTK::UI::ComboBoxStyle01 + TTK::UI::ItemView01);
    m_ui->uploadLimitSpeedComboBox->view()->setStyleSheet(TTK::UI::ScrollBarStyle01);

    m_ui->defaultDownloadModeBox->addItems({tr("Auto"), tr("Manual")});
    for(int i = 1; i <= 50; ++i)
    {
        m_ui->downloadMaxCountBox->addItem(QString::number(i));
    }

    QStringList downloadSpeed;
    downloadSpeed << "100" << "200" << "300" << "400" << "500" << "600"
                  << "700" << "800" << "900" << "1000" << "1100" << "1200";
    m_ui->downloadLimitSpeedComboBox->addItems(downloadSpeed);
    m_ui->uploadLimitSpeedComboBox->addItems(downloadSpeed);

}

void DownloadSettingWidget::initSkinSettingWidget()
{
    m_ui->suspensionVisiableBox->setStyleSheet(TTK::UI::CheckBoxStyle01);
    m_ui->suspensionShowPerBox->setStyleSheet(TTK::UI::CheckBoxStyle01);
#ifdef Q_OS_UNIX
    m_ui->suspensionVisiableBox->setFocusPolicy(Qt::NoFocus);
    m_ui->suspensionShowPerBox->setFocusPolicy(Qt::NoFocus);
#endif

    m_ui->effectLevelBox->setItemDelegate(new QStyledItemDelegate(m_ui->effectLevelBox));
    m_ui->effectLevelBox->setStyleSheet(TTK::UI::ComboBoxStyle01 + TTK::UI::ItemView01);
    m_ui->effectLevelBox->view()->setStyleSheet(TTK::UI::ScrollBarStyle01);

    m_ui->effectLevelBox->addItems({tr("Heigh"), tr("Low"), tr("Close")});
}
