# Contributing

## Workflow (Professional PR)
1. Fork + `git checkout -b feat/xyz`
2. `cmake -S . -B build -G "MinGW Makefiles" && cmake --build build && ctest`
3. `cd apps/desktop/frontend && npm install --legacy-peer-deps && npx vitest run && npx playwright test`
4. Commit with Conventional Commits (`feat:`, `fix:`, `security:`, `docs:`)
5. Push + open PR against `master` — template auto-filled, CI must pass, 1 review, squash merge
6. Update `CHANGELOG.md`

## Standards
- C++20, `-Wall -Wextra -fstack-protector-strong`, `clang-tidy`, `clang-format`
- ReUI: `eslint --max-warnings 0` + `jsx-a11y`
- Tests required for new feature (unit + e2e if UI)

## Reporting
- Bug: `.github/ISSUE_TEMPLATE/bug_report.yml`
- Feature: `feature_request.yml`
- Security: `SECURITY.md` (private, not issue)

## DCO
Sign-off `git commit -s`
