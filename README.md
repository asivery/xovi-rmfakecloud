# rmfakecloud XOVI Module

This is an xovi module for using a self hosted rM cloud with xochitl. It
functions by overriding the Qt functions that are used to connect to the
internet, and swapping them to instead point to the rmfakecloud instance,
should the old URL point to reMarkable's services.

# Setup

> [!CAUTION] Make sure to unpair from the cloud on your reMarkable before
> running these steps. Failing to do so will remove all your files when pairing
> to your self-hosted cloud.

**This requires [rm-xovi-extensions](https://github.com/asivery/rm-xovi-extensions) v18+.**

Download the latest release:

- [rM1/rM2](https://github.com/asivery/xovi-rmfakecloud/releases/latest/download/xovi-rmfakecloud-arm32.tar.gz)
- [rMPP/rMPPM](https://github.com/asivery/xovi-rmfakecloud/releases/latest/download/xovi-rmfakecloud-aarch64.tar.gz)

Copy it onto the device, into `/tmp/xovi-rmfakecloud.tar.gz`.

Extract the archive (on the tablet):

```bash
tar -xzvf /tmp/xovi-rmfakecloud.tar.gz -C /home/root
```

Set your domain and port:

```bash
cat << EOF > /home/root/xovi/exthome/rmfakecloud/config.conf
host=<your domain>
port=443
EOF
```
