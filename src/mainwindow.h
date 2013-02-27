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
    bool player1Turn;
    bool player2Turn;
    bool gameOver;
    bool correctAnswer;
    QVector<int> questionIDVector;
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
    void setQuestionText();
    void enterGameplay();
    void updateTurns();
    int returnRandomNumber(int nMax);
};

#endif // MAINWINDOW_H
