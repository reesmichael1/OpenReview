#include <QtGui>
#include <QFile>
#include <time.h>
#include "mainwindow.h"

MainWindow::MainWindow()
{

    gameOver = false;
    questionIDVector = returnQuestionIDVector();

    questionText = new QTextEdit;
    questionText->setReadOnly(true);
    questionText->setMaximumWidth(300);
    questionText->setFixedWidth(350);

    answer1 = new QCheckBox;
    answer1->setAutoExclusive(true);

    answer2 = new QCheckBox;
    answer2->setAutoExclusive(true);

    answer3 = new QCheckBox;
    answer3->setAutoExclusive(true);

    answer4 = new QCheckBox;
    answer4->setAutoExclusive(true);

    submitButton = new QPushButton(tr("Submit"));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));

    QVBoxLayout *answerLayout = new QVBoxLayout;
    answerLayout->addWidget(questionText);
    answerLayout->addWidget(answer1);
    answerLayout->addWidget(answer2);
    answerLayout->addWidget(answer3);
    answerLayout->addWidget(answer4);
    answerLayout->addWidget(submitButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(answerLayout);

    centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);

    setWindowTitle(tr("OpenReview"));

    setQuestionText();

}

QVector<int> MainWindow::returnQuestionIDVector()
{
    QFile *questionBankFile = new QFile("questionbank.txt");
    dataStream = new QTextStream(questionBankFile);
    questionBankFile->open(QIODevice::Text | QIODevice::ReadOnly);

    QString dataString = dataStream->readLine();
    QStringList dataList;

    if (dataString != "")
    {
        while (dataString != "")
        {
            dataList = dataString.split(",");
            questionIDVector.append(dataList.at(0).toInt());
            dataString = dataStream->readLine();
        }
    }

    questionBankFile->close();
    return questionIDVector;
}

int MainWindow::returnRandomNumber(int nMax)
{

    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);

    int nRandomNumber = rand() % nMax;

    return nRandomNumber;

}

void MainWindow::setQuestionText()
{

    if (!gameOver)
    {

        if (!questionIDVector.isEmpty())
        {

            int questionLocationID = returnRandomNumber(questionIDVector.size());
            int questionID = questionIDVector.at(questionLocationID);

            int i = 0;
            while (questionIDVector.at(i) != questionID)
            {
                i++;
            }
            questionIDVector.remove(i);

            QFile *questionBankFile = new QFile("questionbank.txt");
            dataStream = new QTextStream(questionBankFile);

            questionBankFile->open(QIODevice::Text | QIODevice::ReadOnly);

            QStringList dataList;
            QString dataString = dataStream->readLine();
            while (dataString != "")
            {
                dataList = dataString.split(',');
                if (dataList.at(0).toInt() == questionID)
                {
                    questionText->setText(dataList.at(1));
                    answer1->setText(dataList.at(2));
                    answer2->setText(dataList.at(3));
                    answer3->setText(dataList.at(4));
                    answer4->setText(dataList.at(5));
                    dataString = dataStream->readLine();
                    dataList = dataString.split(',');
                }
                else
                {
                    dataString = dataStream->readLine();
                    dataList = dataString.split(',');
                }
            }
        }
        else
        {
            QMessageBox endBankError;
            endBankError.setText(tr("Error: You have reached the end of the question bank."));
            endBankError.exec();

            gameOver = true;
        }
    }

}

void MainWindow::submit()
{
    QFile *questionBankFile = new QFile("questionbank.txt");
    dataStream = new QTextStream(questionBankFile);

    questionBankFile->open(QIODevice::ReadOnly | QIODevice::Text);

    QString dataString = dataStream->readLine();
    QStringList dataList = dataString.split(',');

    while (dataList.at(1) != questionText->toPlainText())
    {
        dataString = dataStream->readLine();
        dataList = dataString.split(',');
    }

    QMessageBox answerResult;

    switch (dataList.at(6).toInt())
    {

    case 1:
    {
        if (answer1->isChecked())
        {
            answerResult.setText("Correct!");
            answerResult.exec();
            correctAnswer = true;
        }

        else
        {
            answerResult.setText(tr("Sorry, that's not correct. The correct answer is:\n%1")
                                 .arg(dataList.at(2)));
            answerResult.exec();
            correctAnswer = false;
        }

        answer1->setChecked(false);
    }
        break;

    case 2:
    {
        if (answer2->isChecked())
        {
            answerResult.setText("Correct!");
            answerResult.exec();
            correctAnswer = true;
        }

        else
        {
            answerResult.setText(tr("Sorry, that's not correct. The correct answer is:\n%1")
                                 .arg(dataList.at(3)));
            answerResult.exec();
            correctAnswer = false;
        }
        answer2->setChecked(false);
    }
        break;


    case 3:
    {
        if (answer3->isChecked())
        {
            answerResult.setText("Correct!");
            answerResult.exec();
            correctAnswer = true;
        }

        else
        {
            answerResult.setText(tr("Sorry, that's not correct. The correct answer is:\n%1")
                                 .arg(dataList.at(4)));
            answerResult.exec();
            correctAnswer = false;
        }
        answer3->setChecked(false);
    }
        break;

    case 4:
    {
        if (answer4->isChecked())
        {
            answerResult.setText("Correct!");
            answerResult.exec();
            correctAnswer = true;
        }

        else
        {
            answerResult.setText(tr("Sorry, that's not correct. The correct answer is:\n%1")
                                 .arg(dataList.at(5)));
            answerResult.exec();
            correctAnswer = false;
        }
        answer4->setChecked(false);
    }
        break;

    }

    questionBankFile->close();
    setQuestionText();
}
