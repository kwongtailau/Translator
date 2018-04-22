#include "Widget_TranslateWords.h"

Widget_TranslateWords::Widget_TranslateWords(QWidget *parent) : QWidget(parent)
{
    //初始化基本组件
    groupBoxTranslateWords = new QGroupBox(this);
    translateFromDb = new Func_TranslateFromDatabase(this);
    translateFromYoudao = new Func_TranslateFromNet(this);
    textBrowserWords = new QTextBrowser();
    lineEditInput = new QLineEdit();
    buttonSearch = new QPushButton();

    //search按钮设置
    QIcon icoButtonSearch(":/img/resources/ico/icoSearch.png");
    buttonSearch->setIcon(icoButtonSearch);
    buttonSearch->setIconSize(QSize(20, 20));
    buttonSearch->setFlat(true);

    //在输入框中设置提示文字
    lineEditInput->setPlaceholderText("请输入需要翻译的字,词-支持中英互译");

    //配置自动补全功能
    completer = new QCompleter(translateFromDb->getWordList(), this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    lineEditInput->setCompleter(completer);

    //初始化布局管理
    //水平
    layoutUp = new QHBoxLayout();
    layoutUp->addWidget(lineEditInput);
    layoutUp->addWidget(buttonSearch);
    //垂直
    layoutMain = new QVBoxLayout();
    layoutMain->addLayout(layoutUp);
    layoutMain->addWidget(textBrowserWords);

    //连接信号与槽
    connect(translateFromYoudao, SIGNAL(signalValueExplainsFinished(QString)), this, SLOT(receiveValueExplain(QString)));
    connect(lineEditInput, SIGNAL(returnPressed()), this, SLOT(clickButtonSearch()));
    connect(buttonSearch, SIGNAL(clicked()), this, SLOT(clickButtonSearch()));
}

Widget_TranslateWords::~Widget_TranslateWords()
{

}

/*向主窗口返回单词翻译页面*/
QGroupBox *Widget_TranslateWords::createGroupBoxTranslateWords()
{
    groupBoxTranslateWords->setLayout(layoutMain);
    return groupBoxTranslateWords;
}

/*接收联网查询数据的槽函数*/
void Widget_TranslateWords::receiveValueExplain(QString stringExplain)
{
    if(stringExplain != "") {
        //得到查询结果后用html的格式显示出来
        QString stringTemp = stringExplain + "<br><font color=#696969>-该查询结果来源于有道翻译</font>";
        stringTemp.replace(QString("\n"), QString("<br>"));
        textBrowserWords->setText(stringTemp);
    }
    else
        //如果没有得到，可能是存在网络不通，或者拼写错误
        //在此就先不深究联网网络不通怎么处理
        textBrowserWords->setText("<font color=#696969>本地查询与联网查询均无结果 请检查您的输入内容是否正确</font>");
}

/*点击搜索按钮对应的槽函数*/
void Widget_TranslateWords::clickButtonSearch()
{
    //判断是否输入是否为空白
    if(lineEditInput->text() == ""){
        QMessageBox::about(this, "温馨提示：", "你输入的是空字符\n请检查无误再翻译");
        return;
    }
    //使用正则表达式判断输入是否为中文
    if(lineEditInput->text().contains(QRegExp("[\\x4e00-\\x9fa5]+"))) {

        QString replyFromCN = translateFromDb->getReplyFromCN(lineEditInput->text());
        if(replyFromCN == "本地词库查询无结果" /*&& settingManager::getAutoTranslateFromNet()*/)
            translateFromYoudao->getReply(lineEditInput->text(), 2);        //本地无数据 从网络获取查询结果
        else
            //本地查询结果显示
            textBrowserWords->setText(replyFromCN);
    }
    else {
        //输入的是英文的话
        QString replyFromEN = translateFromDb->getReplyFromEN(lineEditInput->text());
        if(replyFromEN == "本地词库查询无结果" /*&& settingManager::getAutoTranslateFromNet()*/)
            translateFromYoudao->getReply(lineEditInput->text(), 2);        //本地无数据 从网络获取查询结果
        else
            //本地查询结果显示
            textBrowserWords->setText(replyFromEN);
    }
}
