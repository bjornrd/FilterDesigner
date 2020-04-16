#ifndef FILTERDESIGNER_H
#define FILTERDESIGNER_H

#include <QWidget>

namespace Ui {
class FilterDesigner;
}

class FilterDesigner : public QWidget
{
    Q_OBJECT

public:
    explicit FilterDesigner(QWidget *parent = nullptr);
    ~FilterDesigner();

private:
    Ui::FilterDesigner *ui;
};

#endif // FILTERDESIGNER_H
