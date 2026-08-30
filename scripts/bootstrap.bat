@echo off
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build -j
ctest --test-dir build --output-on-failure
cd apps\desktop\frontend
call npm ci --legacy-peer-deps
call npm run build

