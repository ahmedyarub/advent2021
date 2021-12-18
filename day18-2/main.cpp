#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class number {
public:
    void setParent(number *const &parent) {
        _parent = parent;
    }

    void setValue(int value) {
        is_simple = true;
        simple_value = value;
    }

    void setLeft(number *const &left) {
        is_simple = false;
        left_branch = left;
    }

    void setRight(number *const &right) {
        is_simple = false;
        right_branch = right;
    }

    void addValue(int val) {
        simple_value += val;
    }

    [[nodiscard]] int get_simple_value() const {
        return simple_value;
    }

    void split_explode() {
        while (explode() || split()) {}
    }

    number *findLeftNeighbour() {
        auto child = this;
        auto parent = _parent;
        while (parent != nullptr && parent->isLeftChild(child)) {
            child = parent;
            parent = parent->getParent();
        }
        if (parent == nullptr) {
            return nullptr;
        }
        auto left_neighbour = parent->getLeftChild();
        while (!left_neighbour->isSimple()) {
            left_neighbour = left_neighbour->getRightChild();
        }
        return left_neighbour;
    }

    number *findRightNeighbour() {
        auto child = this;
        auto parent = _parent;
        while (parent != nullptr && parent->isRightChild(child)) {
            child = parent;
            parent = parent->getParent();
        }
        if (parent == nullptr) {
            return nullptr;
        }
        auto right_neighbour = parent->getRightChild();
        while (!right_neighbour->isSimple()) {
            right_neighbour = right_neighbour->getLeftChild();
        }
        return right_neighbour;
    }

    number *getParent() {
        return _parent;
    }

    number *getLeftChild() {
        return left_branch;
    }

    number *getRightChild() {
        return right_branch;
    }

    [[nodiscard]] bool isSimple() const {
        return is_simple;
    }

    bool isLeftChild(number const *ptr) const {
        return ptr == left_branch;
    }

    bool isRightChild(number const *ptr) const {
        return ptr == right_branch;
    }

    [[nodiscard]] int getMagnitude() const {
        if (is_simple) {
            return simple_value;
        }
        return 3 * left_branch->getMagnitude() + 2 * right_branch->getMagnitude();
    }

private:
    bool is_simple = false;
    int simple_value = 0;
    number *left_branch = nullptr;
    number *right_branch = nullptr;
    number *_parent = nullptr;

    bool explode(int depth = 0) {
        if (is_simple) {
            return false;
        }
        if (depth >= 4) {
            auto left_neighbour = findLeftNeighbour();
            auto right_neighbour = findRightNeighbour();
            if (left_neighbour != nullptr) {
                left_neighbour->addValue(left_branch->get_simple_value());
            }
            if (right_neighbour != nullptr) {
                right_neighbour->addValue(right_branch->get_simple_value());
            }
            is_simple = true;
            simple_value = 0;
            left_branch = nullptr;
            right_branch = nullptr;
            return true;
        }
        if (left_branch->explode(depth + 1)) {
            return true;
        }
        if (right_branch->explode(depth + 1)) {
            return true;
        }
        return false;
    }

    bool split() {
        if (!is_simple) {
            if (left_branch->split()) {
                return true;
            }
            if (right_branch->split()) {
                return true;
            }
            return false;
        }

        if (simple_value > 9) {
            is_simple = false;
            left_branch = new number();
            right_branch = new number();
            left_branch->setValue(simple_value / 2);
            right_branch->setValue(simple_value - left_branch->get_simple_value());
            number *me{};
            if (_parent->isRightChild(this)) {
                me = _parent->getRightChild();
            } else {
                me = _parent->getLeftChild();
            }
            left_branch->setParent(me);
            right_branch->setParent(me);
            simple_value = 0;
            return true;
        }
        return false;
    }
};

std::vector<number *> parseFile(const std::string &file_name) {
    std::vector<number *> numbers{};

    std::ifstream file(file_name);
    std::string str;
    while (std::getline(file, str)) {
        auto cur_num = new number();

        numbers.push_back(cur_num);
        std::deque<number *> parents;

        for (const auto &chr: str) {
            if (chr == '[') {
                parents.push_back(cur_num);
                cur_num = new number();
                cur_num->setParent(parents.back());
                parents.back()->setLeft(cur_num);
            }
            if (chr >= '0' && chr <= '9') {
                cur_num->setValue(chr - '0');
            }
            if (chr == ',') {
                cur_num = new number();
                cur_num->setParent(parents.back());
                parents.back()->setRight(cur_num);
            }
            if (chr == ']') {
                cur_num = parents.back();
                parents.pop_back();
            }
        }
    }

    return numbers;
}

number *add(number *a, number *b) {
    auto result = new number();

    result->setLeft(a);
    result->setRight(b);
    a->setParent(result);
    b->setParent(result);
    result->split_explode();

    return result;
}

int main() {
    std::string line;
    std::fstream file("input.txt");

    std::getline(file, line);

    auto numbers = parseFile("input.txt");

    int max_magnitude = 0;
    for (const auto &number1: numbers) {
        for (const auto &number2: numbers) {
            if (number1 == number2) {
                continue;
            }

            auto res = add(number1, number2);
            auto mag = res->getMagnitude();
            if (mag > max_magnitude) {
                max_magnitude = mag;
            }
        }
    }

    std::cout << max_magnitude;

    return 0;
}