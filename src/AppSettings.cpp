/****************************************************************************
 * Copyright (C) 2020 Bjørn Rudi Dahl
 *
 * Written by: bjornrd
 * 28/04/2020/4/2020
 * me_brd@hotmail.com
 ****************************************************************************/
#include "appsettings.h"
#include "ui_appsettings.h"
#include "version.h"

AppSettings::AppSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppSettings)
{
    ui->setupUi(this);
    this->hide();
}

AppSettings::~AppSettings()
{
    delete ui;
}

bool AppSettings::askOnFilterClose() const
{
    return ui->askOnFilterClose_checkBox->isChecked();
}

void AppSettings::setAskOnFilterClose(bool askOnFilterClose)
{
    ui->askOnFilterClose_checkBox->setChecked(askOnFilterClose);
}

void AppSettings::showAbout()
{
    QMessageBox::about(nullptr, "About Filter Designer",
                       "A Qt Application by Bjørn Rudi Dahl\n"
                       "\n"
                       "bjorn.rudi.dahl@outlook.com\n"
                       "\n"
                       "Version: " + QString::number(version::major) + "." + QString::number(version::minor) + "." + QString::number(version::dev)
                       );
}

void AppSettings::on_about_pushButton_clicked()
{
    showAbout();
}
