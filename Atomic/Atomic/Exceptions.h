#ifndef __ATOMIC__EXCEPTIONS__H
#define __ATOMIC__EXCEPTIONS__H

namespace exceptions {
	enum class ErrorTypes {
		DefaultError,
		PermissionError,
		AuthorizationError,
		RatelimitError,
		NotFoundError
	};

	// Raised when an http request does not return a 2xx
	struct HttpError {
		const std::string message;
		const int status_code;
		exceptions::ErrorTypes errorType = ErrorTypes::DefaultError;
	};

	// Raised when roblox prompts a captcha
	struct CaptchaFailure {
		const std::string message;
	};

	struct TradeFormFailure {
		const std::string message;
	};
}

#endif