import { Card, CardHeader, CardContent } from "./ui/card"
import { Separator } from "./ui/separator"
import { Button } from "./ui/button"
export function PropertiesPanel(){
  return (
    <Card className="h-full rounded-none border-y-0 border-r-0 flex flex-col w-full lg:w-[300px] max-w-[90vw]">
      <CardHeader className="py-3 font-semibold text-sm shrink-0">Properties</CardHeader>
      <Separator />
      <CardContent className="p-3 space-y-4 overflow-auto flex-1">
        <div><div className="text-xs font-medium text-zinc-700 mb-1">Transform</div>
          <div className="grid grid-cols-3 gap-1 text-xs">
            {["X","Y","Z"].map(ax=> <div key={ax} className="bg-zinc-50 border rounded px-2 py-1.5 text-center">{ax}: 0.00</div>)}
          </div>
        </div>
        <Separator />
        <div><div className="text-xs font-medium text-zinc-700 mb-1">Material</div>
          <div className="flex items-center gap-2 text-xs"><div className="w-6 h-6 rounded bg-zinc-300 border shrink-0"/> <span className="truncate">Steel — E: 210 GPa</span></div>
        </div>
        <Separator />
        <div><div className="text-xs font-medium text-zinc-700 mb-1">Simulation</div>
          <div className="space-y-1 text-xs">
            <div className="flex justify-between gap-2"><span className="shrink-0">Max Stress</span><span className="font-mono truncate">12.5 MPa</span></div>
            <div className="flex justify-between gap-2"><span className="shrink-0">Displacement</span><span className="font-mono truncate">0.002 mm</span></div>
            <Button size="sm" className="w-full mt-2">Run FEA</Button>
          </div>
        </div>
        <Separator />
        <div><div className="text-xs font-medium text-zinc-700 mb-1">Python</div>
          <pre className="bg-zinc-900 text-zinc-100 text-[11px] p-2 rounded overflow-auto max-w-full whitespace-pre-wrap break-all">sketch.circle(center=(0,0), radius=25)
part.extrude(sketch, distance=50)</pre>
        </div>
      </CardContent>
    </Card>
  )
}
