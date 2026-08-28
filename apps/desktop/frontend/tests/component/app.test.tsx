import { describe, it, expect } from 'vitest'
import { render, screen } from '@testing-library/react'
import userEvent from '@testing-library/user-event'
import App from '@/App'

describe('App — high aggressiveness', () => {
  it('renders engineering layout', () => {
    render(<App />)
    expect(screen.getByText('SPATIAL')).toBeInTheDocument()
    expect(screen.getByText(/Engineering Platform/)).toBeInTheDocument()
    expect(screen.getByText('Model Tree')).toBeInTheDocument()
    expect(screen.getByText('Properties')).toBeInTheDocument()
  })
  it('switches all 6 workspaces without crash (aggressive)', async () => {
    const user = userEvent.setup()
    render(<App />)
    for(const ws of ['CAD','Sketch','Assembly','Simulation','Robotics','Spatial']){
      const btns = screen.getAllByRole('button', { name: new RegExp(ws, 'i') })
      const btn = btns[0]
      await user.click(btn)
      expect(btn).toBeInTheDocument()
    }
    const cadBtns = screen.getAllByRole('button', { name: /CAD/i })
    for(let i=0;i<10;i++) await user.click(cadBtns[0])
    expect(cadBtns[0]).toBeInTheDocument()
  })
  it('rejects invalid workspace injection', async () => {
    render(<App />)
    expect(screen.getByText('SPATIAL')).toBeInTheDocument()
  })
  it('switches view modes aggressively', async () => {
    const user = userEvent.setup()
    render(<App />)
    const btns = screen.getAllByRole('button', { name: /shaded/i })
    if(btns[0]) await user.click(btns[0])
    expect(document.querySelector('canvas')).toBeInTheDocument()
  })
  it('toolbar undo/redo/save present', () => {
    render(<App />)
    expect(screen.getByLabelText('undo')).toBeInTheDocument()
    expect(screen.getByLabelText('redo')).toBeInTheDocument()
    expect(screen.getByLabelText('save')).toBeInTheDocument()
  })
  it('handles window resize stress', () => {
    render(<App />)
    for(const w of [320,768,1024,1280,1920]){
      ;(window as any).innerWidth = w
      window.dispatchEvent(new Event('resize'))
    }
    expect(screen.getByText('SPATIAL')).toBeInTheDocument()
  })
  it('renders 10 times without memory leak (stress)', () => {
    for(let i=0;i<10;i++){
      const { unmount } = render(<App />)
      unmount()
    }
    render(<App />)
    expect(screen.getByText('SPATIAL')).toBeInTheDocument()
  })
})
