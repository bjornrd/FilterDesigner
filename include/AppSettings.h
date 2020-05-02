/****************************************************************************
 * Copyright (C) 2020 Bjørn Rudi Dahl
 *
 * Written by: bjornrd
 * 28/04/2020/4/2020
 * me_brd@hotmail.com
 ****************************************************************************/
#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QWidget>

namespace Ui {
    class AppSettings;
}

class AppSettings : public QWidget
{
        Q_OBJECT

    public:
        explicit AppSettings(QWidget *parent = nullptr);
        ~AppSettings();


        // Set/Get
        bool askOnFilterClose() const;
        void setAskOnFilterClose(bool askOnFilterClose);

    private:
        Ui::AppSettings *ui;
};

#endif // APPSETTINGS_H
