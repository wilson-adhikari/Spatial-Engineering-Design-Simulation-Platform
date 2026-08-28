import { describe, it, expect } from 'vitest'
import { render, screen } from '@testing-library/react'
import { Card, CardHeader, CardContent } from '@/components/ui/card'

describe('Card — component tests', () => {
  it('renders card with header/content', () => {
    render(<Card><CardHeader>Head</CardHeader><CardContent>Body</CardContent></Card>)
    expect(screen.getByText('Head')).toBeInTheDocument()
    expect(screen.getByText('Body')).toBeInTheDocument()
  })
  it('applies border and shadow', () => {
    render(<Card data-testid="c">X</Card>)
    expect(screen.getByTestId('c')).toHaveClass('border')
  })
  it('handles empty children', () => {
    render(<Card />)
    expect(document.querySelector('.rounded-lg')).toBeInTheDocument()
  })
  it('handles 1000 char content', () => {
    const long = 'X'.repeat(1000)
    const { container } = render(<Card><CardContent>{long}</CardContent></Card>)
    expect(container.textContent).toContain('X'.repeat(10))
  })
  it('nested cards', () => {
    render(<Card><Card><CardContent>Inner</CardContent></Card></Card>)
    expect(screen.getByText('Inner')).toBeInTheDocument()
  })
})
