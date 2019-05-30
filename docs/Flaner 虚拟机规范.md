# Flaner 虚拟机规范

---

## Flaner 模块文件

### 文件扩展名

由 Flaner 源文件编译得到的二进制模块，其文件扩展名为 `flm`（FLaner Module）。

来自外部语言提供的 Flaner 扩展模块，其文件扩展名为 `flx` （FLaner eXtention）。



### 魔数和版本号

Flaner Module 文件的第 1 - 6 个字节是魔数（Magic Number）。它是一个 Flaner Module 文件的二进制标识。

其值固定为：`0x46 0x4c 0x4e 0x4d 0x4f 0x44`，即“FLNMOD”。如果一个 Flaner Module 文件的魔数不是 `0x46 0x4c 0x4e 0x4d 0x4f 0x44`，那么虚拟机将拒绝运行这个模块。

Flaner Module 文件的第 7 - 8 个字节代表了编译器的次版本号（Minor Version）。

Flaner Module 文件的第 9 - 10 个字节代表了编译器的主版本号（Major Version）。

高版本的 Flaner Virtual Machine 可以向下兼容低版本的 Flaner Module 文件，但是更高版本的则会拒绝运行。



### 常量池

Flaner Module 文件的第 11 - 12 个字节用于表示常量池所包含的常量的个数，紧随其后的就是常量池本身。









## Flaner 字节码



