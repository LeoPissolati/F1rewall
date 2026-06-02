# 🔥 Firewall

Firewall em userspace desenvolvido em C, criado como parte do processo seletivo do PATOS.

O firewall atua sobre uma interface de rede virtual (TUN), operando em um IP diferente
do IP da máquina host, roteando e filtrando o tráfego de uma sub-rede inteira (10.0.0.x/24).

**Autor:** Leo Pissolati

---

## 📋 Índice

- [Como funciona](#como-funciona)
- [Requisitos](#requisitos)
- [Instalação e uso](#instalação-e-uso)
- [Funcionalidades](#funcionalidades)
- [Estrutura do projeto](#estrutura-do-projeto)
- [Fontes de pesquisa](#fontes-de-pesquisa)
- [Jornada de aprendizado](#jornada-de-aprendizado)

---

## Como funciona

O programa cria uma interface de rede virtual TUN (`tun0`) e atribui a ela o IP `10.0.0.1/24`.
Todo o tráfego destinado à sub-rede `10.0.0.x` é roteado para essa interface e entregue
diretamente ao processo do firewall como bytes crus.

O firewall lê cada pacote, faz o parse manual dos headers IP, ICMP, TCP e UDP, aplica
as regras de filtragem e decide se o pacote é permitido, bloqueado ou respondido.

Nenhuma biblioteca de abstração de rede foi utilizada. Todo o parse de pacotes,
montagem de respostas e cálculo de checksum é feito manualmente.

---

## Requisitos

| Requisito | Detalhe |
|---|---|
| Sistema operacional | Linux |
| Kernel | 2.6+ (suporte a TUN/TAP) |
| Permissão | root (sudo) |
| Compilador | gcc |
| Dependências | iproute2 (comandos `ip`) |

Verificar se o módulo TUN está carregado:

```bash
sudo modprobe tun
```

---

## Instalação e uso

**Clonar o repositório:**
```bash
git clone https://github.com/LeopPissolati/firewall.git
cd firewall
```

**Compilar:**
```bash
make
```

**Executar:**
```bash
make run
# ou
sudo ./firewall
```

**Limpar arquivos compilados:**
```bash
make clean
```

---

## Funcionalidades

### ✅ Essenciais

**Interface TUN virtual**
- Cria automaticamente a interface `tun0` com IP `10.0.0.1/24`
- Não requer configuração manual de rede

**Filtragem e resposta de ICMP (ping)**
- Responde pings recebidos na sub-rede `10.0.0.x`
- Bloqueia completamente o IP `10.0.0.50` — nenhum pacote passa
- Copia o payload do echo request para o echo reply

**Filtragem de pacotes UDP**
- Bloqueia pacotes cujo payload contenha palavras da lista de palavras proibidas
- Lista carregada do arquivo `blocked_words.txt` — sem necessidade de recompilar

**Filtragem de pacotes TCP**
- Bloqueia pacotes cujo payload contenha palavras da lista de palavras proibidas
- Usa `memmem()` para busca segura em payloads binários com bytes nulos

### ⭐ Diferenciais

**Logs detalhados**
- Cada pacote processado gera um log com timestamp, protocolo, IP origem, IP destino,
porta e ação tomada (ALLOW / BLOCK)

**Exibição de payload**
- Payloads exibidos em formato hexdump: hex + ASCII lado a lado

**TCP Three-Way Handshake**
- Responde SYN com SYN-ACK
- Envia RST para pacotes com conteúdo malicioso

---

## Estrutura do projeto

---

## Fontes de pesquisa

- [Linux TUN/TAP documentation](https://www.kernel.org/doc/html/latest/networking/tuntap.html)
- [RFC 791 — Internet Protocol](https://datatracker.ietf.org/doc/html/rfc791)
- [RFC 792 — ICMP](https://datatracker.ietf.org/doc/html/rfc792)
- [RFC 768 — UDP](https://datatracker.ietf.org/doc/html/rfc768)
- [RFC 793 — TCP](https://datatracker.ietf.org/doc/html/rfc793)
- [Linux man pages — tun(4)](https://man7.org/linux/man-pages/man4/tun.4.html)
- [Linux man pages — ioctl(2)](https://man7.org/linux/man-pages/man2/ioctl.2.html)

---

## Jornada de aprendizado

> ⚠️ **SEÇÃO PARA PREENCHER** — escreva com suas próprias palavras.
> Sugestão de pontos para cobrir:

> - O que você sabia antes de começar e o que não sabia
> - Qual foi o conceito mais difícil de entender (TUN? headers? checksum?)
> - O que travou mais e como você desbloqueou
> - O que você faria diferente se começasse de novo
> - O que esse projeto te ensinou que vai além do código

---

*Desenvolvido por [Leo Pissolati](https://github.com/LeopPissolati) — PATOS PSEL 2025*
