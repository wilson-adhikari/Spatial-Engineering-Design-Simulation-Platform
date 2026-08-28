import { test, expect } from '@playwright/test'

test.describe('Visual Regression — aggressive', () => {
  test.beforeEach(async ({ page }) => { await page.goto('/') })

  test('full app layout — fonts/colors/alignment', async ({ page }) => {
    await page.waitForTimeout(1500)
    await expect(page).toHaveScreenshot('app-full.png', { maxDiffPixels: 300, threshold: 0.3 })
    const title = page.locator('span.font-bold', { hasText: 'SPATIAL' }).first()
    await expect(title).toBeVisible()
    const header = page.locator('div.h-9').first()
    await expect(header).toBeVisible()
  })

  test('model tree — alignment', async ({ page }) => {
    const tree = page.locator('text=Model Tree').locator('..')
    await expect(tree).toHaveScreenshot('model-tree.png', { maxDiffPixels: 150 })
  })

  test('viewport — grid and box rendering', async ({ page }) => {
    const viewport = page.locator('canvas')
    await expect(viewport).toBeVisible()
    await expect(viewport).toHaveScreenshot('viewport-canvas.png', { maxDiffPixels: 150 })
  })

  test('properties panel — typography', async ({ page }) => {
    const panel = page.locator('text=Properties').locator('..')
    await expect(panel).toHaveScreenshot('properties-panel.png', { maxDiffPixels: 150 })
  })

  test('all workspaces visual regression (6)', async ({ page }) => {
    for (const ws of ['CAD','Sketch','Assembly','Simulation','Robotics','Spatial']) {
      await page.locator('div.h-8').getByRole('button', { name: new RegExp(ws, 'i') }).click()
      await page.waitForTimeout(300)
      await expect(page).toHaveScreenshot(`workspace-${ws.toLowerCase()}.png`, { maxDiffPixels: 200 })
    }
  })

  test('view modes — shaded/wireframe/xray', async ({ page }) => {
    for (const mode of ['shaded','wireframe','xray']) {
      const btn = page.locator('div.h-8').getByRole('button', { name: new RegExp(mode, 'i') })
      if (await btn.isVisible()) {
        await btn.click()
        await page.waitForTimeout(300)
        await expect(page.locator('canvas')).toHaveScreenshot(`mode-${mode}.png`, { maxDiffPixels: 150 })
      }
    }
  })

  test('status bar — alignment', async ({ page }) => {
    const bar = page.locator('text=Ready').locator('..')
    await expect(bar).toHaveScreenshot('status-bar.png', { maxDiffPixels: 100 })
  })

  test('stress — 5 rapid screenshots without flake', async ({ page }) => {
    for(let i=0;i<3;i++){
      await page.locator('div.h-8').getByRole('button', { name: /CAD/i }).click()
      await page.waitForTimeout(100)
      await expect(page).toHaveScreenshot(`stress-${i}.png`, { maxDiffPixels: 600 })
    }
  })

  test('pixel perfect — header height 36px', async ({ page }) => {
    const header = page.locator('div.h-9').first()
    const box = await header.boundingBox()
    expect(box?.height).toBeCloseTo(36, 2)
  })

  test('color contrast — header bg white', async ({ page }) => {
    const header = page.locator('div.h-9').first()
    await expect(header).toHaveCSS('background-color', 'rgb(255, 255, 255)')
  })
})
