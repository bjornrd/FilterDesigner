#include "filterdesigner.h"
#include "ui_filterdesigner.h"

#include <QStringList>
#include <QVector>

#include "windowdesigner.h"

FilterDesigner::FilterDesigner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilterDesigner)
{
    ui->setupUi(this);

    populateMethodCombobox();
}

FilterDesigner::~FilterDesigner()
{
    delete ui;
}

void FilterDesigner::populateMethodCombobox()
{
    ui->method_comboBox->clear();


    if(ui->window_radioButton->isChecked())
    {
        QStringList items;
        for(std::string  str : QVector<std::string>::fromStdVector(WindowTypesLiteral::Types) )
            items << QString::fromStdString(str);

        ui->method_comboBox->addItems(items);

    }

    else if (ui->lpf_radioButton->isChecked())
    {
        ui->method_comboBox->addItems(QStringList{"item1", "item2", "item3"});
    }

    else {
        // Should not be here but ok...
    }
}

void FilterDesigner::on_window_radioButton_clicked()
{
    populateMethodCombobox();
}

void FilterDesigner::on_lpf_radioButton_clicked()
{
    populateMethodCombobox();
}

void FilterDesigner::on_hpf_radioButton_clicked()
{
    populateMethodCombobox();
}

void FilterDesigner::on_bpf_radioButton_clicked()
{
    populateMethodCombobox();
}






