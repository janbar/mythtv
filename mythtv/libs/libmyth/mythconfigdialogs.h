// -*- Mode: c++ -*-

#ifndef MYTH_CONFIG_DIALOGS_H
#define MYTH_CONFIG_DIALOGS_H

// Qt headers
#include <QObject>
#include <QString>

// MythTV headers
#include "mythexp.h"
#include "mythdialogs.h"
#include "mythstorage.h"
#include "mythconfiggroups.h"

class MPUBLIC ConfigurationDialogWidget : public MythDialog
{
    Q_OBJECT

        public:
    ConfigurationDialogWidget(MythMainWindow *parent,
                              const char     *widgetName) :
        MythDialog(parent, widgetName) { }

    void keyPressEvent(QKeyEvent *e) override; // QWidget

  signals:
    void editButtonPressed(void);
    void deleteButtonPressed(void);
};

/** \class ConfigurationDialog
 *  \brief A ConfigurationDialog that uses a ConfigurationGroup
 *         all children on one page in a vertical layout.
 */
class MPUBLIC ConfigurationDialog : public Storage
{
  public:
    ConfigurationDialog() : dialog(nullptr), cfgGrp(new ConfigurationGroup()) { }
    virtual ~ConfigurationDialog();

    // Make a modal dialog containing configWidget
    virtual MythDialog *dialogWidget(MythMainWindow *parent,
                                     const char     *widgetName);

    // Show a dialogWidget, and save if accepted
    virtual DialogCode exec(bool saveOnExec = true, bool doLoad = true);

    virtual void addChild(Configurable *child);

    virtual Setting *byName(const QString &settingName)
        { return cfgGrp->byName(settingName); }

    void setLabel(const QString &label);

    // Storage
    void Load(void) override { cfgGrp->Load(); } // Storage
    void Save(void) override { cfgGrp->Save(); } // Storage
    void Save(QString destination) override // Storage
        { cfgGrp->Save(destination); }

  protected:
    typedef std::vector<Configurable*> ChildList;

    ChildList           cfgChildren;
    std::vector<QWidget*>    childwidget;
    MythDialog         *dialog;
    ConfigurationGroup *cfgGrp;
};

/** \class ConfigurationWizard
 *  \brief A ConfigurationDialog that uses a ConfigurationGroup
 *         with one child per page.
 */
class MPUBLIC ConfigurationWizard : public ConfigurationDialog
{
  public:
    ConfigurationWizard() : ConfigurationDialog() {}

    MythDialog *dialogWidget(MythMainWindow *parent,
                             const char *widgetName) override; // ConfigurationDialog
};

#endif // MYTH_CONFIG_DIALOGS_H
