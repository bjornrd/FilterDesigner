#ifndef FILTERTAB_H
#define FILTERTAB_H

#include <QWidget>

namespace Ui {
    class FilterTab;
}

class FilterTab : public QWidget
{
    Q_OBJECT

public:
    explicit FilterTab(QWidget *parent = nullptr);
    ~FilterTab();

private:
    Ui::FilterTab *ui;
};

#endif // FILTERTAB_H
