#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "config.h"
#include <QMainWindow>

// 前向声明
class GamePage;
class MainMenuPage;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void switchToGamePage(GameConfig::MapId mapId);
    void switchToMainMenu();

private slots:
    void onGameOver();

private:
    Ui::MainWindow *ui;
    GamePage *gamePage;
    MainMenuPage *mainMenuPage;
};

#endif // MAINWINDOW_H
