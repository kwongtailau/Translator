#include "Widget_TranslateSentences.h"

Widget_TranslateSentences::Widget_TranslateSentences(QWidget *parent) : QWidget(parent)
{
    //初始化基本组件
    translateByYouDao = new Func_TranslateFromNet(this);
    groupBoxTranslateSentences = new QGroupBox();
    buttonTranslate = new QPushButton("翻译");
    buttonClear = new QPushButton("清空");
    textEditOutput = new QTextEdit();
    textEditInput = new QTextEdit();
    //在输入框中显示提示的文字信息
    textEditInput->setPlaceholderText("原文-支持中英互译以及英日韩法俄西到中文的翻译");
    textEditInput->setFixedSize(428, 125);
    textEditOutput->setPlaceholderText("译文");
    textEditOutput->setFixedSize(428, 125);
    //设置不能编辑显示的文本框
    textEditOutput->setReadOnly(true);

    //初始化布局管理
    //水平布局
    layoutMiddle = new QHBoxLayout();
    layoutMiddle->addStretch();
    layoutMiddle->addWidget(buttonClear);
    layoutMiddle->addWidget(buttonTranslate);
    //垂直布局
    layoutMain = new QVBoxLayout();
    layoutMain->addWidget(textEditInput);
    layoutMain->addLayout(layoutMiddle);
    layoutMain->addWidget(textEditOutput);

    //连接信号与槽
    connect(translateByYouDao, SIGNAL(signalValueTranslationFinished(QString)), this, SLOT(receiveValueTranslation(QString)));
    connect(translateByYouDao, SIGNAL(signalValuePhoneticFinished(QString)), this, SLOT(receiveValuePhonetic(QString)));
    connect(translateByYouDao, SIGNAL(signalValueExplainsFinished(QString)), this, SLOT(receiveValueExplain(QString)));
    connect(translateByYouDao, SIGNAL(signalValueQueryFinished(QString)), this, SLOT(receiveValueQuery(QString)));
    connect(buttonTranslate, SIGNAL(clicked()), this, SLOT(clickButtonTranslate()));
    connect(buttonClear, SIGNAL(clicked()), this, SLOT(clickButtonClear()));

}

/*向主窗口返回长句翻译页面*/
QGroupBox *Widget_TranslateSentences::createGroupBoxTranslateSentences()
{
    groupBoxTranslateSentences = new QGroupBox(this);
    groupBoxTranslateSentences->setLayout(layoutMain);
    return groupBoxTranslateSentences;
}

/*显示翻译结果的槽函数*/
void Widget_TranslateSentences::receiveValueTranslation(QString stringTranslation)
{
    textEditOutput->setText(stringTranslation);
}

void Widget_TranslateSentences::receiveValuePhonetic(QString stringPhonetic)
{
    textEditOutput->setText(stringPhonetic);
}

void Widget_TranslateSentences::receiveValueExplain(QString stringExplain)
{
    textEditOutput->setText(stringExplain);
}

void Widget_TranslateSentences::receiveValueQuery(QString stringQuery)
{
    textEditOutput->setText(stringQuery);
}

/*按钮触发事件的槽函数*/
void Widget_TranslateSentences::clickButtonTranslate()
{
    if(textEditInput->toPlainText()==""){
        //输入为空
        QMessageBox::about(this,"温馨提示：","你输入的是空字符\n请检查无误再翻译");
        return;
    }
    //如果不是空白，则有道翻译
    translateByYouDao->getReply(textEditInput->toPlainText(), 1);
}

/*清空输入和输出的文本框*/
void Widget_TranslateSentences::clickButtonClear()
{
    textEditInput->setText("");
    textEditOutput->setText("");
}









