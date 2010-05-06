#include "metro.h"
#include "ui_metro.h"
#include<QDebug>
#include<QShortcut>

Metro::Metro(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Metro)
{
    ui->setupUi(this);

	s = new Settings();
	s->load();
	int n = s->getInt("number_of_positions");
	qDebug() << "n=" << n;

	graphics = new Graphics();
	graphics->graphicsView = ui->graphicsView;
	graphics->n = n;
	graphics->init();

	simulation = new Simulation();
	simulation->s = s;
	simulation->graphics = graphics;
	simulation->init();


	QShortcut* f1 = new QShortcut( Qt::Key_F1, this );
	connect(f1,SIGNAL(activated()),this,SLOT(on_actionStart_triggered()));

	QShortcut* f2 = new QShortcut( Qt::Key_F2, this );
	connect(f2,SIGNAL(activated()),this,SLOT(on_actionStop_triggered()));

	QShortcut* esc = new QShortcut( Qt::Key_Escape, this );
	connect(esc,SIGNAL(activated()),this,SLOT(close()));
}

Metro::~Metro()
{
	delete graphics;
	delete simulation;
	delete s;
    delete ui;
}

void Metro::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Metro::on_actionStart_triggered()
{
	simulation->start();
}

void Metro::on_actionStop_triggered()
{
	simulation->stopped=true;
}
