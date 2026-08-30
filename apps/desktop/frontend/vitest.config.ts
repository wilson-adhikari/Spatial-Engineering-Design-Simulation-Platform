import { defineConfig } from 'vitest/config'
import react from '@vitejs/plugin-react'
import path from 'path'
export default defineConfig({
  plugins: [react()],
  test: {
    environment: 'jsdom',
    globals: true,
    setupFiles: ['./tests/setup.ts'],
    coverage: { provider: 'v8', reporter: ['text','html','lcov'], thresholds: { lines: 60, branches: 60, functions: 60, statements: 60 } },
    include: ['tests/component/**/*.{test,spec}.{ts,tsx}']
  },
  resolve: { alias: { '@': path.resolve(__dirname, './src') } }
})
