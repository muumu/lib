#ifndef INDEXMAPPER_H
#define INDEXMAPPER_H


#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
#include <functional>

template <int Min, int Max>
class IndexMapper {
    static const unsigned Size = Max - Min + 1;
    std::vector<int> map_;
    std::vector<int> rev_map_;
    int index_ = 0;
public:
    IndexMapper() : map_(Size, -1), rev_map_(Size, -1) {}

    void make_map(const std::vector<std::vector<int> >& sets) {
        for (auto&& set : sets) {
            for (auto&& elem : set) {
                if (map_[elem - Min] == -1) {
                    update(elem - Min, index_);
                    ++index_;
                }
            }
        }
    }

    void update(int key, int value) {
        map_[key] = value;
        rev_map_[value] = key;
    }

    int get_value(int i) const {
        return map_[i - Min] + Min;
    }

    int get_key(int i) const {
        return rev_map_[i - Min] + Min;
    }

    std::string to_string() const {
        using namespace std::placeholders;
        return to_string(std::bind(&IndexMapper::get_value, this, _1)) +
            to_string(std::bind(&IndexMapper::get_key, this, _1));
    }
private:
    template <typename Map>
    std::string to_string(const Map& mp) const {
        std::stringstream ss;
        ss << "{";
        for (int i = Min; i < Max; ++i) {
            ss << "{" << i << ", " << mp(i) << "}" << ", ";
        }
        ss << "{" << Max << ", " << mp(Max) << "}}" << std::endl;
        return ss.str();
    }
};

#endif // INDEXMAPPER_H
