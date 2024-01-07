/*
* Auteur: Yassine Seddaoui, Matei Zama
* Matricules: 2204548, 2207283
*/
#pragma once

#include <stdexcept>

class KingException : public std::logic_error {
public:
    using logic_error::logic_error;
};