#!/usr/bin/env bash
set -euo pipefail
echo "==> Bootstrap: C++ configure/build/test"
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -G Ninja 2>/dev/null || cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure

echo "==> Frontend: npm ci + build + tests"
if command -v npm >/dev/null 2>&1; then
  npm ci --prefix apps/desktop/frontend --legacy-peer-deps || npm install --prefix apps/desktop/frontend --legacy-peer-deps
  npm run build --prefix apps/desktop/frontend
  npx --prefix apps/desktop/frontend vitest run --config vitest.config.ts || true
  npx --prefix apps/desktop/frontend playwright install chromium --with-deps || true
else
  echo "npm not found — skipping frontend"
fi
echo "Bootstrap done — run: cmake --preset dev && npm --prefix apps/desktop/frontend run dev"

