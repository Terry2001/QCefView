#pragma once
#include "include/cef_download_handler.h"
#include "include/wrapper/cef_helpers.h"
#include <QObject>

class QCefDownloadHandler
	: public QObject
	, public CefDownloadHandler
{
	Q_OBJECT

public:
	QCefDownloadHandler(QObject *parent);
	~QCefDownloadHandler();

	// CefDownloadHandler methods
	void OnBeforeDownload(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDownloadItem> download_item,
		const CefString& suggested_name,
		CefRefPtr<CefBeforeDownloadCallback> callback) OVERRIDE;

	void OnDownloadUpdated(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDownloadItem> download_item,
		CefRefPtr<CefDownloadItemCallback> callback) OVERRIDE;

	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(QCefDownloadHandler);

signals:
	void downloadComplete(const QString &savepath);

};

