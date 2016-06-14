#include <string>

#include "TokenHistogram.h"
#include "Token.h"

TokenHistogram::TokenHistogram () {
    this->histogram = TokenHistogram::Histogram();
}