import { Card, CardHeader, CardContent } from "./ui/card"
import { Separator } from "./ui/separator"
import { Box, Layers, Component } from "lucide-react"
export function ModelTree({ onSelect }: { onSelect?: (id:string)=>void }){
  const items = [
    { id:"part1", name:"Robot_Arm.part", icon: Box, count: 3 },
    { id:"asm1", name:"Assembly1", icon: Layers, count: 2 },
    { id:"sketch1", name:"Sketch XY", icon: Component, count: 4 },
  ]
  return (
    <Card className="h-full rounded-none border-y-0 border-l-0 flex flex-col">
      <CardHeader className="py-3 font-semibold text-sm">Model Tree</CardHeader>
      <Separator />
      <CardContent className="flex-1 p-2 space-y-1 overflow-auto">
        {items.map(it=>(
          <div key={it.id} onClick={()=>onSelect?.(it.id)} className="flex items-center gap-2 px-2 py-1.5 rounded hover:bg-zinc-100 cursor-pointer text-sm">
            <it.icon size={16} className="text-zinc-500" /> {it.name} <span className="ml-auto text-xs text-zinc-400">{it.count}</span>
          </div>
        ))}
        <Separator className="my-2"/>
        <div className="text-xs text-zinc-500 px-2">Feature History</div>
        {["Sketch","Extrude 25mm","Fillet 2mm","Pattern x4"].map((f,i)=>(
          <div key={i} className="px-2 py-1 text-xs bg-zinc-50 rounded border ml-2">{i+1}. {f}</div>
        ))}
      </CardContent>
    </Card>
  )
}
