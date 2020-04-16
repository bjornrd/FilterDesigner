#include "filterdesigner.h"
#include "ui_filterdesigner.h"

FilterDesigner::FilterDesigner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilterDesigner)
{
    ui->setupUi(this);
}

FilterDesigner::~FilterDesigner()
{
    delete ui;
}
