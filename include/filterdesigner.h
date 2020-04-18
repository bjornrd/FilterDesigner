#ifndef FILTERDESIGNER_H
#define FILTERDESIGNER_H

#include <QWidget>


/*
 * TODO: Choosing filter type - combobox?
 * TODO: Based on filter type - show cut-off frequencies
 * TODO: Based on pass- and stop-band choose level of gain and suppression
 * TODO: Ripple magnitude (dB) for equiripple filters
 * TODO: What filters to include?
 *
 *
 *
 *
 *
 */

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
