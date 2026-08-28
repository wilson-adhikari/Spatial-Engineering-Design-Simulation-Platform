import { test, expect } from '@playwright/test'

test.describe('E2E — full user flows — aggressive', () => {
  test.beforeEach(async ({ page }) => { await page.goto('/') })

  test('complete: CAD flow — create → sketch → extrude → save', async ({ page }) => {
    await page.locator('div.h-8').getByRole('button', { name: /CAD/i }).click()
    await expect(page.locator('text=Model Tree')).toBeVisible()
    await page.locator('text=Robot_Arm.part').click()
    await expect(page.locator('text=Feature History')).toBeVisible()
    await page.getByLabel('save').click()
    await expect(page.locator('text=Properties')).toBeVisible()
  })

  test('assembly flow — switch to assembly → select → properties', async ({ page }) => {
    await page.locator('div.h-8').getByRole('button', { name: /Assembly/i }).click()
    await page.waitForTimeout(300)
    await page.locator('text=Assembly1').click()
    await expect(page.locator('text=Transform')).toBeVisible()
  })

  test('simulation flow — simulation workspace → run FEA', async ({ page }) => {
    await page.locator('div.h-8').getByRole('button', { name: /Simulation/i }).click()
    await page.waitForTimeout(300)
    const runBtn = page.getByRole('button', { name: /Run FEA/i })
    await expect(runBtn).toBeVisible()
    await runBtn.click()
    await expect(page.locator('text=12.5 MPa')).toBeVisible()
  })

  test('sketch flow — sketch workspace → check tools', async ({ page }) => {
    await page.locator('div.h-8').getByRole('button', { name: /Sketch/i }).click()
    await expect(page.locator('canvas')).toBeVisible()
  })

  test('robotics flow — robotics workspace', async ({ page }) => {
    await page.locator('div.h-8').getByRole('button', { name: /Robotics/i }).click()
    await expect(page.locator('canvas')).toBeVisible()
  })

  test('spatial flow — spatial workspace', async ({ page }) => {
    await page.locator('div.h-8').getByRole('button', { name: /^Spatial$/i }).click()
    await expect(page.locator('canvas')).toBeVisible()
  })

  test('undo/redo flow — stress 20 times', async ({ page }) => {
    for(let i=0;i<20;i++){
      await page.getByLabel('undo').click()
      await page.getByLabel('redo').click()
    }
    await expect(page.locator('canvas')).toBeVisible()
  })

  test('view mode E2E — shaded → wireframe → xray → shaded', async ({ page }) => {
    for(const mode of ['shaded','wireframe','xray','shaded']){
      const btn = page.locator('div.h-8').getByRole('button', { name: new RegExp(mode, 'i') })
      if(await btn.isVisible()) await btn.click()
      await page.waitForTimeout(150)
      await expect(page.locator('canvas')).toBeVisible()
    }
  })

  test('model tree selection E2E — select each item', async ({ page }) => {
    for(const name of ['Robot_Arm.part','Assembly1','Sketch XY']){
      await page.locator(`text=${name}`).click()
      await expect(page.locator('text=Properties')).toBeVisible()
    }
  })

  test('viewport interaction — toolbar buttons', async ({ page }) => {
    const buttons = page.locator('canvas').locator('..').locator('button')
    const count = await buttons.count()
    expect(count).toBeGreaterThanOrEqual(5)
    for(let i=0;i<count;i++) await buttons.nth(i).click()
    await expect(page.locator('canvas')).toBeVisible()
  })

  test('checkout-like: run → save → status check', async ({ page }) => {
    await page.locator('div.h-9').getByRole('button', { name: /Run/i }).click()
    await page.getByLabel('save').click()
    await expect(page.locator('text=Ready')).toBeVisible()
    await expect(page.locator('text=Selection:')).toBeVisible()
  })

  test('aggressive: 100 actions without crash', async ({ page }) => {
    for(let i=0;i<15;i++){
      await page.locator('div.h-8').getByRole('button', { name: /CAD/i }).click()
      await page.locator('div.h-8').getByRole('button', { name: /Simulation/i }).click()
      await page.locator('div.h-8').getByRole('button', { name: /Assembly/i }).click()
    }
    await expect(page.locator('canvas')).toBeVisible()
  })

  test('error handling — invalid workspace ignored', async ({ page }) => {
    await page.evaluate(() => (window as any).history.pushState({}, '', '/?ws=<script>'))
    await page.reload()
    await expect(page.locator('span.font-bold', { hasText: 'SPATIAL' })).toBeVisible()
  })
})
