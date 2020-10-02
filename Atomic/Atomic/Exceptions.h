#include <iostream>
#ifndef __ATOMIC__EXCEPTIONS__H
#define __ATOMIC__EXCEPTIONS__H

namespace exceptions {
	struct HttpError {
		const std::string message;
		const int status_code;
	};

	struct CaptchaFailure {
		const std::string message;
	};

	struct TradeFormFailure {
		const std::string message;
	};
}

#endif