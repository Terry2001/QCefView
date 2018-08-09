#include "qcefviewtest.h"
#include <QtWidgets/QApplication>
#include <include/QCefSetting.h>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//see DevTools at http://localhost:21199
	QCefSetting::setRemoteDebuggingPort(21199);

	//enable cache and set cache directory
	QString dataPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
	QString cachepath = dataPath + "/cefcache";
	QCefSetting::setCachePath(cachepath);

	QCefViewTest w;
	w.show();
	return a.exec();
}
