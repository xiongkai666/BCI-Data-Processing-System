
#ifndef PLAYBACKFILEPOSITIONDIALOG_H
#define PLAYBACKFILEPOSITIONDIALOG_H

#include <QDialog>

class QTimeEdit;
class QCheckBox;
class QDialogButtonBox;

class PlaybackFilePositionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PlaybackFilePositionDialog(const QString& currentPosition, const QString& startPosition,
                                        const QString& endPosition, bool runSelected, QWidget* parent = nullptr);

    QString getTime() const;
    bool runImmediately() const;

private:
    QTimeEdit* timeEdit;
    QCheckBox* runCheckBox;
    QDialogButtonBox* buttonBox;
};

#endif // PLAYBACKFILEPOSITIONDIALOG_H
