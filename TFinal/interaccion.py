import tkinter as tk

def saludar_usuario():
    nombre = caja_texto.get()
    if nombre:
        saludo.config(text="¡Hola, " + nombre + "!")
    else:
        saludo.config(text="Por favor introduce tu nombre.")

ventana = tk.Tk()
ventana.title("Interacción con el usuario")
ventana.geometry("350x250")

instruccion = tk.Label(ventana, text="Introduce tu nombre:")
instruccion.pack(pady=10)

caja_texto = tk.Entry(ventana)
caja_texto.pack(pady=5)

btn_saludar = tk.Button(ventana, text="¡Salúdame!", command=saludar_usuario)
btn_saludar.pack(pady=10)

saludo = tk.Label(ventana, text="", font=("Arial", 12, "bold"))
saludo.pack(pady=10)

btn_cerrar = tk.Button(ventana, text="Cerrar", command=ventana.destroy)
btn_cerrar.pack(pady=10)

ventana.mainloop()
