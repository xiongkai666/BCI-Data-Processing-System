
#include <QtWidgets>
#include "ampsettledialog.h"

// Amp settle dialog - this allows users to select desired values for amplifier settle parameters.
AmpSettleDialog::AmpSettleDialog(double lowerSettleBandwidth, bool useFastSettle, bool headstageGlobalSettle,
                                 QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout *lowFreqSettleLayout = new QVBoxLayout();
    QHBoxLayout *lowFreqSettleSelectLayout = new QHBoxLayout();

    settleHeadstageCheckBox = new QCheckBox(tr("Headstage Global Amp Settle"), this);
    settleHeadstageCheckBox->setChecked(headstageGlobalSettle);

    lowRangeSettleLabel = new QLabel(tr("Lower Bandwidth for Amp Settle Range: 0.1 Hz to 1000 Hz."), this);

    lowFreqSettleLineEdit = new QLineEdit(QString::number(lowerSettleBandwidth, 'f', 2), this);
    QDoubleValidator* lowFreqSettleValidator = new QDoubleValidator(0.1, 1000.0, 3, this);
    lowFreqSettleValidator->setNotation(QDoubleValidator::StandardNotation);
    lowFreqSettleValidator->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));  // Ensure '.' is used as decimal point, not ','
    lowFreqSettleLineEdit->setValidator(lowFreqSettleValidator);
    connect(lowFreqSettleLineEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(onLineEditTextChanged()));

    lowFreqSettleSelectLayout->addWidget(new QLabel(tr("Amplifier Lower Bandwidth for Amp Settle"), this));
    lowFreqSettleSelectLayout->addWidget(lowFreqSettleLineEdit);
    lowFreqSettleSelectLayout->addWidget(new QLabel(tr("Hz"), this));
    lowFreqSettleSelectLayout->addStretch();

    lowFreqSettleLayout->addLayout(lowFreqSettleSelectLayout);
    lowFreqSettleLayout->addWidget(lowRangeSettleLabel);

    // Amplifier settle mode combo box
    ampSettleModeComboBox = new QComboBox(this);
    ampSettleModeComboBox->addItem(tr("Switch Lower Bandwidth"));
    ampSettleModeComboBox->addItem(tr("Traditional Fast Settle"));
    ampSettleModeComboBox->setCurrentIndex(0);

    connect(ampSettleModeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setAmpSettleMode(int)));
    ampSettleModeComboBox->setCurrentIndex(useFastSettle ? 1 : 0);

    QHBoxLayout *ampSettleModeLayout = new QHBoxLayout;
    ampSettleModeLayout->addWidget(new QLabel(tr("Amp Settle Mode"), this));
    ampSettleModeLayout->addWidget(ampSettleModeComboBox);
    ampSettleModeLayout->addStretch();

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(ampSettleModeLayout);
    mainLayout->addLayout(lowFreqSettleLayout);
    mainLayout->addWidget(settleHeadstageCheckBox);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    setWindowTitle(tr("Select Amplifier Settle Parameters"));

    onLineEditTextChanged();
}

// Check the validity of requested frequencies.
void AmpSettleDialog::onLineEditTextChanged()
{
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(
                (lowFreqSettleLineEdit->hasAcceptableInput()));

    if (!lowFreqSettleLineEdit->hasAcceptableInput()) {
        lowRangeSettleLabel->setStyleSheet("color: red");
    } else {
        lowRangeSettleLabel->setStyleSheet("");
    }
}

// Change amp settle mode.
void AmpSettleDialog::setAmpSettleMode(int index)
{
    if (index == 1) {
        lowFreqSettleLineEdit->setEnabled(false);
    } else {
        lowFreqSettleLineEdit->setEnabled(true);
    }
}
