/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:15:38 by yelaissa          #+#    #+#             */
/*   Updated: 2023/10/22 19:44:54 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector<int> IntVector;
typedef std::vector<IntVector> PairVector;

bool compare(const IntVector& a, const IntVector& b)
{
    return (a.back() < b.back());
}

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
    std::cout << "]" << std::endl;
}

void flattenVector(IntVector collection, IntVector &toInsert)
{
    for (IntVector::iterator it = collection.begin(); it != collection.end(); ++it)
    {
        toInsert.push_back(*it);
    }
}

void splitPairs(PairVector &collection, int pairSize)
{
    PairVector tmp;
    for (PairVector::iterator it = collection.begin(); it != collection.end(); ++it)
    {
        IntVector subVec;
        for (IntVector::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2)
        {
            subVec.push_back(*it2);
            if (subVec.size() == pairSize)
            {
                tmp.push_back(subVec);
                subVec.clear();
            }
        }
        if (subVec.size() > 0)
        {
            tmp.push_back(subVec);
        }
    }
    collection.clear();
    collection = tmp;
}

void pairing(PairVector &collection, PairVector &remain)
{
    PairVector tmp;
    for (PairVector::iterator it = collection.begin(); it != collection.end(); ++it)
    {
        if (it + 1 != collection.end())
        {
            IntVector tmp_vec;
            if ((*it).back() > (*(it + 1)).back())
                std::swap((*it), (*(it + 1)));

            flattenVector(*it, tmp_vec);
            flattenVector(*(it + 1), tmp_vec);
            tmp.push_back(tmp_vec);
            it++;
        }
        else
        {
            IntVector tmp_vec;
            flattenVector(*it, tmp_vec);
            remain.push_back(tmp_vec);
        }
    }
    collection.clear();
    collection = tmp;
}

void remove_last(PairVector &collection, PairVector &remain)
{
    IntVector tmp;
    flattenVector(collection.back(), tmp);
    collection.pop_back();
    remain.push_back(tmp);
}

void mergeInsertion(PairVector &collection)
{
    PairVector remain;

    if (collection.size() == 1)
        return ;
    if (collection.size() % 2 != 0)
    {
        remove_last(collection, remain);
    }
    pairing(collection, remain);

    // std::cout << "collection > ";
    // printVector(collection);
    
    mergeInsertion(collection);
    
    splitPairs(collection, collection.at(0).size() / 2);
    splitPairs(remain, collection.at(0).size() / 2);

    PairVector mainchain;
    PairVector pend;

    for (PairVector::iterator it = collection.begin(); it != collection.end(); it += 2)
    {
        pend.push_back(*it);
        if (it + 1 != collection.end())
            mainchain.push_back(*(it + 1));
    }
    for (PairVector::iterator it = remain.begin(); it != remain.end(); ++it)
        pend.push_back(*it);

    for (PairVector::iterator it = pend.begin(); it != pend.end(); ++it)
    {
        PairVector::iterator tmp_it = std::lower_bound(mainchain.begin(), mainchain.end(), *it, compare);
        mainchain.insert(tmp_it, *it);
    }
    pend.clear();
    // std::cout << "after mainchain > ";
    // printVector(mainchain);
    // std::cout << "after pend > ";
    // printVector(pend);

    collection.clear();
    for (PairVector::iterator it = mainchain.begin(); it != mainchain.end(); ++it)
        collection.push_back(*it);
}

int main(int ac, char **av)
{
    PairVector collection;
    if (ac < 2)
    {
        std::cout << "Usage: ./PmergeMe [numbers...]" << std::endl;
        return (0);
    }
    int i = 1;
    while (av[i])
    {
        int tmp = std::atoi(av[i]);
        if (tmp < 0 || tmp < INT_MIN || tmp > INT_MAX)
            throw std::invalid_argument("Invalid argument " + std::string(av[i]));
        IntVector tmp_vec;
        tmp_vec.push_back(tmp);
        collection.push_back(tmp_vec);
        i++;
    }
    
    std::cout << "before > ";
    printVector(collection);

    clock_t start = clock();
    mergeInsertion(collection);
    clock_t end = clock();

    std::cout << "after > ";
    printVector(collection);

    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken by function: " << time_taken * 1000000 << " microseconds" << std::endl;
}