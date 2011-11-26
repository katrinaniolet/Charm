#ifndef CHARMPREFERENCES_H
#define CHARMPREFERENCES_H

#include <QDialog>

#include "Core/Configuration.h"
#include "ui_CharmPreferences.h"

class CharmPreferences : public QDialog
{
    Q_OBJECT

public:
    explicit CharmPreferences( const Configuration& config,
                               QWidget* parent = 0 );
    ~CharmPreferences();

    bool oneEventAtATime() const;
    bool eventsInLeafsOnly() const;
    bool always24hEditing() const;
    Configuration::DurationFormat durationFormat() const;
    bool detectIdling() const;
    bool animatedTrayIcon() const;
    bool tabbedInterface() const;

    Qt::ToolButtonStyle toolButtonStyle() const;

    Configuration::TaskTrackerFontSize taskTrackerFontSize() const;

private:
    Ui::CharmPreferences m_ui;
};

#endif
