export module LoadingModule;
import GlobalModule;
#include "raylib.h"
#include <thread>
#include <chrono>

export void simulateLoading(int& progress) {
    for(int i = 0; i < 100; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        progress++;
    }
}

export void drawLoading(int& progress) {
    // Draw loading text
    DrawText("Loading...", screenWidth / 2 - MeasureText("Loading...", 20) / 2, screenHeight / 2 - 50, 20, DARKGRAY);

    // Draw progress bar background
    DrawRectangle(screenWidth / 2 - 150, screenHeight / 2, 300, 30, LIGHTGRAY);

    // Draw progress bar
    DrawRectangle(screenWidth / 2 - 150, screenHeight / 2, 3 * progress, 30, SKYBLUE);

    // Draw percentage text
    char progressText[10];
    sprintf_s(progressText, "%d%%", progress);
    DrawText(progressText, screenWidth / 2 - MeasureText(progressText, 20) / 2, screenHeight / 2 + 5, 20, DARKGRAY);
}

export void startLoading(int& progress) {
    std::thread loadingThread(simulateLoading, std::ref(progress));
    loadingThread.detach();
}
