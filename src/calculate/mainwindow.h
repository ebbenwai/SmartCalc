#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


extern "C" {
    #include "../calc.h"
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void digit_numbers();
    void on_pushButton_dot_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_plus_clicked();
    void on_pushButton_minus_clicked();
    void on_pushButton_mul_clicked();
    void on_pushButton_div_clicked();
    void on_pushButton_pow_clicked();
    void on_pushButton_sin_clicked();
    void on_pushButton_cos_clicked();
    void on_pushButton_tan_clicked();
    void on_pushButton_asin_clicked();
    void on_pushButton_acos_clicked();
    void on_pushButton_atan_clicked();
    void on_pushButton_sqrt_clicked();
    void on_pushButton_ln_clicked();
    void on_pushButton_log_clicked();
    void on_pushButton_bracket_open_clicked();
    void on_pushButton_bracket_close_clicked();
    void on_pushButton_mod_clicked();
    bool calculateExpression();
    void clearResultField();







    void on_pushButton_x_clicked();
    void on_pushButton_graph_clicked();
    void on_pushButton_clear_clicked();

    void on_pushButton_del_char_clicked();
};
#endif // MAINWINDOW_H
