import subprocess

def run_cmd(cmd):
    return subprocess.run(cmd, shell=True).stdout.decode("utf-8")

def setup_ping():
    # get the network interface name
    device = run_cmd("ip route | grep 10.10.1.1 | awk '{print $3}'").strip()
    run_cmd(f"export DEVICE={device}")
    run_cmd("make bpf.o DEVICE=$DEVICE")
    run_cmd("make qdisc DEVICE=$DEVICE")
    run_cmd("make run DEVICE=$DEVICE")

def main():
    setup_ping()

if __name__ == "__main__":
    main()
