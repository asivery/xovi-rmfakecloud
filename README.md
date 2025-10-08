# rmfakecloud XOVI Module

This is an xovi module for using a self hosted rM cloud with xochitl. It functions by overriding the Qt functions that are used to connect to the internet, and swapping them to instead point to the rmfakecloud instance, should the old URL point to reMarkable's services.

## Setup

> [!CAUTION]
> Make sure to unpair from the cloud on your reMarkable before running these steps. Failing to do so will remove all your files when pairing to your self-hosted cloud.

### TODO!
