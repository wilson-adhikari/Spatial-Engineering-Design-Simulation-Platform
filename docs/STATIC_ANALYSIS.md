# Static Analysis

## C++
- **clang-tidy** (`-checks='*,-fuchsia*'`, warnings-as-errors `bugprone,security`): `clang-tidy engine/**/*.cpp --checks='*,-fuchsia*'`
- **cppcheck**: `cppcheck --enable=all --error-exitcode=1 engine/`
- **Compiler**: `-Wall -Wextra -fstack-protector-strong -D_FORTIFY_SOURCE=2`

## Frontend
- **ESLint** `eslint . --max-warnings 0` + `eslint-plugin-security` + `eslint-plugin-jsx-a11y`
- **TypeScript** `tsc --noEmit` (strict)

## CI
`static-analysis` job in `ci.yml` runs clang-tidy + eslint. Pre-commit hook: `tools/pre-commit.sh`
