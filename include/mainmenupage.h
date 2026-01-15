#ifndef MAINMENUPAGE_H
#define MAINMENUPAGE_H

#include "config.h"
#include <QWidget>
#include <QPixmap>

class QPushButton;
class QLabel;
class QVBoxLayout;

class MainMenuPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuPage(QWidget *parent = nullptr);

signals:
    void startGameRequested(GameConfig::MapId mapId);
    void exitGameRequested();

private slots:
    void onStartButtonClicked();
    void onExitButtonClicked();

private:
    void initUI();
    void loadResources();

    QLabel *titleLabel;
    QLabel *backgroundLabel;
    QPushButton *startButton;
    QPushButton *exitButton;
    QVBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;

    QPixmap backgroundImage;
};

#endif
