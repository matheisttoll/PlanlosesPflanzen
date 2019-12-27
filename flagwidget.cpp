#include "flagwidget.h"
#include "application_constants.h"

#include <QHBoxLayout>
#include <QString>
#include <QSettings>
#include <QString>
#include <QPixmap>


const QString FlagWidget::flagIcon{"/flag_icon"};

FlagWidget::FlagWidget(size_t mines, QSize size, QWidget *parent) : QWidget(parent) {
    flagCount = 0;
    QHBoxLayout *layout = new QHBoxLayout(this);

    flagCountLabel = new QLabel(this);
    flagIconLabel = new QLabel(this);
    layout->addWidget(flagCountLabel);
    layout->addWidget(flagIconLabel);

    QSettings settings;
    QString resourcePath = settings.value(keys::resourcesPath).toString();
    flagIconLabel->setPixmap(QPixmap(resourcePath + flagIcon + ".png", "png").scaled(size));

    setMines(mines);
}

FlagWidget::~FlagWidget() {
    delete flagCountLabel;
    delete flagIconLabel;
}

void FlagWidget::setMines(size_t m) {
    mines = m;
    resetFlagCount();
}

void FlagWidget::resetFlagCount() {
    flagCount = 0;
    updateFlagLabel();
}

void FlagWidget::incFlagCount(bool flagSet) {
    if(flagSet) {
        flagCount++;
    } else {
        flagCount--;
    }
    updateFlagLabel();
}

void FlagWidget::updateFlagLabel() {
    flagCountLabel->setText(QString::number(flagCount) + " / " + QString::number(mines));
}
