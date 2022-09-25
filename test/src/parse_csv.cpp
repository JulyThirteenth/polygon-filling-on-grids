#include "../include/test/parse_csv.h"

namespace JulyThirteenth
{
    std::shared_ptr<struct GridMap> parseCsv(const std::string &csv_path, double padding, double resolution)
    {
        std::shared_ptr<struct GridMap> p;
        std::cout << std::fixed << std::setprecision(6); //设置数据流保留小数点后6位
        std::fstream csv_reader;
        csv_reader.open(csv_path.c_str(), std::ios::in);
        if (!csv_reader.is_open())
        {
            p = nullptr;
            return p;
        }
        std::string csv_data;
        csv_reader >> csv_data;
        csv_reader.close();
        int id = 0, sub_id = 0;
        while (csv_data[id + sub_id] != ',') //障碍物个数
        {
            sub_id++;
        }
        int obstacle_num = atof(csv_data.substr(id, sub_id).c_str());
        id += (++sub_id);
        sub_id = 0;
        std::vector<int> obstacle_vertex_num;
        for (int i = 0; i < obstacle_num; i++)
        {
            while (csv_data[id + sub_id] != ',') //每个障碍物顶点个数
            {
                sub_id++;
            }
            obstacle_vertex_num.push_back(atof(csv_data.substr(id, sub_id).c_str()));
            id += (++sub_id);
            sub_id = 0;
        }
        std::vector<std::vector<Point>> obstacles_vertexes;
        std::vector<Point> obstacle_vertexes;
        Point vertex;
        for (int i = 0; i < obstacle_num; i++)
        {
            obstacle_vertexes.clear();
            for (int j = 0; j < obstacle_vertex_num[i]; j++)
            {
                while (csv_data[id + sub_id] != ',') //障碍物顶点x坐标
                {
                    sub_id++;
                }
                vertex.x = atof(csv_data.substr(id, sub_id).c_str());
                id += (++sub_id);
                sub_id = 0;
                while (csv_data[id + sub_id] != ',') //障碍物顶点y坐标
                {
                    sub_id++;
                    if (id + sub_id == csv_data.size()) // csv 文件最后一个数据无‘,’，需要判断是否退出循环
                        break;
                }
                vertex.y = atof(csv_data.substr(id, sub_id).c_str());
                id += (++sub_id);
                sub_id = 0;
                obstacle_vertexes.push_back(vertex);
            }
            obstacles_vertexes.push_back(obstacle_vertexes);
        }
        std::vector<double> vertex_x, vertex_y;
        for (int i = 0; i < obstacles_vertexes.size(); i++)
        {
            for (int j = 0; j < obstacles_vertexes[i].size(); j++)
            {
                vertex_x.push_back(obstacles_vertexes[i][j].x);
                vertex_y.push_back(obstacles_vertexes[i][j].y);
            }
        }
        double minX = *std::min_element(vertex_x.begin(), vertex_x.end());
        double maxX = *std::max_element(vertex_x.begin(), vertex_x.end());
        double minY = *std::min_element(vertex_y.begin(), vertex_y.end());
        double maxY = *std::max_element(vertex_y.begin(), vertex_y.end());
        Point corrd_shift = {minX - padding / 2, minY - padding / 2};
        std::cout << "corrd_shift: "
                  << "(" << corrd_shift.x << "," << corrd_shift.y << ")" << std::endl;
        for (int i = 0; i < obstacles_vertexes.size(); i++)
        {
            for (int j = 0; j < obstacles_vertexes[i].size(); j++)
            {
                obstacles_vertexes[i][j].x -= corrd_shift.x;
                obstacles_vertexes[i][j].y -= corrd_shift.y;
            }
        }
        int cols = std::ceil((maxX + padding / 2 - corrd_shift.x) / resolution);
        int rows = std::ceil((maxY + padding / 2 - corrd_shift.y) / resolution);
        p.reset(new struct GridMap(cols, rows));
        std::vector<intPoint> polygon_area;
        for (int i = 0; i < obstacles_vertexes.size(); i++)
        {
            fillPolygon(obstacles_vertexes[i], resolution, polygon_area);
        }
        for (int i = 0; i < polygon_area.size(); i++)
        {
            p->grids[polygon_area[i].x][polygon_area[i].y] = true;
        }
        return p;
    }
}