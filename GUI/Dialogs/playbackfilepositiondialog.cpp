
#include "playbackfilepositiondialog.h"

#include <QtWidgets>

PlaybackFilePositionDialog::PlaybackFilePositionDialog(const QString& currentPosition, const QString& startPosition,
                                                       const QString& endPosition, bool runSelected, QWidget* parent) :
    QDialog(parent)
{
    QTime currentTime(0, 0);
    if (currentPosition.left(1) != "-") {    // If file position is negative, set up 00:00:00.
        currentTime = QTime::fromString(currentPosition, "HH:mm:ss");
    }

    bool negativeStartTime = false;
    QTime startTime(0, 0);
    if (startPosition.left(1) != "-") {
        startTime = QTime::fromString(startPosition, "HH:mm:ss");
    } else {
        negativeStartTime = true;
    }

    QTime endTime(0, 0);
    if (endPosition.left(1) != "-") {
        endTime = QTime::fromString(endPosition, "HH:mm:ss");
    }

    timeEdit = new QTimeEdit(currentTime, this);
    timeEdit->setDisplayFormat("HH:mm:ss");
    timeEdit->setMinimumTime(startTime);
    timeEdit->setMaximumTime(endTime);

    runCheckBox = new QCheckBox(tr("Run Immediately After Jump"), this);
    runCheckBox->setChecked(runSelected);

    setWindowTitle(tr("Jump To Position"));

    QVBoxLayout *textLayout = new QVBoxLayout;
    textLayout->addWidget(new QLabel(tr("The playback file contains data from ") + startPosition + tr(" to ") +
                                     endPosition + tr("."), this));
    if (negativeStartTime) {
        textLayout->addWidget(new QLabel(tr("(Use Jump to Start button to access times before 00:00:00.)"), this));
    }

    QHBoxLayout *timeEditRow = new QHBoxLayout;
    timeEditRow->addStretch(1);
    timeEditRow->addWidget(new QLabel(tr("Jump to"), this));
    timeEditRow->addWidget(timeEdit);

    QHBoxLayout *runCheckBoxRow = new QHBoxLayout;
    runCheckBoxRow->addStretch(1);
    runCheckBoxRow->addWidget(runCheckBox);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(textLayout);
    mainLayout->addLayout(timeEditRow);
    mainLayout->addLayout(runCheckBoxRow);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

QString PlaybackFilePositionDialog::getTime() const
{
    return timeEdit->time().toString("HH:mm:ss");
}

bool PlaybackFilePositionDialog::runImmediately() const
{
    return runCheckBox->isChecked();
}
