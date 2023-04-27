import subprocess

def run_cmd(cmd):
    return subprocess.run(cmd, shell=True, capture_output=True).stdout.decode()

def setup_ping():
    # get the network interface name
    device = run_cmd("ip route | grep 10.10.1.1 | awk '{print $3}'").strip()
    run_cmd(f"export DEVICE={device}")
    run_cmd("make bpf.o && make qdisc && make run")

def main():
    setup_ping()

if __name__ == "__main__":
    main()
