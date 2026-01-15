#ifndef LEVELSELECTPAGE_H
#define LEVELSELECTPAGE_H

#include "config.h"
#include <QDialog>

class QPushButton;
class QLabel;
class QVBoxLayout;

class LevelSelectPage : public QDialog
{
    Q_OBJECT

public:
    explicit LevelSelectPage(QWidget *parent = nullptr);

    GameConfig::MapId selectedMap() const;

private slots:
    void onMap1Clicked();
    void onMap2Clicked();
    void onCancelClicked();

private:
    void initUI();
    void loadProgress();

    GameConfig::MapId mapId;
    QLabel *map1StatusLabel;
    QLabel *map2StatusLabel;
    QLabel *map1WaveLabel;
    QLabel *map2WaveLabel;
    QPushButton *map2Button;
};

#endif

