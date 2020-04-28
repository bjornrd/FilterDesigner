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

    private slots:
        void on_window_radioButton_clicked();
        void on_lpf_radioButton_clicked();
        void on_hpf_radioButton_clicked();
        void on_bpf_radioButton_clicked();




    private:
        void populateMethodCombobox();

    private:
        Ui::FilterDesigner *ui;
};

#endif // FILTERDESIGNER_H
