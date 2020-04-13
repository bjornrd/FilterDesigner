#include "filterdesignermain.h"
#include "ui_filterdesignermain.h"


FilterDesignerMain::FilterDesignerMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FilterDesignerMain)
{
    ui->setupUi(this);

    // Main Application setup
    mainAppSetup();


    // Set up tools
    setUpTools();

    ui->main_gridLayout->addWidget(_filterDesigner);
}

FilterDesignerMain::~FilterDesignerMain()
{
    delete ui;
}

void FilterDesignerMain::mainAppSetup()
{
    this->setWindowTitle("Filter Designer");
}

void FilterDesignerMain::setUpTools()
{
    _filterDesigner = new FilterDesigner(this);
}
