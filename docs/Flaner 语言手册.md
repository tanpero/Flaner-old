# Flaner 语言手册

---

[TOC]





---

## 值

---

### 字面值

#### 基本值

- null

  **语法**

  `null`

  **描述**

  代表*此时没有任何实际值*的特殊值。其类型为 `Null` 。

  

- number

  **语法**

  ```
  123456       // 十进制整数
  123E+456     // 使用科学计数法的十进制浮点数
  123.456      // 十进制浮点数
  -123456      // 负的十进制整数
  0x1234abcdef // 十六进制整数
  0o12347654   // 八进制整数
  0b10110100   // 二进制整数
  ```

  **描述**

  遵循大多数编程语言中的数值惯例形式。

  



#### 对象字面值



#### 数组字面值



#### 正则表达式字面值



#### 符号字面值



### 声明

---

#### 语法

```
let var1;     // 声明变量 var1，拥有默认值 null
const const1; // 错误：常量 const1 必须被赋予值
```

#### 描述

`let` 和 `const` 关键字分别在当前作用域中声明一个变量或常量，统称为*标识符*。

标识符不可重复声明。



### 赋值和实例化

---

#### 语法

```
var1 as Map;      // 使 var1 成为 Map 类的实例，拥有默认值（一个空 map）
var1 as Set;      // 错误：var1 的类型不能改变
let var2 as List; // 使 var2 成为 List 类的实例，拥有默认值（一个空 list）

let boy as Child = "Jim"; // 声明变量 boy，它是 Child 类的实例，并使用 "Jim" 初始化
// 声明常量 count，它是 Bigint 类的实例，并使用 "10E10000000" 初始化
const count as Bigint = "10E10000000"; 

let anotherboy as Child = "Ken";
let boy = anotherboy; // 错误：重复声明变量 boy
boy = anotherboy;     // 现在把 anotherboy 的值赋给 boy，它们指向同一个对象
anotherboy = null;    // 销毁了 anotherboy 所指向的对象
print(boy);           // boy 所指向的对象被销毁了

let number as Number; // 显式声明变量 number 为 Number 类的实例，并拥有默认值 0
let number2 = 0;      // 与上方代码等价，number2 被推导为 Number 类的实例

let object as Object; // Object 类的实例 object 拥有默认值 {} （空对象）
object = {a: 1, b: 2}; // 使用对象字面量构造一个新对象并赋予 object
object = [1, 2, 3];    // object 现在是 List 类的实例，它的值使用列表字面量构造。
                       // 这是允许的，因为 List 是 Object 的子类
                       
let map as Map = {a: 1, b: 2}; // map 是 Map 类的实例
                               // 使用对象字面量构造一个对象并用于初始化 map
                               
let set as Set = [1, 2, 3];    // 使用列表 [1, 2, 3] 初始化 Set 类的实例 set
set = {a: 1, b: 2, c: 3};      // 错误：对象字面量是 Object 的实例，而 Set 是 Object 的子类
                               // 不能把父类的实例赋给子类实例
```

#### 描述

- 变量在声明后拥有默认值 `null`，它是一个*空类型* 的变量，可以使用 `as` 关键字使其成为已有类的实例。

- 一旦一个变量的值被确定为某个类的实例，那么它就拥有了*类型*。

- 拥有了类型的变量，可以使用一个值进行*初始化*，前提是变量所属类型必须具有面向该值的*初始函数*。

- 如果值是一个*字面量*，那么变量的类型是可推断的。可推断类型的变量不需要显式声明类型，当它被初始化后，自动拥有对应类型。

- 一个确定了类型的变量，其类型是*不可更改*的。若对该变量进行重新赋值，值的类型必须满足以下任一条件：

  1. 值的类型 `S` 与变量的类型 `T` 完全匹配（同一个类型）；
  2. 值的类型 `S` 继承于变量的类型 `T` ；
  3. `T` 的类声明中包含了显式接受 `S` 实例的初始函数。

  若不满足条件，会引发类型错误。

- 常量必须在声明时被初始化，初始化后其值不可更改。



## 表达式

---







## 模块

------



### 导入

------

`import` 语句用于导入由另一个模块导出的标识符。

#### 语法

```
import defaultExport from "module-name";
import * as name from "module-name";
import { export } from "module-name";
import { export as alias } from "module-name";
import { export1 , export2 } from "module-name";
import { foo , bar } from "module-name/path/to/specific/un-exported/file";
import { export1 , export2 as alias2 , [...] } from "module-name";
import defaultExport, { export [ , [...] ] } from "module-name";
import defaultExport, * as name from "module-name";
import "module-name";

// 导入标准模块
import numeric.Bigint;
import network.http as http
```

- `defaultExport`

  导入模块的默认导出接口的引用名。

- `module-name`

  要导入的模块名称。虚拟机会在特定的路径中查找具有指定名称和特定后缀名的文件，但是 `<module-name>` 本身不应包含文件后缀名。

  优先查找 `.flm` 为后缀名的*通用模块*，如果没有找到对应的文件，那么查找以 `.flx` 为后缀名的*扩展模块*。

- `name`

  导入模块对象整体的别名，在引用导入模块时，它将作为一个命名空间来使用。

- `export, exportN`

  被导入模块的导出接口的名称。

- `alias, aliasN`

  将引用指定的导入的名称。



#### 描述

`name` 参数是“导入模块对象”的名称，它将用一种名称空间来引用导入模块的接口。export参数指定单个的命名导出，而`import * as name`语法导入所有导出接口，即导入模块整体。以下示例阐明该语法。

##### 导入整个模块的内容

这将`myModule`插入当前作用域，其中包含来自位于`/modules/my-module.`文件中导出的所有接口。

```
import * as myModule from '/modules/my-module';
```

在这里，访问导出接口意味着使用模块名称（在本例为“myModule”）作为命名空间。例如，如果上面导入的模块包含一个接口`doAllTheAmazingThings()`，你可以这样调用：

```
myModule.doAllTheAmazingThings();
```

导入单个接口

给定一个名为`myExport`的对象或值，它已经从模块`my-module`导出（因为整个模块被导出）或显式地导出（使用 `export` 语句），将`myExport`插入当前作用域。

```
import {myExport} from '/modules/my-module';
```

##### 导入多个接口

这将`foo`和`bar`插入当前作用域。

```
import {foo, bar} from '/modules/my-module';
```

##### 导入带有别名的接口

你可以在导入时重命名接口。例如，将`shortName`插入当前作用域。

```
import {reallyReallyLongModuleExportName as shortName}
  from '/modules/my-module';
```

##### 导入时重命名多个接口

使用别名导入模块的多个接口。

```
import {
  reallyReallyLongModuleMemberName as shortName, 
  anotherLongModuleName as short
} from '/modules/my-module';
```

##### 仅为副作用而导入一个模块

整个模块仅为副作用（中性词，无贬义含义）而导入，而不导入模块中的任何内容（接口）。 这将运行模块中的全局代码, 但实际上不导入任何值。

```
import '/modules/my-module';
```

##### 导入默认值

引入模块可能有一个 `default export`（无论它是对象，函数，类等）可用。然后可以使用`import`语句来导入这样的默认接口。

最简单的用法是直接导入默认值：

```
import myDefault from '/modules/my-module';
```

也可以同时将`default`语法与上述用法（命名空间导入或命名导入）一起使用。在这种情况下，`default`导入必须首先声明。 例如：

```
import myDefault, * as myModule from '/modules/my-module';
// myModule used as a namespace
```

或者

```
import myDefault, {foo, bar} from '/modules/my-module';
// specific, named imports
```



### 导出

------

`export` 语句将本文件看做一个独立模块，并导出指定的标识符。

#### 语法

```
// 导出单个特性
export let name1, name2, ..., nameN; // 也可以为 const
export let name1 = ..., name2 = ..., ..., nameN; // 也可以为 const
export (...) => {...}
export class ClassName {...}

// 导出列表
export { name1, name2, ..., nameN };

// 重命名导出
export { variable1 as name1, variable2 as name2, ..., nameN };

// 默认导出
export default expression;
export default (...) => { ... } // 也可以为 class, generator
export default name1 = (...) => { ... } // 也可以为 class, generator*
export { name1 as default, ... };

// Aggregating modules
export * from ...;
export { name1, name2, ..., nameN } from ...;
export { import1 as name1, import2 as name2, ..., nameN } from ...;
export { default } from ...;
```

- `nameN`

  要导出的标识符（以便被其他模块导入）

  

#### 描述

有两种不同的导出方式，命名导出和默认导出。你能够在每一个模块中定义多个命名导出，但是只允许有一个默认导出。每种方式对应于上述的一种语法：

- 命名导出：

  ```
  // exports a function declared earlier
  export { myFunction }; 
  
  // exports a   constant
  export   const foo = Math.sqrt(2);
  ```

- 默认导出（函数）：

  ```
  export default () => {}
  ```

- 默认导出（类）：

  ```
  export default class {}
  ```

在导出多个值时，命名导出非常有用。在导入期间，必须使用相应对象的相同名称。但是，可以使用任何名称导入默认导出，例如：

```
let k;
export default k = 12; // in file test.

import m from './test' // note that we have the freedom to use
                       // import m instead of import k, because k was default export

print(m);        // will print 12
```

 下面的语法不能从导入的模块导出默认导出值：

```
export * from ...;
```

如果需要导出默认值，请使用下列代码：

```
export {default} from 'mod';
```