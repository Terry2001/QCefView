
#include "QCefDisplayHandler.h"


QCefDisplayHandler::QCefDisplayHandler(QObject *parent)
	: QObject(parent)
{
}


QCefDisplayHandler::~QCefDisplayHandler()
{
}


void QCefDisplayHandler::OnAddressChange(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	const CefString& url) {
	CEF_REQUIRE_UI_THREAD();

	// Only update the address for the main (top-level) frame.
	if (frame->IsMain())
	{
		emit urlChanged(QString::fromStdString(url.ToString()));
	}
}

void QCefDisplayHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
	const CefString& title) {
	CEF_REQUIRE_UI_THREAD();

	//NotifyTitle(title);
}

void QCefDisplayHandler::OnFullscreenModeChange(CefRefPtr<CefBrowser> browser,
	bool fullscreen) {
	CEF_REQUIRE_UI_THREAD();

	//NotifyFullscreen(fullscreen);
}

bool QCefDisplayHandler::OnConsoleMessage(CefRefPtr<CefBrowser> browser,
	const CefString& message,
	const CefString& source,
	int line) {
	CEF_REQUIRE_UI_THREAD();

	/*FILE* file = fopen(console_log_file_.c_str(), "a");
	if (file) {
		std::stringstream ss;
		ss << "Message: " << message.ToString() << NEWLINE <<
			"Source: " << source.ToString() << NEWLINE <<
			"Line: " << line << NEWLINE <<
			"-----------------------" << NEWLINE;
		fputs(ss.str().c_str(), file);
		fclose(file);

		if (first_console_message_) {
			test_runner::Alert(
				browser, "Console messages written to \"" + console_log_file_ + "\"");
			first_console_message_ = false;
		}
	}*/

	return false;
}
