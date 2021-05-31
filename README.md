# Layer 2 Switch Simulator

## Desciption

This is a Switch simulator that used an interface for making a network and send commands to nodes to comminucate with each other.

## How to run

```bash
make clean
make
./simulator.out
```

## Simulation commands

```bash
add_switch <id> <portCount>
add_system <id>
connect <system_id> <switch_id> <port_number>
connect_switch <switch1_id> <s1_port> <switch2_id> <s2_port>
ping <system1_id> <system2_id>
req <system1_id> <system2_id> <file_name>
stptree
```
