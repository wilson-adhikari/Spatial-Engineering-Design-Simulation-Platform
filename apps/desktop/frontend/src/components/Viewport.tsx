import { useRef, useEffect } from "react"
import { Button } from "./ui/button"
import { Eye, Grid3X3, Move, Rotate3D, Ruler } from "lucide-react"
export function Viewport({ mode="shaded" }: { mode?: string }){
  const ref = useRef<HTMLCanvasElement>(null)
  const containerRef = useRef<HTMLDivElement>(null)
  useEffect(()=>{
    const c = ref.current
    const container = containerRef.current
    if(!c || !container) return
    const ctx = c.getContext("2d")
    if(!ctx) return
    let raf=0
    const resize = () => {
      const rect = container.getBoundingClientRect()
      const dpr = window.devicePixelRatio || 1
      c.width = rect.width * dpr
      c.height = rect.height * dpr
      c.style.width = `${rect.width}px`
      c.style.height = `${rect.height}px`
      ctx.setTransform(dpr,0,0,dpr,0,0)
    }
    resize()
    const ro = new ResizeObserver(resize)
    ro.observe(container)
    const draw = (t:number)=>{
      const w = c.width / (window.devicePixelRatio || 1)
      const h = c.height / (window.devicePixelRatio || 1)
      ctx.clearRect(0,0,w,h)
      ctx.fillStyle="#0a0a0a"; ctx.fillRect(0,0,w,h)
      ctx.strokeStyle="#27272a"; ctx.lineWidth=1
      for(let i=0;i<w;i+=32){ ctx.beginPath(); ctx.moveTo(i,0); ctx.lineTo(i,h); ctx.stroke() }
      for(let i=0;i<h;i+=32){ ctx.beginPath(); ctx.moveTo(0,i); ctx.lineTo(w,i); ctx.stroke() }
      const cx=w/2 + Math.sin(t*0.0005)*20, cy=h/2 + Math.cos(t*0.0003)*10
      const boxW = Math.min(120, w*0.3), boxH = Math.min(80, h*0.2)
      ctx.strokeStyle="#e4e4e7"; ctx.lineWidth=2; ctx.strokeRect(cx-boxW/2, cy-boxH/2, boxW, boxH)
      ctx.fillStyle="rgba(255,255,255,0.08)"; ctx.fillRect(cx-boxW/2, cy-boxH/2, boxW, boxH)
      ctx.fillStyle="#fafafa"; ctx.font="11px monospace"; ctx.fillText(mode.toUpperCase()+"  |  Perspective", 12, h-12)
      raf=requestAnimationFrame(draw)
    }
    raf=requestAnimationFrame(draw)
    return ()=>{cancelAnimationFrame(raf); ro.disconnect()}
  },[mode])
  return (
    <div ref={containerRef} className="relative flex-1 bg-zinc-950 flex flex-col min-h-0 min-w-0 overflow-hidden" role="region" aria-label="3D Viewport">
      <div className="absolute top-2 left-2 flex gap-1 bg-zinc-900/80 backdrop-blur rounded-md p-1 border border-zinc-800 max-w-[90%] overflow-x-auto" role="toolbar" aria-label="Viewport tools">
        <Button variant="ghost" size="icon" className="h-7 w-7 text-zinc-300 shrink-0" aria-label="Toggle view mode"><Eye size={14}/></Button>
        <Button variant="ghost" size="icon" className="h-7 w-7 text-zinc-300 shrink-0" aria-label="Toggle grid"><Grid3X3 size={14}/></Button>
        <Button variant="ghost" size="icon" className="h-7 w-7 text-zinc-300 shrink-0" aria-label="Move tool"><Move size={14}/></Button>
        <Button variant="ghost" size="icon" className="h-7 w-7 text-zinc-300 shrink-0" aria-label="Rotate view"><Rotate3D size={14}/></Button>
        <Button variant="ghost" size="icon" className="h-7 w-7 text-zinc-300 shrink-0" aria-label="Measure"><Ruler size={14}/></Button>
      </div>
      <canvas ref={ref} className="w-full h-full flex-1 block" aria-label="3D engineering viewport" role="img" style={{ width: '100%', height: '100%' }} />
      <div className="absolute bottom-2 right-2 text-[10px] text-zinc-500 bg-zinc-900 px-2 py-1 rounded border border-zinc-800 hidden sm:block" aria-live="polite">GPU: NullRenderer | 120 FPS | 48 tris</div>
      <div className="absolute bottom-2 right-2 text-[9px] text-zinc-500 bg-zinc-900 px-1.5 py-0.5 rounded sm:hidden">120 FPS</div>
    </div>
  )
}
