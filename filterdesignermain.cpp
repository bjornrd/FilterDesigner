#include "filterdesignermain.h"
#include "ui_filterdesignermain.h"

#include <QStyleFactory>


FilterDesignerMain::FilterDesignerMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FilterDesignerMain)
{
    ui->setupUi(this);



    // Main Application setup
    mainAppSetup();

    // Set up tools
    setUpTools();

    // Set up tab-bar stylesheet
    setTabbarStyleSheet();

    // Add the Design- and Analysis- tabs
    ui->Design_tab  ->layout()->addWidget(_filterDesigner);
    ui->Analysis_tab->layout()->addWidget(_filterAnalyzer);

}

FilterDesignerMain::~FilterDesignerMain()
{
    delete ui;
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

    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");


    // Make sure the tabs also are affected by the palette
    ui->Analysis_tab->setAutoFillBackground(true);
    ui->Design_tab->setAutoFillBackground(true);
}

void FilterDesignerMain::setTabbarStyleSheet()
{
    QString tabbarStyleSheet =
                                "QTabWidget::pane {" /* The tab widget frame */
                                    "border-top: 2px solid #C2C7CB;"
                                "}"

                                "QTabBar::tab::hover{"
                                "background: #5E5F60"
                                "}"

                                "QTabBar::tab::selected{"
                                    "background: #5E5F60"
                                "}"

                                "QTabBar::tab {"
                                    "background: #1C1C1C;"
                                    "border: 1px solid #1C1C1C;"
                                    "border-bottom-color: #1C1C1C;" /* same as the pane color */
                                    "min-width: 8ex;"
                                    "min-height: 8ex;"
                                    "padding: 2px;"
                                "}";

    ui->mainTabWidget->setStyleSheet(tabbarStyleSheet);
}

void FilterDesignerMain::mainAppSetup()
{
    this->setWindowTitle("Filter Designer");


    setDarkUI();

}

void FilterDesignerMain::setUpTools()
{
    _filterDesigner = new FilterDesigner();
    _filterAnalyzer = new FilterAnalyzer();
}
