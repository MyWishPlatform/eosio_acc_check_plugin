Clone repo:
```bash
eos/plugins]$ git clone https://github.com/MyWishPlatform/eosio_acc_check_plugin/
eos/plugins]$ mv eosio_acc_check_plugin acc_check_plugin
```

<br />

Modify eos/plugins/CMakeLists.txt:
```
...
add_subdirectory(acc_check_plugin)
...
```

<br />

Modify eos/programs/nodeos/CMakeLists.txt:
```
...
PRIVATE -Wl,${whole_archive_flag} acc_check_plugin  -Wl,${no_whole_archive_flag}
...
```

<br />

Compile:
```bash
eos/build]$ make
eos/build]$ sudo make install
```

<br />

Add to config.ini:
```
plugin = eosio::acc_check_plugin
```
