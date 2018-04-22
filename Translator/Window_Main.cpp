#include "Window_Main.h"

Window_Main::Window_Main(QWidget *parent)
    : QWidget(parent)
{
    hideSetting = false;
    initializeWidgets();
    initializeLayout();
    initializeConnection();
    showLayout();
}

Window_Main::~Window_Main()
{

}

/*各按钮对应的槽函数*/
void Window_Main::clickButtonTranslateWords()
{
    layoutRight->setCurrentIndex(0);
}

void Window_Main::clickButtonTranslateSentences()
{
    layoutRight->setCurrentIndex(1);
}

void Window_Main::clickButtonAbout()
{
    layoutRight->setCurrentIndex(2);
}

/*设置隐藏变量为假*/
void Window_Main::setSettingHideFalse()
{
    hideSetting = false;
    buttonQuit->setText("退出软件");
}

/*设置隐藏变量为真*/
void Window_Main::setSettingHideTrue()
{
    hideSetting = true;
    buttonQuit->setText("隐藏软件");
}

void Window_Main::quit()
{
    quitTrayClicked = true;
    close();
}

/*重写close事件*/
void Window_Main::closeEvent(QCloseEvent *event)
{
    if(quitTrayClicked) {
        //托盘菜单的退出按钮被按下 直接退出程序
        trayIcon->deleteLater();
        event->accept();
    }
    else {
        //主程序的关闭按钮被按下
        if(!hideSetting) {
            //退出程序
            trayIcon->deleteLater();
            event->accept();
        }
        else {
            //最小化到托盘
            event->ignore();
            hide();
        }
    }
}

/*连接信号与槽*/
void Window_Main::initializeConnection()
{
    connect(buttonTranslateSentences, SIGNAL(clicked()), this, SLOT(clickButtonTranslateSentences()));
    connect(buttonTranslateWords, SIGNAL(clicked()), this, SLOT(clickButtonTranslateWords()));
    connect(buttonQuit, SIGNAL(clicked()), this, SLOT(close()));
    connect(buttonAbout, SIGNAL(clicked()), this, SLOT(clickButtonAbout()));
    connect(radioButtonSetHide, SIGNAL(clicked()), this, SLOT(setSettingHideTrue()));
    connect(radioButtonSetQuit, SIGNAL(clicked()), this, SLOT(setSettingHideFalse()));
    connect(actionShowWindowMain, SIGNAL(triggered()), this, SLOT(show()));
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(quit()));
}

/*初始化基本组件*/
void Window_Main::initializeWidgets()
{
    buttonTranslateWords = new QPushButton("单词查询");
    buttonTranslateSentences = new QPushButton("长句翻译");
    buttonQuit = new QPushButton("退出软件");
    buttonAbout = new QPushButton("关于软件");

    setting = new QLabel("设置是否隐藏:");
    radioButtonSetHide = new QRadioButton("隐藏在任务栏");
    radioButtonSetQuit = new QRadioButton("完全退出软件");

    trayIcon = new QSystemTrayIcon(QIcon(":/img/resources/ico/ico2.png"), this);
    trayMenu = new QMenu(this);
    actionShowWindowMain = new QAction("显示主窗口", this);
    actionQuit = new QAction("退出", this);
    quitTrayClicked = false;

    buttonTranslateSentences->setFixedSize(120,35);
    buttonTranslateWords->setFixedSize(120,35);
    buttonQuit->setFixedSize(120, 35);
    buttonAbout->setFixedSize(120,35);

    radioButtonSetHide->setChecked(false);
    radioButtonSetQuit->setChecked(true);
    setting->setFixedSize(120,35);
    radioButtonSetHide->setFixedSize(120,35);
    radioButtonSetQuit->setFixedSize(120,35);

    //托盘图标及菜单
    trayMenu->addAction(actionShowWindowMain);
    trayMenu->addAction(actionQuit);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->setToolTip("迷你翻译机");
    trayIcon->show();

    groupBoxTranslateSentences = new Widget_TranslateSentences(this);
    groupBoxTranslateWords = new Widget_TranslateWords(this);
    groupBoxAbout = new Widget_About(this);
}

/*初始化布局管理*/
void Window_Main::initializeLayout()
{
    //水平
    layoutLeft = new QVBoxLayout;
    layoutLeft->addWidget(buttonTranslateWords);
    layoutLeft->addWidget(buttonTranslateSentences);
    layoutLeft->addWidget(buttonQuit);
    layoutLeft->addWidget(buttonAbout);
    layoutLeft->addStretch();
    layoutLeft->addWidget(setting);
    layoutLeft->addWidget(radioButtonSetHide);
    layoutLeft->addWidget(radioButtonSetQuit);

    layoutRight = new QStackedLayout;
    layoutRight->addWidget(groupBoxTranslateWords->createGroupBoxTranslateWords());
    layoutRight->addWidget(groupBoxTranslateSentences->createGroupBoxTranslateSentences());
    layoutRight->addWidget(groupBoxAbout->createGroupBoxAbout());
    //垂直
    layoutMain = new QHBoxLayout(this);
    layoutMain->addLayout(layoutLeft);
    layoutMain->addLayout(layoutRight);
}

void Window_Main::showLayout()
{
    setWindowTitle("迷你翻译机");
    setWindowIcon(QIcon(":/img/resources/ico/ico.png"));
    setLayout(layoutMain);
    setFixedSize(sizeHint());
}




