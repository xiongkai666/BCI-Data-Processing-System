
#include "renamechanneldialog.h"

RenameChannelDialog::RenameChannelDialog(const QString& nativeName, const QString& oldName, QWidget* parent) :
    QDialog(parent)
{
    QString addNativeName;
    if (nativeName != oldName) addNativeName = " (" + nativeName + ")";

    QHBoxLayout* oldNameLayout = new QHBoxLayout;
    oldNameLayout->addWidget(new QLabel(tr("Old channel name: ") + oldName + addNativeName, this));

    nameLineEdit = new QLineEdit;
    QRegExp regExp("[\\w-\\+\\./]{1,16}");  // Name must be 1-16 characters, alphanumeric or _-+./
    nameLineEdit->setValidator(new QRegExpValidator(regExp, this));

    connect(nameLineEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(onLineEditTextChanged()));

    QHBoxLayout* newNameLayout = new QHBoxLayout;
    newNameLayout->addWidget(new QLabel(tr("New channel name:"), this));
    newNameLayout->addWidget(nameLineEdit);
    newNameLayout->addWidget(new QLabel(tr("(16 characters max)"), this));
    newNameLayout->addStretch();

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(oldNameLayout);
    mainLayout->addLayout(newNameLayout);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    setWindowTitle(tr("Rename Channel"));
}

// Enable OK button on valid name.
void RenameChannelDialog::onLineEditTextChanged()
{
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(nameLineEdit->hasAcceptableInput());
}

