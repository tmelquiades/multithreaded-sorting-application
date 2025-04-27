FROM ubuntu:22.04 AS builder

# Instalar dependências de build
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    pkg-config \
    libboost-all-dev \
    libasio-dev \
    && rm -rf /var/lib/apt/lists/*

# Copiar arquivos do projeto
WORKDIR /app
COPY . .

# Criar diretório para build
RUN mkdir -p build

# Compilar o projeto
WORKDIR /app/build
RUN cmake .. && \
    make -j$(nproc)

# Segunda etapa: imagem final
FROM ubuntu:22.04

# Instalar dependências de runtime
RUN apt-get update && apt-get install -y \
    libboost-system1.74.0 \
    libboost-filesystem1.74.0 \
    && rm -rf /var/lib/apt/lists/*

# Copiar executável e arquivos estáticos da etapa de build
WORKDIR /app
COPY --from=builder /app/build/ordenacao_paralela /app/

# Variáveis de ambiente
ENV NUM_THREADS=4

CMD ["/app/ordenacao_paralela"]