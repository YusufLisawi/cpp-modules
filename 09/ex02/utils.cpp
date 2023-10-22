/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:22:03 by yelaissa          #+#    #+#             */
/*   Updated: 2023/10/22 22:36:57 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void printVector(IntVector collection)
{
    std::cout << "[";
    for (IntVector::iterator it = collection.begin(); it != collection.end(); ++it)
    {
        std::cout << *it << ((it + 1 != collection.end()) ? ", " : "");
    }
    std::cout << "]" << std::endl;
}

void printVector(PairVector collection)
{
    std::cout << "[";
    for (PairVector::iterator it = collection.begin(); it != collection.end(); ++it)
    {
        std::cout << "[";
        for (IntVector::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2)
            std::cout << *it2 << ((it2 + 1 != (*it).end()) ? ", " : "");
        std::cout << "]";
    }
    // std::cout << std::endl;
    std::cout << "]" << std::endl;
}

void flattenVector(IntVector collection, IntVector &toInsert)
{
    for (IntVector::iterator it = collection.begin(); it != collection.end(); ++it)
    {
        toInsert.push_back(*it);
    }
}