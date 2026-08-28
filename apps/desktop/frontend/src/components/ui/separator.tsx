import * as React from "react"
import { cn } from "@/lib/utils"
export const Separator = ({ className, orientation="horizontal", ...props }: React.HTMLAttributes<HTMLDivElement> & {orientation?: "horizontal"|"vertical"}) => (
  <div className={cn(orientation==="horizontal" ? "h-px w-full bg-zinc-200" : "w-px h-full bg-zinc-200", className)} {...props} />
)
