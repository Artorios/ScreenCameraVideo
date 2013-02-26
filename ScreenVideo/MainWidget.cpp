#include "MainWidget.h"

void MainWidget::trayIconInitial() {
	//setWindowIcon(icon);
	startIcon = new QIcon("startIcon.bmp");
	stopIcon = new QIcon("stopIcon.bmp");
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(*startIcon);
	trayIcon->setToolTip("Press ctrl+F2 to start/stop record.");
	recordAction = new QAction(QString::fromLocal8Bit("��ʼ¼��/ֹͣ¼�� (Ctrl+F2)"), this);
	minimizeAction = new QAction(QString::fromLocal8Bit("��С�� (&I)"), this);
	maximizeAction = new QAction(QString::fromLocal8Bit("��� (&X)"), this);
	restoreAction = new QAction(QString::fromLocal8Bit("��ԭ (&R)"), this);
	quitAction = new QAction(QString::fromLocal8Bit("�˳� (&Q)"), this);
	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(recordAction);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(minimizeAction);
	trayIconMenu->addAction(maximizeAction);
	trayIconMenu->addAction(restoreAction);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(quitAction);
	trayIcon->setContextMenu(trayIconMenu);
	trayIcon->show();
}

void MainWidget::interfaceInitial() {
	tabWidget = new QTabWidget(this);
	setCentralWidget(tabWidget);
	recordSettings = new QWidget(this);
	transcodeSettings = new QWidget(this);
	tabWidget->addTab(recordSettings, tr("¼������"));
	tabWidget->addTab(transcodeSettings, tr("ת������"));

	QLabel* cameraLabel = new QLabel(tr("�����豸:  "), this);
	cameraLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
	cameraDevice = new QComboBox(this);
	int number = CCameraDS::CameraCount();
	for (int i = 0; i < number; i++) {
		int nBufferSize = 100;
		char* sName = new char[nBufferSize];
		CCameraDS::CameraName(i, sName, nBufferSize);
		cameraDevice->addItem(sName);
	}
	cameraDevice->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

	QLabel* routeLabel = new QLabel(tr("����·��:  "), this);
	routeLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
	route = new QLineEdit(tr("movies"), this);
	route->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	route->setReadOnly(true);
	routeChangeButton = new QPushButton(QString::fromLocal8Bit("����"), this);
	routeChangeButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

	QSpacerItem* spacer = new QSpacerItem(100, 10, QSizePolicy::Expanding, QSizePolicy::Preferred);
	record = new QPushButton(QString::fromLocal8Bit("��ʼ¼��"), this);
	record->setAutoDefault(true);
	record->setDefault(true);
	record->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	quit = new QPushButton(QString::fromLocal8Bit("    �˳�    "), this);
	quit->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

	QHBoxLayout* hBox1 = new QHBoxLayout(this);
	hBox1->addWidget(cameraLabel);
	hBox1->addWidget(cameraDevice);
	QHBoxLayout* hBox2 = new QHBoxLayout(this);
	hBox2->addWidget(routeLabel);
	hBox2->addWidget(route);
	hBox2->addWidget(routeChangeButton);
	QHBoxLayout* hBox3 = new QHBoxLayout(this);
	hBox3->addSpacerItem(spacer);
	hBox3->addWidget(record);
	hBox3->addWidget(quit);
	QVBoxLayout* vBox = new QVBoxLayout(this);
	vBox->addLayout(hBox1);
	vBox->addLayout(hBox2);
	vBox->addLayout(hBox3);
	recordSettings->setLayout(vBox);

	QLabel* resolutionLabel = new QLabel(tr("�ֱ���:    "), this);
	resolutionLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
	resolution = new QComboBox(this);
	resolutionList.append(std::make_pair(1024, 768));
	resolutionList.append(std::make_pair(1024, 576));
	resolutionList.append(std::make_pair(480, 320));
	for(int i = 0; i < resolutionList.size(); i++) {
		resolution->addItem(QString("%1 x %2").arg(resolutionList[i].first).arg(resolutionList[i].second));
	}
	resolution->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

	QLabel* srcRouteLabel = new QLabel(tr("Դ�ļ�:    "), this);
	srcRouteLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
	srcRoute = new QLineEdit(this);
	srcRoute->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	srcRoute->setReadOnly(true);
	srcRouteChange = new QPushButton(tr("����"), this);
	srcRouteChange->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

	QLabel* dstRouteLabel = new QLabel(tr("Ŀ���ļ�:  "), this);
	dstRouteLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
	dstRoute = new QLineEdit(this);
	dstRoute->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	dstRoute->setReadOnly(true);
	dstRouteChange = new QPushButton(tr("����"), this);
	dstRouteChange->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

	progressBar = new QProgressBar(this);
	progressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	transcodeStart = new QPushButton(tr("��ʼת��"), this);
	transcodeStart->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

	QHBoxLayout* hBoxT1 = new QHBoxLayout(this);
	hBoxT1->addWidget(resolutionLabel);
	hBoxT1->addWidget(resolution);
	QHBoxLayout* hBoxT2 = new QHBoxLayout(this);
	hBoxT2->addWidget(srcRouteLabel);
	hBoxT2->addWidget(srcRoute);
	hBoxT2->addWidget(srcRouteChange);
	QHBoxLayout* hBoxT3 = new QHBoxLayout(this);
	hBoxT3->addWidget(dstRouteLabel);
	hBoxT3->addWidget(dstRoute);
	hBoxT3->addWidget(dstRouteChange);
	QHBoxLayout* hBoxT4 = new QHBoxLayout(this);
	hBoxT4->addWidget(progressBar);
	hBoxT4->addWidget(transcodeStart);
	QVBoxLayout* vBoxT = new QVBoxLayout(this);
	vBoxT->addLayout(hBoxT1);
	vBoxT->addLayout(hBoxT2);
	vBoxT->addLayout(hBoxT3);
	vBoxT->addLayout(hBoxT4);
	transcodeSettings->setLayout(vBoxT);
}

void MainWidget::registHotKey() {
	HWND hWnd = this->winId();
	id = GlobalAddAtom(LPCWSTR("myHotKey"));
	UINT fsModifiers = MOD_CONTROL;
	UINT vk = VK_F2;
	if (!RegisterHotKey(hWnd, id, fsModifiers, vk)) 
	{
		QMessageBox::information(this, "Wrong", "Can't regist hot key!");
		this->close();
	}
}