cmake_minimum_required(VERSION 3.10)
project(OrdenacaoParalela)

# Definir versão C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configuração de compilação
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Opções de compilação para diferentes ambientes
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -pthread")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
endif()

# Encontrar bibliotecas
find_package(Threads REQUIRED)

# Diretórios de inclusão
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Arquivos fonte do projeto
set(SOURCE_FILES
    src/main.cpp
    src/algoritmos_ordenacao.cpp
    src/ordenacao_paralela.cpp
    src/gerador_dados.cpp
    src/benchmark.cpp
)

# Criar executável
add_executable(ordenacao_paralela ${SOURCE_FILES})

# Vincular bibliotecas
target_link_libraries(ordenacao_paralela
    PRIVATE
    Threads::Threads
    $<$<PLATFORM_ID:Windows>:ws2_32>
    $<$<PLATFORM_ID:Windows>:mswsock>
)

# Opções para instalação
install(TARGETS ordenacao_paralela 
    RUNTIME DESTINATION bin
)

# Informação de compilação
message(STATUS "Modo de compilação: ${CMAKE_BUILD_TYPE}")
message(STATUS "Flags C++: ${CMAKE_CXX_FLAGS}")
