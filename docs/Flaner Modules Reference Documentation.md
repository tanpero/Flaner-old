# Flaner Modules Reference Documentation

---

## core

### object

### string

### list

### set

### map

### numeric

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



---

### querystring

`querystring` 模块提供用于解析和格式化URL查询字符串的实用程序。它可以使用以下方式访问：

```
import network.querystring
```

#### querystring.decode()

`querystring.decode()`函数是 `querystring.parse()` 的别名。

#### querystring.encode()

`querystring.encode()`函数是 `querystring.stringify()`的别名。

#### querystring.escape(str)

- `str` <String>

该`querystring.escape()`方法`str`以针对URL查询字符串的特定要求进行了优化的方式对给定执行URL百分比编码 。

该`querystring.escape()`方法由`querystring.stringify()`并且通常不期望直接使用。它的导出主要是为了允许应用程序代码在必要时通过分配`querystring.escape`替代函数来提供替换的百分比编码实现。

#### querystring.parse（str [，sep [，eq [，options]]])

- `str` 要解析的URL查询字符串
- `sep` 用于在查询字符串中分隔键和值对的子字符串。**默认值：** `'&'`。
- `eq` 用于分隔查询字符串中的键和值的子字符串。**默认值：** `'='`。
- `options` <Object>
  - `decodeURIComponent`<Function> 解码查询字符串中的百分比编码字符时使用的函数。**默认值：** `querystring.unescape()`。
  - `maxKeys` <Number> 指定要解析的最大键数。指定`0`删除键计数限制。**默认值：** `1000`。

该`querystring.parse()`方法将URL查询字符串（`str`）解析为键和值对的集合。

例如，查询字符串`'foo=bar&abc=xyz&abc=123'`被解析为：

```
{
  foo: 'bar',
  abc: ['xyz', '123']
}
```

该`querystring.parse()`方法返回的对象*不是* 原型继承自JavaScript `Object`。这意味着，典型的 `Object`方法，例如`obj.toString()`，`obj.hasOwnProperty()`和其他没有定义，*将无法正常工作*。

默认情况下，将假定查询字符串中的百分比编码字符使用UTF-8编码。如果使用替代字符编码，则`decodeURIComponent` 需要指定备用选项：

```
// Assuming gbkDecodeURIComponent function already exists...

querystring.parse('w=%D6%D0%CE%C4&foo=bar', null, null,
                  { decodeURIComponent: gbkDecodeURIComponent });
```

#### querystring.stringify（obj [，sep [，eq [，options]]]）

- `obj` 要序列化为URL查询字符串的对象

- `sep` 用于在查询字符串中分隔键和值对的子字符串。**默认值：** `'&'`。

- `eq` 用于分隔查询字符串中的键和值的子字符串。**默认值：** `'='`。

- `options`

  - `encodeURIComponent`  <Function>

    在查询字符串中将URL不安全字符转换为百分比编码时使用的函数。**默认值：** `querystring.escape()`。

该`querystring.stringify()`方法`obj`通过迭代对象的“自己的属性” 从给定的URL生成URL查询字符串。

它序列化传入的以下类型的值`obj`：<String> | <Number> | <Boolean> | <List<String>> | <List<Number>> | <List<Boolean>>

任何其他输入值都将被强制转换为空字符串。

```
querystring.stringify({ foo: 'bar', baz: ['qux', 'quux'], corge: '' });
// returns 'foo=bar&baz=qux&baz=quux&corge='

querystring.stringify({ foo: 'bar', baz: 'qux' }, ';', ':');
// returns 'foo:bar;baz:qux'
```

默认情况下，查询字符串中需要百分比编码的字符将编码为UTF-8。如果需要替代编码，则`encodeURIComponent`需要指定备用 选项：

```
// Assuming gbkEncodeURIComponent function already exists,

querystring.stringify({ w: '中文', foo: 'bar' }, null, null,
                      { encodeURIComponent: gbkEncodeURIComponent });
```

#### querystring.unescape(str)

- `str`  <String>

该`querystring.unescape()`方法对给定的URL百分比编码字符进行解码`str`。

该`querystring.unescape()`方法由`querystring.parse()`并且通常不期望直接使用。它的导出主要是为了允许应用程序代码在必要时通过分配`querystring.unescape`替代函数来提供替换解码实现。







## concurrency

### thread

### threadPool

### cluster







## data

### xml

### on

### yaml

### toml

### hocon

### prop

### csv







## runtime

---

### os

`os`模块提供了许多与操作系统相关的实用方法。它可以使用以下方式访问：

```
import runtime.os
```

#### os.EOL

- `returns` <String>

定义特定于操作系统的行尾标记的字符串常量：

- POSIX 平台：`\n` 
- Window 平台：`\r\n`

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

- `model` <String>
- `speed` （以MHz为单位）
- `times` <Object>
  - `user`  CPU在用户模式下花费的毫秒数。
  - `nice`  CPU在nice模式下花费的毫秒数。
  - `sys`  CPU在sys模式下花费的毫秒数。
  - `idle`  CPU在空闲模式下花费的毫秒数。
  - `irq`  CPU在irq模式下花费的毫秒数。

```
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

由于 `nice` 值是特定于 UNIX 的，因此在  Windows 上 `nice` 的值始终为 0。

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

负载平均值是特定于 UNIX 的概念，在  Windows   平台上没有真正的等价物。在  Windows  上，返回值始终为`[0, 0, 0]`。

#### os.networkInterfaces() 

- `returns` <String>

`os.networkInterfaces()` 方法返回一个对象，该对象仅包含已分配网络地址的网络接口。

返回对象上的每个键都标识一个网络接口。关联值是一个对象数组，每个对象描述一个分配的网络地址。

分配的网络地址对象上可用的属性包括：

- `address` 分配的IPv4或IPv6地址
- `netmask`  IPv4或IPv6网络掩码
- `family` <String>要么`IPv4`或`IPv6`
- `mac` 网络接口的MAC地址
- `internal` `true`如果网络接口是无法远程访问的环回或类似接口，则为[ ; 除此以外`false`
- `scopeid` <数字>的数字IPv6范围ID（当仅指定`family` 是`IPv6`）
- `cidr` 分配的IPv4或IPv6地址，其路由前缀为CIDR表示法。如果`netmask`无效，则将此属性设置为`null`。

```
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

`os.platform()` 方法返回一个标识运行运行时操作系统 平台的字符串。

目前可能的值是：

- `'aix'`
- `'darwin'`
- `'freebsd'`
- `'linux'`
- `'openbsd'`
- `'sunos'`
- `'win32'`

如果 Flaner 是在 Android 上构建的，那么可以返回 `"android"`。

#### os.release() 

- `returns` <String>

`os.release()` 方法返回标识操作系统版本的字符串。

在 POSIX 系统上，操作系统版本由调用确定  `uname(3)`。在 Windows 上，`GetVersionExW()`使用。有关更多信息，请参阅<https://en.wikipedia.org/wiki/Uname#Examples>。

#### os.setPriority（[pid，] priority）

添加于：v10.10.0

- `pid` 为其设置调度优先级的进程ID。 **默认** `0`。
- `priority` 分配给进程的调度优先级。

`os.setPriority()` 方法尝试为指定的进程设置调度优先级`pid`。如果`pid`未提供，或者是`0`，则使用当前进程的优先级。

的`priority`输入必须之间的整数`-20`（高优先级）和`19` （低优先级）。由于Unix优先级和 Windows 优先级之间的差异，`priority`映射到六个优先级常量之一 `os.constants.priority`。检索进程优先级时，此范围映射可能导致 Windows 上的返回值略有不同。为避免混淆，建议将其设置`priority`为优先级常量之一。

在 Windows 上设置优先级`PRIORITY_HIGHEST`需要提升用户，否则设置优先级将以静默方式减少到`PRIORITY_HIGH`。

#### os.tmpdir() 

- `returns` <String>

`os.tmpdir()` 方法返回一个字符串，指定操作系统临时文件的默认目录。

#### os.totalmem() 

- `returns` <String>

`os.totalmem()` 方法以整数形式返回系统内存总量（以字节为单位）。

#### os.type() 

- `returns` <String>

`os.type()` 方法返回一个字符串，标识返回的操作系统名称 `uname(3)`。例如，`'Linux'`在Linux，`'Darwin'`macOS和`' Windows _NT'` Windows 上。

有关运行输出的其他信息，请参阅<https://en.wikipedia.org/wiki/Uname#Examples> `uname(3)` 在各种操作系统上。

#### os.uptime() 

- `returns` <String>

`os.uptime()` 方法以秒为单位返回系统正常运行时间。

#### os.userInfo（[options]）

- `options` <Object>
  - `encoding` 用于解释结果字符串的字符编码。如果`encoding`设置为`'buffer'`，则`username`，`shell`和`homedir` 值将是`Buffer`实例。**默认值：** `'utf8'`。
- `returns` <String>

`os.userInfo()` 方法返回有关当前有效用户的信息 - 在 POSIX  平台上，这通常是密码文件的子集。返回的对象包括`username`，`uid`，`gid`，`shell`，和`homedir`。在 Windows 上，`uid`和`gid`字段是`-1`，并且`shell`是`null`。

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

######  POSIX  错误常量

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
| `EOPNOTSUPP`      | 表示套接字不支持该操作。请注意，虽然`ENOTSUP`和`EOPNOTSUPP`在Linux上相同的值，根据 POSIX .1这些错误值应该是不同的。） |
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

######  Windows 错误常量

以下错误代码特定于 Windows 操作系统：

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
| `RTLD_LAZY`     | 执行延迟绑定。Node.默认设置此标志。                      |
| `RTLD_NOW`      | 在dlopen（3）返回之前解析库中的所有未定义符号。            |
| `RTLD_GLOBAL`   | 库定义的符号将可用于后续加载的库的符号解析。               |
| `RTLD_LOCAL`    | 相反的`RTLD_GLOBAL`。如果未指定任何标志，则这是默认行为。  |
| `RTLD_DEEPBIND` | 使一个独立的库使用自己的符号，而不是先前加载的库中的符号。 |

##### 优先级常数

以下进程调度常量通过以下方式导出 `os.constants.priority`：

| 不变                    | 描述                                                         |
| ----------------------- | ------------------------------------------------------------ |
| `PRIORITY_LOW`          | 最低进程调度优先级。这对应 `IDLE_PRIORITY_CLASS`于 Windows ，并且`19`在所有其他 平台上都很有价值 。 |
| `PRIORITY_BELOW_NORMAL` | 流程调度优先级高于`PRIORITY_LOW`和低于`PRIORITY_NORMAL`。这对应 `BELOW_NORMAL_PRIORITY_CLASS`于 Windows ，并且`10`在所有其他 平台上都很有价值 。 |
| `PRIORITY_NORMAL`       | 默认进程调度优先级。这对应 `NORMAL_PRIORITY_CLASS`于 Windows ，并且`0`在所有其他 平台上都很有价值 。 |
| `PRIORITY_ABOVE_NORMAL` | 流程调度优先级高于`PRIORITY_NORMAL`和低于`PRIORITY_HIGH`。这对应 `ABOVE_NORMAL_PRIORITY_CLASS`于 Windows ，并且`-7`在所有其他 平台上都很有价值 。 |
| `PRIORITY_HIGH`         | 流程调度优先级高于`PRIORITY_ABOVE_NORMAL` 和低于`PRIORITY_HIGHEST`。这对应 `HIGH_PRIORITY_CLASS`于 Windows ，并且`-14`在所有其他 平台上都很有价值 。 |
| `PRIORITY_HIGHEST`      | 最高进程调度优先级。这对应 `REALTIME_PRIORITY_CLASS`于 Windows ，并且`-20`在所有其他 平台上都很有价值 。 |



---

### path

该`path`模块提供了用于处理文件和目录路径的实用程序。它可以使用以下方式访问：

```
const path = require('path');
```

####  Windows 与 POSIX  

`path`模块的默认操作因运行Node.应用程序的操作系统而异。具体来说，在 Windows 操作系统上运行时，`path`模块将假定正在使用 Windows 样式的路径。

因此使用`path.basename()` 可能会在 POSIX 和 Windows 上产生不同的结果：

在 POSIX 上：

```
path.basename('C:\\temp\\myfile.html');
// Returns: 'C:\\temp\\myfile.html'
```

在 Windows 上：

```
path.basename('C:\\temp\\myfile.html');
// Returns: 'myfile.html'
```

要在任何操作系统上使用 Windows 文件路径时获得一致的结果，请使用 `path.win32`：

在 POSIX 和 Windows 上：

```
path.win32.basename('C:\\temp\\myfile.html');
// Returns: 'myfile.html'
```

要在任何操作系统上使用 POSIX 文件路径时获得一致的结果，请使用 `path.POSIX `：

在 POSIX 和 Windows 上：

```
path.POSIX .basename('/tmp/myfile.html');
// Returns: 'myfile.html'
```

在 Windows 上，Node.遵循每个驱动器工作目录的概念。使用没有反斜杠的驱动器路径时，可以观察到此行为。例如，`path.resolve('c:\\')`可能会返回不同的结果 `path.resolve('c:')`。有关详细信息，请参阅 [此MSDN页面。

#### path.basename（path [，ext]）

- `path` <String>
- `ext` [可选的文件扩展名
- returns <>

这些`path.basename()` 方法返回a的最后一部分`path`，类似于Unix `basename`命令。尾随目录分隔符将被忽略，请参阅  `path.sep`。

```
path.basename('/foo/bar/baz/asdf/quux.html');
// Returns: 'quux.html'

path.basename('/foo/bar/baz/asdf/quux.html', '.html');
// Returns: 'quux'
```

 `TypeError`如果`path`不是字符串或者是否`ext`给定且不是字符串，则抛出A.

#### path.delimiter

- <String>

提供特定于 平台的路径分隔符：

- `;` 对于 Windows 
- `:` 对于 POSIX 

例如，在 POSIX 上：

```
console.log(process.env.PATH);
// Prints: '/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin'

process.env.PATH.split(path.delimiter);
// Returns: ['/usr/bin', '/bin', '/usr/sbin', '/sbin', '/usr/local/bin']
```

在 Windows 上：

```
console.log(process.env.PATH);
// Prints: 'C:\   Windows  \system32;C:\   Windows  ;C:\Program Files\node\'

process.env.PATH.split(path.delimiter);
// Returns ['C:\\   Windows  \\system32', 'C:\\   Windows  ', 'C:\\Program Files\\node\\']
```

#### path.dirname(path)

- `path` <String>
- returns <>

该`path.dirname()` 方法返回a的目录名`path`，类似于Unix `dirname`命令。尾随目录分隔符将被忽略，请参阅  `path.sep`。

```
path.dirname('/foo/bar/baz/asdf/quux');
// Returns: '/foo/bar/baz/asdf'
```

 `TypeError`如果`path`不是字符串，则抛出A.

#### path.extname(path)

- `path` <String>
- returns <>

该`path.extname()` 方法返回`path`从`.`（句点）字符的最后一次出现到最后一部分的字符串结尾的扩展`path`。如果`.`在最后一部分中没有`path`，或者`path`（参见`path.basename()` ）的基本名称的第一个字符是`.`，则返回空字符串。

```
path.extname('index.html');
// Returns: '.html'

path.extname('index.coffee.md');
// Returns: '.md'

path.extname('index.');
// Returns: '.'

path.extname('index');
// Returns: ''

path.extname('.index');
// Returns: ''
```

 `TypeError`如果`path`不是字符串，则抛出A.

#### path.format(pathObject)



- `pathObject` <Object>
  - `dir` <String>
  - `root` <String>
  - `base` <String>
  - `name` <String>
  - `ext` <String>
- returns <>

该`path.format()` 方法从对象返回路径字符串。这与之相反 `path.parse()` 。

在提供属性时，`pathObject`请记住存在一个属性优先于另一个属性的组合：

- `pathObject.root`如果`pathObject.dir`提供，则被忽略
- `pathObject.ext`并且`pathObject.name`如果`pathObject.base`存在则被忽略

例如，在 POSIX 上：

```
// If `dir`, `root` and `base` are provided,
// `${dir}${path.sep}${base}`
// will be returned. `root` is ignored.
path.format({
  root: '/ignored',
  dir: '/home/user/dir',
  base: 'file.txt'
});
// Returns: '/home/user/dir/file.txt'

// `root` will be used if `dir` is not specified.
// If only `root` is provided or `dir` is equal to `root` then the
// platform separator will not be included. `ext` will be ignored.
path.format({
  root: '/',
  base: 'file.txt',
  ext: 'ignored'
});
// Returns: '/file.txt'

// `name` + `ext` will be used if `base` is not specified.
path.format({
  root: '/',
  name: 'file',
  ext: '.txt'
});
// Returns: '/file.txt'
```

在 Windows 上：

```
path.format({
  dir: 'C:\\path\\dir',
  base: 'file.txt'
});
// Returns: 'C:\\path\\dir\\file.txt'
```

#### path.isAbsolute(path)



- `path` <String>
- returns <>

该`path.isAbsolute()` 方法确定是否`path`是绝对路径。

如果给定的`path`是零长度字符串，`false`则返回。

例如，在 POSIX 上：

```
path.isAbsolute('/foo/bar'); // true
path.isAbsolute('/baz/..');  // true
path.isAbsolute('qux/');     // false
path.isAbsolute('.');        // false
```

在 Windows 上：

```
path.isAbsolute('//server');    // true
path.isAbsolute('\\\\server');  // true
path.isAbsolute('C:/foo/..');   // true
path.isAbsolute('C:\\foo\\..'); // true
path.isAbsolute('bar\\baz');    // false
path.isAbsolute('bar/baz');     // false
path.isAbsolute('.');           // false
```

 `TypeError`如果`path`不是字符串，则抛出A.

#### path.join（[... paths]）



- `...paths` [一系列路径段
- returns <>

该`path.join()` 方法`path`使用特定于 平台的分隔符作为分隔符将所有给定段连接在一起，然后规范化生成的路径。

零长度`path`段被忽略。如果连接的路径字符串是零长度字符串，`'.'`则将返回，表示当前工作目录。

```
path.join('/foo', 'bar', 'baz/asdf', 'quux', '..');
// Returns: '/foo/bar/baz/asdf'

path.join('foo', {}, 'bar');
// throws 'TypeError: Path must be a string. Received {}'
```

 `TypeError`如果任何路径段不是字符串，则抛出A.

#### path.normalize(path)



- `path` <String>
- returns <>

该`path.normalize()` 方法规范化给定`path`，解析`'..'`和 `'.'`分段。

当找到多个顺序路径段分隔字符时（例如， `/`在 POSIX 上`\`或`/`在 Windows  上或在 Windows 上），它们被特定于 平台的路径段分隔符的单个实例（`/`在 POSIX 和 `\` Windows 上）替换。尾随分隔符被保留。

如果`path`是零长度字符串，`'.'`则返回，表示当前工作目录。

例如，在 POSIX 上：

```
path.normalize('/foo/bar//baz/asdf/quux/..');
// Returns: '/foo/bar/baz/asdf'
```

在 Windows 上：

```
path.normalize('C:\\temp\\\\foo\\bar\\..\\');
// Returns: 'C:\\temp\\foo\\'
```

由于 Windows 识别多个路径分隔符，因此两个分隔符将被 Windows 首选分隔符（`\`）的实例替换：

```
path.win32.normalize('C:////temp\\\\/\\/\\/foo/bar');
// Returns: 'C:\\temp\\foo\\bar'
```

 `TypeError`如果`path`不是字符串，则抛出A.

#### path.parse(path)



- `path` <String>
- returns <>

该`path.parse()` 方法返回一个对象，其属性表示该对象的重要元素`path`。尾随目录分隔符将被忽略，请参阅 `path.sep`。

返回的对象将具有以下属性：

- `dir` <String>
- `root` <String>
- `base` <String>
- `name` <String>
- `ext` <String>

例如，在 POSIX 上：

```
path.parse('/home/user/dir/file.txt');
// Returns:
// { root: '/',
//   dir: '/home/user/dir',
//   base: 'file.txt',
//   ext: '.txt',
//   name: 'file' }
┌─────────────────────┬────────────┐
│          dir        │    base    │
├──────┬              ├──────┬─────┤
│ root │              │ name │ ext │
"  /    home/user/dir / file  .txt "
└──────┴──────────────┴──────┴─────┘
(all spaces in the "" line should be ignored — they are purely for formatting)
```

在 Windows 上：

```
path.parse('C:\\path\\dir\\file.txt');
// Returns:
// { root: 'C:\\',
//   dir: 'C:\\path\\dir',
//   base: 'file.txt',
//   ext: '.txt',
//   name: 'file' }
┌─────────────────────┬────────────┐
│          dir        │    base    │
├──────┬              ├──────┬─────┤
│ root │              │ name │ ext │
" C:\      path\dir   \ file  .txt "
└──────┴──────────────┴──────┴─────┘
(all spaces in the "" line should be ignored — they are purely for formatting)
```

 `TypeError`如果`path`不是字符串，则抛出A.

#### path.POSIX 

- <Object>

该`path.POSIX `属性提供对`path`方法的 POSIX 特定实现的访问。

#### path.relative(from，to)

- `from` <String>
- `to` <String>
- returns <String>

该`path.relative()` 方法返回从相对路径`from`来`to`基于当前的工作目录。如果`from`和`to`每个解析到相同的路径（在调用`path.resolve()` 每个路径之后），则返回零长度字符串。

如果将零长度字符串作为`from`或传递`to`，则将使用当前工作目录而不是零长度字符串。

例如，在 POSIX 上：

```
path.relative('/data/orandea/test/aaa', '/data/orandea/impl/bbb');
// Returns: '../../impl/bbb'
```

在 Windows 上：

```
path.relative('C:\\orandea\\test\\aaa', 'C:\\orandea\\impl\\bbb');
// Returns: '..\\..\\impl\\bbb'
```

 `TypeError`如果其中一个`from`或`to`不是字符串，则抛出A.

#### path.resolve([... paths])

- `...paths` <String>
- returns <String>

该`path.resolve()` 方法将一系列路径或路径段解析为绝对路径。

给定的路径序列从右到左处理，随后每个`path`路径都被预先加载，直到构造出绝对路径。例如，给定路径段的序列：`/foo`，`/bar`，`baz`，调用`path.resolve('/foo', '/bar', 'baz')`将返回`/bar/baz`。

如果在处理`path`完所有给定段之后尚未生成绝对路径，则使用当前工作目录。

生成的路径已规范化，并且除非将路径解析为根目录，否则将删除尾部斜杠。

零长度`path`段被忽略。

如果没有`path`传递段，`path.resolve()` 将返回当前工作目录的绝对路径。

```
path.resolve('/foo/bar', './baz');
// Returns: '/foo/bar/baz'

path.resolve('/foo/bar', '/tmp/file/');
// Returns: '/tmp/file'

path.resolve('wwwroot', 'static_files/png/', '../gif/image.gif');
// if the current working directory is /home/myself/node,
// this returns '/home/myself/node/wwwroot/static_files/gif/image.gif'
```

 `TypeError`如果任何参数不是字符串，则抛出A.

#### path.sep

- <String>

提供特定于 平台的路径段分隔符：

- `\` 在 Windows 上
- `/` 在 POSIX 上

例如，在 POSIX 上：

```
'foo/bar/baz'.split(path.sep);
// Returns: ['foo', 'bar', 'baz']
```

在 Windows 上：

```
'foo\\bar\\baz'.split(path.sep);
// Returns: ['foo', 'bar', 'baz']
```

在 Windows 上，正斜杠（`/`）和反斜杠（`\`）都被接受为路径段分隔符; 但是，这些`path`方法只添加反斜杠（`\`）。

#### path.toNamespacedPath(path)

- `path`<String>
- `returns` <String>

仅在 Windows 系统上，返回给定的等效[命名空间前缀路径`path`。如果`path`不是字符串，`path`将返回而不进行修改。

此方法仅在 Windows 系统上有意义。在 POSIX 系统上，该方法不可操作，并且始终`path`无需修改即可返回。

#### path.win32

- `returns` <Object>

该`path.win32`属性提供对特定于 Windows 的`path`方法实现的访问。



### filesystem

### stdio







## utility

### compress

### crypto