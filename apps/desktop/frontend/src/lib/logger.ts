type Level = 'debug' | 'info' | 'warn' | 'error'
interface LogEntry { level: Level; message: string; context?: Record<string, unknown>; timestamp: string }

class Logger {
  private levelRank: Record<Level, number> = { debug: 0, info: 1, warn: 2, error: 3 }
  private current: Level = (import.meta.env.VITE_LOG_LEVEL as Level) || 'info'

  private log(level: Level, message: string, context?: Record<string, unknown>) {
    if (this.levelRank[level] < this.levelRank[this.current]) return
    const entry: LogEntry = { level, message, context, timestamp: new Date().toISOString() }
    const out = JSON.stringify(entry)
    if (level === 'error') console.error(out)
    else if (level === 'warn') console.warn(out)
    else console.log(out)
  }
  debug(msg: string, ctx?: Record<string, unknown>) { this.log('debug', msg, ctx) }
  info(msg: string, ctx?: Record<string, unknown>) { this.log('info', msg, ctx) }
  warn(msg: string, ctx?: Record<string, unknown>) { this.log('warn', msg, ctx) }
  error(msg: string, ctx?: Record<string, unknown>) { this.log('error', msg, ctx) }
}

export const logger = new Logger()
export type { LogEntry, Level }
