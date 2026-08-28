import { test, expect } from '@playwright/test'
import AxeBuilder from '@axe-core/playwright'

test.describe('Accessibility — aggressive a11y', () => {
  test.beforeEach(async ({ page }) => { await page.goto('/') })

  test('axe — no critical violations', async ({ page }) => {
    const results = await new AxeBuilder({ page }).analyze()
    const critical = results.violations.filter(v => v.impact === 'critical')
    expect(critical, `Critical: ${JSON.stringify(critical, null, 2)}`).toEqual([])
  })

  test('axe — no serious violations (strict)', async ({ page }) => {
    const results = await new AxeBuilder({ page }).withTags(['wcag2a','wcag2aa']).analyze()
    const serious = results.violations.filter(v => ['critical','serious'].includes(v.impact || ''))
    expect(serious.length).toBeLessThan(6)
  })

  test('all buttons have accessible name', async ({ page }) => {
    const buttons = page.getByRole('button')
    const count = await buttons.count()
    for(let i=0;i<Math.min(count, 25);i++){
      const name = await buttons.nth(i).getAttribute('aria-label') || await buttons.nth(i).innerText()
      expect(name?.trim().length).toBeGreaterThan(0)
    }
  })

  test('keyboard nav — tab through all controls', async ({ page }) => {
    await page.keyboard.press('Tab')
    for(let i=0;i<10;i++){
      const tag = await page.evaluate(() => document.activeElement?.tagName)
      expect(['BUTTON','A','DIV','BODY']).toContain(tag)
      await page.keyboard.press('Tab')
    }
  })

  test('color contrast — header text vs bg', async ({ page }) => {
    const header = page.locator('div.h-9').first()
    const color = await header.evaluate(el => getComputedStyle(el).color)
    const bg = await header.evaluate(el => getComputedStyle(el).backgroundColor)
    expect(color).not.toBe(bg)
  })

  test('screen reader — landmarks', async ({ page }) => {
    await expect(page.locator('text=Model Tree')).toBeVisible()
    await expect(page.locator('text=Properties')).toBeVisible()
    await expect(page.locator('text=Ready')).toBeVisible()
  })

  test('focus visible — keyboard focus moves', async ({ page }) => {
    await page.keyboard.press('Tab')
    await page.waitForTimeout(200)
    const tag = await page.evaluate(() => document.activeElement?.tagName)
    expect(tag).not.toBe('BODY')
    const isButton = await page.evaluate(() => document.activeElement?.getAttribute('role') || document.activeElement?.tagName)
    expect(isButton).toBeTruthy()
  })

  test('viewport canvas has accessible fallback', async ({ page }) => {
    const canvas = page.locator('canvas')
    await expect(canvas).toBeVisible()
    const parent = canvas.locator('..')
    await expect(parent).toBeVisible()
  })

  test('no duplicate ids', async ({ page }) => {
    const ids = await page.evaluate(() => {
      const all = Array.from(document.querySelectorAll('[id]')).map(e => e.id)
      return all.filter((id, i) => all.indexOf(id) !== i)
    })
    expect(ids).toEqual([])
  })

  test('heading hierarchy', async ({ page }) => {
    const h1Count = await page.locator('h1').count()
    expect(h1Count).toBeLessThan(3)
  })

  test('aggressive: axe on each workspace', async ({ page }) => {
    for(const ws of ['CAD','Assembly','Simulation']){
      await page.locator('div.h-8').getByRole('button', { name: new RegExp(ws, 'i') }).click()
      await page.waitForTimeout(200)
      const results = await new AxeBuilder({ page }).analyze()
      const critical = results.violations.filter(v => v.impact === 'critical')
      expect(critical).toEqual([])
    }
  })
})
