# rmfakecloud XOVI Module

This is an xovi module for using a self hosted rM cloud with xochitl. It functions by overriding the Qt functions that are used to connect to the internet, and swapping them to instead point to the rmfakecloud instance, should the old URL point to reMarkable's services.

## Setup

> [!CAUTION]
> Make sure to unpair from the cloud on your reMarkable before running these steps. Failing to do so will remove all your files when pairing to your self-hosted cloud.

- Run the following commands on the tablet via SSH (assuming CWD is /home/root):
```bash
mkdir -p xovi/roots/rmfakecloud/extensions.d
ln -rs xovi/exthome xovi/roots/rmfakecloud/exthome
mkdir xovi/exthome/rmfakecloud
cat << EOF > xovi/exthome/rmfakecloud/config.conf
host=<your domain>
port=443
EOF
```
- Copy the three .SO files into both `xovi/extensions.d` and `xovi/roots/rmfakecloud/extensions.d`
- Edit `xovi/start` and add the following code instead of `systemctl daemon-reload`:
```
mkdir -p /etc/systemd/system/rm-sync.service.d
mount -t tmpfs tmpfs /etc/systemd/system/rm-sync.service.d
cat << END > etc/systemd/system/rm-sync.service.d/xovi.conf
Environment="XOVI_ROOT=/home/root/xovi/roots/rmfakecloud"
Environment="LD_PRELOAD=/home/root/xovi/xovi.so"
Environment="QML_DISABLE_DISK_CACHE=1"
END
systemctl daemon-reload
systemctl restart rm-sync
```
- Edit `xovi/stock` - at the start of the file add `rm /etc/systemd/system/rm-sync.service.d/xovi.conf` at the start and `systemctl restart rm-sync` at the end
