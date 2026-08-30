export function StatusBar(){
  return (
    <div className="h-6 border-t bg-zinc-50 flex items-center px-2 md:px-3 text-[10px] md:text-[11px] text-zinc-600 gap-2 md:gap-4 overflow-hidden shrink-0">
      <span className="shrink-0">Ready</span><span className="w-px h-3 bg-zinc-300 hidden sm:block shrink-0"/>
      <span className="truncate hidden md:inline">Selection: Part1.Face3</span><span className="w-px h-3 bg-zinc-300 hidden md:block shrink-0"/>
      <span className="truncate hidden sm:inline">Coords: (12.3, -4.1, 0.0)</span>
      <span className="ml-auto truncate text-[9px] md:text-[11px] shrink-0">Spatial v0.1.0</span>
    </div>
  )
}
