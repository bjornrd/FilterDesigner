/****************************************************************************
 * Copyright (C) 2020 Bjørn Rudi Dahl
 *
 * Written by: bjornrd
 * 28/04/2020/4/2020
 * me_brd@hotmail.com
 ****************************************************************************/
#include "AppSettings.h"
#include "ui_AppSettings.h"

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
