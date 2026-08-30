module.exports = {
  root: true,
  parser: '@typescript-eslint/parser',
  extends: ['eslint:recommended', 'plugin:@typescript-eslint/recommended', 'plugin:jsx-a11y/recommended', 'plugin:security/recommended'],
  plugins: ['@typescript-eslint', 'jsx-a11y', 'security'],
  env: { browser: true, es2020: true },
  rules: { 'security/detect-object-injection': 'off' },
  ignorePatterns: ['dist', 'node_modules', 'playwright-report', 'test-results']
}
