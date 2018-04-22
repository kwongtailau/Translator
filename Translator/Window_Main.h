#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H

#include <QWidget>
#include "Widget_TranslateSentences.h"
#include "Widget_TranslateWords.h"
#include "Widget_About.h"
#include <QSystemTrayIcon>
#include <QStackedLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QCloseEvent>
#include <QBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QMenu>

class Window_Main : public QWidget
{
    Q_OBJECT
public:
    Window_Main(QWidget *parent = 0);
    ~Window_Main();
private slots:
    //各按钮所对应的槽函数
    void clickButtonTranslateSentences();
    void clickButtonTranslateWords();
    void clickButtonAbout();
    void setSettingHideFalse();
    void setSettingHideTrue();
    void quit();
private:
    Widget_TranslateSentences * groupBoxTranslateSentences; //长句翻译界面
    Widget_TranslateWords * groupBoxTranslateWords;         //单词翻译界面
    Widget_About * groupBoxAbout;                           //关于软件的界面
    //各个按钮
    QPushButton * buttonTranslateSentences;
    QPushButton * buttonTranslateWords;
    QPushButton * buttonQuit;
    QPushButton * buttonAbout;
    //设置
    QLabel * setting;
    bool hideSetting;
    QRadioButton * radioButtonSetHide;
    QRadioButton * radioButtonSetQuit;
    //布局
    QStackedLayout * layoutRight;
    QHBoxLayout * layoutMain;
    QVBoxLayout * layoutLeft;
    //托盘事件的变量
    QAction * actionShowWindowMain;
    QAction * actionQuit;
    QSystemTrayIcon * trayIcon;
    QMenu * trayMenu;
    bool quitTrayClicked;
private:
    void closeEvent(QCloseEvent *event);
    void initializeConnection();
    void initializeWidgets();
    void initializeLayout();
    void showLayout();
};

#endif // WINDOW_MAIN_H
