#include <QFileDialog>
#include <QMessageBox>

#include "Atrc.h"
#include "ui_Atrc.h"

Atrc::Atrc(QWidget*)
    : ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    connect(ui_->menuItem_open, SIGNAL(triggered()), this, SLOT(OnOpenFile()));
    connect(ui_->menuItem_close, SIGNAL(triggered()), this, SLOT(OnCloseFile()));
    connect(ui_->menuItem_quit, SIGNAL(triggered()), this, SLOT(close()));
}

Atrc::~Atrc()
{
    delete ui_;
}

void Atrc::OnOpenFile()
{
    QString filename = QFileDialog::getOpenFileName();

    img_ = std::make_unique<QImage>();
    if(!img_->load(filename))
    {
        QMessageBox::information(this, u8"����", u8"���ļ�ʧ��");
        img_ = nullptr;
    }
    else
        ui_->label->setPixmap(QPixmap::fromImage(*img_));
}

void Atrc::OnCloseFile()
{
    img_ = nullptr;
    ui_->label->setPixmap(QPixmap());
}
