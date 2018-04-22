#ifndef WIDGET_TRANSLATEWORDS_H
#define WIDGET_TRANSLATEWORDS_H

#include <QWidget>
#include "Func_TranslateFromDatabase.h"
#include "Func_TranslateFromNet.h"
#include <QTextBrowser>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCompleter>
#include <QGroupBox>
#include <QLineEdit>
#include <QFile>

class Widget_TranslateWords : public QWidget
{
    Q_OBJECT
public:
    explicit Widget_TranslateWords(QWidget *parent = nullptr);
    ~Widget_TranslateWords();
    //向主窗口返回单词翻译页面
    QGroupBox * createGroupBoxTranslateWords();
signals:
    void sendAccountLogin();
private slots:
    //接收联网查询数据的槽函数
    void receiveValueExplain(QString stringExplain);
    //点击搜索按钮对应的槽函数
    void clickButtonSearch();
private:
    Func_TranslateFromDatabase * translateFromDb;   //取数据库
    Func_TranslateFromNet * translateFromYoudao;    //取有道翻译
    QGroupBox * groupBoxTranslateWords;             //取翻译单词的widget
    QTextBrowser * textBrowserWords;                //显示单词的解释
    QCompleter * completer;                         //用于自动补全
    QPushButton * buttonSearch;
    QLineEdit * lineEditInput;
    //布局
    QVBoxLayout * layoutMain;
    QHBoxLayout * layoutUp;
};

#endif // WIDGET_TRANSLATEWORDS_H
