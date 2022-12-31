#include <fstream>
#include <string>
#include <stack>

#include "bvh_parser.h"

joint *create_joint_tree(std::ifstream &stream)
{
    auto *root = new joint();
    std::stack<joint *> s;

    s.push(root);

    std::string token;

    while (!s.empty())
    {
        auto node = s.top();
        stream >> token;

        if (token == "ROOT")
        {
            stream >> node->name;
            node->joint_type = "ROOT";
        }
        else if (token == "JOINT")
        {
            auto child = new joint();
            child->joint_type = "JOINT";
            stream >> child->name;
            node->children.push_back(child);
            s.push(child);
        }
        else if (token == "OFFSET")
        {
            stream >> node->offset_x;
            stream >> node->offset_y;
            stream >> node->offset_z;
        }
        else if (token == "CHANNELS")
        {
            size_t channel_size;
            stream >> channel_size;

            std::string channel;

            for (auto i = 0; i < channel_size; i++)
            {
                stream >> channel;
                node->channels.push_back(channel);
            }
        }
        else if (token == "End")
        {
            auto child = new joint();
            child->name = node->name + "_End";
            node->children.push_back(child);
            s.push(child);
        }
        else if (token == "}")
        {
            s.pop();
        }
    }

    return root;
}

void read_meta(META &meta_data, std::ifstream &stream) {
    std::string buffer;
    stream >> buffer;   // Motion
    stream >> buffer;   // Frames
    stream >> meta_data.frame;
    stream >> buffer;
    stream >> buffer; 
    stream >> meta_data.frame_time;
}

void populate_motion_data(joint *root, std::ifstream &stream)
{
    std::stack<joint*> s;
    s.push(root);

    while (!s.empty()) 
    {
        auto node = s.top();
        s.pop();
        std::vector<double> motions;
        double motion;

        for (auto i = 0; i < node->channels.size(); i++)
        {
            stream >> motion;
            motions.push_back(motion);
        }

        for (auto it = node->children.rbegin(); it != node->children.rend(); it++)
        {
            s.push(*it);
        }
    }
}


int main(int argc, char **argv)
{
    std::ifstream file(argv[1]);

    auto root = create_joint_tree(file);
    META meta_data;

    read_meta(meta_data, file);
    populate_motion_data(root, file);
    
    jsonify(*root, meta_data);
    file.close();
    return 0;
}
