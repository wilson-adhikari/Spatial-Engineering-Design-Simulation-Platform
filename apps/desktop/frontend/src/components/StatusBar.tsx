export function StatusBar(){
  return (
    <div className="h-6 border-t bg-zinc-50 flex items-center px-3 text-[11px] text-zinc-600 gap-4">
      <span>Ready</span><span className="w-px h-3 bg-zinc-300"/>
      <span>Selection: Part1.Face3</span><span className="w-px h-3 bg-zinc-300"/>
      <span>Coords: (12.3, -4.1, 0.0)</span><span className="ml-auto">Spatial Engine v0.1.0 — ReUI</span>
    </div>
  )
}
