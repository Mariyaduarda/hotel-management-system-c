# 🏨 Hotel Management System — C

Sistema de controle gerencial para hotel desenvolvido em linguagem C, como trabalho pratico da disciplina **Algoritmos II**.

---

## 📋 Sobre o projeto

O sistema permite gerenciar todas as operacoes de um hotel, desde o cadastro de hospedes e acomodacoes ate reservas, transacoes financeiras e relatorios.

---

## 🗂️ Estrutura do projeto

```
hotel-management-system-c/
├── main.c
├── common.h / common.c          # Utilitarios globais
├── model/                       # Estruturas de dados e persistência
│   ├── hotel.c / hotel.h
│   ├── hospede.c / hospede.h
│   ├── acomodacao.c / acomodacao.h
│   ├── reserva.c / reserva.h
│   ├── produto.c / produto.h
│   └── operador.c / operador.h
├── controller/                  # Regras de negocio
│   ├── hospede_controller.c / .h
│   ├── acomodacao_controller.c / .h
│   ├── reserva_controller.c / .h
│   ├── produto_controller.c / .h
│   ├── hotel_controller.c / .h
│   └── operador_controller.c / .h
├── view/                        # Interface com o usuario
│   ├── menu_principal.c / .h
│   ├── hospede_view.c / .h
│   ├── reserva_view.c / .h
│   ├── relatorio_view.c / .h
│   └── login_view.c / .h
├── utils/                       # Modulos auxiliares
│   ├── relatorio.c / .h
│   └── validacao.c / .h
└── dados/                       # Arquivos de persistência gerados em runtime
    ├── *.bin
    └── *.txt
```

---

## ⚙️ Modulos implementados

### ✅ Cadastros
- **Hotel** — dados da empresa (CNPJ, endereco, horarios de check-in/out, margem de lucro)
- **Hospedes** — cadastro completo com exclusao logica
- **Acomodacoes** — quartos com facilidades e categoria associada
- **Categorias** — Standard, Luxo, Presidencial etc. com valor de diaria e capacidade
- **Produtos** — itens de consumo com controle de estoque minimo
- **Operadores** — funcionarios com permissoes por modulo e senha SHA-256

### ✅ Reservas
- Verificacao de disponibilidade por periodo (sem sobreposicao de datas)
- Filtros por categoria, facilidade e numero de pessoas
- Cancelamento de reservas ativas

### 🚧 Transacoes *(em desenvolvimento)*
- Check-in e check-out
- Venda de produtos
- Controle de caixa
- Contas a pagar e a receber

### ✅ Relatorios
- Hospedes, acomodacoes, reservas, produtos e estoque minimo
- Saida em tela ou arquivo CSV

---

## 💾 Persistência

O sistema suporta três tipos de armazenamento, configuraveis:

| Tipo | Formato |
|------|---------|
| Memoria | Listas encadeadas em RAM |
| Arquivo texto | `.txt` separado por `;` |
| Arquivo binario | `.bin` com `fwrite`/`fread` |

Na inicializacao, o sistema tenta carregar o `.bin` primeiro. Se nao existir, tenta o `.txt`.

---

## 🔐 Seguranca

- Senhas dos operadores armazenadas como hash **SHA-256** via OpenSSL
- Permissoes por modulo usando **bitmask**
- Exclusao **logica** (campo `ativo`) — nenhum dado e deletado fisicamente

---

## 🛠️ Compilacao

### Pre-requisitos

- GCC
- OpenSSL (`libssl-dev`)

```bash
# Ubuntu/Debian
sudo apt install gcc libssl-dev
```

### Compilar e executar

```bash
make        # compila
make run    # compila e executa
make clean  # remove arquivos objeto e executavel
make re     # rebuild completo
```

---

## 🚀 Primeira execucao

Na primeira vez que o sistema e iniciado:

1. Cadastro do **operador administrador** (nome, usuario e senha)
2. Cadastro dos **dados do hotel** (CNPJ, endereco, horarios, margem de lucro)
3. Menu principal liberado

Nas execucoes seguintes, o sistema carrega os dados salvos e pede login.

---

## 📄 Licenca

Projeto acadêmico — Algoritmos II, 1º semestre de 2026.
