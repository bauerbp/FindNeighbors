#include <chrono>

// Simple timer
class TickTock {
    public:
    // starts timer
    void tick() {
        m_time = std::chrono::steady_clock::now();
    }
    // stops timer, returns elapsed time in ms
    int tock() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_time).count();
    }

    private:
    std::chrono::time_point<std::chrono::steady_clock> m_time;
    
};
