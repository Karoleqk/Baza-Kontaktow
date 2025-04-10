#include "user.h"

User::User() : Id(), Name(""), Password("") {

}

User *currentUser = nullptr;
