FROM --platform=linux/arm64 alpine:latest
EXPOSE 443
COPY ./apiRunner \
    ./libapi.so \
    ./config.Production.json \
    ./config.Staging.json \
    ./
ENTRYPOINT ["apiRunner"]