#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <clocale>
#include <QTimer>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->customplot->addGraph();
    ui->customplot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customplot->graph(0)->setLineStyle(QCPGraph::lsLine);

    ui->customplot->xAxis->setLabel("X");
    ui->customplot->yAxis->setLabel("Y");


    ui->customplot->xAxis->setRange(-6000, 100);
    ui->customplot->yAxis->setRange(-6000, 8000);




    ui->customplot->rescaleAxes();
    ui->customplot->replot();
    ui->customplot->update();

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_equally, SIGNAL(clicked()), this, SLOT(calculateExpression()));


}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::digit_numbers()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    ui->result_show->setText(ui->result_show->text() + button->text());

}


void MainWindow::on_pushButton_dot_clicked()
{
    if (!ui->result_show->text().contains('.') || !(ui->result_show->text().contains('.') && ui->result_show->text().right(1) == '.')) {

        ui->result_show->setText(ui->result_show->text() + ".");

    }

}






void MainWindow::on_pushButton_delete_clicked()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_div->setChecked(false);
    ui->pushButton_mul->setChecked(false);

    ui->result_show->setText("\0");

}





void MainWindow::on_pushButton_plus_clicked()
{
    ui->result_show->setText(ui->result_show->text() + '+');
}


void MainWindow::on_pushButton_minus_clicked()
{
    ui->result_show->setText(ui->result_show->text() + '-');
}


void MainWindow::on_pushButton_mul_clicked()
{
    ui->result_show->setText(ui->result_show->text() + '*');
}


void MainWindow::on_pushButton_div_clicked()
{
    ui->result_show->setText(ui->result_show->text() + '/');
}


void MainWindow::on_pushButton_pow_clicked()
{
    ui->result_show->setText(ui->result_show->text() + '^');
}

void MainWindow::on_pushButton_sin_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "sin");
}
void MainWindow::on_pushButton_cos_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "cos");
}
void MainWindow::on_pushButton_tan_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "tan");
}
void MainWindow::on_pushButton_asin_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "asin");
}
void MainWindow::on_pushButton_acos_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "acos");
}
void MainWindow::on_pushButton_atan_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "atan");
}
void MainWindow::on_pushButton_ln_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "ln");
}
void MainWindow::on_pushButton_log_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "log");
}
void MainWindow::on_pushButton_sqrt_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "sqrt");
}

void MainWindow::on_pushButton_bracket_open_clicked()
{
    ui->result_show->setText(ui->result_show->text() + '(');
}
void MainWindow::on_pushButton_bracket_close_clicked()
{
    ui->result_show->setText(ui->result_show->text() + ')');
}
void MainWindow::on_pushButton_mod_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "");
}


void MainWindow::clearResultField()
{
    ui->result_show->clear();
}

bool MainWindow::calculateExpression()
{
    QString expression = ui->result_show->text();

    if (expression.isEmpty()) {

        return false;
    }
    double x = 0.0;
    setlocale(LC_ALL, "C");
    QString x_line = ui->result_show->text();
    QByteArray bufferx = x_line.toUtf8();
    char* x_bu = bufferx.data();

    Stack* stack = NULL;
    if (check_error(x_bu)) {
        qDebug() << "ERROR: Invalid expression";
        ui->result_show->clear();

        ui->result_show->setText("ERROR");

        QTimer::singleShot(500, this, &MainWindow::clearResultField);

        return false;
    } else {
        parseExpression(&stack, x_bu, x);


        convertToReversePolishNotation(&stack);

        double result = evaluateExpression(stack);

        QString resultString = QString::number(result, 'g', 15);
        ui->result_show->setText(resultString);
    }

    return true;
}






void MainWindow::on_pushButton_x_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "x");
}





void MainWindow::on_pushButton_graph_clicked()
{
    double x_max = ui->input_x_last->text().toDouble();
    double x_min = ui->input_x_first->text().toDouble();

//    if (x_min > x_max) {
//        QMessageBox::warning(this, "Error", "First value of x cannot be greater than second value of x.");
//        ui->result_show->setText(ui->result_show->text() + "ERROR   ");
//        return;
//    }

    QVector<double> x_values, y_values;

    for (double x = x_min; x <= x_max; x += 0.1) {
        double y = calculate(ui->result_show->text().toStdString().c_str(), x);
        x_values.append(x);
        y_values.append(y);
    }

    ui->customplot->clearGraphs();
    ui->customplot->addGraph();
    ui->customplot->graph(0)->setData(x_values, y_values);
    ui->customplot->xAxis->setRange(x_min, x_max);
    ui->customplot->xAxis->setLabel("X");
    ui->customplot->yAxis->setLabel("Y");

    ui->customplot->xAxis->setRange(-6000, 100);
    ui->customplot->yAxis->setRange(-6000, 8000);

    ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->customplot->replot();
}



void MainWindow::on_pushButton_clear_clicked()
{

    ui->customplot->clearGraphs();


    ui->customplot->replot();
}



void MainWindow::on_pushButton_del_char_clicked()
{
    QString currentText = ui->result_show->text();
    if (!currentText.isEmpty()) {

        if (currentText.endsWith("asin") || currentText.endsWith("acos") || currentText.endsWith("atan") ) {
            currentText.chop(4);
        }else if ( currentText.endsWith("sin") || currentText.endsWith("cos") || currentText.endsWith("tan") ||
                   currentText.endsWith("ln") || currentText.endsWith("log") || currentText.endsWith("sqrt") || currentText.endsWith("mod")) {
            currentText.chop(3);
        } else {
            currentText.chop(1);
        }

        ui->result_show->setText(currentText);
    }
}



