import "@testing-library/jest-dom"

// Mock canvas getContext for jsdom
Object.defineProperty(HTMLCanvasElement.prototype, 'getContext', {
  value: (type: string) => {
    if (type === '2d') {
      return {
        clearRect: () => {},
        fillRect: () => {},
        strokeRect: () => {},
        beginPath: () => {},
        moveTo: () => {},
        lineTo: () => {},
        stroke: () => {},
        fill: () => {},
        fillText: () => {},
        createLinearGradient: () => ({ addColorStop: () => {} }),
      } as any
    }
    return null
  },
  writable: true,
})

// Mock requestAnimationFrame
global.requestAnimationFrame = (cb: FrameRequestCallback) => setTimeout(cb, 16) as unknown as number
global.cancelAnimationFrame = (id: number) => clearTimeout(id)

// Mock ResizeObserver
global.ResizeObserver = class ResizeObserver {
  observe() {}
  unobserve() {}
  disconnect() {}
} as any

// Suppress console errors for aggressive tests
const origError = console.error
console.error = (...args: any[]) => {
  const msg = args[0]?.toString() || ''
  if (msg.includes('not wrapped in act')) return
  origError(...args)
}
