#include "QCefDownloadHandler.h"

QCefDownloadHandler::QCefDownloadHandler(QObject *parent)
	: QObject(parent)
{
}

QCefDownloadHandler::~QCefDownloadHandler()
{
}

void QCefDownloadHandler::OnBeforeDownload(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefDownloadItem> download_item,
	const CefString& suggested_name,
	CefRefPtr<CefBeforeDownloadCallback> callback) {
	CEF_REQUIRE_UI_THREAD();

	// Continue the download and show the "Save As" dialog.
	callback->Continue("", true);
}

void QCefDownloadHandler::OnDownloadUpdated(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefDownloadItem> download_item,
	CefRefPtr<CefDownloadItemCallback> callback) {
	CEF_REQUIRE_UI_THREAD();

	if (download_item->IsComplete()) {

		emit downloadComplete(QString::fromStdString(download_item->GetFullPath().ToString()));

	}
}