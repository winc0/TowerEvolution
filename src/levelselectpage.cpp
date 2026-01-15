#include "include/levelselectpage.h"
#include "include/resourcemanager.h"

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QSettings>
#include <QDebug>

LevelSelectPage::LevelSelectPage(QWidget *parent)
    : QDialog(parent),
      mapId(GameConfig::MAP1),
      map1StatusLabel(nullptr),
      map2StatusLabel(nullptr),
      map1WaveLabel(nullptr),
      map2WaveLabel(nullptr),
      map2Button(nullptr)
{
    setModal(true);
    setWindowTitle("选择关卡");
    setFixedSize(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT);

    initUI();
    loadProgress();
}

GameConfig::MapId LevelSelectPage::selectedMap() const
{
    return mapId;
}

void LevelSelectPage::initUI()
{
    ResourceManager &rm = ResourceManager::instance();
    QPixmap background = rm.getDefaultBackground();

    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(background);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(0, 0, GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    mainLayout->addStretch(2);

    QLabel *titleLabel = new QLabel("选择关卡", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("Microsoft YaHei", 36, QFont::Bold));
    titleLabel->setStyleSheet(
        "QLabel {"
        "   color: #2c3e50;"
        "   background-color: rgba(255, 255, 255, 200);"
        "   padding: 16px;"
        "   border-radius: 18px;"
        "   border: 2px solid #95a5a6;"
        "}");
    mainLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);

    mainLayout->addStretch(1);

    QWidget *levelContainer = new QWidget(this);
    levelContainer->setStyleSheet("background-color: rgba(255, 255, 255, 200); border-radius: 15px;");
    levelContainer->setFixedWidth(640);

    QVBoxLayout *levelContainerLayout = new QVBoxLayout(levelContainer);
    levelContainerLayout->setSpacing(20);
    levelContainerLayout->setContentsMargins(24, 24, 24, 24);

    QHBoxLayout *levelLayout = new QHBoxLayout();
    levelLayout->setSpacing(20);

    ResourceManager &rm2 = ResourceManager::instance();

    QWidget *map1Card = new QWidget(levelContainer);
    QVBoxLayout *map1Layout = new QVBoxLayout(map1Card);
    map1Layout->setSpacing(8);

    QLabel *map1Preview = new QLabel(map1Card);
    QPixmap map1Pixmap = rm2.getGameMap(GameConfig::MAP1).scaled(260, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    map1Preview->setPixmap(map1Pixmap);
    map1Preview->setFixedSize(260, 180);
    map1Preview->setScaledContents(true);
    map1Layout->addWidget(map1Preview);

    QLabel *map1NameLabel = new QLabel("关卡 1 - 农田之路", map1Card);
    map1NameLabel->setAlignment(Qt::AlignCenter);
    map1NameLabel->setFont(QFont("Microsoft YaHei", 16, QFont::Bold));
    map1NameLabel->setStyleSheet("color: #34495e;");
    map1Layout->addWidget(map1NameLabel);

    map1StatusLabel = new QLabel(map1Card);
    map1StatusLabel->setAlignment(Qt::AlignCenter);
    map1StatusLabel->setFont(QFont("Microsoft YaHei", 12, QFont::Normal));
    map1StatusLabel->setStyleSheet("color: #27ae60;");
    map1Layout->addWidget(map1StatusLabel);

    map1WaveLabel = new QLabel(map1Card);
    map1WaveLabel->setAlignment(Qt::AlignCenter);
    map1WaveLabel->setFont(QFont("Microsoft YaHei", 12, QFont::Normal));
    map1WaveLabel->setStyleSheet("color: #7f8c8d;");
    map1Layout->addWidget(map1WaveLabel);

    QPushButton *map1Button = new QPushButton("选择关卡 1", map1Card);
    map1Button->setFixedHeight(40);
    map1Button->setStyleSheet(
        "QPushButton {"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   color: white;"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #4CAF50, stop:1 #45a049);"
        "   border: 2px solid #388E3C;"
        "   border-radius: 8px;"
        "   padding: 6px;"
        "}"
        "QPushButton:hover {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #45a049, stop:1 #4CAF50);"
        "   border: 2px solid #2E7D32;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #3d8b40;"
        "   border: 2px solid #1B5E20;"
        "}");
    connect(map1Button, &QPushButton::clicked, this, &LevelSelectPage::onMap1Clicked);
    map1Layout->addWidget(map1Button);

    map1Card->setLayout(map1Layout);
    levelLayout->addWidget(map1Card);

    QWidget *map2Card = new QWidget(levelContainer);
    QVBoxLayout *map2Layout = new QVBoxLayout(map2Card);
    map2Layout->setSpacing(8);

    QLabel *map2Preview = new QLabel(map2Card);
    QPixmap map2Pixmap = rm2.getGameMap(GameConfig::MAP2).scaled(260, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    map2Preview->setPixmap(map2Pixmap);
    map2Preview->setFixedSize(260, 180);
    map2Preview->setScaledContents(true);
    map2Layout->addWidget(map2Preview);

    QLabel *map2NameLabel = new QLabel("关卡 2 - 神秘森林", map2Card);
    map2NameLabel->setAlignment(Qt::AlignCenter);
    map2NameLabel->setFont(QFont("Microsoft YaHei", 16, QFont::Bold));
    map2NameLabel->setStyleSheet("color: #34495e;");
    map2Layout->addWidget(map2NameLabel);

    map2StatusLabel = new QLabel(map2Card);
    map2StatusLabel->setAlignment(Qt::AlignCenter);
    map2StatusLabel->setFont(QFont("Microsoft YaHei", 12, QFont::Normal));
    map2StatusLabel->setStyleSheet("color: #c0392b;");
    map2Layout->addWidget(map2StatusLabel);

    map2WaveLabel = new QLabel(map2Card);
    map2WaveLabel->setAlignment(Qt::AlignCenter);
    map2WaveLabel->setFont(QFont("Microsoft YaHei", 12, QFont::Normal));
    map2WaveLabel->setStyleSheet("color: #7f8c8d;");
    map2Layout->addWidget(map2WaveLabel);

    map2Button = new QPushButton("选择关卡 2", map2Card);
    map2Button->setFixedHeight(40);
    map2Button->setStyleSheet(
        "QPushButton {"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   color: white;"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #9b59b6, stop:1 #8e44ad);"
        "   border: 2px solid #7d3c98;"
        "   border-radius: 8px;"
        "   padding: 6px;"
        "}"
        "QPushButton:disabled {"
        "   background-color: #bdc3c7;"
        "   border: 2px solid #95a5a6;"
        "   color: #ecf0f1;"
        "}"
        "QPushButton:hover:enabled {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #8e44ad, stop:1 #9b59b6);"
        "   border: 2px solid #6c3483;"
        "}"
        "QPushButton:pressed:enabled {"
        "   background-color: #7d3c98;"
        "   border: 2px solid #5b2c6f;"
        "}");
    connect(map2Button, &QPushButton::clicked, this, &LevelSelectPage::onMap2Clicked);
    map2Layout->addWidget(map2Button);

    map2Card->setLayout(map2Layout);
    levelLayout->addWidget(map2Card);

    levelContainerLayout->addLayout(levelLayout);

    QWidget *bottomButtonContainer = new QWidget(levelContainer);
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomButtonContainer);
    bottomLayout->setContentsMargins(0, 0, 0, 0);
    bottomLayout->setSpacing(20);

    bottomLayout->addStretch(1);

    QPushButton *cancelButton = new QPushButton("返回主菜单", bottomButtonContainer);
    cancelButton->setFixedHeight(40);
    cancelButton->setStyleSheet(
        "QPushButton {"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   color: white;"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #95a5a6, stop:1 #7f8c8d);"
        "   border: 2px solid #7f8c8d;"
        "   border-radius: 8px;"
        "   padding: 6px;"
        "}"
        "QPushButton:hover {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #7f8c8d, stop:1 #95a5a6);"
        "   border: 2px solid #707b7c;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #707b7c;"
        "   border: 2px solid #515a5a;"
        "}");
    connect(cancelButton, &QPushButton::clicked, this, &LevelSelectPage::onCancelClicked);
    bottomLayout->addWidget(cancelButton);
    bottomLayout->addStretch(1);

    bottomButtonContainer->setLayout(bottomLayout);
    levelContainerLayout->addWidget(bottomButtonContainer);

    mainLayout->addWidget(levelContainer, 0, Qt::AlignHCenter);

    mainLayout->addStretch(2);

    backgroundLabel->lower();
}

void LevelSelectPage::loadProgress()
{
    // 使用相同的组织名和应用名来初始化 QSettings
    QSettings settings("TowerDefenseStudio", "TowerDefenseGame");

    int unlockedMaxIndex = settings.value("levels/unlocked_max_index", 0).toInt();

    int map1BestWave = settings.value("levels/map_0/bestWave", 0).toInt();
    int map2BestWave = settings.value("levels/map_1/bestWave", 0).toInt();

    qDebug() << "[LevelSelect] unlocked_max_index =" << unlockedMaxIndex
             << "map1BestWave =" << map1BestWave
             << "map2BestWave =" << map2BestWave;

    if (map1StatusLabel)
        map1StatusLabel->setText("已解锁");
    if (map1WaveLabel)
    {
        int displayedWave = map1BestWave > 0 ? map1BestWave : 1;
        map1WaveLabel->setText(QString("最高波次：第 %1 波").arg(displayedWave));
    }

    bool map2Unlocked = unlockedMaxIndex >= 1;
    if (map2StatusLabel)
        map2StatusLabel->setText(map2Unlocked ? "已解锁" : "未解锁");
    if (map2WaveLabel)
    {
        if (map2BestWave > 0)
            map2WaveLabel->setText(QString("最高波次：第 %1 波").arg(map2BestWave));
        else
            map2WaveLabel->setText("最高波次：未挑战");
    }

    if (map2Button)
        map2Button->setEnabled(map2Unlocked);
}

void LevelSelectPage::onMap1Clicked()
{
    mapId = GameConfig::MAP1;
    accept();
}

void LevelSelectPage::onMap2Clicked()
{
    mapId = GameConfig::MAP2;
    accept();
}

void LevelSelectPage::onCancelClicked()
{
    reject();
}
