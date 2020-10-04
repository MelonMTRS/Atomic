#include <iostream>
#ifndef __ATOMIC__EXCEPTIONS__H
#define __ATOMIC__EXCEPTIONS__H

namespace exceptions {
	enum class ErrorTypes {
		DefaultError,
		PermissionError,
		AuthorizationError,
		NotFoundError
	};

	struct HttpError {
		const std::string message;
		const int status_code;
		exceptions::ErrorTypes errorType = ErrorTypes::DefaultError;
	};

	struct CaptchaFailure {
		const std::string message;
	};

	struct TradeFormFailure {
		const std::string message;
	};
}

#endif