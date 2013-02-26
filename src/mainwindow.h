#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

class QCheckBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    
signals:
    
public slots:

private:
    QPushButton *submitButton;
    QSpinBox *player1Score;
    QSpinBox *player2Score;
    QCheckBox *answer1;
    QCheckBox *answer2;
    QCheckBox *answer3;
    QCheckBox *answer4;
    QWidget *centralWidget;
    QVector<int> returnQuestionIDVector();
};

#endif // MAINWINDOW_H
