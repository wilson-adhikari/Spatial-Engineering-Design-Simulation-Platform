import { describe, it, expect } from 'vitest'
import { render, screen } from '@testing-library/react'
import { Viewport } from '@/components/Viewport'

describe('Viewport — component', () => {
  it('renders canvas', () => {
    render(<Viewport />)
    expect(document.querySelector('canvas')).toBeInTheDocument()
  })
  it('renders with all modes', () => {
    const { rerender } = render(<Viewport mode="shaded" />)
    expect(document.querySelector('canvas')).toBeInTheDocument()
    rerender(<Viewport mode="wireframe" />)
    expect(document.querySelector('canvas')).toBeInTheDocument()
    rerender(<Viewport mode="xray" />)
    expect(document.querySelector('canvas')).toBeInTheDocument()
  })
  it('handles 50 rapid mode switches', () => {
    const { rerender } = render(<Viewport mode="shaded" />)
    for(let i=0;i<50;i++) rerender(<Viewport mode={i%2===0?"shaded":"wireframe"} />)
    expect(document.querySelector('canvas')).toBeInTheDocument()
  })
  it('shows toolbar buttons', () => {
    render(<Viewport />)
    expect(document.querySelectorAll('button').length).toBeGreaterThanOrEqual(5)
  })
  it('shows GPU stats', () => {
    render(<Viewport />)
    expect(screen.getByText(/GPU/)).toBeInTheDocument()
  })
  it('canvas has correct dimensions', () => {
    render(<Viewport />)
    const c = document.querySelector('canvas') as HTMLCanvasElement
    expect(c.width).toBe(1200)
    expect(c.height).toBe(800)
  })
})
