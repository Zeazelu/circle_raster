#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QSettings>
#include <view/TopWidget.h>
#include <Constants.h>
#include <view/UstawieniaDialog.h>

namespace SSw
{

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_model(),
    m_timer(),
    m_prefs()
{
    ui->setupUi(this);

    loadSettings();

    initTable();
    initMenubar();
    initTimer();
    initConnections();

    setWindowIcon(QIcon(QPixmap(BIG_MINE_PATH)));
    setWindowTitle(APP);
    newGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    event->accept();
}

void MainWindow::initTable()
{
    ui->m_view->setModel(&m_model);
    ui->m_view->activate();
}

void MainWindow::initMenubar()
{
    QMenu *fileMenu = new QMenu(tr("&Opcje"), this);

    QAction *newGameAction = fileMenu->addAction(tr("&Nowa Gra"));


    QAction *preferencesAction = fileMenu->addAction(tr("&Ustawienia"));


    QAction *quitAction = fileMenu->addAction(tr("&Exit"));


    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    QAction *aboutAction = helpMenu->addAction(tr("&Help"));

    menuBar()->addMenu(fileMenu);
    menuBar()->addSeparator();
    menuBar()->addMenu(helpMenu);

    connect(quitAction,         &QAction::triggered, qApp, &QApplication::quit);
    connect(newGameAction,      &QAction::triggered, this, &MainWindow::newGame);
    connect(preferencesAction,  &QAction::triggered, this, &MainWindow::showPreferences);
    connect(aboutAction,        &QAction::triggered, this, &MainWindow::showAboutBox);
}

void MainWindow::initTimer()
{
    m_timer.setInterval(1000);
}

void MainWindow::initConnections()
{
    // TopWidget connections
    connect(ui->m_view, &TableView::pressed,       ui->topWidget, &TopWidget::onPressed);
    connect(ui->m_view, &TableView::clicked,       ui->topWidget, &TopWidget::onReleased);
    connect(ui->m_view, &TableView::bothClicked,   ui->topWidget, &TopWidget::onReleased);
    connect(&m_timer,   &QTimer::timeout,           ui->topWidget, &TopWidget::incrementTimer);
    connect(&m_model,   &TableModel::mineDisplay, ui->topWidget, &TopWidget::setMinaDisplay);
    connect(&m_model,   &TableModel::gameLost,     ui->topWidget, &TopWidget::onLost);
    connect(&m_model,   &TableModel::gameWon,      ui->topWidget, &TopWidget::onWon);

    // TableModel connections
    connect(ui->m_view, &TableView::clicked,       &m_model, &TableModel::onTableClicked);
    connect(ui->m_view, &TableView::rightClicked,  &m_model, &TableModel::onRightClicked);
    connect(ui->m_view, &TableView::bothClicked,   &m_model, &TableModel::onBothClicked);

    // MainWindow connections
    connect(&m_model,        &TableModel::gameLost,         this, &MainWindow::onGameLost);
    connect(&m_model,        &TableModel::gameWon,          this, &MainWindow::onGameWon);
    connect(ui->topWidget,   &TopWidget::buttonClicked,     this, &MainWindow::newGame);
    connect(&m_model,        SIGNAL(gameStarted()),          &m_timer, SLOT(start()));
}

void MainWindow::newGame()
{
    m_timer.stop();

    m_model.resetModel(m_prefs.height, m_prefs.width, m_prefs.mine);
    ui->m_view->setModel(&m_model);
    ui->m_view->activate();
    ui->topWidget->resetTimer();
    ui->topWidget->setDefault();
    statusBar()->showMessage(tr("Good luck!"), MSG_TIMEOUT);
    updateView();
}

void MainWindow::onGameLost()
{
    m_timer.stop();
    ui->m_view->deactivate();
    statusBar()->showMessage(tr("You died."), MSG_TIMEOUT);
}

void MainWindow::onGameWon()
{
    m_timer.stop();
    ui->m_view->deactivate();
    statusBar()->showMessage(tr("You won!"), MSG_TIMEOUT);
}

void MainWindow::showPreferences()
{
    bool accepted = UstawieniaDialog::getPreferences(m_prefs, this);

    if (accepted)
    {
        newGame();
    }
}

void MainWindow::showAboutBox()
{
    QMessageBox::about(this, APP, tr("Rozbrajaj bomby<br>\
"));
}

void MainWindow::updateView()
{
    ui->m_view->adjustSizeToContents();
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void MainWindow::loadSettings()
{
    QSettings settings;
    m_prefs.width   = settings.value("width", int32_t(DEFAULT_WIDTH)).toInt();
    m_prefs.height  = settings.value("height", int32_t(DEFAULT_HEIGHT)).toInt();
    m_prefs.mine   = settings.value("mine", int32_t(DEFAULT_MINE)).toInt();
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("width", m_prefs.width);
    settings.setValue("height", m_prefs.height);
    settings.setValue("mine", m_prefs.mine);
}

} // namespace SSw

