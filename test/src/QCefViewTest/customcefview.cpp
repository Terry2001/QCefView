#include <windows.h>
#include <QMessageBox>
#include <QColor>
#include "customcefview.h"
#include "QCefDownloadHandler.h"
#include "QCefDisplayHandler.h"


CustomCefView::CustomCefView(const QString& url, QWidget *parent)
	: QCefView(url, parent)
{
	QCefDownloadHandler *downloadHandler = new QCefDownloadHandler(this);
	setDownloadHandler(downloadHandler);

	QCefDisplayHandler *displayHandler = new QCefDisplayHandler(this);
	setDisplayHandler(displayHandler);

	connect(displayHandler, &QCefDisplayHandler::urlChanged, this, &CustomCefView::onUrlChanged);
	connect(downloadHandler, &QCefDownloadHandler::downloadComplete, this, &CustomCefView::onDownloadComplete);
}

CustomCefView::~CustomCefView()
{

}

void CustomCefView::changeColor()
{
	qsrand(::GetTickCount());
	QColor color(qrand());

	QCefEvent event("colorChangedEvent");
	event.setStringProperty("color", color.name());
	broadcastEvent("colorChange", event);
}

void CustomCefView::onQCefUrlRequest(const QString& url)
{
	QString title("QCef Url Request");
	QString text = QString(
		"Current Thread: QT_UI\r\n"
		"Url: %1").arg(url);

	QMessageBox::information(this->window(), title, text);
}

void CustomCefView::onQCefQueryRequest(const QCefQuery& query)
{
	QString title("QCef Query Request");
	QString text = QString(
		"Current Thread: QT_UI\r\n"
		"Query: %1").arg(query.reqeust());

	QMessageBox::information(this->window(), title, text);

	QString response = query.reqeust().toUpper();
	query.setResponseResult(true, response);
	responseQCefQuery(query);
}

void CustomCefView::onInvokeMethodNotify(int browserId, 
	int frameId, 
	const QString& method, 
	const QVariantList& arguments)
{
	if (0 == method.compare("onDragAreaMouseDown"))
	{
		HWND hWnd = ::GetAncestor((HWND)getCefWinId(), GA_ROOT);
		
		// get current mouse cursor position
		POINT pt;
		::GetCursorPos(&pt);

		// in case the mouse is being captured, try to release it
		::ReleaseCapture();

		// simulate that the mouse left button is down on the title area
		::SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, POINTTOPOINTS(pt));
		return;
	}

	QString title("QCef InvokeMethod Notify");
	QString text = QString(
		"Current Thread: QT_UI\r\n"
		"Method: %1\r\n"
		"Arguments: ...")
		.arg(method);

	QMessageBox::information(this->window(), title, text);
}

void CustomCefView::onUrlChanged(const QString &url)
{
	emit urlChanged(url);
}

void CustomCefView::onDownloadComplete(const QString &savepath)
{
	emit downloadComplete(savepath);
}