# Traffic Simulation DSA Project 🚦

A C-based smart traffic simulation system that dynamically manages traffic signals based on vehicle density and emergency vehicle presence. It also supports shortest path estimation using Dijkstra's algorithm.

## ✨ Features

- 😁 Dynamic traffic signal timing based on real-time input
- 🚨 Emergency vehicle prioritization with signal override
- 🔹 Real-time simulation loop for multiple intersections
- 📅 Estimated travel time and shortest path calculation
- 💡 Modular code design with separate files for graph, heap, Dijkstra, and simulation
- 🖥️ Optional Python UI (`ui.py`) for enhanced interaction

## 📂 Project Structure

| File              | Purpose                                      |
|-------------------|----------------------------------------------|
| `main.c`          | Main simulation driver                       |
| `graph.c/.h`      | Graph structure and edge management         |
| `dijkstra.c/.h`   | Dijkstra's algorithm for shortest paths      |
| `Heaps.c/.h`      | Min-Heap operations for priority queue       |
| `simulation.c/.h` | Traffic simulation logic                    |
| `ui.py`           | Python interface (optional)                 |
| `run.sh`          | Shell script to compile & run (Linux/Git Bash) |

## 📄 Compilation & Execution

### Windows (Command Prompt or Git Bash)

```bash
# Compile manually
gcc main.c dijkstra.c Heaps.c graph.c simulation.c -o Combined
Combined.exe

# OR use run.sh in Git Bash
./run.sh
```

### Linux / macOS

```bash
chmod +x run.sh
./run.sh
```

## 📊 Sample Output

```plaintext
--- Simulation Time: 1 ---
Enter traffic density manually? (y/n): y
Updated density at Intersection 5 to 80.00
Emergency at Intersection 9! Green Light for 60 sec
Shortest Path: 4 --> 14 --> 13 --> 15
Estimated Travel Duration: 95 mins
Total Distance: 18.87 Km
```

## 📅 How to Use

1. Run simulation
2. Input traffic density or emergency status
3. Perform operations:
   - Find shortest path
   - Add/delete roads (edges)
   - Print current graph

## 🌐 License

This project is open-source and available under the [MIT License](LICENSE).

---

### 📊 Author
Developed by Atharva Gharge as a Data Structures & Algorithms project.

> For any issues or contributions, feel free to open an issue or pull request on [GitHub](https://github.com/Atharvagharge/Traffic-Simulation-DSA-Project).
