#ifndef TABMAINWINDOW_H
#define TABMAINWINDOW_H

#include "CharmWindow.h"
#include "Core/ViewInterface.h"
class TasksWindow;
class EventWindow;
class TimeTrackingWindow;
class QToolBar;
class QMenu;
class QAction;

namespace Ui {
class TabMainWindow;
}

class TabMainWindow : public CharmWindow
{

Q_OBJECT

public:
    explicit TabMainWindow( QWidget* parent = 0 );
    void addTimeTracker( TimeTrackingWindow * window );
    void addEventEditor( EventWindow * window );
    void addTaskEditor( TasksWindow * window );
    /* reimpl */ QMenu * editMenu() const;
    /* reimpl */ void insertEditMenu();

public slots:
    /*reimp*/ void configurationChanged();
    void tabChanged( int index );

private:
    Ui::TabMainWindow *ui;
    TimeTrackingWindow * m_timeTracker;
    EventWindow * m_eventWindow;
    TasksWindow * m_tasksWindow;
    QToolBar * m_eventToolbar;
    QToolBar * m_tasksToolbar;
    QToolBar * m_currentToolbar;
    QMenu * m_eventEditMenu;
    QMenu * m_timeEditMenu;
    QMenu * m_tasksEditMenu;
    QMenu * m_currentMenu;
    QAction * m_insertPoint;

};

#endif // TABMAINWINDOW_H
