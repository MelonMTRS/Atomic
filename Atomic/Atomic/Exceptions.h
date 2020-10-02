#include <iostream>
#ifndef __ATOMIC__EXCEPTIONS__H
#define __ATOMIC__EXCEPTIONS__H

namespace exceptions {
	struct HttpError {
		std::string message;
		const int status_code;
	};
}

#endif