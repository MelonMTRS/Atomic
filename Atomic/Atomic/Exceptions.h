#ifndef ATOMIC_EXCEPTIONS_H
#define ATOMIC_EXCEPTIONS_H
#include <string>

namespace atomic {
	void throwException(const std::string& message);

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

	struct TradeFormFailure {
		std::string message;
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

	struct ConfigLoadFailure {
		const std::string message;
	};

	struct ConfigKeyParse {
		const std::string message;
		const std::string key;
	};

	struct UnknownValue {
		const std::string message;
	};
}

#endif