#ifndef __ATOMIC__EXCEPTIONS__H
#define __ATOMIC__EXCEPTIONS__H

namespace atomic {
	enum class ErrorTypes {
		DefaultError,
		PermissionError,
		AuthorizationError,
		RatelimitError,
		NotFoundError
	};

	// Raised when an http request does not return a 2xx status code
	struct HttpError {
		const std::string message;
		const int status_code;
		atomic::ErrorTypes errorType = ErrorTypes::DefaultError;
	};

	// Raised when a config key cannot be found
	struct KeyNotFound {
		std::string message;
	};

	// Raised when roblox prompts a captcha
	struct CaptchaFailure {
		const std::string message;
	};

	// Raised when a trade couldn't be formed with the user
	// This may get raised often, it's expected to be handled
	struct TradeFormFailure {
		const std::string message;
	};
}

#endif