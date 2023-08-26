{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    # Всякие бинарные программы, типа компиляторов
    nativeBuildInputs = with pkgs; [
      protobuf
      cmake
      pkg-config
    ];
    # Всякие библиотечные зависимости
    buildInputs = with pkgs; [
        openssl
        zlib
        jsoncpp
	    drogon
    ];
}
