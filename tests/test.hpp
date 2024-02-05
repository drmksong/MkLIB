#ifndef __TEST_HPP__
#define __TEST_HPP__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <random>
#include <chrono>
#include <format>
#include <boost/make_shared.hpp>
#include "MkMatrix.hpp"
#include "MkPoint.hpp"
#include "MkLine.hpp"
#include "MkRect.hpp"
#include "MkObject.hpp"
#include "MkArray.hpp"

#include "glLib.hpp"

bool point_test();
bool array_test();
void arr_test_move_op();
void shared_test();
void fblr_test();
void pnts_test();

#endif