# rmfakecloud XOVI Module

This is an xovi module for using a self hosted rM cloud with xochitl. It functions by overriding the Qt functions that are used to connect to the internet, and swapping them to instead point to the rmfakecloud instance, should the old URL point to reMarkable's services.

## Setup

> [!CAUTION]
> Make sure to unpair from the cloud on your reMarkable before running these steps. Failing to do so will remove all your files when pairing to your self-hosted cloud.

### Installation

1. Copy the extension files to your reMarkable device:
```bash
scp rmfakecloud_ns.so rmfakecloud_ts.so rmfakecloud_ws.so root@<remarkable-ip>:/home/root/.xovi/extensions.d/
```

2. Create the configuration directory:
```bash
ssh root@<remarkable-ip> "mkdir -p /home/root/.xovi/exthome/rmfakecloud"
```

3. Create the configuration file at `/home/root/.xovi/exthome/rmfakecloud/config.conf`:
```ini
[General]
host=your-server-hostname.com
port=3000
```   
Replace `your-server-hostname.com` with your rmfakecloud server's hostname or IP address, and adjust the port if needed.

4. (Optional) If using a custom CA certificate, place it at `/home/root/.xovi/exthome/rmfakecloud/ca.pem`

5. Restart xochitl or reboot your reMarkable device.
