import { describe, it, expect } from 'vitest'
import { render, screen } from '@testing-library/react'
import { PropertiesPanel } from '@/components/PropertiesPanel'

describe('PropertiesPanel', () => {
  it('renders all sections', () => {
    render(<PropertiesPanel />)
    expect(screen.getByText('Properties')).toBeInTheDocument()
    expect(screen.getByText('Transform')).toBeInTheDocument()
    expect(screen.getByText('Material')).toBeInTheDocument()
    expect(screen.getByText('Simulation')).toBeInTheDocument()
    expect(screen.getByText('Python')).toBeInTheDocument()
  })
  it('shows transform XYZ', () => {
    render(<PropertiesPanel />)
    expect(screen.getByText(/X: 0/)).toBeInTheDocument()
  })
  it('shows simulation values', () => {
    render(<PropertiesPanel />)
    expect(screen.getByText(/12\.5 MPa/)).toBeInTheDocument()
    expect(screen.getByText(/0\.002 mm/)).toBeInTheDocument()
  })
  it('has Run FEA button', () => {
    render(<PropertiesPanel />)
    expect(screen.getByRole('button', { name: /Run FEA/i })).toBeInTheDocument()
  })
  it('shows Python snippet safely', () => {
    render(<PropertiesPanel />)
    expect(screen.getByText(/sketch\.circle/)).toBeInTheDocument()
  })
})
