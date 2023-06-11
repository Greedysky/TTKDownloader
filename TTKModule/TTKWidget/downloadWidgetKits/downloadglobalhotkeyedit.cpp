#include "downloadglobalhotkeyedit.h"
#include "downloadhotkeymanager.h"

#include <QKeyEvent>

DownloadGlobalHotKeyEdit::DownloadGlobalHotKeyEdit(QWidget *parent)
    : QLineEdit(parent)
{
    setReadOnly(true);
}

void DownloadGlobalHotKeyEdit::setHotKeyEnabled(bool state)
{
    setEnabled(state);
    setReadOnly(!state);
    setStyleSheet("color:#444444;");
}

void DownloadGlobalHotKeyEdit::keyPressEvent(QKeyEvent *event)
{
    setText(G_HOTKEY_PTR->toString(event->key(), event->modifiers()));
}
