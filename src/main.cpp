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
long double a = 1.0;
long double b = 1.0 / sqrt(2);
long double t = 0.25;
long double p = 1.0;

mutex mtx;

void calculatePi(int num_iterations, int thread_id, atomic<int>& iterations_completed) {
    for (int i = 0; i < num_iterations; i++) {
        long double a_new = (a + b) / 2;
        long double b_new = sqrt(a * b);
        long double t_new = t - p * pow(a - a_new, 2);
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
    int num_threads = 1000;
    int num_iterations = 100000;
    int total_iterations = num_threads * num_iterations;

    vector<thread> threads;
    atomic<int> iterations_completed(0);
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(calculatePi, num_iterations, i, ref(iterations_completed));
    }

    auto start_time = chrono::steady_clock::now();

    while (iterations_completed < total_iterations) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "\rCurrent amount of characters: " << iterations_completed << " out of " << total_iterations << " | Predicted time to finish: " << chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start_time).count() * (total_iterations - iterations_completed) / iterations_completed << " seconds" << flush;
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end_time = chrono::steady_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::seconds>(end_time - start_time).count();

    long double pi = pow(a + b, 2) / (4 * t);
    double score = static_cast<double>(total_iterations) / elapsed_time / 10;

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    cout << "Total iterations: " << total_iterations << ", Elapsed time: " << elapsed_time << " seconds" << endl;
    cout << "Score: " << score << " digits per second" << endl;
    cout << "Core i7 9700f score: 727273" << endl;
    return 0;
}