#include <string>

// Benchmarking functions base on type, mode
void benchmarkBruteForceByIters(int totalSize = 2500, int largeBodyCount = 2, int iters = 100);
void benchmarkBarnesHutByIters(int totalSize = 10000, int largeBodyCount = 3, int iters = 500);
void benchmarkThreadedBarnesHutByIters(int totalSize = 25000, int largeBodyCount = 4, int iters = 500);

void benchmarkBruteForceByTime(int totalSize = 2500, int largeBodyCount = 2, int time = 20000);
void benchmarkBarnesHutByTime(int totalSize = 15000, int largeBodyCount = 3, int time = 20000);
void benchmarkThreadedBarnesHutByTime(int totalSize = 15000, int largeBodyCount = 3, int time = 20000);

// Default simulation parameters
int defaultSize(std::string type, std::string mode) {
    if (type == "bruteforce") { return 2500; }
    if (type == "barneshut") { return mode == "iters" ?  10000 : 15000; }
    if (type == "threadedbh") { return mode == "iters" ? 25000 : 15000; }
    else { return 0; }
}
int defaultLargeCount(std::string type, std::string mode) {
    if (type == "bruteforce") { return 2; }
    if (type == "barneshut") { return 3; }
    if (type == "threadedbh") { return mode == "iters" ? 4 : 3; }
    else { return 0; }
}
int defaultSimCount(std::string type, std::string mode) {
    if (mode == "time") { return 20000; }
    else if (mode == "iters") {
        if (type == "bruteforce") { return 100; }
        else { return 500; }}
    return 0;
}

// Simulation runner template
template <typename F>
void runSimulation(F func, const std::string& type, const std::string& mode, int totalSize, int largeCount, int count) {
    func(
        totalSize == -1 ? defaultSize(type, mode) : totalSize,
        largeCount == -1 ? defaultLargeCount(type, mode) : largeCount,
        (count == -1 || count == 0) ? defaultSimCount(type, mode) : count
    );
}

int main(int argc, char* argv[]) {
    // Get inputs
    std::string type = argc > 1 ? argv[1] : "all";
    std::string mode = argc > 2 ? argv[2] : "inf";

    int totalSize = argc > 3 ? std::stoi(argv[3]) : -1;
    int largeCount = argc > 4 ? std::stoi(argv[4]) : -1;
    int count = argc > 5 ? std::stoi(argv[5]) : -1;

    if (mode != "time" && mode != "iters") { count = 0; } // Infinite simulation if not benchmarking mode
    
    // Run simulation based on choice
    if (type == "bruteforce") {
        if (mode == "time") { runSimulation(benchmarkBruteForceByTime, type, mode, totalSize, largeCount, count); } 
        else { runSimulation(benchmarkBruteForceByIters, type, mode, totalSize, largeCount, count); }
    } else if (type == "barneshut") {
        if (mode == "time") { runSimulation(benchmarkBarnesHutByTime, type, mode, totalSize, largeCount, count); } 
        else { runSimulation(benchmarkBarnesHutByIters, type, mode, totalSize, largeCount, count); }
    } else if (type == "threadedbh") {
        if (mode == "time") { runSimulation(benchmarkThreadedBarnesHutByTime, type, mode, totalSize, largeCount, count); } 
        else { runSimulation(benchmarkThreadedBarnesHutByIters, type, mode, totalSize, largeCount, count); }
    } else { // Run all benchmarking if no specific choice
        runSimulation(benchmarkBruteForceByIters, "bruteforce", "iters", totalSize, largeCount, count);
        runSimulation(benchmarkBarnesHutByIters, "barneshut", "iters", totalSize, largeCount, count);
        runSimulation(benchmarkThreadedBarnesHutByIters, "threadedbh", "iters", totalSize, largeCount, count);
        runSimulation(benchmarkBruteForceByTime, "bruteforce", "time", totalSize, largeCount, count);
        runSimulation(benchmarkBarnesHutByTime, "barneshut", "time", totalSize, largeCount, count);
        runSimulation(benchmarkThreadedBarnesHutByTime, "threadedbh", "time", totalSize, largeCount, count);
    }

    return 0;
}