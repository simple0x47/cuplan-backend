FROM --platform=linux/arm64 alpine:latest
EXPOSE 443
COPY ./apiRunner \
    ./config.Production.json \
    ./config.Staging.json \
    ./config.Development.json \
    ./
ENTRYPOINT ["apiRunner"]