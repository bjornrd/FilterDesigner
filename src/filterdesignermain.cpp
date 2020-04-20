#include "filterdesignermain.h"
#include "ui_filterdesignermain.h"

#include <QStyleFactory>
#include <QInputDialog>
#include <QMessageBox>

FilterDesignerMain::FilterDesignerMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FilterDesignerMain)
{
    ui->setupUi(this);

    // Remove the two dud-tabs that are created by the designer
    delete(ui->main_TabWidget->widget(1));
    delete(ui->main_TabWidget->widget(0));

    // Main Application setup
    mainAppSetup();

    // Set up tab-bar stylesheet
    setTabbarStyleSheet();

}

FilterDesignerMain::~FilterDesignerMain()
{
    delete ui;
}

void FilterDesignerMain::mainAppSetup()
{
    this->setWindowTitle("Filter Designer");
    setDarkUI();
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
        "padding: 1px;"
    "}"
    );


    ui->main_TabWidget->setStyleSheet(tabbarStyleSheet);
}



void FilterDesignerMain::on_actionNew_Filter_triggered()
{
    ui->main_TabWidget->addTab(new FilterTab(this), "Filter " + QString::number(ui->main_TabWidget->count() + 1) );

    ui->main_TabWidget->setCurrentIndex(ui->main_TabWidget->count()-1);

//    auto p = static_cast<FilterTab*>(ui->main_TabWidget->widget(0));
//    FilterAnalyzer* a = p->analyzer();
}

void FilterDesignerMain::on_main_TabWidget_tabCloseRequested(int index)
{
    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to close the tab: "  + ui->main_TabWidget->tabText(index) + " ?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    int ret = msgBox.exec();

    if(ret == QMessageBox::Ok)
        delete(ui->main_TabWidget->widget(index));
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
    this->close();
}
