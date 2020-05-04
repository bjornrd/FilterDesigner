#include "filterdesignermain.h"
#include "ui_filterdesignermain.h"

#include <QStyleFactory>
#include <QInputDialog>
#include <QMessageBox>

FilterDesignerMain::FilterDesignerMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FilterDesignerMain)
    , _appSettings(new AppSettings(this))
{
    ui->setupUi(this);

    // Remove the two dud-tabs that are created by the designer
    delete(ui->main_TabWidget->widget(1));
    delete(ui->main_TabWidget->widget(0));

    // Main Application setup
    mainAppSetup();
}


FilterDesignerMain::~FilterDesignerMain()
{
    delete ui;
}


void FilterDesignerMain::mainAppSetup()
{
    this->setWindowTitle("Filter Designer");
    this->installEventFilter(this);

    setDarkUI();
    setTabbarStyleSheet();
    setOtherStyleSheet();

    readSettings();
}


void FilterDesignerMain::setDarkUI()
{
    qApp->setStyle(QStyleFactory::create("fusion"));

    QPalette darkPalette;
    QColor ActiveTextColor      = QColor(200,200,200);
    QColor DisabledTextColor    = QColor(110,110,110);

    // Enabled
    darkPalette.setColor(                    QPalette::AlternateBase,   QColor(29,27,27));
    darkPalette.setColor(                    QPalette::Base,            QColor(12,12,12));
    darkPalette.setColor(                    QPalette::BrightText,      Qt::red);
    darkPalette.setColor(                    QPalette::Button,          QColor(64,64,64));
    darkPalette.setColor(                    QPalette::ButtonText,      ActiveTextColor);
    darkPalette.setColor(                    QPalette::Link,            QColor(42, 130, 218));
    darkPalette.setColor(                    QPalette::Text,            ActiveTextColor);
    darkPalette.setColor(                    QPalette::ToolTipBase,     ActiveTextColor);
    darkPalette.setColor(                    QPalette::ToolTipText,     ActiveTextColor);
    darkPalette.setColor(                    QPalette::Window,          QColor(24,24,24));
    darkPalette.setColor(                    QPalette::WindowText,      ActiveTextColor);
    darkPalette.setColor(                    QPalette::Highlight,       QColor(42, 130, 218));
    darkPalette.setColor(                    QPalette::HighlightedText, Qt::black);

    // Disabled
    darkPalette.setColor(QPalette::Disabled, QPalette::AlternateBase,   QColor(25,23,23));
    darkPalette.setColor(QPalette::Disabled, QPalette::Base,            QColor(11,11,11));
    darkPalette.setColor(QPalette::Disabled, QPalette::BrightText,      Qt::red);
    darkPalette.setColor(QPalette::Disabled, QPalette::Button,          QColor(44,44,44));
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText,      Qt::gray);
    darkPalette.setColor(QPalette::Disabled, QPalette::Link,            QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Disabled, QPalette::Text,            Qt::gray);
    darkPalette.setColor(QPalette::Disabled, QPalette::ToolTipBase,     DisabledTextColor);
    darkPalette.setColor(QPalette::Disabled, QPalette::ToolTipText,     DisabledTextColor);
    darkPalette.setColor(QPalette::Disabled, QPalette::Window,          QColor(20,20,20));
    darkPalette.setColor(QPalette::Disabled, QPalette::WindowText,      DisabledTextColor);



    qApp->setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
}


void FilterDesignerMain::setTabbarStyleSheet()
{
    QString tabbarStyleSheet =
    (
    "QTabWidget::pane {" /* The tab widget frame */
        "border-top: 2px solid #C2C7CB;"
    "}"

    "QTabBar::tab::hover{"
    "background: #484852"
    "}"

    "QTabBar::tab::selected{"
        "background: #484852"
    "}"

    "QTabBar::tab {"
        "background: #1C1C1C;"
        "border: 1px solid #1C1C1C;"
        "border-bottom-color: #1C1C1C;" /* same as the pane color */
        "min-width: 4em;"
        "min-height: 1.3em;"
    "}"
    );


    ui->main_TabWidget->setStyleSheet(tabbarStyleSheet);
}


void FilterDesignerMain::setOtherStyleSheet()
{
    QString pushButtonStyleSheet = "QPushButton{"
                                            "border: 1px solid red;"
                                            "min-width: 6em;"
                                            "min-height: 2em;"
                                    "}"

                                    "QPushButton:hover {background: #484852;}";

    ui->newFilter_pushButton->setStyleSheet(pushButtonStyleSheet);
}


bool FilterDesignerMain::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);

    bool retval = false;
    if(event->type() == QEvent::Resize)
    {
        if(_appSettings->isVisible())
        {
            _appSettings->resize(QSize(_appSettings->width(), this->height()));
            _appSettings->move(QPoint(this->width()  - _appSettings->width(), 0));
        }
        retval = true;
    }

    if(event->type() == QEvent::MouseButtonPress)
    {
        // Hide the uiSettings-widget if we're not clicking directly inside it
        if (!_appSettings->rect().contains(_appSettings->mapFromGlobal(QCursor::pos()))) {
            hideAppSettings();
            retval = true;
        }
    }

    if(event->type() == QEvent::KeyPress)
    {
        auto keyEvent = dynamic_cast<QKeyEvent*>(event);

        if(keyEvent->key() == Qt::Key::Key_Escape)
        {
            hideAppSettings();
            retval = true;
        }
    }

    return retval;
}

void FilterDesignerMain::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}


void FilterDesignerMain::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    settings.beginGroup("FilterDesigner");
    // Geometry
    const QByteArray geometry = settings.value("FilterDesignerGeometry", QByteArray()).toByteArray();

    if (geometry.isEmpty())
    {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        this->resize(availableGeometry.width()/3, availableGeometry.height()/2);

        this->move((availableGeometry.width() - this->width()) / 2,
                   (availableGeometry.height() - this->height()) / 2);

    } else {
        this->restoreGeometry(geometry);
    }


    settings.endGroup();

    // Apply any additional settings
    applySettings();
}

void FilterDesignerMain::applySettings()
{
    // Currently empty until we have something to apply
}

void FilterDesignerMain::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    settings.beginGroup("FilterDesigner");

    // Geometry
    settings.setValue("FilterDesignerGeometry", this->saveGeometry());

    settings.endGroup();
}


void FilterDesignerMain::on_actionNew_Filter_triggered()
{
    if(ui->main_TabWidget->count() == 0)
        ui->stackedWidget->setCurrentIndex(1);

    ui->main_TabWidget->addTab(new FilterTab(this), "Filter " + QString::number(ui->main_TabWidget->count() + 1) );
    ui->main_TabWidget->setCurrentIndex(ui->main_TabWidget->count()-1);
}


void FilterDesignerMain::on_main_TabWidget_tabCloseRequested(int index)
{
    if(_appSettings->askOnFilterClose())
    {
        QCheckBox* cb = new QCheckBox("Don't Show This Again");
        QMessageBox msgBox(this);
        msgBox.setText("Are you sure you want to close the tab: "  + ui->main_TabWidget->tabText(index) + " ?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setCheckBox(cb);

        QObject::connect(cb, &QCheckBox::stateChanged, [this](int state)
        {
            if (static_cast<Qt::CheckState>(state) == Qt::CheckState::Checked) {
                _appSettings->setAskOnFilterClose(false);

            } else { // If we check/uncheck the cb, then we need to reset the ask-on-filter-close
                _appSettings->setAskOnFilterClose(true);
            }
        });

        if(msgBox.exec() == QMessageBox::Ok)
            delete(ui->main_TabWidget->widget(index));

    } else {

        delete(ui->main_TabWidget->widget(index));
    }

    if(ui->main_TabWidget->count() == 0)
        ui->stackedWidget->setCurrentIndex(0);

}


void FilterDesignerMain::on_main_TabWidget_tabBarDoubleClicked(int index)
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Tab label"),
                                         tr("New Tab Label:"), QLineEdit::Normal,
                                         "Filter / Window", &ok);

    if(ok)
        ui->main_TabWidget->setTabText(index, text);
}


void FilterDesignerMain::on_actionExit_triggered()
{
    writeSettings();
    this->close();
}

void FilterDesignerMain::on_newFilter_pushButton_clicked()
{
    ui->main_TabWidget->addTab(new FilterTab(this), "Filter " + QString::number(ui->main_TabWidget->count() + 1) );
    ui->main_TabWidget->setCurrentIndex(ui->main_TabWidget->count()-1);

    ui->stackedWidget->setCurrentIndex(1);
}

void FilterDesignerMain::showAppSettings()
{
    _appSettings->resize(QSize(_appSettings->width(), this->height()));
    _appSettings->show();
    _appSettings->raise();

    QPropertyAnimation *animation = new QPropertyAnimation(_appSettings, "geometry");
    animation->setDuration(300);

    double startX, endX, Y, width, height;
    startX = this->width();
    endX   = this->width()  - _appSettings->width();
    Y      = 0;
    width  = _appSettings->width();
    height = _appSettings->height();

    QRect startRect(startX,Y,width,height);
    QRect endRect(endX,Y,width,height);
    animation->setStartValue(startRect);
    animation->setEndValue(endRect);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start(QPropertyAnimation::DeleteWhenStopped);

    ui->centralwidget->setDisabled(true);

    // Blur the tab-widgets when showing the UI-settings
    QGraphicsBlurEffect* blurEffect = new QGraphicsBlurEffect();
    blurEffect->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
    blurEffect->setBlurRadius(5);
    ui->centralwidget->setGraphicsEffect(blurEffect);
}


void FilterDesignerMain::hideAppSettings()
{
    QPropertyAnimation *animation = new QPropertyAnimation(_appSettings, "geometry");
    animation->setDuration(300);

    double startX, endX, Y, width, height;
    startX = this->width()  - _appSettings->width();
    endX   = this->width();
    Y      = 0;
    width  = _appSettings->width();
    height = _appSettings->height();

    QRect startRect(startX,Y,width,height);
    QRect endRect(endX,Y,width,height);
    animation->setStartValue(startRect);
    animation->setEndValue(endRect);
    animation->setEasingCurve(QEasingCurve::InCubic);
    animation->start();

    connect(animation, &QPropertyAnimation::finished, [this](){
        _appSettings->hide();
    });

    ui->centralwidget->setEnabled(true);
    ui->centralwidget->setGraphicsEffect(NULL);
}



void FilterDesignerMain::on_actionSettings_triggered()
{
    if(_appSettings->isHidden())
        showAppSettings();
    else
        hideAppSettings();
}

void FilterDesignerMain::on_actionAbout_triggered()
{
    _appSettings->showAbout();
}
