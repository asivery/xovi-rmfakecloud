# rmfakecloud XOVI Module

This is an xovi module for using a self hosted rM cloud with xochitl. It functions by overriding the Qt `QNetworkAccessManager#createRequest` function, and changing the URL host to one of your own.

## Setup

> [!CAUTION]
> Make sure to unpair from the cloud on your reMarkable before running these steps. Failing to do so will remove all your files when pairing to your self-hosted cloud.

1. Download the latest release or build it yourself by running build.sh.
2. Put the `rmfakecloud.so` file in your `extensions.d` folder.
3. Download the `start` and `debug` scripts from the latest release, and put them in your xovi folder, to replace the existing scripts.
4. Modify both `start` and `debug` and replace **all** occurences (2 in `start`, and 1 in `debug`) of `rm.example.org` with your own domain. Do **not** include `https://`.
5. Run the `start` script. Try pairing with the cloud, and everything should work!
