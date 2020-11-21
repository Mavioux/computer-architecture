<center> 
  <h1> Αρχιτεκτονική Υπολογιστών</h1>
  <h1>  Μάριος Πάκας </h1>
  <h1> 9498 </h1> 
  <br>
  <h2> Εργαστήριο 1 </h2>
</center>


---
### 1) Από το αρχείο starter_se.py παρατηρούμε τα εξής:

Τα τρία είδη επεξεργαστών που μπορούν να προσομοιωθούν είναι τα παρακάτω:

- atomic
- minor
- hpi

όπως προκύπτει από εδώ:

```python
cpu_types = {
    "atomic" : ( AtomicSimpleCPU, None, None, None, None),
    "minor" : (MinorCPU,
               devices.L1I, devices.L1D,
               devices.WalkCache,
               devices.L2),
    "hpi" : ( HPI.HPI,
              HPI.HPI_ICache, HPI.HPI_DCache,
              HPI.HPI_WalkCache,
              HPI.HPI_L2)
}
```

Μπορούμε να επιλέγξουμε το είδος του επεξεργαστή μέσα από το όρισμα --cpu και μάλιστα παρατηρούμε ότι στην δικιά μας εντολή χρησιμοποιήσαμε τον minor επεξεργαστή αφού γράψαμε --cpu=”minor”

#### Για τη μνήμη cache αναφέρεται: 

 
`# Use a fixed cache line size of 64 bytes`  
`cache_line_size = 64`

το οποίο θέτει το μέγεθος της cache σε 64 bytes

#### Ακόμη οι παρακάτω εντολές θέτουν την τάση στα 3.3V και το ρολόι του επεξεργαστή στο 1GHz

```
# Create a voltage and clock domain for system components
self.voltage_domain = VoltageDomain(voltage="3.3V")
self.clk_domain = SrcClockDomain(clock="1GHz",
voltage_domain=self.voltage_domain)
```

#### Ενώ η παρακάτω εντολή δημιουργεί τον memory bus:

```
# Create the off-chip memory bus.
self.membus = SystemXBar()
```

#### Οι παρακάτω εντολές προσθέτουν τους CPUs στο cluster, αυτό που με προβλημάτισε όμως είναι η αναφορά στα 1.2V, ενώ η τάση του συστήματος παραπάνω έχει οριστεί στα 3.3V.  

```python
  # Add CPUs to the system. A cluster of CPUs typically have private L1 caches and a shared L2 cache.
  self.cpu_cluster = devices.CpuCluster(self,
                                        args.num_cores,
                                        args.cpu_freq, "1.2V",
                                        *cpu_types[args.cpu])
```

#### Στο παρακάτω κομμάτι κώδικα ορίζονται τα ορίσματα που μπορεί να δώσει κανείς πριν την εκτέλεση της προσομοίωσης, καθώς και οι default τιμές. Επομένως, καθώς εμείς δεν ορίζουμε κάτι πέραν του τύπου της cpu παρατηρούμε ότι:

```python
# Choose the type of the cpu for the simulation from the cpu_types
parser.add_argument("--cpu", type=str, choices=list(cpu_types.keys()),
                        default="atomic",
                        help="CPU model to use")

# Set the CPU frequency
parser.add_argument("--cpu-freq", type=str, default="4GHz")

# Set number of cores
parser.add_argument("--num-cores", type=int, default=1,
                        help="Number of CPU cores")

# Set the type of memory to be used
parser.add_argument("--mem-type", default="DDR3_1600_8x8",
                        choices=ObjectList.mem_list.get_names(),
                        help = "type of memory to use")

# Set the number of memory channels
parser.add_argument("--mem-channels", type=int, default=2,
                        help = "number of memory channels")

# Set the memory ranks per channel (don’t know what that means though)

parser.add_argument("--mem-ranks", type=int, default=None,
                        help = "number of memory ranks per channel")

# Set the memory size
parser.add_argument("--mem-size", action="store", type=str,
                        default="2GB",
                        help="Specify the physical memory size")
```



### 2)

### a)
### Από το stats.txt

```
sim_freq                                 1000000000000                       # Frequency of simulated ticks
sim_insts                                        5028                       # Number of instructions simulated
sim_ticks                                    24321000                       # Number of ticks simulated
system.cpu_cluster.voltage_domain.voltage     1.200000                       # Voltage in Volts
system.voltage_domain.voltage                3.300000                       # Voltage in Volts
```

Από τα παραπάνω συμπεραίνουμε ότι η συχνότητα του επεξεργαστή είναι 1GHz, ο αριθμός των εντολών που προσομοιώθηκαν είναι 5028, τα ticks που προσομοιώθηκαν ειναι 24321000, η τάση του επεξεργαστή είναι 3.3V και το cluster voltage, όπως δηλώνεται και στο starter_se.py είναι 1.2V.

### Από το config.json

Με σχόλιο αναφέρομαι στα κομμάτια του config που επιβεβαιώνουν το stats.txt

```
"system": {
	# Το μέγεθος της cache
	"cache_line_size": 64,
	# Δύο μνήμες
	"memories": [
            "system.mem_ctrls0.dram",
            "system.mem_ctrls1.dram"
        ],
	"clk_domain": {
            "type": "SrcClockDomain",
            "cxx_class": "SrcClockDomain",
            "name": "clk_domain",
            "path": "system.clk_domain",
            "clock": [
                1000
            ],
            "domain_id": -1,
            "eventq_index": 0,
            "init_perf_level": 0,
            "voltage_domain": "system.voltage_domain"
        },
	"cpu_cluster": {
		"cpus": [
                {
	              # Type of CPU
                    "type": "MinorCPU",
                    "cxx_class": "MinorCPU",
		},
	},
	"voltage_domain": {
            "type": "VoltageDomain",
            "cxx_class": "VoltageDomain",
            "name": "voltage_domain",
            "path": "system.voltage_domain",
            "eventq_index": 0,
	           # Voltage 3.3 V
            "voltage": [
                3.3
            ]
        },
	# L2
	"l2": {
                "type": "Cache",
                "cxx_class": "Cache",
                "name": "l2",
                "path": "system.cpu_cluster.l2",
                "addr_ranges": [
                    "0:18446744073709551615"
                ],
                "assoc": 16,
	},
}
```


### b) 

### Stats.txt

```
Committed Instructions: 5028
system.cpu_cluster.cpus.committedInsts           5028                       # Number of instructions committed
```

Αλλά δεν μπορώ να βρω με ποιόν αριθμό του gem5 να το συγκρίνω.

### c) Στο stats.txt αναγράφεται το εξής:

```
system.cpu_cluster.l2.demand_misses::total          479                       # number of demand (read+write) misses
```


### 3) Για το ερώτημα αυτό έγραψα ένα απλό for-loop το οποίο απαριθμεί από το 0 έως το 9 και στη συνέχεια το έκανα compile σε arm με την εντολή: arm-linux-gnueabihf-gcc --static for_loop.c -o for_loop_arm

Εν συνεχεία το εκτέλεσα στον προσομοιωτή μέσω των εντολών (μία για κάθε τύπο διαθέσιμου CPU) για το starter_se config όμως.: 

build/ARM/gem5.opt -d for_loop-atomic-cpu configs/example/arm/starter_se.py --cpu="atomic" tests/test-progs/for-loop/src/for_loop_arm

build/ARM/gem5.opt -d for_loop-minorCPU configs/example/arm/starter_se.py --cpu="minor" tests/test-progs/for-loop/src/for_loop_arm

build/ARM/gem5.opt -d for_loop-hpi configs/example/arm/starter_se.py --cpu="hpi" tests/test-progs/for-loop/src/for_loop_arm
