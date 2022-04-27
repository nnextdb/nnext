## Installation

#### Nnext is supported on
<table>
  <tr>
    <td><img src="https://s3.us-east-2.amazonaws.com/assets.nnext.io/img/build.png" width="50" /></td>
    <td>Build from Source</td>
    <td>Build and install nnext from source using cmake & gcc/g++. Please follow the <a href="/COMPILATION.md">Compilation guide</a>.</td>
  </tr>
  <tr>
    <td><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/a/ab/Logo-ubuntu_cof-orange-hex.svg/570px-Logo-ubuntu_cof-orange-hex.svg.png?20130511162351" width="50" /></td>
    <td>Debian <br> Ubuntu</td>
    <td>Install NNext on Ubuntu using <span style="color: yellowgreen">debian</span> package manager. Please see 
the <a href="#Debian">Debian section below</a>.</td>
  </tr>
  <tr>
    <td><img src="https://upload.wikimedia.org/wikipedia/commons/a/ab/Apple-logo.png" width="50" /></td>
    <td>MacOS</td>
    <td>🚧 WIP 🚧<br>Install via <span style="color: yellowgreen">homebrew</span></td>
  </tr>
  <tr>
    <td><img src="https://www.docker.com/wp-content/uploads/2022/03/vertical-logo-monochromatic.png" width="50" /></td>
    <td>Docker</td>
    <td>🚧 WIP 🚧<br>Get the image <span style="color: yellowgreen">nnext:latest</span> image from docker hub</td>
  </tr>
  <tr>
    <td><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/39/Kubernetes_logo_without_workmark.svg/1234px-Kubernetes_logo_without_workmark.svg.png" width="50" /></td>
    <td>Kubernetes</td>
    <td>🚧 WIP 🚧<br>Create a NNext service on a kubernetes cluster</td>
  </tr>
  <tr>
    <td><img src="https://www.datocms-assets.com/2885/1620155116-brandhcterraformverticalcolor.svg" width="50" /></td>
    <td>Terraform + Kubernetes</td>
    <td>🚧 WIP 🚧<br>Create a NNext service via Terraform on a kubernetes cluster</td>
  </tr>
  <tr>
    <td><img src="https://www.datocms-assets.com/2885/1620155116-brandhcterraformverticalcolor.svg" width="50" /></td>
    <td>Terraform + NNext Cloud</td>
    <td>🚧 WIP 🚧<br>Provision a Cluster on NNext's cloud via terraform</td>
  </tr>
  <tr>
    <td><img src="https://www.pngall.com/wp-content/uploads/2/Windows-Logo-PNG-File-Download-Free.png" width="50" /></td>
    <td>Windows</td>
    <td>🚧 WIP 🚧<br>Not really supported, for purposes development only</td>
  </tr>
 </table>

## Debian
The Debian package for NNext v0.0.1 can be downloaded from the website and installed as follows:
```shell
NNEXT_PKG=nnext-0.0.1-amd64.deb
NNEXT_URL=https://trove.nnext.io/downloads
wget $NNEXT_URL/$NNEXT_PKG
wget $NNEXT_URL/$NNEXT_PKG.sha512
shasum -a 512 -c $NNEXT_PKG.sha512 
sudo dpkg -i $NNEXT_PKG
```

Run nnext
```shell
sudo nnext
```

You should see output like this
```shell
...
...
[2022-04-27 13:02:10.029] [info] 🏁 Started NNext at ▸ 127.0.0.1:6040
```