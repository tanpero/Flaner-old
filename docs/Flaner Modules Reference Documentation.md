# Flaner Modules Reference Documentation

---

## core

### object

### string

### list

### set

### map

### number

### bigint

### symbol

### function

### regexp

### date

### buffer







## network

### http

### http2

### https

### dgram

### net

### dns

### url



### querystring







## concurrency

### thread

### threadPool







## data

### xml

### json

### yaml

### toml

### hocon

### prop

### csv







## runtime

### os

`os`模块提供了许多与操作系统相关的实用方法。它可以使用以下方式访问：

```js
import runtime.os
```

#### os.EOL

- `returns` <String>

定义特定于操作系统的行尾标记的字符串常量：

- `\n` 在POSIX上
- `\r\n` 在Windows上

#### os.arch() 

- `returns` <String>

该 `os.arch()` 方法返回一个字符串，用于标识运行当前 Flaner 模块的机器 CPU 体系结构。

可能的值是：`'arm'`，`'arm64'`，`'ia32'`，`'mips'`， `'mipsel'`，`'ppc'`，`'ppc64'`，`'s390'`，`'s390x'`，`'x32'`，和`'x64'`。

#### os.constants

- `returns` <Object>

返回包含常用操作系统特定常量的对象，用于错误代码，过程信号等。当前定义的特定常量在[OS常量中描述。

#### os.cpus() 

- `returns` <String>

`os.cpus()` 方法返回一个对象数组，其中包含有关每个逻辑CPU核心的信息。

每个对象包含的属性包括：

- `model` <字符串>
- `speed` （以MHz为单位）
- `times` <对象>
  - `user`  CPU在用户模式下花费的毫秒数。
  - `nice`  CPU在nice模式下花费的毫秒数。
  - `sys`  CPU在sys模式下花费的毫秒数。
  - `idle`  CPU在空闲模式下花费的毫秒数。
  - `irq`  CPU在irq模式下花费的毫秒数。

```js
[
  {
    model: 'Intel(R) Core(TM) i7 CPU         860  @ 2.80GHz',
    speed: 2926,
    times: {
      user: 252020,
      nice: 0,
      sys: 30340,
      idle: 1070356870,
      irq: 0
    }
  },
  {
    model: 'Intel(R) Core(TM) i7 CPU         860  @ 2.80GHz',
    speed: 2926,
    times: {
      user: 306960,
      nice: 0,
      sys: 26980,
      idle: 1071569080,
      irq: 0
    }
  },
  {
    model: 'Intel(R) Core(TM) i7 CPU         860  @ 2.80GHz',
    speed: 2926,
    times: {
      user: 248450,
      nice: 0,
      sys: 21750,
      idle: 1070919370,
      irq: 0
    }
  },
  {
    model: 'Intel(R) Core(TM) i7 CPU         860  @ 2.80GHz',
    speed: 2926,
    times: {
      user: 256880,
      nice: 0,
      sys: 19430,
      idle: 1070905480,
      irq: 20
    }
  },
  {
    model: 'Intel(R) Core(TM) i7 CPU         860  @ 2.80GHz',
    speed: 2926,
    times: {
      user: 511580,
      nice: 20,
      sys: 40900,
      idle: 1070842510,
      irq: 0
    }
  },
  {
    model: 'Intel(R) Core(TM) i7 CPU         860  @ 2.80GHz',
    speed: 2926,
    times: {
      user: 291660,
      nice: 0,
      sys: 34360,
      idle: 1070888000,
      irq: 10
    }
  },
  {
    model: 'Intel(R) Core(TM) i7 CPU         860  @ 2.80GHz',
    speed: 2926,
    times: {
      user: 308260,
      nice: 0,
      sys: 55410,
      idle: 1071129970,
      irq: 880
    }
  },
  {
    model: 'Intel(R) Core(TM) i7 CPU         860  @ 2.80GHz',
    speed: 2926,
    times: {
      user: 266450,
      nice: 1480,
      sys: 34920,
      idle: 1072572010,
      irq: 30
    }
  }
]
```

由于 `nice` 值是特定于 UNIX 的，因此在 Windows上 `nice` 的值始终为 0。

#### os.endianness() 

- `returns` <String>

`os.endianness()` 方法返回一个字符串，用于标识运行当前 Flaner 模块的机器 CPU 的字节顺序。

可能的值是：

- `'BE'` （大端字节序）
- `'LE'` （小端字节序）

#### os.freemem() 

- `returns` <String>

该 `os.freemem()` 方法以整数形式返回可用系统内存量（以字节为单位）。

#### os.getPriority([pid])

添加于：v10.10.0

- `pid` 检索调度优先级的进程ID。 **默认为** `0`。
- `returns` <String>

`os.getPriority()` 方法返回由指定的进程的调度优先级`pid`。如果`pid`未提供，或者是`0`，则返回当前进程的优先级。

#### os.homedir() 

- `returns` <String>

`os.homedir()` 方法以字符串形式返回当前用户的主目录。

#### os.hostname() 

- `returns` <String>

`os.hostname()` 方法以字符串形式返回操作系统的主机名。

#### os.loadavg() 

- `returns` <String>

`os.loadavg()` 方法返回一个包含1分钟，5分钟和15分钟负载平均值的数组。

负载平均值是系统活动的度量，由操作系统计算并表示为小数。理想情况下，平均负载应小于系统中逻辑 CPU 的数量。

负载平均值是特定于 UNIX 的概念，在 Windows 平台上没有真正的等价物。在 Windows 上，返回值始终为`[0, 0, 0]`。

#### os.networkInterfaces() 

- `returns` <String>

`os.networkInterfaces()` 方法返回一个对象，该对象仅包含已分配网络地址的网络接口。

返回对象上的每个键都标识一个网络接口。关联值是一个对象数组，每个对象描述一个分配的网络地址。

分配的网络地址对象上可用的属性包括：

- `address` 分配的IPv4或IPv6地址
- `netmask`  IPv4或IPv6网络掩码
- `family` <字符串>要么`IPv4`或`IPv6`
- `mac` 网络接口的MAC地址
- `internal` `true`如果网络接口是无法远程访问的环回或类似接口，则为[ ; 除此以外`false`
- `scopeid` <数字>的数字IPv6范围ID（当仅指定`family` 是`IPv6`）
- `cidr` 分配的IPv4或IPv6地址，其路由前缀为CIDR表示法。如果`netmask`无效，则将此属性设置为`null`。

```js
{
  lo: [
    {
      address: '127.0.0.1',
      netmask: '255.0.0.0',
      family: 'IPv4',
      mac: '00:00:00:00:00:00',
      internal: true,
      cidr: '127.0.0.1/8'
    },
    {
      address: '::1',
      netmask: 'ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff',
      family: 'IPv6',
      mac: '00:00:00:00:00:00',
      scopeid: 0,
      internal: true,
      cidr: '::1/128'
    }
  ],
  eth0: [
    {
      address: '192.168.1.108',
      netmask: '255.255.255.0',
      family: 'IPv4',
      mac: '01:02:03:0a:0b:0c',
      internal: false,
      cidr: '192.168.1.108/24'
    },
    {
      address: 'fe80::a00:27ff:fe4e:66a1',
      netmask: 'ffff:ffff:ffff:ffff::',
      family: 'IPv6',
      mac: '01:02:03:0a:0b:0c',
      scopeid: 1,
      internal: false,
      cidr: 'fe80::a00:27ff:fe4e:66a1/64'
    }
  ]
}
```

#### os.platform() 

- `returns` <String>

`os.platform()` 方法返回一个标识运行运行时操作系统平台的字符串。

目前可能的值是：

- `'aix'`
- `'darwin'`
- `'freebsd'`
- `'linux'`
- `'openbsd'`
- `'sunos'`
- `'win32'`

相当于 `process.platform`。

`'android'`如果Node.js是在Android操作系统上构建的，则也可以返回该值。但是，Node.js中的Android支持目前被认为 [是实验性的。

#### os.release() 

- `returns` <String>

`os.release()` 方法返回标识操作系统版本的字符串。

在POSIX系统上，操作系统版本由调用确定  `uname(3)`。在Windows上，`GetVersionExW()`使用。有关更多信息，请参阅<https://en.wikipedia.org/wiki/Uname#Examples>。

#### os.setPriority（[pid，] priority）

添加于：v10.10.0

- `pid` 为其设置调度优先级的进程ID。 **默认** `0`。
- `priority` 分配给进程的调度优先级。

`os.setPriority()` 方法尝试为指定的进程设置调度优先级`pid`。如果`pid`未提供，或者是`0`，则使用当前进程的优先级。

的`priority`输入必须之间的整数`-20`（高优先级）和`19` （低优先级）。由于Unix优先级和Windows优先级之间的差异，`priority`映射到六个优先级常量之一 `os.constants.priority`。检索进程优先级时，此范围映射可能导致Windows上的返回值略有不同。为避免混淆，建议将其设置`priority`为优先级常量之一。

在Windows上设置优先级`PRIORITY_HIGHEST`需要提升用户，否则设置优先级将以静默方式减少到`PRIORITY_HIGH`。

#### os.tmpdir() 

历史

- `returns` <String>

`os.tmpdir()` 方法返回一个字符串，指定操作系统临时文件的默认目录。

#### os.totalmem() 

- `returns` <String>

`os.totalmem()` 方法以整数形式返回系统内存总量（以字节为单位）。

#### os.type() 

- `returns` <String>

`os.type()` 方法返回一个字符串，标识返回的操作系统名称 `uname(3)`。例如，`'Linux'`在Linux，`'Darwin'`macOS和`'Windows_NT'`Windows上。

有关运行输出的其他信息，请参阅<https://en.wikipedia.org/wiki/Uname#Examples> `uname(3)` 在各种操作系统上。

#### os.uptime() 

- `returns` <String>

`os.uptime()` 方法以秒为单位返回系统正常运行时间。

#### os.userInfo（[options]）

- `options` <对象>
  - `encoding` 用于解释结果字符串的字符编码。如果`encoding`设置为`'buffer'`，则`username`，`shell`和`homedir` 值将是`Buffer`实例。**默认值：** `'utf8'`。
- `returns` <String>

`os.userInfo()` 方法返回有关当前有效用户的信息 - 在POSIX平台上，这通常是密码文件的子集。返回的对象包括`username`，`uid`，`gid`，`shell`，和`homedir`。在Windows上，`uid`和`gid`字段是`-1`，并且`shell`是`null`。

 `homedir` 返回的值`os.userInfo()`由操作系统提供。这与`os.homedir()`在回退到操作系统响应之前查询主目录的多个环境变量的结果不同。

#### 操作系统常量

以下常量导出`os.constants`。

并非所有常量都可用于每个操作系统。

##### 信号常数

以下信号常量通过 `os.constants.signals` 导出：

| 不变                | 描述                                                         |
| ------------------- | ------------------------------------------------------------ |
| `SIGHUP`            | 发送以指示何时关闭控制终端或父进程退出。                     |
| `SIGINT`            | 发送以指示用户何时希望中断进程（`(Ctrl+C)`）。               |
| `SIGQUIT`           | 发送以指示用户何时希望终止进程并执行核心转储。               |
| `SIGILL`            | 发送到进程以通知它已尝试执行非法，格式错误，未知或特权指令。 |
| `SIGTRAP`           | 发生异常时发送到进程。                                       |
| `SIGABRT`           | 发送到进程请求它中止。                                       |
| `SIGIOT`            | 同义词 `SIGABRT`                                             |
| `SIGBUS`            | 发送到进程以通知它已导致总线错误。                           |
| `SIGFPE`            | 发送到进程以通知它已执行非法算术运算。                       |
| `SIGKILL`           | 发送到进程以立即终止它。                                     |
| `SIGUSR1` `SIGUSR2` | 发送到流程以识别用户定义的条件。                             |
| `SIGSEGV`           | 发送到进程以通知分段错误。                                   |
| `SIGPIPE`           | 尝试写入断开连接的管道时发送到进程。                         |
| `SIGALRM`           | 系统计时器过去后发送到进程。                                 |
| `SIGTERM`           | 发送到请求终止的进程。                                       |
| `SIGCHLD`           | 子进程终止时发送到进程。                                     |
| `SIGSTKFLT`         | 发送到进程以指示协处理器上的堆栈故障。                       |
| `SIGCONT`           | 发送以指示操作系统继续暂停的过程。                           |
| `SIGSTOP`           | 发送以指示操作系统暂停进程。                                 |
| `SIGTSTP`           | 发送到进程请求它停止。                                       |
| `SIGBREAK`          | 发送以指示用户何时希望中断进程。                             |
| `SIGTTIN`           | 当它在后台从TTY读取时发送到进程。                            |
| `SIGTTOU`           | 在后台写入TTY时发送到进程。                                  |
| `SIGURG`            | 当套接字有紧急数据要读取时发送到进程。                       |
| `SIGXCPU`           | 当它超出CPU使用限制时发送到进程。                            |
| `SIGXFSZ`           | 发送到大于允许的最大文件的进程时发送到进程。                 |
| `SIGVTALRM`         | 虚拟计时器结束后发送到进程。                                 |
| `SIGPROF`           | 系统计时器结束后发送到进程。                                 |
| `SIGWINCH`          | 当控制终端改变其大小时发送到进程。                           |
| `SIGIO`             | 当I / O可用时发送到进程。                                    |
| `SIGPOLL`           | 同义词 `SIGIO`                                               |
| `SIGLOST`           | 文件锁丢失时发送到进程。                                     |
| `SIGPWR`            | 发送到进程以通知电源故障。                                   |
| `SIGINFO`           | 同义词 `SIGPWR`                                              |
| `SIGSYS`            | 发送到进程以通知错误的参数。                                 |
| `SIGUNUSED`         | 同义词 `SIGSYS`                                              |

##### 错误常量

以下错误常量通过 `os.constants.errno` 导出：

###### POSIX 错误常量

| 不变              | 描述                                                         |
| ----------------- | ------------------------------------------------------------ |
| `E2BIG`           | 表示参数列表长于预期。                                       |
| `EACCES`          | 表示该操作没有足够的权限。                                   |
| `EADDRINUSE`      | 表示网络地址已在使用中。                                     |
| `EADDRNOTAVAIL`   | 表示网络地址当前不可用。                                     |
| `EAFNOSUPPORT`    | 表示不支持网络地址系列。                                     |
| `EAGAIN`          | 表示当前没有可用数据，稍后再次尝试操作。                     |
| `EALREADY`        | 表示套接字已有正在进行的挂起连接。                           |
| `EBADF`           | 表示文件描述符无效。                                         |
| `EBADMSG`         | 表示无效的数据消息。                                         |
| `EBUSY`           | 表示设备或资源正忙。                                         |
| `ECANCELED`       | 表示操作已取消。                                             |
| `ECHILD`          | 表示没有子进程。                                             |
| `ECONNABORTED`    | 表示网络连接已中止。                                         |
| `ECONNREFUSED`    | 表示网络连接已被拒绝。                                       |
| `ECONNRESET`      | 表示网络连接已重置。                                         |
| `EDEADLK`         | 表示已避免资源死锁。                                         |
| `EDESTADDRREQ`    | 表示需要目标地址。                                           |
| `EDOM`            | 表示参数超出了函数的域。                                     |
| `EDQUOT`          | 表示已超出磁盘配额。                                         |
| `EEXIST`          | 表示该文件已存在。                                           |
| `EFAULT`          | 表示无效的指针地址。                                         |
| `EFBIG`           | 表示文件太大。                                               |
| `EHOSTUNREACH`    | 表示主机无法访问。                                           |
| `EIDRM`           | 表示已删除标识符。                                           |
| `EILSEQ`          | 表示非法字节序列。                                           |
| `EINPROGRESS`     | 表示操作已在进行中。                                         |
| `EINTR`           | 表示函数调用已中断。                                         |
| `EINVAL`          | 表示提供了无效参数。                                         |
| `EIO`             | 表示未指定的I / O错误。                                      |
| `EISCONN`         | 表示套接字已连接。                                           |
| `EISDIR`          | 表示路径是目录。                                             |
| `ELOOP`           | 表示路径中的符号链接级别太多。                               |
| `EMFILE`          | 表示打开的文件太多。                                         |
| `EMLINK`          | 表示文件的硬链接太多。                                       |
| `EMSGSIZE`        | 表示提供的消息太长。                                         |
| `EMULTIHOP`       | 表示尝试了多跳。                                             |
| `ENAMETOOLONG`    | 表示文件名太长。                                             |
| `ENETDOWN`        | 表示网络已关闭。                                             |
| `ENETRESET`       | 表示连接已被网络中止。                                       |
| `ENETUNREACH`     | 表示网络无法访问。                                           |
| `ENFILE`          | 表示系统中打开的文件太多。                                   |
| `ENOBUFS`         | 表示没有可用的缓冲区空间。                                   |
| `ENODATA`         | 表示流头部读取队列中没有可用消息。                           |
| `ENODEV`          | 表示没有此类设备。                                           |
| `ENOENT`          | 表示没有此类文件或目录。                                     |
| `ENOEXEC`         | 表示exec格式错误。                                           |
| `ENOLCK`          | 表示没有可用的锁。                                           |
| `ENOLINK`         | 链接已被切断的迹象。                                         |
| `ENOMEM`          | 表示没有足够的空间。                                         |
| `ENOMSG`          | 表示没有所需类型的消息。                                     |
| `ENOPROTOOPT`     | 表示给定协议不可用。                                         |
| `ENOSPC`          | 表示设备上没有可用空间。                                     |
| `ENOSR`           | 表示没有可用的流资源。                                       |
| `ENOSTR`          | 表示给定资源不是流。                                         |
| `ENOSYS`          | 表示尚未实现某个功能。                                       |
| `ENOTCONN`        | 表示套接字未连接。                                           |
| `ENOTDIR`         | 表示该路径不是目录。                                         |
| `ENOTEMPTY`       | 表示该目录不为空。                                           |
| `ENOTSOCK`        | 表示给定项目不是套接字。                                     |
| `ENOTSUP`         | 表示不支持给定的操作。                                       |
| `ENOTTY`          | 表示不适当的I / O控制操作。                                  |
| `ENXIO`           | 表示没有此类设备或地址。                                     |
| `EOPNOTSUPP`      | 表示套接字不支持该操作。请注意，虽然`ENOTSUP`和`EOPNOTSUPP`在Linux上相同的值，根据POSIX.1这些错误值应该是不同的。） |
| `EOVERFLOW`       | 表示某个值太大而无法存储在给定的数据类型中。                 |
| `EPERM`           | 表示不允许该操作。                                           |
| `EPIPE`           | 表示管道损坏。                                               |
| `EPROTO`          | 表示协议错误。                                               |
| `EPROTONOSUPPORT` | 表示不支持协议。                                             |
| `EPROTOTYPE`      | 表示套接字的协议类型错误。                                   |
| `ERANGE`          | 表示结果太大。                                               |
| `EROFS`           | 表示文件系统是只读的。                                       |
| `ESPIPE`          | 表示无效的搜索操作。                                         |
| `ESRCH`           | 表示没有这样的过程。                                         |
| `ESTALE`          | 表示文件句柄是陈旧的。                                       |
| `ETIME`           | 表示过期的计时器。                                           |
| `ETIMEDOUT`       | 表示连接超时。                                               |
| `ETXTBSY`         | 表示文本文件正忙。                                           |
| `EWOULDBLOCK`     | 表示操作将阻止。                                             |
| `EXDEV`           | 表示链接不正确。                                             |

###### Windows 错误常量

以下错误代码特定于Windows操作系统：

| 不变                     | 描述                            |
| ------------------------ | ------------------------------- |
| `WSAEINTR`               | 表示中断的函数调用。            |
| `WSAEBADF`               | 表示文件句柄无效。              |
| `WSAEACCES`              | 表示没有足够的权限来完成操作。  |
| `WSAEFAULT`              | 表示无效的指针地址。            |
| `WSAEINVAL`              | 表示传递了无效参数。            |
| `WSAEMFILE`              | 表示打开的文件太多。            |
| `WSAEWOULDBLOCK`         | 表示资源暂时不可用。            |
| `WSAEINPROGRESS`         | 表示当前正在进行操作。          |
| `WSAEALREADY`            | 表示操作已在进行中。            |
| `WSAENOTSOCK`            | 表示资源不是套接字。            |
| `WSAEDESTADDRREQ`        | 表示需要目标地址。              |
| `WSAEMSGSIZE`            | 表示邮件大小太长。              |
| `WSAEPROTOTYPE`          | 表示套接字的协议类型错误。      |
| `WSAENOPROTOOPT`         | 表示协议选项不正确。            |
| `WSAEPROTONOSUPPORT`     | 表示不支持该协议。              |
| `WSAESOCKTNOSUPPORT`     | 表示不支持套接字类型。          |
| `WSAEOPNOTSUPP`          | 表示不支持该操作。              |
| `WSAEPFNOSUPPORT`        | 表示不支持协议族。              |
| `WSAEAFNOSUPPORT`        | 表示不支持地址系列。            |
| `WSAEADDRINUSE`          | 表示网络地址已在使用中。        |
| `WSAEADDRNOTAVAIL`       | 表示网络地址不可用。            |
| `WSAENETDOWN`            | 表示网络已关闭。                |
| `WSAENETUNREACH`         | 表示网络无法访问。              |
| `WSAENETRESET`           | 表示网络连接已重置。            |
| `WSAECONNABORTED`        | 表示连接已中止。                |
| `WSAECONNRESET`          | 表示对等体已重置连接。          |
| `WSAENOBUFS`             | 表示没有可用的缓冲区空间。      |
| `WSAEISCONN`             | 表示套接字已连接。              |
| `WSAENOTCONN`            | 表示套接字未连接。              |
| `WSAESHUTDOWN`           | 表示套接字关闭后无法发送数据。  |
| `WSAETOOMANYREFS`        | 表示引用太多。                  |
| `WSAETIMEDOUT`           | 表示连接已超时。                |
| `WSAECONNREFUSED`        | 表示连接已被拒绝。              |
| `WSAELOOP`               | 表示无法翻译名称。              |
| `WSAENAMETOOLONG`        | 表示名称太长。                  |
| `WSAEHOSTDOWN`           | 表示网络主机已关闭。            |
| `WSAEHOSTUNREACH`        | 表示没有到网络主机的路由。      |
| `WSAENOTEMPTY`           | 表示该目录不为空。              |
| `WSAEPROCLIM`            | 表示进程太多。                  |
| `WSAEUSERS`              | 表示已超出用户配额。            |
| `WSAEDQUOT`              | 表示已超出磁盘配额。            |
| `WSAESTALE`              | 表示陈旧的文件句柄引用。        |
| `WSAEREMOTE`             | 表示该项目是远程的。            |
| `WSASYSNOTREADY`         | 表示网络子系统尚未就绪。        |
| `WSAVERNOTSUPPORTED`     | 表示`winsock.dll`版本超出范围。 |
| `WSANOTINITIALISED`      | 表示尚未执行成功的WSAStartup。  |
| `WSAEDISCON`             | 表示正在进行正常关闭。          |
| `WSAENOMORE`             | 表示没有更多结果。              |
| `WSAECANCELLED`          | 表示已取消操作。                |
| `WSAEINVALIDPROCTABLE`   | 表示过程调用表无效。            |
| `WSAEINVALIDPROVIDER`    | 表示无效的服务提供商。          |
| `WSAEPROVIDERFAILEDINIT` | 表示服务提供程序未能初始化。    |
| `WSASYSCALLFAILURE`      | 表示系统调用失败。              |
| `WSASERVICE_NOT_FOUND`   | 表示未找到服务。                |
| `WSATYPE_NOT_FOUND`      | 表示未找到类类型。              |
| `WSA_E_NO_MORE`          | 表示没有更多结果。              |
| `WSA_E_CANCELLED`        | 表示呼叫已取消。                |
| `WSAEREFUSED`            | 表示数据库查询被拒绝。          |

##### dlopen 常数

如果在操作系统上可用，则导出以下常量 `os.constants.dlopen`。有关 `dlopen(3)`详细信息，请参阅

| 不变            | 描述                                                       |
| --------------- | ---------------------------------------------------------- |
| `RTLD_LAZY`     | 执行延迟绑定。Node.js默认设置此标志。                      |
| `RTLD_NOW`      | 在dlopen（3）返回之前解析库中的所有未定义符号。            |
| `RTLD_GLOBAL`   | 库定义的符号将可用于后续加载的库的符号解析。               |
| `RTLD_LOCAL`    | 相反的`RTLD_GLOBAL`。如果未指定任何标志，则这是默认行为。  |
| `RTLD_DEEPBIND` | 使一个独立的库使用自己的符号，而不是先前加载的库中的符号。 |

##### 优先级常数

添加于：v10.10.0

以下进程调度常量通过以下方式导出 `os.constants.priority`：

| 不变                    | 描述                                                         |
| ----------------------- | ------------------------------------------------------------ |
| `PRIORITY_LOW`          | 最低进程调度优先级。这对应 `IDLE_PRIORITY_CLASS`于Windows，并且`19`在所有其他平台上都很有价值 。 |
| `PRIORITY_BELOW_NORMAL` | 流程调度优先级高于`PRIORITY_LOW`和低于`PRIORITY_NORMAL`。这对应 `BELOW_NORMAL_PRIORITY_CLASS`于Windows，并且`10`在所有其他平台上都很有价值 。 |
| `PRIORITY_NORMAL`       | 默认进程调度优先级。这对应 `NORMAL_PRIORITY_CLASS`于Windows，并且`0`在所有其他平台上都很有价值 。 |
| `PRIORITY_ABOVE_NORMAL` | 流程调度优先级高于`PRIORITY_NORMAL`和低于`PRIORITY_HIGH`。这对应 `ABOVE_NORMAL_PRIORITY_CLASS`于Windows，并且`-7`在所有其他平台上都很有价值 。 |
| `PRIORITY_HIGH`         | 流程调度优先级高于`PRIORITY_ABOVE_NORMAL` 和低于`PRIORITY_HIGHEST`。这对应 `HIGH_PRIORITY_CLASS`于Windows，并且`-14`在所有其他平台上都很有价值 。 |
| `PRIORITY_HIGHEST`      | 最高进程调度优先级。这对应 `REALTIME_PRIORITY_CLASS`于Windows，并且`-20`在所有其他平台上都很有价值 。 |



### path

### filesystem









