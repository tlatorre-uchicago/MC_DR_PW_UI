#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <stdlib.h>

void trim(char *ptr)
{
    while((ptr != NULL) && (*ptr != '\n'))
    {
        ++ptr;
    }
    *ptr = '\0';
}

#ifndef __unix__
/* getline() replacement for windows. From https://stackoverflow.com/questions/735126/are-there-alternate-implementations-of-gnu-getline-interface/735472#735472. */
size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = (char *) malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = (char *) realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("INQNET - Macom power distribution"));
    com = new socket_com();
    ui->onoff->setState(false);

    /* Set default values for the IP and ports. These will get updated when we
     * load the settings from the file. */
    ui->ip->setText("192.168.0.101");
    ui->local_port->setText("55180");
    ui->remote_port->setText("5005");

    /* Load previous settings. */
    this->loadFromFile("settings.txt");

    /* Set the last known state to impossible values. This way, we are
     * guaranteed when we connect to reset all the values. */
    this->last_channel_state[0] = -1;
    this->last_channel_state[1] = -1;
    this->last_channel_state[2] = -1;
    this->last_channel_state[3] = -1;

    this->last_vc[0] = -999;
    this->last_vc[1] = -999;
    this->last_vc[2] = -999;
    this->last_vc[3] = -999;

    this->last_vcx[0] = -999;
    this->last_vcx[1] = -999;
    this->last_vcx[2] = -999;
    this->last_vcx[3] = -999;

    this->last_vgain[0] = -999;
    this->last_vgain[1] = -999;
    this->last_vgain[2] = -999;
    this->last_vgain[3] = -999;

    QObject::connect(ui->connect, SIGNAL(pressed()), this, SLOT(connect()));
    QObject::connect(this, SIGNAL(disconnect_socket()), com, SLOT(disconnect_socket()));
    QObject::connect(com, SIGNAL(net_ledon()), this, SLOT(ledon()));
    QObject::connect(ui->disconnect, SIGNAL(pressed()), this, SLOT(turnoff()));

    /* For most of the channel settings, we use the same updateUI() slot function.
     * The advantage of this is that we can check in updateUI() which elements
     * changed and call socket_com methods where we pass the channel as a
     * parameter. */
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
}

/* Connect to the Teensy board and then send it all the commands to sync up the
 * state with the GUI. */
void MainWindow::connect(void)
{
    this->com->connect_socket();
    this->updateUI();
}

/* Save the GUI settings to a file.
 *
 * Returns 0 on success, -1 on error. */
int MainWindow::saveToFile(const char *filename)
{
    int i;
    int channel_state[4];
    double vc[4];
    double vcx[4];
    double vgain[4];
    FILE *f;

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

    f = fopen(filename,"w");

    if (!f) {
        fprintf(stderr, "error opening file '%s'!\n",filename);
        return 1;
    }

    fprintf(f,"%s\n", this->ui->ip->text().trimmed().toLocal8Bit().data());
    fprintf(f,"%s\n", this->ui->local_port->text().trimmed().toLocal8Bit().data());
    fprintf(f,"%s\n", this->ui->remote_port->text().trimmed().toLocal8Bit().data());
    for (i = 0; i < 4; i++) {
        fprintf(f,"%i\n", channel_state[i]);
        fprintf(f,"%.2f\n", vc[i]);
        fprintf(f,"%.2f\n", vcx[i]);
        fprintf(f,"%.2f\n", vgain[i]);
    }

    fclose(f);

    return 0;
}

/* Load the GUI settings from a file.
 *
 * Returns 0 on success, -1 on error. */
int MainWindow::loadFromFile(const char *filename)
{
    int i;
    int channel_state[4];
    double vc[4];
    double vcx[4];
    double vgain[4];
    FILE *f;
    char *line;

    channel_state[0] = ui->CH1_on->isChecked();
    channel_state[1] = ui->CH2_on->isChecked();
    channel_state[2] = ui->CH3_on->isChecked();
    channel_state[3] = ui->CH4_on->isChecked();

    vc[0] = ui->vc1->value();
    vc[1] = ui->vc2->value();
    vc[2] = ui->vc3->value();
    vc[3] = ui->vc4->value();

    vcx[1] = ui->vcx2->value();
    vcx[2] = ui->vcx3->value();
    vcx[3] = ui->vcx4->value();

    vgain[0] = ui->vgain1->value();
    vgain[1] = ui->vgain2->value();
    vgain[2] = ui->vgain3->value();
    vgain[3] = ui->vgain4->value();

    f = fopen(filename,"r");

    if (!f) {
        fprintf(stderr, "error opening file settings.txt!");
        return 1;
    }

    line = (char *) malloc(256);
    size_t n = 256;
    if (getline(&line, &n, f) == -1) goto err;
    trim(line);
    ui->ip->setText(line);
    if (getline(&line, &n, f) == -1) goto err;
    trim(line);
    ui->local_port->setText(line);
    if (getline(&line, &n, f) == -1) goto err;
    trim(line);
    ui->remote_port->setText(line);
    for (i = 0; i < 4; i++) {
        if (getline(&line, &n, f) == -1) goto err;
        channel_state[i] = atoi(line);
        if (getline(&line, &n, f) == -1) goto err;
        vc[i] = atof(line);
        if (getline(&line, &n, f) == -1) goto err;
        vcx[i] = atof(line);
        if (getline(&line, &n, f) == -1) goto err;
        vgain[i] = atof(line);
    }
    free(line);

    fclose(f);

    this->ui->CH1_on->setCheckState(channel_state[0] ? Qt::Checked : Qt::Unchecked);
    this->ui->CH2_on->setCheckState(channel_state[1] ? Qt::Checked : Qt::Unchecked);
    this->ui->CH3_on->setCheckState(channel_state[2] ? Qt::Checked : Qt::Unchecked);
    this->ui->CH4_on->setCheckState(channel_state[3] ? Qt::Checked : Qt::Unchecked);

    this->ui->vc1->setValue(vc[0]);
    this->ui->vc2->setValue(vc[1]);
    this->ui->vc3->setValue(vc[2]);
    this->ui->vc4->setValue(vc[3]);

    this->ui->vcx1->setValue(vcx[0]);
    this->ui->vcx2->setValue(vcx[1]);
    this->ui->vcx3->setValue(vcx[2]);
    this->ui->vcx4->setValue(vcx[3]);

    this->ui->vgain1->setValue(vgain[0]);
    this->ui->vgain2->setValue(vgain[1]);
    this->ui->vgain3->setValue(vgain[2]);
    this->ui->vgain4->setValue(vgain[3]);

    return 0;

err:
    free(line);

    fclose(f);

    return -1;
}

/* Function to check the UI state, look for differences with the last state
 * sent to the Teensy board, and make sure to update the board with all changes
 * from the UI. */
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
            this->com->enable_channel(i+1,channel_state[i]);
            last_channel_state[i] = channel_state[i];
        }

        if (vc[i] != this->last_vc[i]) {
            this->com->change_vc(i+1,vc[i]);
            last_vc[i] = vc[i];
        }

        if (vcx[i] != this->last_vcx[i]) {
            this->com->change_vcx(i+1,vcx[i]);
            last_vcx[i] = vcx[i];
        }

        if (vgain[i] != this->last_vgain[i]) {
            this->com->change_vgain(i+1,vgain[i]);
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
    this->saveToFile("settings.txt");
    delete ui;
}

