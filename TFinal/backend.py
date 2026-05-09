import reedsolo
import random

def codificar_mensaje(texto, t):
    """Convierte el texto en un paquete codificado usando Reed-Solomon."""
    nsym = 2 * t
    rs_obj = reedsolo.RSCodec(nsym)
    datos_bytes = texto.encode('utf-8')
    paquete_codificado = bytearray(rs_obj.encode(datos_bytes))
    
    return rs_obj, paquete_codificado, nsym

def aplicar_ruido_canal(paquete_codificado, porcentaje_ruido):
    """Simula un canal ruidoso alterando bytes al azar."""
    prob_error = porcentaje_ruido / 100.0
    paquete_corrupto = bytearray(paquete_codificado)
    errores_introducidos = 0
    
    for i in range(len(paquete_corrupto)):
        if random.random() < prob_error:
            paquete_corrupto[i] ^= random.randint(1, 255)
            errores_introducidos += 1
            
    return paquete_corrupto, errores_introducidos

def decodificar_mensaje(rs_obj, paquete_corrupto):
    """Intenta corregir los errores y recuperar el texto original."""
    try:
        datos_corregidos, _, err_pos = rs_obj.decode(paquete_corrupto)
        texto_recuperado = datos_corregidos.decode('utf-8', errors='ignore')
        return True, len(err_pos), texto_recuperado
    except reedsolo.ReedSolomonError:
        return False, 0, ""
