#include "filtertab.h"
#include "ui_filtertab.h"

FilterTab::FilterTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilterTab)
{
    ui->setupUi(this);
}

FilterTab::~FilterTab()
{
    delete ui;
}