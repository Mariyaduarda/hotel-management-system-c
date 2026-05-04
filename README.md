# 🏨 Hotel Management System — C

Sistema de controle gerencial para hotel desenvolvido em linguagem C, como trabalho prático da disciplina **Algoritmos II**.

---

## 📋 Sobre o projeto

O sistema permite gerenciar todas as operações de um hotel, desde o cadastro de hóspedes e acomodações até reservas, transações financeiras e relatórios.

---

## 🗂️ Estrutura do projeto

```
hotel-management-system-c/
├── main.c
├── common.h / common.c          # Utilitários globais (lerString, limparBuffer)
├── model/                       # Estruturas de dados e persistência
│   ├── hotel.c / hotel.h
│   ├── hospede.c / hospede.h
│   ├── acomodacao.c / acomodacao.h
│   ├── reserva.c / reserva.h
│   ├── produto.c / produto.h
│   └── operador.c / operador.h
├── controller/                  # Regras de negócio
│   ├── hospede_controller.c / .h
│   ├── acomodacao_controller.c / .h
│   ├── reserva_controller.c / .h
│   ├── produto_controller.c / .h
│   ├── hotel_controller.c / .h
│   └── operador_controller.c / .h
├── view/                        # Interface com o usuário
│   ├── menu_principal.c / .h
│   ├── hospede_view.c / .h
│   ├── reserva_view.c / .h
│   ├── relatorio_view.c / .h
│   └── login_view.c / .h
├── utils/                       # Módulos auxiliares
│   ├── relatorio.c / .h
│   └── validacao.c / .h
└── dados/                       # Arquivos de persistência gerados em runtime
    ├── *.bin
    └── *.txt
```

---

## ⚙️ Módulos implementados

### ✅ Cadastros
- **Hotel** — dados da empresa (CNPJ, endereço, horários de check-in/out, margem de lucro)
- **Hóspedes** — cadastro completo com exclusão lógica
- **Acomodações** — quartos com facilidades e categoria associada
- **Categorias** — Standard, Luxo, Presidencial etc. com valor de diária e capacidade
- **Produtos** — itens de consumo com controle de estoque mínimo
- **Operadores** — funcionários com permissões por módulo e senha SHA-256

### ✅ Reservas
- Verificação de disponibilidade por período (sem sobreposição de datas)
- Filtros por categoria, facilidade e número de pessoas
- Cancelamento de reservas ativas

### 🚧 Transações *(em desenvolvimento)*
- Check-in e check-out
- Venda de produtos
- Controle de caixa
- Contas a pagar e a receber

### ✅ Relatórios
- Hóspedes, acomodações, reservas, produtos e estoque mínimo
- Saída em tela ou arquivo CSV

---

## 💾 Persistência

O sistema suporta três tipos de armazenamento, configuráveis:

| Tipo | Formato |
|------|---------|
| Memória | Listas encadeadas em RAM |
| Arquivo texto | `.txt` separado por `;` |
| Arquivo binário | `.bin` com `fwrite`/`fread` |

Na inicialização, o sistema tenta carregar o `.bin` primeiro. Se não existir, tenta o `.txt`.

---

## 🔐 Segurança

- Senhas dos operadores armazenadas como hash **SHA-256** via OpenSSL
- Permissões por módulo usando **bitmask**
- Exclusão **lógica** (campo `ativo`) — nenhum dado é deletado fisicamente

---

## 🛠️ Compilação

### Pré-requisitos

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
make clean  # remove arquivos objeto e executável
make re     # rebuild completo
```

---

## 🚀 Primeira execução

Na primeira vez que o sistema é iniciado:

1. Cadastro do **operador administrador** (nome, usuário e senha)
2. Cadastro dos **dados do hotel** (CNPJ, endereço, horários, margem de lucro)
3. Menu principal liberado

Nas execuções seguintes, o sistema carrega os dados salvos e pede login.

---

## 📄 Licença

Projeto acadêmico — Algoritmos II, 1º semestre de 2026.
