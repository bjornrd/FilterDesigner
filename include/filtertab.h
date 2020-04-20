#ifndef FILTERTAB_H
#define FILTERTAB_H

#include <QWidget>

#include "filterdesigner.h"
#include "filteranalyzer.h"

namespace Ui {
    class FilterTab;
}

class FilterTab : public QWidget
{
    Q_OBJECT

public:
    explicit FilterTab(QWidget *parent = nullptr);
    ~FilterTab();

    FilterDesigner* designer();
    FilterAnalyzer* analyzer();

private:
    Ui::FilterTab *ui;
};

#endif // FILTERTAB_H
