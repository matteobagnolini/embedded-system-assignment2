import tkinter as tk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt
import threading
import time
from WasteDisposalHandler import (
    empty_container,
    resolve_temperature_problems,
    receive_temp,
    communication_routine,
    get_filling_perc,
    get_container_full,
    get_temp_problem_detected,
)

temperature_data = []


def update_graph(canvas, ax, line):
    """
    Update the graphic with newer data.
    """
    window_size = 50
    if len(temperature_data) > window_size:
        displayed_data = temperature_data[-window_size:]
    else:
        displayed_data = temperature_data

    line.set_ydata(displayed_data)
    line.set_xdata(range(len(displayed_data)))
    ax.relim()
    ax.autoscale_view()
    ax.set_ylim(10, 30)

    ax.xaxis.set_ticks([])
    ax.set_xticklabels([])

    canvas.draw()


def message_loop(canvas, ax, line):
    """
    Loop for updating temeprature graphic.
    """
    global temperature_data
    while True:
        new_temperature = receive_temp()
        temperature_data.append(new_temperature)
        if len(temperature_data) > 500:
            temperature_data = temperature_data[-500:]
        update_graph(canvas, ax, line)
        time.sleep(1)


def update_filling_label(filling_label):
    """
    Update filling percentage message.
    """
    while True:
        filling_percentage = max(0, min(get_filling_perc(), 100))
        filling_label.config(text=f"Container filling: {filling_percentage}%")
        time.sleep(1)


def update_container_warning(container_warning_label):
    """
    Update message for container state.
    """
    while True:
        if get_container_full():
            container_warning_label.config(text="Warning! The container is FULL", foreground="red")
        else:
            container_warning_label.config(text="")
        time.sleep(1)


def update_temperature_status(temp_status_label):
    """
    Update message of temperature status.
    """
    while True:
        if get_temp_problem_detected():
            temp_status_label.config(text="Warning! Temperature problem detected", foreground="red")
        else:
            temp_status_label.config(text="Temperature status: Normal", foreground="green")
        time.sleep(1)


def create_gui():
    root = tk.Tk()
    root.title("Container Management")
    root.geometry("1600x800")

    root.update_idletasks()
    width = root.winfo_width()
    height = root.winfo_height()
    x = (root.winfo_screenwidth() // 2) - (width // 2)
    y = (root.winfo_screenheight() // 2) - (height // 2)
    root.geometry(f"{width}x{height}+{x}+{y}")

    main_frame = tk.Frame(root)
    main_frame.pack(fill=tk.BOTH, expand=True)

    graph_frame = tk.Frame(main_frame, width=400, height=200)
    graph_frame.pack(side=tk.LEFT, padx=10, pady=10)

    fig, ax = plt.subplots(figsize=(6, 3))
    ax.set_title("Temperature Graphic")
    ax.set_xlabel("")
    ax.set_ylabel("Temperature")
    ax.set_ylim(10, 30)
    ax.grid(True)

    line, = ax.plot([], [], color='red', linestyle='-')
    canvas = FigureCanvasTkAgg(fig, master=graph_frame)
    canvas_widget = canvas.get_tk_widget()
    canvas_widget.pack(fill=tk.BOTH, expand=True)

    control_frame = tk.Frame(main_frame)
    control_frame.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True, padx=20, pady=20)

    button_container = tk.Frame(control_frame)
    button_container.place(relx=0.5, rely=0.3, anchor=tk.CENTER)

    btn_empty_container = tk.Button(button_container, text="Empty Container", command=empty_container, width=20, height=2)
    btn_resolve_temp = tk.Button(button_container, text="Resolve Temperature Problems", command=resolve_temperature_problems, width=20, height=2)

    btn_empty_container.pack(pady=10)
    btn_resolve_temp.pack(pady=10)

    filling_label = tk.Label(control_frame, text="Container filling: 0%", font=("Arial", 14), fg="black")
    filling_label.place(relx=0.5, rely=0.5, anchor=tk.CENTER)

    container_warning_label = tk.Label(control_frame, text="", font=("Arial", 14), fg="red")
    container_warning_label.place(relx=0.5, rely=0.6, anchor=tk.CENTER)

    temp_status_label = tk.Label(control_frame, text="Temperature status: Normal", font=("Arial", 14), fg="green")
    temp_status_label.place(relx=0.5, rely=0.7, anchor=tk.CENTER)

    threading.Thread(target=message_loop, args=(canvas, ax, line), daemon=True).start()
    threading.Thread(target=update_filling_label, args=(filling_label,), daemon=True).start()
    threading.Thread(target=update_container_warning, args=(container_warning_label,), daemon=True).start()
    threading.Thread(target=update_temperature_status, args=(temp_status_label,), daemon=True).start()

    root.mainloop()


if __name__ == "__main__":
    threading.Thread(target=communication_routine, daemon=True).start()
    create_gui()
