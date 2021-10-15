#include <vector>
#include <sys/time.h>
#include <iostream>
#include <cstring>
#include "mat.h"

static const size_t NUM_TESTS = 1;

template<typename T>
std::vector<std::pair<double, double>> test(const std::vector<size_t> sizes, const std::string &filePrefix="") {
    std::vector<std::pair<double, double>> elapsed;
    std::vector<std::pair<double, double>> result;
    timeval start;
    timeval temp;
    timeval end;
    double mmDuration = 0.0;
    double mvDuration = 0.0;
    for (auto s:sizes) {
        std::cout << "size: " << s << std:: endl;
        elapsed.clear();
        for (size_t i = 0; i != NUM_TESTS; ++i) {
            Mat<T> mat1(s, s);
            Mat<T> mat2(s, s);
            Mat<T> vec(1, s);
            mat1.fillRandom();
            mat2.fillRandom();
            vec.fillRandom();

            gettimeofday(&start, nullptr);
            auto mmProd = mat1 * mat2;
            gettimeofday(&temp, nullptr);
            auto mvProd = mat1 * vec;
            gettimeofday(&end, nullptr);

            mmDuration = temp.tv_sec - start.tv_sec + (static_cast<double>(temp.tv_usec - start.tv_usec)) / 1e6;
            mvDuration = end.tv_sec - temp.tv_sec + (static_cast<double>(end.tv_usec - temp.tv_usec)) / 1e6;
            std::cout << '\t' << i << '\t' << mmDuration << '\t' << mvDuration << std::endl;
            elapsed.emplace_back(std::make_pair(mmDuration, mvDuration));

            if (i == 0) {
                saveToCsv(mat1, filePrefix + std::to_string(s) + "_mat1.csv");
                saveToCsv(mat2, filePrefix + std::to_string(s) + "_mat2.csv");
                saveToCsv(vec, filePrefix + std::to_string(s) + "_vec.csv");
                saveToCsv(mmProd, filePrefix + std::to_string(s) + "_mm_prod.csv");
                saveToCsv(mvProd, filePrefix + std::to_string(s) + "_mv_prod.csv");
            }
        }
        double mmSum = 0.0;
        double mvSum = 0.0;
        for (auto &e: elapsed) {
            auto& [mm, mv] = e;
            mmSum += mm;
            mvSum += mv;
        }
        mmSum /= NUM_TESTS;
        mvSum /= NUM_TESTS;
        std::cout << "\tsize: " << s << '\t' << mmSum << '\t' << mvSum << std::endl;
        result.emplace_back(std::make_pair(mmSum, mvSum));
    }
    return result;
}

template<typename T>
void printResult(const std::vector<T> &result, const std::vector<size_t> &sizes) {
    for (size_t i = 0; i != result.size(); ++i) {
        auto &[mm, mv] = result[i];
        std::cout << sizes[i] << " :\t" <<
                  "mm :\t" << mm << "\t\t" <<
                  "mv :\t" << mv << std::endl;
    }
}

int main(int argc, char **argv) {
    const std::vector<size_t> sizes = {2, 3, 500, 512, 1000, 1024};

    if (argc > 1) {
        if (strcmp(argv[1], "float") == 0) {
            std::cout << "float:\n";
            auto result = test<float>(sizes, "float_");
            printResult(result, sizes);
        } else if (strcmp(argv[1], "double") == 0) {
            std::cout << "double:\n";
            auto result = test<double>(sizes, "double_");
            printResult(result, sizes);
        } else if (strcmp(argv[1], "int") == 0) {
            std::cout << "int:\n";
            auto result = test<int>(sizes, "int_");
            printResult(result, sizes);
        } else {
            std::cout << "parameter not recognized. Use \"float\", \"double\" or \"int\"\n";
        }
    }
    return 0;
}