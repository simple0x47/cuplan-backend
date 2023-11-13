FROM alpine:latest
EXPOSE 443
COPY ./apiRunner \
    ./libapi.so \
    ./config.Development.json \
    ./config.Production.json \
    ./
ENTRYPOINT ["./apiRunner"]