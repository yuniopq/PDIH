# Seminario: Módulos Cargables del Kernel (LKM)

## 1. Proceso de Desarrollo

### Preparación del entorno
Primero, he preparado el sistema instalando las cabeceras del kernel correspondientes a mi versión:
```bash
sudo apt-get update
sudo apt-get install linux-headers-$(uname -r)
