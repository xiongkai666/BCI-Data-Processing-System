
#include "autocolordialog.h"

AutoColorDialog::AutoColorDialog(QWidget *parent) :
    QDialog(parent)
{
    numColorsSpinBox = new QSpinBox(this);
    numColorsSpinBox->setRange(1, 128);
    numColorsSpinBox->setValue(16);

    numChannelsSameColorSpinBox = new QSpinBox(this);
    numChannelsSameColorSpinBox->setRange(1, 128);
    numChannelsSameColorSpinBox->setValue(1);

    QHBoxLayout *numColorsLayout = new QHBoxLayout;
    numColorsLayout->addWidget(new QLabel(tr("Total number of colors:"), this));
    numColorsLayout->addWidget(numColorsSpinBox);
    numColorsLayout->addStretch();

    QHBoxLayout *numChannelsSameColorLayout = new QHBoxLayout;
    numChannelsSameColorLayout->addWidget(new QLabel(tr("Number of adjacent channels with same color:"), this));
    numChannelsSameColorLayout->addWidget(numChannelsSameColorSpinBox);
    numChannelsSameColorLayout->addStretch();

    QHBoxLayout *infoLayout = new QHBoxLayout;
    infoLayout->addWidget(new QLabel(tr("<b>Note:</b> You can undo this operation."), this));
    infoLayout->addStretch();

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(numColorsLayout);
    mainLayout->addLayout(numChannelsSameColorLayout);
    mainLayout->addLayout(infoLayout);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
    setWindowTitle(tr("Color Amplifier Channels"));
}
