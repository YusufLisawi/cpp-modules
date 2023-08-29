/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:20:23 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/29 18:05:13 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() {
    std::cout << "Constructor called for Dog"<< std::endl;
    this->type = "Dog";
}

Dog::~Dog() {
    std::cout << "Destructor called for Dog"<< std::endl;
}

Dog::Dog(const Dog& other) : Animal(other) {
    std::cout << "Copy constructor called for Dog"<< std::endl;
    *this = other;
}

Dog& Dog::operator=(const Dog& other) {
    std::cout << "Assignment operator called for Dog" << std::endl;
    if (this != &other) {
        this->type = other.type;
    }
    return *this;
}

void Dog::makeSound() const {
    std::cout << "Woof Woof!!" << std::endl;
}