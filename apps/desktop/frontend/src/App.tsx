import { useState } from "react"
import { ModelTree } from "./components/ModelTree"
import { Viewport } from "./components/Viewport"
import { PropertiesPanel } from "./components/PropertiesPanel"
import { StatusBar } from "./components/StatusBar"
import { Button } from "./components/ui/button"
import { Separator } from "./components/ui/separator"
import { Box, Cpu, Layers, Play, Save, Undo2, Redo2, Settings, Beaker, Bot, Cuboid, Menu, PanelLeft, PanelRight, X } from "lucide-react"

const workspaces = [
  { id:"cad", label:"CAD", icon: Cuboid }, { id:"sketch", label:"Sketch", icon: Layers },
  { id:"assembly", label:"Assembly", icon: Box }, { id:"simulation", label:"Simulation", icon: Beaker },
  { id:"robotics", label:"Robotics", icon: Bot }, { id:"spatial", label:"Spatial", icon: Cpu },
] as const
type WsId = typeof workspaces[number]["id"]
const ALLOWED_WS = new Set<string>(workspaces.map(w=>w.id))
const ALLOWED_MODES = new Set(["shaded","wireframe","xray"])

export default function App(){
  const [ws, setWs] = useState<WsId>("cad")
  const [mode, setMode] = useState("shaded")
  const [showLeft, setShowLeft] = useState(false)
  const [showRight, setShowRight] = useState(false)
  const [mobileMenu, setMobileMenu] = useState(false)
  const safeSetWs = (id: string) => {
    if(!ALLOWED_WS.has(id)) return
    setWs(id as WsId)
  }
  const safeSetMode = (m: string) => {
    if(!ALLOWED_MODES.has(m)) return
    setMode(m)
  }
  return (
    <div className="h-screen flex flex-col bg-white text-zinc-900 overflow-hidden">
      {/* Header — responsive */}
      <div className="h-9 border-b flex items-center px-2 gap-1 bg-white shrink-0">
        <span className="font-bold text-sm mr-1 md:mr-3 tracking-tight shrink-0">SPATIAL</span>
        <span className="hidden md:inline text-xs text-zinc-500 mr-2">Engineering Platform</span>
        <Separator orientation="vertical" className="hidden md:block h-5 mx-2"/>
        {/* Desktop menu */}
        <div className="hidden lg:flex gap-1">
          {["File","Edit","View","Design","Simulation","Tools","Help"].map(m=>(
            <Button key={m} variant="ghost" size="sm" className="h-7 text-xs px-2">{m}</Button>
          ))}
        </div>
        {/* Mobile menu toggle */}
        <Button variant="ghost" size="icon" className="lg:hidden h-7 w-7 ml-1" aria-label="menu" onClick={()=>setMobileMenu(!mobileMenu)}><Menu size={16}/></Button>
        {/* Mobile left/right toggles */}
        <div className="flex md:hidden gap-1 ml-1">
          <Button variant="outline" size="icon" className="h-7 w-7" aria-label="toggle model tree" onClick={()=>setShowLeft(!showLeft)}><PanelLeft size={14}/></Button>
          <Button variant="outline" size="icon" className="h-7 w-7" aria-label="toggle properties" onClick={()=>setShowRight(!showRight)}><PanelRight size={14}/></Button>
        </div>
        <div className="ml-auto flex gap-1 items-center">
          <div className="hidden sm:flex gap-1">
            <Button variant="ghost" size="icon" className="h-7 w-7" aria-label="undo"><Undo2 size={14}/></Button>
            <Button variant="ghost" size="icon" className="h-7 w-7" aria-label="redo"><Redo2 size={14}/></Button>
            <Button variant="ghost" size="icon" className="h-7 w-7" aria-label="save"><Save size={14}/></Button>
            <Separator orientation="vertical" className="hidden sm:block h-5 mx-1"/>
          </div>
          <Button size="sm" className="h-7 gap-1 text-xs px-2 md:px-3"><Play size={12}/> <span className="hidden sm:inline">Run</span></Button>
        </div>
      </div>
      {/* Mobile menu dropdown */}
      {mobileMenu && (
        <div className="lg:hidden border-b bg-zinc-50 p-2 flex flex-wrap gap-1">
          {["File","Edit","View","Design","Simulation","Tools","Help"].map(m=>(
            <Button key={m} variant="ghost" size="sm" className="h-7 text-xs">{m}</Button>
          ))}
        </div>
      )}

      {/* Workspace bar — scrollable */}
      <div className="h-auto min-h-8 border-b flex items-center px-2 gap-1 bg-zinc-50 shrink-0 overflow-x-auto scrollbar-thin">
        <div className="flex gap-1 shrink-0">
          {workspaces.map(w=>(
            <button key={w.id} onClick={()=>safeSetWs(w.id)} className={`flex items-center gap-1 md:gap-1.5 px-2 md:px-3 py-1 rounded-md text-xs font-medium transition-colors whitespace-nowrap shrink-0 ${ws===w.id ? "bg-zinc-900 text-white" : "hover:bg-zinc-200 text-zinc-600"}`}>
              <w.icon size={14}/> <span className="hidden sm:inline">{w.label}</span><span className="sm:hidden">{w.label.slice(0,3)}</span>
            </button>
          ))}
        </div>
        <div className="ml-auto flex gap-1 shrink-0 pl-2 border-l ml-2">
          {(["shaded","wireframe","xray"] as const).map(m=>(
            <Button key={m} variant={mode===m ? "default":"outline"} size="sm" className="h-7 text-xs capitalize px-2" onClick={()=>safeSetMode(m)}>{m.slice(0,2)}</Button>
          ))}
          <Button variant="ghost" size="icon" className="h-7 w-7 hidden md:flex" aria-label="settings"><Settings size={14}/></Button>
        </div>
      </div>

      {/* Main — responsive */}
      <div className="flex flex-1 overflow-hidden relative">
        {/* Left panel — desktop fixed, mobile drawer */}
        <div className={`${showLeft ? 'flex' : 'hidden'} md:flex w-[260px] border-r bg-white overflow-hidden shrink-0 absolute md:relative inset-y-0 left-0 z-20 md:z-auto shadow-lg md:shadow-none`}>
          <div className="flex-1 flex flex-col min-w-0">
            <div className="md:hidden flex justify-end p-1 border-b">
              <Button variant="ghost" size="icon" className="h-6 w-6" onClick={()=>setShowLeft(false)}><X size={14}/></Button>
            </div>
            <div className="flex-1 overflow-hidden"><ModelTree /></div>
          </div>
        </div>
        {/* Viewport */}
        <div className="flex-1 flex flex-col overflow-hidden min-w-0 min-h-0"><Viewport mode={mode} /><StatusBar /></div>
        {/* Right panel — desktop fixed, mobile drawer */}
        <div className={`${showRight ? 'flex' : 'hidden'} lg:flex w-[300px] border-l bg-white overflow-hidden shrink-0 absolute lg:relative inset-y-0 right-0 z-20 lg:z-auto shadow-lg lg:shadow-none`}>
          <div className="flex-1 flex flex-col min-w-0">
            <div className="lg:hidden flex justify-end p-1 border-b">
              <Button variant="ghost" size="icon" className="h-6 w-6" onClick={()=>setShowRight(false)}><X size={14}/></Button>
            </div>
            <div className="flex-1 overflow-hidden"><PropertiesPanel /></div>
          </div>
        </div>
        {/* Mobile overlay */}
        {(showLeft || showRight) && (
          <div className="absolute inset-0 bg-black/20 md:hidden z-10" onClick={()=>{setShowLeft(false);setShowRight(false)}} />
        )}
      </div>
    </div>
  )
}
