import { defineConfig, devices } from '@playwright/test'
export default defineConfig({
  testDir: './tests/visual',
  timeout: 30000,
  retries: 0,
  reporter: [['html', { open: 'never' }], ['list']],
  use: { baseURL: 'http://127.0.0.1:5173', trace: 'on', screenshot: 'on' },
  webServer: { command: 'npm run dev', url: 'http://127.0.0.1:5173', reuseExistingServer: !process.env.CI, timeout: 120000 },
  projects: [{ name: 'chromium', use: { ...devices['Desktop Chrome'] } }],
  expect: { toHaveScreenshot: { maxDiffPixels: 100, threshold: 0.2 } }
})
