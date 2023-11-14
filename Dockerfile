FROM ubuntu:22.04
EXPOSE 443
COPY ./apiRunner \
    ./config.Production.json \
    ./config.Staging.json \
    ./config.Development.json \
    .
ENTRYPOINT ["./apiRunner"]