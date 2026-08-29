#!/bin/sh
clang-tidy engine/**/*.cpp --checks="*,-fuchsia*" || exit 1
npx --prefix apps/desktop/frontend eslint . --max-warnings 0 || exit 1
ctest --test-dir build/test || exit 1
npx --prefix apps/desktop/frontend vitest run || exit 1

