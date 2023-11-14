
#include "displaylistmanager.h"
#include "autogroupdialog.h"

AutoGroupDialog::AutoGroupDialog(QWidget *parent) :
    QDialog(parent)
{
    groupSizeSpinBox = new QSpinBox(this);
    groupSizeSpinBox->setRange(2, MaxNumWaveformsInGroup);
    groupSizeSpinBox->setValue(4);

    QHBoxLayout *groupSizeLayout = new QHBoxLayout;
    groupSizeLayout->addWidget(new QLabel(tr("Number of amplifier channels per group:"), this));
    groupSizeLayout->addWidget(groupSizeSpinBox);
    groupSizeLayout->addStretch();

    QHBoxLayout *infoLayout1 = new QHBoxLayout;
    infoLayout1->addWidget(new QLabel(tr("Any existing groups will be ungrouped, and all disabled channels will be moved to the bottom."), this));
    infoLayout1->addStretch();

    QHBoxLayout *infoLayout2 = new QHBoxLayout;
    infoLayout2->addWidget(new QLabel(tr("<b>Note:</b> You can undo this operation."), this));
    infoLayout2->addStretch();

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(groupSizeLayout);
    mainLayout->addLayout(infoLayout1);
    mainLayout->addLayout(infoLayout2);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
    setWindowTitle(tr("Group Amplifier Channels"));
}
