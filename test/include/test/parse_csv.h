#ifndef _PARSE_CSV_H_
#define _PARSE_CSV_H_

#include <cmath>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "fill_polygon.h"

namespace JulyThirteenth
{
    struct GridMap
    {
        int cols;
        int rows;
        std::vector<std::vector<bool>> grids;
        
        GridMap(int cols_, int rows_)
        {
            cols = cols_;
            rows = rows_;
            std::vector<bool> temp;
            for (int i = 0; i < cols; i++)
            {
                for (int j = 0; j < rows; j++)
                {
                    temp.push_back(false);
                }
                grids.push_back(temp);
                temp.clear();
            }
        }
    };

    std::shared_ptr<struct GridMap> parseCsv(const std::string &csv_path, double padding, double resolution);
}

#endif