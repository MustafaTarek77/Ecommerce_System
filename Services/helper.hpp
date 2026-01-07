#ifndef HELPER_HPP
#define HELPER_HPP

#include <vector>
#include "../Models/product.hpp"

void clearScreen();
void waitForEnter();
void printProductsTable(const std::vector<Product>& products);

#endif
