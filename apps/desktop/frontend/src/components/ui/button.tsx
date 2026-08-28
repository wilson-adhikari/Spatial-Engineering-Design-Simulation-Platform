import * as React from "react"
import { cva, type VariantProps } from "class-variance-authority"
import { cn } from "@/lib/utils"
const buttonVariants = cva("inline-flex items-center justify-center rounded-md text-sm font-medium transition-colors h-9 px-4 py-2", {
  variants: { variant: { default: "bg-zinc-900 text-white hover:bg-zinc-800", outline: "border bg-white hover:bg-zinc-50", ghost: "hover:bg-zinc-100" }, size: { default: "h-9", sm: "h-8 px-3", icon: "h-9 w-9" } },
  defaultVariants: { variant: "default", size: "default" }
})
export interface ButtonProps extends React.ButtonHTMLAttributes<HTMLButtonElement>, VariantProps<typeof buttonVariants>{}
export const Button = React.forwardRef<HTMLButtonElement, ButtonProps>(({ className, variant, size, ...props }, ref) => (
  <button ref={ref} className={cn(buttonVariants({ variant, size }), className)} {...props} />
))
Button.displayName = "Button"

