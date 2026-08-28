import { defineConfig, devices } from '@playwright/test'
export default defineConfig({
  testDir: './tests/responsive',
  timeout: 30000,
  reporter: [['html', { open: 'never' }], ['list']],
  use: { baseURL: 'http://127.0.0.1:5173' },
  webServer: { command: 'npm run dev', url: 'http://127.0.0.1:5173', reuseExistingServer: !process.env.CI, timeout: 120000 },
  projects: [
    { name: 'mobile-320', use: { ...devices['iPhone SE'], viewport: { width: 320, height: 568 } } },
    { name: 'tablet-768', use: { ...devices['iPad Mini'], viewport: { width: 768, height: 1024 } } },
    { name: 'laptop-1024', use: { viewport: { width: 1024, height: 768 } } },
    { name: 'desktop-1280', use: { viewport: { width: 1280, height: 720 } } },
    { name: 'wide-1920', use: { viewport: { width: 1920, height: 1080 } } },
    { name: 'ultra-2560', use: { viewport: { width: 2560, height: 1440 } } }
  ]
})
