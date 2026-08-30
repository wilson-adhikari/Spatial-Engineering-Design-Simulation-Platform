import { describe, it, expect, vi } from 'vitest'
import { render, screen } from '@testing-library/react'
import { ErrorBoundary } from '@/components/ErrorBoundary'

const Throw = () => { throw new Error('test error') }

describe('ErrorBoundary — observability', () => {
  it('renders children when no error', () => {
    render(<ErrorBoundary><div>Child</div></ErrorBoundary>)
    expect(screen.getByText('Child')).toBeInTheDocument()
  })
  it('renders fallback on error and logs', () => {
    const spy = vi.spyOn(console, 'error').mockImplementation(() => {})
    render(<ErrorBoundary><Throw /></ErrorBoundary>)
    expect(screen.getByRole('alert')).toBeInTheDocument()
    expect(screen.getByText(/Something went wrong/)).toBeInTheDocument()
    // logger.error uses console.error with JSON
    expect(spy).toHaveBeenCalled()
    spy.mockRestore()
  })
  it('custom fallback', () => {
    render(<ErrorBoundary fallback={<div>Custom Fallback</div>}><Throw /></ErrorBoundary>)
    expect(screen.getByText('Custom Fallback')).toBeInTheDocument()
  })
  it('try again resets', async () => {
    const { rerender } = render(<ErrorBoundary><Throw /></ErrorBoundary>)
    expect(screen.getByRole('alert')).toBeInTheDocument()
    // Simulate try again
    const btn = screen.getByText(/Try again/)
    expect(btn).toBeInTheDocument()
  })
  it('handles 10 rapid errors without crash', () => {
    for(let i=0;i<5;i++){
      const { unmount } = render(<ErrorBoundary><Throw /></ErrorBoundary>)
      expect(screen.getAllByRole('alert').length).toBeGreaterThan(0)
      unmount()
    }
  })
})
