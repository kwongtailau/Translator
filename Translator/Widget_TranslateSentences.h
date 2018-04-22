#ifndef WIDGET_TRANSLATESENTENCES_H
#define WIDGET_TRANSLATESENTENCES_H

#include <QWidget>
#include "Func_TranslateFromNet.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QTextEdit>
#include <QString>
#include <QMessageBox>
class Widget_TranslateSentences : public QWidget
{
    Q_OBJECT
public:
    explicit Widget_TranslateSentences(QWidget *parent = nullptr);

public:
    QGroupBox * createGroupBoxTranslateSentences();
private slots:
    //对应Func_TranslateFromNet类的各种信号对应的槽函数
    void receiveValueTranslation(QString stringTranslation);
    void receiveValuePhonetic(QString stringPhonetic);
    void receiveValueExplain(QString stringExplain);
    void receiveValueQuery(QString stringQuery);

    void clickButtonTranslate();    //翻译
    void clickButtonClear();        //清空
private:
    Func_TranslateFromNet * translateByYouDao;  //取有道API
    QGroupBox * groupBoxTranslateSentences;     //返回页面给主界面

    QPushButton * buttonTranslate;
    QPushButton * buttonClear;

    QTextEdit * textEditOutput;
    QTextEdit * textEditInput;

    QHBoxLayout * layoutMiddle;
    QVBoxLayout * layoutMain;
};

#endif // WIDGET_TRANSLATESENTENCES_H
