#include <string>

void benchmarkBruteForceByIters(int totalSize = 2500, int largeBodyCount = 2, int iters = 100);
void benchmarkBarnesHutByIters(int totalSize = 10000, int largeBodyCount = 3, int iters = 500);
void benchmarkThreadedBarnesHutByIters(int totalSize = 25000, int largeBodyCount = 4, int iters = 500);

void benchmarkBruteForceByTime(int totalSize = 2500, int largeBodyCount = 2, int time = 20000);
void benchmarkBarnesHutByTime(int totalSize = 15000, int largeBodyCount = 3, int time = 20000);
void benchmarkThreadedBarnesHutByTime(int totalSize = 15000, int largeBodyCount = 3, int time = 20000);

int defaultSize(std::string type, std::string mode) {
    if (type == "bruteforce") { return 2500; }
    if (type == "barneshut") { return mode == "iters" ?  10000 : 15000; }
    if (type == "threadedbh") { return mode == "iters" ? 25000 : 15000; }
    else { return 0; }
}

int defaultLargeBodyCount(std::string type, std::string mode) {
    if (type == "bruteforce") { return 2; }
    if (type == "barneshut") { return 3; }
    if (type == "threadedbh") { return mode == "iters" ? 4 : 3; }
    else { return 0; }
}

int getSimSize(std::string type, std::string mode, int input) {
    if (input == -1) { return defaultSize(type, mode); }
    return input;
}

int getLargeBodyCount(std::string type, std::string mode, int input) {
    if (input == -1) { return defaultLargeBodyCount(type, mode); }
    return input;
}


int main(int argc, char* argv[]) {
    std::string type = argc > 1 ? argv[1] : "all";
    std::string mode = argc > 2 ? argv[2] : "inf";

    int totalSize = argc > 3 ? std::stoi(argv[3]) : -1;
    int largeCount = argc > 4 ? std::stoi(argv[4]) : -1;
    int count = argc > 5 ? std::stoi(argv[5]) : -1;

    if (type == "bruteforce") {
        if (mode == "time") { benchmarkBruteForceByTime(getSimSize(type, mode, totalSize), getLargeBodyCount(type, mode, largeCount), count); } 
        else if (mode == "iters") { benchmarkBruteForceByIters(getSimSize(type, mode, totalSize), getLargeBodyCount(type, mode, largeCount), count); }
        else { benchmarkBruteForceByIters(getSimSize(type, mode, totalSize), getLargeBodyCount(type, mode, largeCount), 0); }
    } else if (type == "barneshut") {
        if (mode == "time") { benchmarkBarnesHutByTime(getSimSize(type, mode, totalSize), getLargeBodyCount(type, mode, largeCount), count); } 
        else if (mode == "iters") { benchmarkBarnesHutByIters(getSimSize(type, mode, totalSize), getLargeBodyCount(type, mode, largeCount), count); }
        else { benchmarkBarnesHutByIters(getSimSize(type, mode, totalSize), getLargeBodyCount(type, mode, largeCount), 0); }
    } else if (type == "threadedbh") {
        if (mode == "time") { benchmarkThreadedBarnesHutByTime(getSimSize(type, mode, totalSize), getLargeBodyCount(type, mode, largeCount), count); } 
        else if (mode == "iters") { benchmarkThreadedBarnesHutByIters(getSimSize(type, mode, totalSize), getLargeBodyCount(type, mode, largeCount), count); }
        else { benchmarkThreadedBarnesHutByIters(getSimSize(type, mode, totalSize), getLargeBodyCount(type, mode, largeCount), 0); }
    } else {
        benchmarkBruteForceByIters();
        benchmarkBarnesHutByIters();
        benchmarkThreadedBarnesHutByIters();
        benchmarkBruteForceByTime();
        benchmarkBarnesHutByTime();
        benchmarkThreadedBarnesHutByTime();
    }

    return 0;
}