#include "qcefviewtest.h"

#include <windows.h>

#include <QDir>
#include <QCoreApplication>
#include <QHBoxLayout>
#include <QMessageBox>

QCefViewTest::QCefViewTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QHBoxLayout* layout = new QHBoxLayout();
	layout->setContentsMargins(2, 2, 2, 2);
	layout->setSpacing(3);

	connect(ui.btn_changeColor, SIGNAL(clicked()),
		this, SLOT(onBtnChangeColorClicked()));
	layout->addWidget(ui.nativeContainer);

	QDir dir = QCoreApplication::applicationDirPath();
	QString uri = QDir::toNativeSeparators(dir.filePath("web\\QCefViewTestPage.html"));

	//uri = "http://www.bing.com";

	cefview = new CustomCefView(uri, this);
	ui.cefContainer->layout()->addWidget(cefview);
	layout->addWidget(ui.cefContainer);

	centralWidget()->setLayout(layout);

	connect(cefview, &CustomCefView::urlChanged, this, &QCefViewTest::onUrlChanged);
	connect(cefview, &CustomCefView::downloadComplete, this, &QCefViewTest::onDownloadComplete);
}

QCefViewTest::~QCefViewTest() 
{

}

void QCefViewTest::onBtnChangeColorClicked()
{
	cefview->changeColor();
}

void QCefViewTest::onUrlChanged(const QString &url)
{
	this->setWindowTitle(url);
}

void QCefViewTest::onDownloadComplete(const QString &savePath)
{
	QMessageBox::information(this, "download complete", "file at:" + savePath);
}