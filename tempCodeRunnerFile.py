import tkinter as tk
import random
from tkinter import Tk

# Load Graph Data from File
filename = "graph_data.txt"
with open(filename, "r") as file:
    content = file.readlines()
    data_dict = {}
    for line in content:
        values = line.split()
        if values:  # Ensure line is not empty
            key = values[0]
            dictionary_values = values[1:]
            data_dict[key] = dictionary_values

# Load Shortest Path Data from File
spname = "shortpath.txt"
with open(spname, "r") as file:
    nums = [int(num) for num in file.read().split()]

class GraphDisplay(tk.Canvas):
    def __init__(self, master, graph, sp, **kwargs):
        super().__init__(master, **kwargs)
        self.graph = graph
        self.sp = sp
        self.node_radius = 20
        self.edge_width = 2
        self.node_positions = {}  # Store node positions
        
        # Traffic Data
        self.traffic_density = {node: random.randint(10, 100) for node in self.graph}  # Initialize random density
        self.traffic_signals = {node: "RED" for node in self.graph}  # Default to RED

        # Start traffic updates
        self.update_traffic()

    def draw_graph(self):
        self.delete(tk.ALL)  # Clear canvas

        # Calculate node positions
        self.calculate_node_positions()

        # Draw edges with varying thickness based on traffic density
        for node, edges in self.graph.items():
            x1, y1 = self.node_positions[node]
            for adj_node in edges:
                if adj_node not in self.node_positions:
                    continue
                x2, y2 = self.node_positions[adj_node]

                # Set color and thickness based on traffic density
                traffic_level = self.traffic_density.get(node, 50)
                color = "green" if traffic_level < 40 else "orange" if traffic_level < 70 else "red"
                width = 2 + (traffic_level / 20)  # Dynamic thickness
                
                self.create_line(x1, y1, x2, y2, width=width, fill=color)

        # Draw nodes with signals
        for node, position in self.node_positions.items():
            x, y = position

            # Select node color based on signal
            signal = self.traffic_signals[node]
            if signal == "GREEN":
                fill_color = "green"
            elif signal == "YELLOW":
                fill_color = "yellow"
            else:
                fill_color = "red"

            self.create_oval(x - self.node_radius, y - self.node_radius,
                             x + self.node_radius, y + self.node_radius,
                             fill=fill_color, outline='black')
            self.create_text(x, y, text=str(node), font=("Arial", 10, "bold"), fill="white")

    def update_traffic(self):
        """Simulate traffic density changes and update signals."""
        for node in self.graph:
            # Randomly update traffic density (or get from C backend)
            self.traffic_density[node] = random.randint(10, 100)

            # Change signals based on traffic
            if self.traffic_density[node] < 40:
                self.traffic_signals[node] = "GREEN"
            elif self.traffic_density[node] < 70:
                self.traffic_signals[node] = "YELLOW"
            else:
                self.traffic_signals[node] = "RED"

        self.draw_graph()  # Redraw with updated data

        # Schedule next update after 2 seconds
        self.after(2000, self.update_traffic)

    def calculate_node_positions(self):
        """Manually assigned positions for each node"""
        arr = [600,600,    #0
               720,650,    #1
               960,590,   #2
               790,490,   #3
               920,470,     #4
               590,350,     #5
               400,630,     #6
               740,270,     #7
               250,440,     #8
               290,200,     #9
               590,470,     #10
               850,70,     #11
               870,680,     #12
               935,770,     #13
               1170,470,     #14
               600,740,     #15
               950,320,     #16
               530,160,     #17
               1190,70,     #18
               950, 190 ]  #19
            
        j = 0
        for i, node in enumerate(self.graph.keys()):        
            x = arr[j] 
            y = arr[j + 1]
            j += 2
            self.node_positions[node] = (x, y)

    def resize(self, event):
        self.draw_graph()

# Example usage
if __name__ == "__main__":
    graph = data_dict
    sp = {}
    k = 0
    while k < len(nums):
        if k + 1 == len(nums):
            sp[str(nums[k])] = ""
            break
        sp[str(nums[k])] = str(nums[k + 1])
        k += 1

    root = Tk()
    root.title("Traffic Simulation")

    canvas = GraphDisplay(root, graph, sp, width=800, height=600)
    canvas.pack(fill=tk.BOTH, expand=True)
    canvas.draw_graph()
    canvas.bind("<Configure>", canvas.resize)

    root.mainloop()