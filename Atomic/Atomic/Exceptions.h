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

	struct HttpError {
		const std::string message;
		const int status_code;
		atomic::ErrorTypes errorType = ErrorTypes::DefaultError;
	};

	struct KeyNotFound {
		std::string message;
		atomic::ErrorTypes errorType = ErrorTypes::DefaultError;
	};

	struct ItemNotFound {
		std::string message;
		atomic::ErrorTypes errorType = ErrorTypes::DefaultError;
	};

	struct ItemFetchFailure {
		std::string message;
		atomic::ErrorTypes errorType = ErrorTypes::DefaultError;
	};

	struct CaptchaFailure {
		const std::string message;
		atomic::ErrorTypes errorType = ErrorTypes::DefaultError;
	};

	struct TradeFormFailure {
		const std::string message;
		atomic::ErrorTypes errorType = ErrorTypes::DefaultError;
	};
}

#endif