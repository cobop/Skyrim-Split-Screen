# Contributing to Skyrim Split‑Screen Launcher

We welcome contributions! This project follows the **GNU GPL v3** license, so any contributions must also be licensed under GPL v3.

## How to Contribute

1. **Fork the repository** on GitHub.
2. **Create a feature branch**:
   ```bash
   git checkout -b my-feature
   ```
3. **Make changes** following the project's coding style:
   - C++17, Qt‑style guidelines, `clang-format` recommended.
   - Keep source files under `src/` and tests under `tests/`.
4. **Add or update tests** (GoogleTest) for any new functionality.
5. **Run the build and tests**:
   ```bash
   mkdir -p build && cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   make -j$(nproc)
   ctest --output-on-failure
   ```
6. **Commit your changes** with a clear message:
   ```bash
   git add .
   git commit -m "feat: short description of your change"
   ```
7. **Push to your fork** and open a Pull Request against `main`.

## Code Review

- PRs will be reviewed for correctness, licensing compliance, and adherence to the coding style.
- Please ensure the CI passes before requesting a review.

## Release Process

- The maintainer will create a signed tag (e.g., `v1.0.0`) and publish a release on GitHub.
- Release artifacts include source tarballs and Flatpak builds.

Thank you for helping improve the launcher!
