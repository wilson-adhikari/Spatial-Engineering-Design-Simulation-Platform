import { useRef, useEffect } from "react"
import { Button } from "./ui/button"
import { Eye, Grid3X3, Move, Rotate3D, Ruler } from "lucide-react"
export function Viewport({ mode="shaded" }: { mode?: string }){
  const ref = useRef<HTMLCanvasElement>(null)
  useEffect(()=>{
    const c = ref.current; if(!c) return
    const ctx = c.getContext("2d")!; let raf=0
    const draw = (t:number)=>{
      ctx.clearRect(0,0,c.width,c.height)
      ctx.fillStyle="#0a0a0a"; ctx.fillRect(0,0,c.width,c.height)
      ctx.strokeStyle="#27272a"; ctx.lineWidth=1
      for(let i=0;i<c.width;i+=32){ ctx.beginPath(); ctx.moveTo(i,0); ctx.lineTo(i,c.height); ctx.stroke() }
      for(let i=0;i<c.height;i+=32){ ctx.beginPath(); ctx.moveTo(0,i); ctx.lineTo(c.width,i); ctx.stroke() }
      const cx=c.width/2 + Math.sin(t*0.0005)*20, cy=c.height/2 + Math.cos(t*0.0003)*10
      ctx.strokeStyle="#e4e4e7"; ctx.lineWidth=2; ctx.strokeRect(cx-60, cy-40, 120, 80)
      ctx.fillStyle="rgba(255,255,255,0.08)"; ctx.fillRect(cx-60, cy-40, 120, 80)
      ctx.fillStyle="#fafafa"; ctx.font="11px monospace"; ctx.fillText(mode.toUpperCase()+"  |  Perspective", 12, c.height-12)
      raf=requestAnimationFrame(draw)
    }
    raf=requestAnimationFrame(draw); return ()=>cancelAnimationFrame(raf)
  },[mode])
  return (
    <div className="relative flex-1 bg-zinc-950 flex flex-col">
      <div className="absolute top-2 left-2 flex gap-1 bg-zinc-900/80 backdrop-blur rounded-md p-1 border border-zinc-800">
        <Button variant="ghost" size="icon" className="h-7 w-7 text-zinc-300"><Eye size={14}/></Button>
        <Button variant="ghost" size="icon" className="h-7 w-7 text-zinc-300"><Grid3X3 size={14}/></Button>
        <Button variant="ghost" size="icon" className="h-7 w-7 text-zinc-300"><Move size={14}/></Button>
        <Button variant="ghost" size="icon" className="h-7 w-7 text-zinc-300"><Rotate3D size={14}/></Button>
        <Button variant="ghost" size="icon" className="h-7 w-7 text-zinc-300"><Ruler size={14}/></Button>
      </div>
      <canvas ref={ref} width={1200} height={800} className="w-full h-full object-contain flex-1" />
      <div className="absolute bottom-2 right-2 text-[10px] text-zinc-500 bg-zinc-900 px-2 py-1 rounded border border-zinc-800">GPU: NullRenderer | 120 FPS | 48 tris</div>
    </div>
  )
}
