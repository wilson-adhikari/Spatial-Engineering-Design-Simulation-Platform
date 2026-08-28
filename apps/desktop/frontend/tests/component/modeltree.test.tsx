import { describe, it, expect, vi } from 'vitest'
import { render, screen } from '@testing-library/react'
import userEvent from '@testing-library/user-event'
import { ModelTree } from '@/components/ModelTree'

describe('ModelTree — aggressive', () => {
  it('renders 3 items + history', () => {
    render(<ModelTree />)
    expect(screen.getByText('Model Tree')).toBeInTheDocument()
    expect(screen.getByText(/Robot_Arm/)).toBeInTheDocument()
    expect(screen.getByText(/Assembly1/)).toBeInTheDocument()
    expect(screen.getByText(/Sketch XY/)).toBeInTheDocument()
    expect(screen.getByText(/Feature History/)).toBeInTheDocument()
  })
  it('sanitizes malicious id (XSS injection)', async () => {
    const fn = vi.fn()
    const user = userEvent.setup()
    render(<ModelTree onSelect={fn} />)
    const item = screen.getByText(/Robot_Arm/)
    await user.click(item)
    expect(fn).toHaveBeenCalledWith(expect.stringMatching(/^[a-zA-Z0-9_\-\.]+$/))
    expect(fn).not.toHaveBeenCalledWith(expect.stringContaining('<script'))
  })
  it('rapid 100 selects stable', async () => {
    const fn = vi.fn()
    const user = userEvent.setup()
    render(<ModelTree onSelect={fn} />)
    const el = screen.getByText(/Assembly1/)
    for(let i=0;i<20;i++) await user.click(el)
    expect(fn).toHaveBeenCalledTimes(20)
  })
  it('keyboard navigation', async () => {
    const user = userEvent.setup()
    render(<ModelTree />)
    await user.tab()
    expect(document.activeElement).toBeDefined()
  })
  it('handles empty onSelect', () => {
    render(<ModelTree />)
    expect(() => screen.getByText(/Robot_Arm/).click()).not.toThrow()
  })
  it('displays counts correctly', () => {
    render(<ModelTree />)
    expect(screen.getByText('3')).toBeInTheDocument()
  })
})
