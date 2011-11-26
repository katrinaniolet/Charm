#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>

#include "Core/Configuration.h"
#include "TabMainWindow.h"
#include "EventWindow.h"
#include "TasksWindow.h"
#include "TimeTrackingView/TimeTrackingWindow.h"
#include "ui_TabMainWindow.h"

TabMainWindow::TabMainWindow( QWidget* parent )
    : CharmWindow( tr("Charm"), parent ),
      ui(new Ui::TabMainWindow() )
    , m_eventWindow(0)
    , m_timeTracker(0)
    , m_tasksWindow(0)
    , m_eventEditMenu(0)
    , m_tasksEditMenu(0)
    , m_timeEditMenu(0)
    , m_eventToolbar(0)
    , m_tasksToolbar(0)
    , m_currentToolbar(0)
    , m_currentMenu(0)
{
    ui->setupUi(this);
    setWindowIdentifier("TabbedMainWindow");
    removeToolBar(toolBar());
    connect(ui->tabs,SIGNAL(currentChanged(int)),this,SLOT(tabChanged(int)));
}

void TabMainWindow::configurationChanged()
{
    if(Configuration::instance().tabbedInterface) {
        if(m_timeTracker && m_tasksWindow && m_eventWindow) {
            QWidget * tracker = m_timeTracker->centralWidget();
            QWidget * event = m_eventWindow->centralWidget();
            QWidget * tasks = m_tasksWindow->centralWidget();

            m_eventToolbar = m_eventWindow->toolBar();
            m_tasksToolbar = m_tasksWindow->toolBar();

            m_eventWindow->removeToolBar(m_eventToolbar);
            m_tasksWindow->removeToolBar(m_tasksToolbar);

            addToolBar(Qt::BottomToolBarArea,m_eventToolbar);
            addToolBar(Qt::BottomToolBarArea,m_tasksToolbar);
            m_eventToolbar->hide();
            m_tasksToolbar->hide();

            ui->tabs->addTab( tracker, m_timeTracker->windowName() );
            ui->tabs->addTab( event, m_eventWindow->windowName() );
            ui->tabs->addTab( tasks, m_tasksWindow->windowName() );

            m_timeEditMenu->menuAction()->setVisible(true);
            m_currentMenu = m_timeEditMenu;

            m_timeTracker->hide();
            m_eventWindow->hide();
            m_tasksWindow->hide();

            m_timeTracker->setCentralWidget(0);
            m_eventWindow->setCentralWidget(0);
            m_tasksWindow->setCentralWidget(0);

        }
        show();
    }
    else {
        if(m_timeTracker && m_tasksWindow && m_eventWindow) {
            if(ui->tabs->count()==3) {
                QWidget * tracker = ui->tabs->widget(0);
                QWidget * event = ui->tabs->widget(1);
                QWidget * tasks = ui->tabs->widget(2);

                ui->tabs->clear();

                m_tasksWindow->setCentralWidget(tasks);
                m_eventWindow->setCentralWidget(event);
                m_timeTracker->setCentralWidget(tracker);

                removeToolBar(m_eventToolbar);
                removeToolBar(m_tasksToolbar);

                m_eventWindow->addToolBar(m_eventToolbar);
                m_tasksWindow->addToolBar(m_tasksToolbar);

                m_eventToolbar->show();
                m_tasksToolbar->show();
                m_tasksWindow->show();
                m_eventWindow->show();
                m_timeTracker->show();
                tracker->show();
                event->show();
                tasks->show();

            }
        }
        hide();
    }
    CharmWindow::configurationChanged();
}

void TabMainWindow::tabChanged(int index)
{
    if(m_currentToolbar)
        m_currentToolbar->hide();
    if(m_currentMenu)
        m_currentMenu->menuAction()->setVisible(false);

    switch(index) {
        case 0:
            m_currentToolbar = 0;
            m_currentMenu = m_timeEditMenu;
            break;
        case 1:
            m_currentToolbar = m_eventToolbar;
            m_currentMenu = m_eventEditMenu;
            break;
        case 2:
            m_currentToolbar = m_tasksToolbar;
            m_currentMenu = m_tasksEditMenu;
            break;
    }
    if(m_currentToolbar)
        m_currentToolbar->show();
    m_currentMenu->menuAction()->setVisible(true);
}

void TabMainWindow::addTimeTracker(TimeTrackingWindow *window)
{
    m_timeTracker = window;
    m_timeEditMenu = window->editMenu();
}

void TabMainWindow::addEventEditor(EventWindow *window)
{
    m_eventWindow = window;
    m_eventEditMenu = window->editMenu();
    m_eventToolbar = window->toolBar();
}

void TabMainWindow::addTaskEditor(TasksWindow *window)
{
    m_tasksWindow = window;
    m_tasksEditMenu = window->editMenu();
    m_tasksToolbar = window->toolBar();
}

QMenu *TabMainWindow::editMenu() const
{
    return m_currentMenu;
}

void TabMainWindow::insertEditMenu()
{
    QMenu * menu = menuBar()->addMenu("");
    m_insertPoint = menu->menuAction();
    menu->menuAction()->setVisible(false);
    menuBar()->insertMenu(m_insertPoint,m_eventEditMenu);
    m_eventEditMenu->menuAction()->setVisible(false);
    menuBar()->insertMenu(m_insertPoint,m_tasksEditMenu);
    m_tasksEditMenu->menuAction()->setVisible(false);
    menuBar()->insertMenu(m_insertPoint,m_timeEditMenu);
    m_timeEditMenu->menuAction()->setVisible(true);
    m_currentMenu = m_timeEditMenu;
}


#include "TabMainWindow.moc"
