import { describe, it, expect, vi } from 'vitest'
import { render, screen } from '@testing-library/react'
import userEvent from '@testing-library/user-event'
import { Button } from '@/components/ui/button'

describe('Button — aggressive component tests', () => {
  it('renders default variant', () => {
    render(<Button>Click me</Button>)
    expect(screen.getByRole('button', { name: /click me/i })).toBeInTheDocument()
  })
  it('handles 50 rapid clicks without breaking', async () => {
    const fn = vi.fn()
    const user = userEvent.setup()
    render(<Button onClick={fn}>Tap</Button>)
    const btn = screen.getByRole('button')
    for(let i=0;i<50;i++) await user.click(btn)
    expect(fn).toHaveBeenCalledTimes(50)
  })
  it('disabled blocks clicks', async () => {
    const fn = vi.fn()
    const user = userEvent.setup()
    render(<Button disabled onClick={fn}>No</Button>)
    await user.click(screen.getByRole('button'))
    expect(fn).not.toHaveBeenCalled()
  })
  it('outline/ghost variants render', () => {
    const { rerender } = render(<Button variant="outline">O</Button>)
    expect(screen.getByRole('button')).toBeInTheDocument()
    rerender(<Button variant="ghost">G</Button>)
    expect(screen.getByRole('button')).toBeInTheDocument()
  })
  it('sizes sm/icon render', () => {
    render(<><Button size="sm">S</Button><Button size="icon">I</Button></>)
    expect(screen.getAllByRole('button')).toHaveLength(2)
  })
  it('keyboard enter/space triggers', async () => {
    const fn = vi.fn()
    const user = userEvent.setup()
    render(<Button onClick={fn}>K</Button>)
    const btn = screen.getByRole('button')
    btn.focus()
    await user.keyboard('{Enter}')
    await user.keyboard(' ')
    expect(fn).toHaveBeenCalledTimes(2)
  })
  it('has accessible name when icon only', () => {
    render(<Button aria-label="save" size="icon">S</Button>)
    expect(screen.getByLabelText('save')).toBeInTheDocument()
  })
  it('applies custom className', () => {
    render(<Button className="custom-xyz">C</Button>)
    expect(screen.getByRole('button')).toHaveClass('custom-xyz')
  })
  it('renders with 200 char label (overflow)', () => {
    const long = 'A'.repeat(200)
    render(<Button>{long}</Button>)
    expect(screen.getByRole('button')).toHaveTextContent(long.slice(0,20))
  })
  it('supports forwarded ref', () => {
    const ref = { current: null as HTMLButtonElement | null }
    const RefComp = () => { const r = (el: HTMLButtonElement) => (ref.current = el); return <Button ref={r}>R</Button> }
    render(<RefComp />)
    expect(ref.current).toBeInstanceOf(HTMLButtonElement)
  })
})
