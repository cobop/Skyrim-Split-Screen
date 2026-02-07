#include "GameInstance.h"
#include "Launcher.h"
#include <iostream>
#include <cstdlib>   // std::system, setenv
#include <csignal>   // signal handling
#include <unistd.h>  // getpid, kill, fork, execlp
#include <sys/wait.h>

/*
 * SPDX-FileCopyrightText: 2026 Jane Doe
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

bool GameInstance::launch(const Config& config, ScreenPlacement side)
{
    // Set the Proton prefix environment variable so Proton knows where to store its
    // compatibility data. If the user did not specify a prefix, we simply skip it.
    if (!config.proton_prefix.empty()) {
        setenv("STEAM_COMPAT_DATA_PATH", config.proton_prefix.c_str(), 1);
    }

    // Build the command that will be handed to Steam/Proton.
    // Using the steam protocol URL is sufficient – the Steam client will invoke
    // Proton automatically for the given AppID.
    std::string command = "steam steam://run/" + config.steam_app_id;
    if (!config.launch_args.empty()) {
        command += " " + config.launch_args;
    }

    std::cout << "[GameInstance] Launching Skyrim ("
              << (side == ScreenPlacement::LEFT ? "LEFT" : "RIGHT")
              << ") with command: " << command << std::endl;

    // Fork a child that executes the command via the shell.
    pid_t pid = fork();
    if (pid == -1) {
        std::cerr << "[GameInstance] fork() failed." << std::endl;
        return false;
    }
    if (pid == 0) {
        // Child process – replace with the shell executing the command.
        // Using /bin/sh -c ensures the whole command line is interpreted correctly.
        execlp("sh", "sh", "-c", command.c_str(), (char *)nullptr);
        // If execlp fails, exit with error.
        _exit(1);
    }

    // Parent process – store child PID and a placeholder window ID.
    m_pid = pid;
    m_windowId = "dummy-window-id-" + std::to_string(pid); // real implementation will query X11/Wayland
    std::cout << "[GameInstance] Launched process with PID " << m_pid << std::endl;
    return true;
}

void GameInstance::terminate()
{
    if (m_pid > 0) {
        std::cout << "[GameInstance] Terminating process PID " << m_pid << std::endl;
        // Send SIGTERM to the child process.
        if (kill(m_pid, SIGTERM) == -1) {
            std::cerr << "[GameInstance] Failed to terminate PID " << m_pid << std::endl;
        } else {
            // Wait for the process to exit.
            int status = 0;
            waitpid(m_pid, &status, 0);
            std::cout << "[GameInstance] Process PID " << m_pid << " terminated." << std::endl;
        }
        m_pid = 0;
        m_windowId.clear();
    }
}
