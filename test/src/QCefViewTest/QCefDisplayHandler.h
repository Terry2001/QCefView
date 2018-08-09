#pragma once
#include "include/cef_display_handler.h"
#include "include/wrapper/cef_helpers.h"
#include <QObject>

class QCefDisplayHandler
	: public QObject
	, public CefDisplayHandler
{
	Q_OBJECT

public:
	QCefDisplayHandler(QObject *parent);
	~QCefDisplayHandler();

	void OnAddressChange(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& url) OVERRIDE;

	void OnTitleChange(CefRefPtr<CefBrowser> browser,
		const CefString& title) OVERRIDE;

	void OnFullscreenModeChange(CefRefPtr<CefBrowser> browser,
		bool fullscreen) OVERRIDE;

	bool OnConsoleMessage(CefRefPtr<CefBrowser> browser,
		const CefString& message,
		const CefString& source,
		int line) OVERRIDE;

	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(QCefDisplayHandler);

signals:
	void urlChanged(const QString &url);

};

