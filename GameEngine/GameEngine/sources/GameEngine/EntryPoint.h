#pragma once

#include "Core.h"
#include "Application/Application.h"
#include "Log/Log.h"
#include "Time/Timer.h"


extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
    Engine::Timer timer;

    timer.Reset();
    auto app = Engine::CreateApplication();
    ENGINE_CORE_INFO("Create App: %fms", timer.GetElapsedTimeMs());

    app->Run();

    timer.Reset();
    delete app;
    ENGINE_CORE_INFO("Destroy App: %fms", timer.GetElapsedTimeMs());
}
