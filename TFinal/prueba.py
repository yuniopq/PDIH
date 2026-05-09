import tkinter as tk

ventana = tk.Tk()
ventana.title("Prueba")
ventana.geometry("300x200")

saludo = tk.Label(ventana, text="¡Hola, Mundo!")
saludo.pack()
btn = tk.Button(ventana, text="Cerrar", command=ventana.destroy)
btn.pack()

ventana.mainloop()
