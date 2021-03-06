#ifndef LOGVIEWER_H_
#define LOGVIEWER_H_

// qt
#include <QTimer>

// myth
#include <mythscreentype.h>

class MythUIButton;
class MythUIButtonList;
class MythUIText;

void showLogViewer(void);

class LogViewer : public MythScreenType
{
  Q_OBJECT

  public:

    explicit LogViewer(MythScreenStack *parent);
   ~LogViewer(void);

    bool Create(void) override; // MythScreenType
    bool keyPressEvent(QKeyEvent *e) override; // MythScreenType

    void setFilenames(const QString &progressLog, const QString &fullLog);

  protected slots:
    void cancelClicked(void);
    void updateClicked(void);
    void updateTimerTimeout(void);
    void toggleAutoUpdate(void);
    bool loadFile(QString filename, QStringList &list, int startline);
    void showProgressLog(void);
    void showFullLog(void);
    void ShowMenu(void) override; // MythScreenType
    void updateLogItem(MythUIButtonListItem *item);

  private:
    void Init(void) override; // MythScreenType
    QString getSetting(const QString &key);

    bool                m_autoUpdate;
    int                 m_updateTime;
    QTimer             *m_updateTimer;

    QString             m_currentLog;
    QString             m_progressLog;
    QString             m_fullLog;

    MythUIButtonList   *m_logList;
    MythUIText         *m_logText;

    MythUIButton       *m_exitButton;
    MythUIButton       *m_cancelButton;
    MythUIButton       *m_updateButton;
};

#endif
