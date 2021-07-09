#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("INQNET - Macom power distribution"));
    com = new socket_com();
    ui->onoff->setState(false);

    this->last_channel_state[0] = ui->CH1_on->isChecked();
    this->last_channel_state[1] = ui->CH2_on->isChecked();
    this->last_channel_state[2] = ui->CH3_on->isChecked();
    this->last_channel_state[3] = ui->CH4_on->isChecked();

    this->last_vc[0] = ui->vc1->value();
    this->last_vc[1] = ui->vc2->value();
    this->last_vc[2] = ui->vc3->value();
    this->last_vc[3] = ui->vc4->value();

    this->last_vcx[0] = ui->vcx1->value();
    this->last_vcx[1] = ui->vcx2->value();
    this->last_vcx[2] = ui->vcx3->value();
    this->last_vcx[3] = ui->vcx4->value();

    this->last_vgain[0] = ui->vgain1->value();
    this->last_vgain[1] = ui->vgain2->value();
    this->last_vgain[2] = ui->vgain3->value();
    this->last_vgain[3] = ui->vgain4->value();

    QObject::connect(ui->connect, SIGNAL(pressed()), com, SLOT(connect_socket()));
    QObject::connect(this, SIGNAL(disconnect_socket()), com, SLOT(disconnect_socket()));
    QObject::connect(com, SIGNAL(net_ledon()), this, SLOT(ledon()));
    QObject::connect(ui->disconnect, SIGNAL(pressed()), this, SLOT(turnoff()));

    QObject::connect(ui->CH1_on, SIGNAL(stateChanged(int)), this, SLOT(updateUI()));
    QObject::connect(ui->CH2_on, SIGNAL(stateChanged(int)), this, SLOT(updateUI()));
    QObject::connect(ui->CH3_on, SIGNAL(stateChanged(int)), this, SLOT(updateUI()));
    QObject::connect(ui->CH4_on, SIGNAL(stateChanged(int)), this, SLOT(updateUI()));

    QObject::connect(ui->ip, SIGNAL(textChanged(QString)), com, SLOT(set_network_ip(QString)));
    QObject::connect(ui->local_port, SIGNAL(textChanged(QString)), com, SLOT(set_network_local_port_(QString)));
    QObject::connect(ui->remote_port, SIGNAL(textChanged(QString)), com, SLOT(set_network_remote_port_(QString)));

    QObject::connect(com, SIGNAL(vd3_1_chang(double)), ui->vd3_1, SLOT(display(double)));
    QObject::connect(com, SIGNAL(vd2_1_chang(double)), ui->vd2_1, SLOT(display(double)));
    QObject::connect(com, SIGNAL(vd1_1_chang(double)), ui->vd1_1, SLOT(display(double)));
    QObject::connect(com, SIGNAL(vg3_1_chang(double)), ui->vg3_1, SLOT(display(double)));
    QObject::connect(com, SIGNAL(vg2_1_chang(double)), ui->vg2_1, SLOT(display(double)));
    QObject::connect(com, SIGNAL(I3_1_chang(double)), ui->I3_1, SLOT(display(double)));
    QObject::connect(com, SIGNAL(I2_1_chang(double)), ui->I2_1, SLOT(display(double)));
    QObject::connect(com, SIGNAL(Vpeak_1_chang(double)), ui->vpeak_1, SLOT(display(double)));

    QObject::connect(com, SIGNAL(vd3_2_chang(double)), ui->vd3_2, SLOT(display(double)));
    QObject::connect(com, SIGNAL(vd2_2_chang(double)), ui->vd2_2, SLOT(display(double)));
    QObject::connect(com, SIGNAL(vd1_2_chang(double)), ui->vd1_2, SLOT(display(double)));
    QObject::connect(com, SIGNAL(vg3_2_chang(double)), ui->vg3_2, SLOT(display(double)));
    QObject::connect(com, SIGNAL(vg2_2_chang(double)), ui->vg2_2, SLOT(display(double)));
    QObject::connect(com, SIGNAL(I3_2_chang(double)), ui->I3_2, SLOT(display(double)));
    QObject::connect(com, SIGNAL(I2_2_chang(double)), ui->I2_2, SLOT(display(double)));
    QObject::connect(com, SIGNAL(Vpeak_2_chang(double)), ui->vpeak_2, SLOT(display(double)));

    QObject::connect(com, SIGNAL(vd3_3_chang(double)), ui->vd3_3, SLOT(display(double)));
    QObject::connect(com, SIGNAL(vd2_3_chang(double)), ui->vd2_3, SLOT(display(double)));
    QObject::connect(com, SIGNAL(vd1_3_chang(double)), ui->vd1_3, SLOT(display(double)));
    QObject::connect(com, SIGNAL(vg3_3_chang(double)), ui->vg3_3, SLOT(display(double)));
    QObject::connect(com, SIGNAL(vg2_3_chang(double)), ui->vg2_3, SLOT(display(double)));
    QObject::connect(com, SIGNAL(I3_3_chang(double)), ui->I3_3, SLOT(display(double)));
    QObject::connect(com, SIGNAL(I2_3_chang(double)), ui->I2_3, SLOT(display(double)));
    QObject::connect(com, SIGNAL(Vpeak_3_chang(double)), ui->vpeak_3, SLOT(display(double)));

    QObject::connect(com, SIGNAL(vd3_4_chang(double)), ui->vd3_4, SLOT(display(double)));
    QObject::connect(com, SIGNAL(vd2_4_chang(double)), ui->vd2_4, SLOT(display(double)));
    QObject::connect(com, SIGNAL(vd1_4_chang(double)), ui->vd1_4, SLOT(display(double)));
    QObject::connect(com, SIGNAL(vg3_4_chang(double)), ui->vg3_4, SLOT(display(double)));
    QObject::connect(com, SIGNAL(vg2_4_chang(double)), ui->vg2_4, SLOT(display(double)));
    QObject::connect(com, SIGNAL(I3_4_chang(double)), ui->I3_4, SLOT(display(double)));
    QObject::connect(com, SIGNAL(I2_4_chang(double)), ui->I2_4, SLOT(display(double)));
    QObject::connect(com, SIGNAL(Vpeak_4_chang(double)), ui->vpeak_4, SLOT(display(double)));

    QObject::connect(ui->vc1, SIGNAL(valueChanged(double)), this, SLOT(updateUI()));
    QObject::connect(ui->vc2, SIGNAL(valueChanged(double)), this, SLOT(updateUI()));
    QObject::connect(ui->vc3, SIGNAL(valueChanged(double)), this, SLOT(updateUI()));
    QObject::connect(ui->vc4, SIGNAL(valueChanged(double)), this, SLOT(updateUI()));

    QObject::connect(ui->vcx1, SIGNAL(valueChanged(double)), this, SLOT(updateUI()));
    QObject::connect(ui->vcx2, SIGNAL(valueChanged(double)), this, SLOT(updateUI()));
    QObject::connect(ui->vcx3, SIGNAL(valueChanged(double)), this, SLOT(updateUI()));
    QObject::connect(ui->vcx4, SIGNAL(valueChanged(double)), this, SLOT(updateUI()));

    QObject::connect(ui->vgain1, SIGNAL(valueChanged(double)), this, SLOT(updateUI()));
    QObject::connect(ui->vgain2, SIGNAL(valueChanged(double)), this, SLOT(updateUI()));
    QObject::connect(ui->vgain3, SIGNAL(valueChanged(double)), this, SLOT(updateUI()));
    QObject::connect(ui->vgain4, SIGNAL(valueChanged(double)), this, SLOT(updateUI()));

    ui->ip->setText("192.168.0.101");
    ui->local_port->setText("55180");
    ui->remote_port->setText("5005");

}

void MainWindow::updateUI(void)
{
    int i;
    int channel_state[4];
    double vc[4];
    double vcx[4];
    double vgain[4];

    channel_state[0] = ui->CH1_on->isChecked();
    channel_state[1] = ui->CH2_on->isChecked();
    channel_state[2] = ui->CH3_on->isChecked();
    channel_state[3] = ui->CH4_on->isChecked();

    vc[0] = ui->vc1->value();
    vc[1] = ui->vc2->value();
    vc[2] = ui->vc3->value();
    vc[3] = ui->vc4->value();

    vcx[0] = ui->vcx1->value();
    vcx[1] = ui->vcx2->value();
    vcx[2] = ui->vcx3->value();
    vcx[3] = ui->vcx4->value();

    vgain[0] = ui->vgain1->value();
    vgain[1] = ui->vgain2->value();
    vgain[2] = ui->vgain3->value();
    vgain[3] = ui->vgain4->value();

    for (i = 0; i < 4; i++) {
        if (channel_state[i] != this->last_channel_state[i]) {
            this->com->enable_channel(i,channel_state[i]);
            last_channel_state[i] = channel_state[i];
        }

        if (vc[i] != this->last_vc[i]) {
            this->com->change_vc(i,vc[i]);
            last_vc[i] = vc[i];
        }

        if (vcx[i] != this->last_vcx[i]) {
            this->com->change_vcx(i,vcx[i]);
            last_vcx[i] = vcx[i];
        }

        if (vgain[i] != this->last_vgain[i]) {
            this->com->change_vgain(i,vgain[i]);
            last_vgain[i] = vgain[i];
        }
    }
}

void MainWindow::turnoff(){
    ui->CH1_on->setChecked(false);
    ui->CH2_on->setChecked(false);
    ui->CH3_on->setChecked(false);
    ui->CH4_on->setChecked(false);
    ui->onoff->setState(false);
    emit disconnect_socket();
}

void MainWindow::ledon(){
    ui->onoff->setState(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

