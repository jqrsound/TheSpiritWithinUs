FROM gcc:12.5.0 AS builder
WORKDIR /usr/src/myapp

RUN apt-get update \
 && apt-get install -y --no-install-recommends \
 make gawk graphviz zip unzip \
 && rm -rf /var/lib/apt/lists/*

COPY . .

RUN cd src && make


FROM debian:bookworm-slim
WORKDIR /usr/src/myapp

COPY --from=builder /usr/src/myapp/src/spirit ./spirit

ENV TERM=xterm-256color

RUN useradd -m appuser \
 && chown -R appuser:appuser /usr/src/myapp
USER appuser

CMD ["./spirit"]
