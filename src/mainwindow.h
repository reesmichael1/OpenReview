#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QFile>

class QCheckBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    
signals:
    
public slots:
    void submit();

private:
    QPushButton *submitButton;
    QSpinBox *player1Score;
    QSpinBox *player2Score;
    QCheckBox *answer1;
    QCheckBox *answer2;
    QCheckBox *answer3;
    QCheckBox *answer4;
    QTextStream *dataStream;
    QTextEdit *questionText;
    QWidget *centralWidget;
    QVector<int> returnQuestionIDVector();
    void readQuestionFromFile();
    void setQuestionText(QVector<int> questionIDVector);
    void enterGameplay();
    int returnRandomNumber(int nMax);
};

#endif // MAINWINDOW_H
