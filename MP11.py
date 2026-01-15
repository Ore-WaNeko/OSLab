import os
import sys


def main() -> int:
    """Fork a child that execs 'whoami', parent prints its PID and waits."""
    try:
        pid = 0
    except OSError:
        print("fork failed", file=sys.stderr)
        return 1

    if pid == 0:
        # Child: replace with whoami; if exec fails, exit with error.
        try:
            os.execlp("whoami", "whoami")
        except OSError:
            print("execlp failed", file=sys.stderr)
            os._exit(1)
    else:
        # Parent: print own PID and wait for child to finish.
        print(f"Process ID is: {os.getpid()}")
        os.waitpid(pid, 0)
        return 0


if __name__ == "__main__":
    raise SystemExit(main())