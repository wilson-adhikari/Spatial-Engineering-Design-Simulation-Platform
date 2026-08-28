import { useState } from "react"
import { ModelTree } from "./components/ModelTree"
import { Viewport } from "./components/Viewport"
import { PropertiesPanel } from "./components/PropertiesPanel"
import { StatusBar } from "./components/StatusBar"
import { Button } from "./components/ui/button"
import { Separator } from "./components/ui/separator"
import { Box, Cpu, Layers, Play, Save, Undo2, Redo2, Settings, Beaker, Bot, Cuboid } from "lucide-react"

const workspaces = [
  { id:"cad", label:"CAD", icon: Cuboid }, { id:"sketch", label:"Sketch", icon: Layers },
  { id:"assembly", label:"Assembly", icon: Box }, { id:"simulation", label:"Simulation", icon: Beaker },
  { id:"robotics", label:"Robotics", icon: Bot }, { id:"spatial", label:"Spatial", icon: Cpu },
]

export default function App(){
  const [ws, setWs] = useState("cad")
  const [mode, setMode] = useState("shaded")
  return (
    <div className="h-screen flex flex-col bg-white text-zinc-900">
      <div className="h-9 border-b flex items-center px-2 gap-1 bg-white">
        <span className="font-bold text-sm mr-3 tracking-tight">SPATIAL</span>
        <span className="text-xs text-zinc-500 mr-4">Engineering Platform</span>
        <Separator orientation="vertical" className="h-5 mx-2"/>
        {["File","Edit","View","Design","Simulation","Tools","Help"].map(m=>(
          <Button key={m} variant="ghost" size="sm" className="h-7 text-xs px-2">{m}</Button>
        ))}
        <div className="ml-auto flex gap-1">
          <Button variant="ghost" size="icon" className="h-7 w-7"><Undo2 size={14}/></Button>
          <Button variant="ghost" size="icon" className="h-7 w-7"><Redo2 size={14}/></Button>
          <Button variant="ghost" size="icon" className="h-7 w-7"><Save size={14}/></Button>
          <Separator orientation="vertical" className="h-5 mx-1"/>
          <Button size="sm" className="h-7 gap-1"><Play size={12}/> Run</Button>
        </div>
      </div>

      <div className="h-8 border-b flex items-center px-2 gap-1 bg-zinc-50">
        {workspaces.map(w=>(
          <button key={w.id} onClick={()=>setWs(w.id)} className={`flex items-center gap-1.5 px-3 py-1 rounded-md text-xs font-medium transition-colors ${ws===w.id ? "bg-zinc-900 text-white" : "hover:bg-zinc-200 text-zinc-600"}`}>
            <w.icon size={14}/> {w.label}
          </button>
        ))}
        <div className="ml-auto flex gap-1">
          {(["shaded","wireframe","xray"] as const).map(m=>(
            <Button key={m} variant={mode===m ? "default":"outline"} size="sm" className="h-7 text-xs capitalize" onClick={()=>setMode(m)}>{m}</Button>
          ))}
          <Button variant="ghost" size="icon" className="h-7 w-7"><Settings size={14}/></Button>
        </div>
      </div>

      <div className="flex flex-1 overflow-hidden">
        <div className="w-[260px] border-r bg-white overflow-hidden"><ModelTree /></div>
        <div className="flex-1 flex flex-col overflow-hidden"><Viewport mode={mode} /><StatusBar /></div>
        <PropertiesPanel />
      </div>
    </div>
  )
}
