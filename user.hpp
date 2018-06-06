#ifndef USER_HPP
#define USER_HPP
#include "string.hpp"

class User {
public:
	tstring<20> password, email, phone;
	tstring<40> name;
        char privilege;
        unsigned int id;
};

#endif
