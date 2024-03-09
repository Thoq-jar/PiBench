#include <iostream>
#include <iomanip>
#include <thread>
#include <cmath>
#include <vector>
#include <mutex>
#include <chrono>
#include <atomic>
#include <cstdlib>

using namespace std;
std::mutex mtx;
long double a = 1.0;
long double b = 1.0 / std::sqrt(2);
long double t = 0.25;
long double p = 1.0;

void calculatePi(int num_iterations, int thread_id, std::atomic<int>& iterations_completed) {
    for (int i = 0; i < num_iterations; i++) {
        long double a_new = (a + b) / 2;
        long double b_new = std::sqrt(a * b);
        long double t_new = t - p * std::pow(a - a_new, 2);
        long double p_new = 2 * p;

        mtx.lock();
        a = a_new;
        b = b_new;
        t = t_new;
        p = p_new;
        mtx.unlock();

        iterations_completed++;
    }
}

int main() {
    cout << "Calculating Pi with 1,000,000 digits and 10,000,000,000,000 threads | This will take awhile..." << endl;
    int num_threads = std::thread::hardware_concurrency();
    int num_iterations = 10000000; // Adjust the number of iterations for 1,000,000 digits
    int total_iterations = num_threads * num_iterations;

    std::vector<std::thread> threads;
    std::atomic<int> iterations_completed(0);
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(calculatePi, num_iterations, i, std::ref(iterations_completed));
    }

    auto start_time = std::chrono::steady_clock::now();

    while (iterations_completed < total_iterations) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "\rCurrent amount of characters: " << iterations_completed << " out of " << total_iterations << " | Predicted time to finish: " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_time).count() * (total_iterations - iterations_completed) / iterations_completed << " seconds" << std::flush;
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

    long double pi = std::pow(a + b, 2) / (4 * t);
    double score = static_cast<double>(total_iterations) / elapsed_time / 10;

#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    std::cout << "Total iterations: " << total_iterations << ", Elapsed time: " << elapsed_time << " seconds" << std::endl;
    std::cout << "Score: " << score << " digits per second" << std::endl;
    cout << "Core i7 9700f score: 727273" << endl;
    return 0;
}