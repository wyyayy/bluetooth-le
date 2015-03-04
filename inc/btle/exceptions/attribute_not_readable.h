#ifndef ATTRIBUTE_NOT_READABLE_H
#define ATTRIBUTE_NOT_READABLE_H

#include <stdexcept>
#include <string>

namespace btle {
    namespace exceptions {
        class attribute_not_readable: public std::runtime_error{
        public:
            explicit attribute_not_readable(const std::string& what);
            attribute_not_readable();
            attribute_not_readable(const attribute_not_readable& other);
        };
    }
}
#endif // ATTRIBUTE_NOT_READABLE_H

