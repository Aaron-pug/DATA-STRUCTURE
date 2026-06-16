# Vue3 + TypeScript 完整知识点教�?
> 配套项目：`travel-hotel-demo`（差旅通酒店预订页�?> 适用对象�?*0 基础**，从未写�?Vue 的同�?> 阅读方式�?*跟着目录顺序�?+ 对照项目源码**，每个知识点都有"在哪个文件里�?的指�?
---

## 📚 目录

1. [先搞懂：一�?Vue 项目是怎么跑起来的](#1-先搞懂一�?vue-项目是怎么跑起来的)
2. [工程目录与文件职责](#2-工程目录与文件职�?
3. [模板语法（template 必备 10 招）](#3-模板语法template-必备-10-�?
4. [响应式与逻辑（script setup）](#4-响应式与逻辑script-setup)
5. [组件化核心：props / emits / v-model / slot](#5-组件化核心props--emits--v-model--slot)
6. [路由 vue-router](#6-路由-vue-router)
7. [逻辑复用：Composables（组合式函数）](#7-逻辑复用composables组合式函�?
8. [状态管理：Pinia ★★★](#8-状态管理pinia)
9. [接口请求：axios（封�?+ 拦截器）](#9-接口请求axios封装--拦截�?
10. [TypeScript �?Vue 里的用法](#10-typescript-�?vue-里的用法)
11. [样式�?scoped](#11-样式�?scoped)
12. [工程化配置：代理 / 路径别名 / 环境变量](#12-工程化配置代�?-路径别名--环境变量)
13. [常见疑问 FAQ](#13-常见疑问-faq)

---

## 1. 先搞懂：一�?Vue 项目是怎么跑起来的

学任何框架前，先建立"**一张图在脑子里**"。Vue3 项目启动流程如下�?
```
浏览器打开 http://localhost:5173
        �?        �?加载 index.html  ←── 整个项目唯一一个真�?HTML 文件
        �?             里面只有一个空�?<div id="app"></div>
        �?加载 /src/main.ts  ←── index.html 最后一�?<script> 指向�?        �?        �? �?createApp(App)    创建应用实例
        �? �?app.use(router)   注册路由
        �? �?app.mount('#app') 挂载到那个空 div �?        �?渲染 App.vue（根组件�?        �?        ├── <AppHeader />        顶部导航
        ├── <router-view />      �?路由匹配到的页面塞这�?        └── <footer>             页脚
```

**一句话总结**：浏览器加载 `index.html` �?执行 `main.ts` �?�?`App.vue` 渲染�?`<div id="app">` �?之后所有页面切换都在这�?div 内部完成�?*浏览器不再整页刷�?*（这就是 SPA，单页应用）�?
### 三个文件先读一�?
::: tip 建议按这个顺序读
1. `index.html` —�?看到那个�?div 和引�?main.ts �?script 标签
2. `src/main.ts` —�?看到三步：createApp �?use(router) �?mount
3. `src/App.vue` —�?看到根组件长什么样
:::

> 本项目没有用�?Markdown 文档系统，上�?`:::tip` 只是排版习惯，实际文档里不依赖任何特殊渲染�?
---

## 2. 工程目录与文件职�?
```
travel-hotel-demo/
├─ index.html              # 【入口HTML】唯一真实页面，含 <div id="app">
├─ package.json            # 【依赖清单】项目用了哪些库 + npm 脚本命令
├─ vite.config.ts          # 【构建配置】Vite 配置，含路径别名 @ -> src
├─ tsconfig.json           # 【TS配置】总入口，引用下面两个
├─ tsconfig.app.json       #   应用代码(src)�?TS 配置
├─ tsconfig.node.json      #   构建代码(vite.config)�?TS 配置
├─ README.md               # 项目快速上�?├─ TUTORIAL.md             # �?本文档（完整教程�?└─ src/                    # ★★�?所有源码都在这�?   ├─ main.ts              # 【应用入口】创建App + 注册路由 + 挂载
   ├─ App.vue              # 【根组件】最外层壳子
   ├─ env.d.ts             # 【类型声明】让 TS 认识 .vue 文件
   ├─ types.ts             # 【类型定义】所�?interface/type 集中放这
   �?   ├─ router/
   �? └─ index.ts          # 【路由表】地址(URL) �?页面 映射关系
   �?   ├─ data/
   �? └─ mockData.ts       # 【假数据】模拟后端返回的酒店列表
   �?   ├─ composables/
   �? └─ useFavorites.ts   # 【逻辑复用】收藏功�?跨组件共享状�?
   �?   ├─ styles/
   �? └─ global.css        # 【全局样式】CSS 变量 + 浏览器默认样式重�?   �?   ├─ components/          # 【组件库】可复用的小积木 �?   �? ├─ CounterDemo.vue       # 计数器：最小可运行组件
   �? ├─ MultiEmitDemo.vue     # 多参�?emit 演示
   �? ├─ AppHeader.vue         # 顶部导航�?   �? ├─ SearchBar.vue         # 搜索�?   �? ├─ FilterBar.vue         # 筛选栏
   �? ├─ SortBar.vue           # 排序�?   �? ├─ HotelCard.vue         # 酒店卡片
   �? └─ RecommendSidebar.vue  # 推荐侧边�?   �?   └─ views/               # 【页面】每个路由对应一个页�?�?      ├─ HomeView.vue          # 首页(酒店列表)
      ├─ HotelDetailView.vue   # 酒店详情�?      └─ FavoritesView.vue     # 我的收藏�?```

### components �?views 有什么区别？

| | `components/` | `views/` |
|---|---|---|
| **是什�?* | 可复用的**零件**（按钮、卡片、搜索框�?| 一个个完整�?*页面** |
| **数量关系** | 一个组件可能被多个页面使用 | 一个页面通常对应一条路�?|
| **举例** | `HotelCard.vue` 在首页和收藏页都用到�?| `HomeView.vue` 对应 `/` 这条路由 |
| **判断标准** | "这块东西会在别处复用吗？" �?�?components | "这是一整张页面吗？" �?�?views |

> 💡 这是**社区约定**，不是强制规则。但遵守它能让项目结构清晰，别人接手也容易看懂�?
### 几个关键配置文件速览

**`package.json`** —�?项目名片
```json
{
  "scripts": {
    "dev": "vite",          // 开发：npm run dev 启动热更新服务器
    "build": "vue-tsc -b && vite build",  // 打包：先类型检查再构建
    "preview": "vite preview"             // 预览打包结果
  },
  "dependencies": { "vue": "...", "vue-router": "..." },  // 运行时依�?  "devDependencies": { "vite": "...", "typescript": "..." }  // 开发时才需�?}
```

**`vite.config.ts`** —�?构建工具配置
```ts
export default defineConfig({
  plugins: [vue()],         // �?Vite 能编�?.vue 文件
  resolve: {
    alias: { '@': path.resolve(__dirname, 'src') }  // @ 就是 src 目录
  },
  server: { port: 5173, open: true }   // 端口 + 自动开浏览�?})
```

---

## 3. 模板语法（template 必备 10 招）

> **对照文件**：`src/components/CounterDemo.vue`（最小示例）+ 各组件的 `<template>` 部分

Vue 的模板就�?HTML 加了几个特殊语法。下�?10 个是用得最多的�?
### 3.1 插�?`{{ }}` —�?显示变量

```html
<template>
  <div>当前计数：{{ count }}</div>
  <!-- 还能写简单表达式 -->
  <div>价格：¥{{ price.toFixed(2) }}</div>
  <div>{{ count > 10 ? '很多' : '不多' }}</div>
</template>
```

- 双花括号会把里面的值当�?JS 来算，然后显示成字符�?- **只能用在标签的文本内容位�?*，不能用在属性里（属性要�?`v-bind`�?
### 3.2 `v-bind` / `:` —�?绑定属�?
```html
<!-- 完整写法 -->
<img v-bind:src="hotel.cover" />

<!-- 简写（99% 都用这个�?-->
<img :src="hotel.cover" :alt="hotel.name" />

<!-- 绑定对象（一次性设多个属性） -->
<img v-bind="hotelAttrs" />
```

**记忆�?*：看�?`:` 就想"等号右边的值是个变量，不是字符�?�?- `src="x.png"` �?src 就是字符�?"x.png"
- `:src="x"` �?src 是变�?x 的�?
### 3.3 `v-on` / `@` —�?绑定事件

```html
<!-- 完整写法 -->
<button v-on:click="increase">+1</button>

<!-- 简�?-->
<button @click="increase">+1</button>

<!-- 直接写语�?-->
<button @click="count++">+1</button>

<!-- 事件修饰符：.stop 阻止冒泡�?prevent 阻止默认行为 -->
<form @submit.prevent="onSubmit">...</form>

<!-- 按键修饰符：按回车才触发 -->
<input @keyup.enter="onSearch" />
```

**常见修饰�?*�?| 修饰�?| 作用 | 例子 |
|---|---|---|
| `.stop` | 阻止事件冒泡 | `@click.stop="..."` |
| `.prevent` | 阻止默认行为 | `@submit.prevent="..."` |
| `.enter` / `.esc` | 指定按键 | `@keyup.enter="..."` |
| `.once` | 只触发一�?| `@click.once="..."` |

### 3.4 `v-model` —�?双向绑定

> **对照文件**：`SearchBar.vue` 的关键词输入�?
```html
<!-- 输入框的值和变量 keyword 互相绑定 -->
<input v-model="keyword" placeholder="请输�? />

<!-- .number 修饰符：自动把输入转成数�?-->
<input v-model.number="nights" type="number" />
```

**双向**的含义：
- 用户在输入框打字 �?`keyword` 变量**自动更新**
- 代码里改 `keyword.value = 'xxx'` �?输入框显�?*自动跟着�?*

它等价于这一长串�?```html
<input :value="keyword" @input="keyword = $event.target.value" />
```

### 3.5 `v-if` / `v-else` / `v-show` —�?条件渲染

```html
<!-- v-if：条件为 false 时，这个元素【完全不渲染�?DOM�?-->
<div v-if="count > 10">很多</div>
<div v-else-if="count > 5">一�?/div>
<div v-else>很少</div>

<!-- v-show：条件为 false 时，元素还在 DOM 里，只是 display:none -->
<div v-show="isVisible">我会显示/隐藏</div>
```

**v-if vs v-show 怎么选？**

| | `v-if` | `v-show` |
|---|---|---|
| false �?| 元素**不存�?*�?DOM | 元素�?DOM，但 `display:none` |
| 切换成本 | 高（要创�?销毁元素） | 低（只改 CSS�?|
| 初始渲染 | false 时不渲染，省资源 | 一开始就渲染 |
| 适用场景 | **不常切换**（如弹窗、详情） | **频繁切换**（如 Tab�?|

> 💡 本项目里：收藏徽�?`v-if="favoriteCount > 0"`、空状�?`v-if="filteredHotels.length === 0"` 用的都是 v-if�?
### 3.6 `v-for` —�?列表渲染

> **对照文件**：`HomeView.vue` 的酒店列�?
```html
<!-- 遍历数组 -->
<li v-for="hotel in hotelList" :key="hotel.id">
  {{ hotel.name }}
</li>

<!-- 需要索引时 -->
<li v-for="(hotel, index) in hotelList" :key="hotel.id">
  {{ index + 1 }}. {{ hotel.name }}
</li>

<!-- 遍历数字 -->
<span v-for="n in 5" :key="n">{{ n }}</span>
```

**⚠️ 铁律：`v-for` 必须�?`:key`�?*

`:key` 是每个元素的"身份证号"，Vue 用它来追踪哪一项变了�?*必须唯一且稳�?*�?- �?用数据的唯一 id：`:key="hotel.id"`
- �?不要用数组索引：`:key="index"`（列表增删会错乱�?- �?不要用随机数（每次都变，Vue 追踪不了�?
### 3.7 `v-html` —�?渲染 HTML 字符�?
```html
<!-- content 是一�?HTML 字符串，比如 '<b>加粗</b>' -->
<div v-html="content"></div>
```

**⚠️ 安全警告**：`v-html` 会执行里面的 HTML，如果内容来自用户输入，会有 **XSS 攻击**风险。只在内容可信时使用�?
### 3.8 动态class / style

```html
<!-- 对象语法：active �?true 时加上该 class -->
<div :class="{ active: isActive, 'text-red': hasError }"></div>

<!-- 数组语法：组合多�?class -->
<div :class="[baseClass, isActive ? 'active' : '']"></div>

<!-- 混用 -->
<div :class="['base', { active: isActive }]"></div>

<!-- style 也能动态绑�?-->
<div :style="{ color: textColor, fontSize: size + 'px' }"></div>
```

本项目里大量用到对象语法，例�?`FilterBar.vue`�?```html
<button :class="{ 'filter__chip--active': brand === b }">
```

### 3.9 模板引用 ref —�?直接�?DOM

```html
<template>
  <input ref="myInput" />
  <button @click="focusInput">聚焦</button>
</template>

<script setup lang="ts">
import { ref } from 'vue'
// 变量名必须和 template �?ref="xxx" 一�?const myInput = ref<HTMLInputElement | null>(null)

function focusInput() {
  myInput.value?.focus()   // 挂载后才有�?}
</script>
```

> 注意：这�?`ref` 和响应式�?`ref()` 同名但是两个概念，别混淆。这里是"模板引用"，用来直接操�?DOM�?
### 3.10 模板速查�?
| 需�?| 写法 |
|---|---|
| 显示变量 | `{{ name }}` |
| 绑定属�?| `:src="url"` |
| 绑定事件 | `@click="fn"` |
| 双向绑定 | `v-model="name"` |
| 条件显示 | `v-if` / `v-show` |
| 循环 | `v-for="x in list" :key="x.id"` |
| 动态class | `:class="{ active: ok }"` |

---

## 4. 响应式与逻辑（script setup�?
> **对照文件**：`HomeView.vue`、`HotelDetailView.vue`、各组件�?`<script setup>`

这一章讲 `<script setup>` 里怎么写数据、怎么写逻辑�?
### 4.1 `<script setup>` 是什么？

Vue3 推荐�?`<script setup>` 写组件逻辑，它是语法糖�?
```vue
<script setup lang="ts">
import { ref } from 'vue'

const count = ref(0)         // �?顶层声明的变�?function increase() {        // �?顶层声明的函�?  count.value++
}
</script>

<template>
  <button @click="increase">{{ count }}</button>
  <!-- �?模板里直接用 count / increase，不�?return -->
</template>
```

**对比旧的 Options API**（不用学，看一眼知道区别就行）�?```ts
// 旧写法：啰嗦，要�?export default + methods + data
export default {
  data() { return { count: 0 } },
  methods: { increase() { this.count++ } }
}
```

`<script setup>` 的好处：
1. **少写样板代码**，不�?`export default`、不�?`return`
2. **更好�?TS 支持**，类型推导更�?3. **顶层导入的组件直接能�?*，不用注�?
### 4.2 ref —�?响应式数据（基础类型�?
> **对照文件**：`CounterDemo.vue`

```ts
import { ref } from 'vue'

const count = ref(0)          // 创建响应式变量，初始�?0
console.log(count.value)      // �?JS 里读写必�?.value
count.value++                 // �?修改也要 .value

const name = ref<string>('')  // TS：用泛型指定类型
```

**为什么要�?`.value`�?*

`ref()` 把原始值包成了一个对�?`{ value: 0 }`，因�?JS 里基本类型（数字、字符串）没法被"拦截"感知变化，包成对象后 Vue 才能追踪到对 `.value` 的读写�?
**模板里不用写 `.value`**（Vue 自动解包）：
```html
<!-- �?�?-->
<div>{{ count }}</div>
<!-- �?错（多此一举，会显�?undefined�?-->
<div>{{ count.value }}</div>
```

**规则总结**�?| 在哪 | 怎么�?|
|---|---|
| `<script>` �?| `count.value`（必须加 .value�?|
| `<template>` �?| `count`（自动解包） |

### 4.3 reactive —�?响应式对�?
```ts
import { reactive } from 'vue'

const state = reactive({
  count: 0,
  user: { name: '张三' }
})

state.count++              // �?不用 .value，直接改�?state.user.name = '李四'   // 嵌套属性也是响应式�?```

**ref vs reactive 怎么选？**

| | `ref` | `reactive` |
|---|---|---|
| 适合 | 基础类型、单个�?| 对象 |
| 访问 | �?`.value` | 直接访问 |
| 重新赋�?| `xxx.value = 新值` �?| `state = 新对象` �?会丢响应�?|
| 推荐 | **官方推荐优先�?ref** | 对象字段多时也行 |

> 💡 为什么推�?ref？因�?reactive 有个坑：**不能整体替换**。`state = newObj` 会让响应式失效，只能 `Object.assign(state, newObj)`。ref 没这个问题�?
### 4.4 computed —�?计算属�?
> **对照文件**：`HomeView.vue` �?`filteredHotels`、`HotelCard.vue` �?`starText`

**作用**：根据其他响应式数据"�?出一个新值，**依赖变了自动重算，且有缓�?*�?
```ts
import { ref, computed } from 'vue'

const price = ref(100)
const count = ref(3)

// 总价：依�?price �?count，任意一个变了就重算
const total = computed(() => price.value * count.value)

console.log(total.value)   // 300
count.value = 5
console.log(total.value)   // 150（自动更新）
```

**带类型的写法**�?```ts
const filteredHotels = computed<Hotel[]>(() => {
  return hotelList.filter(/* ... */)
})
```

**computed vs methods 的区�?*�?
```ts
// �?computed
const total = computed(() => price.value * count.value)

// 用方�?function getTotal() { return price.value * count.value }
```

| | `computed` | `methods` |
|---|---|---|
| 缓存 | �?有（依赖没变就用旧结果） | �?无（每次调用都算�?|
| 调用方式 | `total.value`（像属性） | `getTotal()`（像函数�?|
| 性能 | 多次访问只算一�?| 多次访问算多�?|

> 💡 模板里多次用同一个值，**优先 computed**�?
**可写 computed**（少用）�?```ts
const fullName = computed({
  get() { return firstName.value + ' ' + lastName.value },
  set(newValue) {
    [firstName.value, lastName.value] = newValue.split(' ')
  }
})
```

### 4.5 watch —�?侦听�?
> **对照文件**：`HomeView.vue` 末尾�?watch

**作用**：监听某个响应式数据�?*它变了就执行一段逻辑**（比如发请求、存本地、打印日志）�?
```ts
import { ref, watch } from 'vue'

const keyword = ref('')

// 基本用法：监听一�?ref
watch(keyword, (newValue, oldValue) => {
  console.log(`关键词从 "${oldValue}" 变成 "${newValue}"`)
})

// 监听多个
watch([a, b], ([newA, newB], [oldA, oldB]) => {
  console.log('a �?b 变了')
})
```

**监听对象/数组（深度监听）**�?```ts
const filter = ref({ brand: '不限', star: 0 })

// 默认只监听引用变化，内部字段改了不触�?// �?deep: true 才能监听嵌套变化
watch(filter, (newVal) => { /* ... */ }, { deep: true })

// 立即执行一次：immediate: true
watch(filter, (newVal) => { /* ... */ }, { immediate: true })
```

**watch vs computed 怎么选？**

| 场景 | 用什�?|
|---|---|
| 需�?*算出一个新�?*给模板用 | `computed` |
| 数据变了�?*执行副作�?*（发请求、改别的数据、console.log�?| `watch` |

**watchEffect**（自动追踪依赖的 watch）：
```ts
import { watchEffect } from 'vue'

watchEffect(() => {
  // 函数里用到了什�?ref，就自动监听什�?  console.log(keyword.value, filter.value.brand)
})
```

### 4.6 生命周期钩子

> **对照文件**：本项目用得不多，但属于必备知识

组件从创建到销毁会经历一系列阶段，Vue 提供"钩子函数"让你在特定时机插代码�?
```ts
import { onMounted, onUpdated, onUnmounted } from 'vue'

// 组件挂载�?DOM 后触发（最常用！比如发请求、操作DOM�?onMounted(() => {
  console.log('组件已挂载，DOM 可以访问�?)
  // 这里可以�?API 请求、初始化第三方库�?})

// 数据更新导致 DOM 重新渲染后触�?onUpdated(() => {
  console.log('DOM 更新�?)
})

// 组件卸载前触发（清理定时器、解绑事件）
onUnmounted(() => {
  console.log('组件要销毁了，做清理工作')
})
```

**常用钩子速查**�?
| 钩子 | 何时触发 | 典型用�?|
|---|---|---|
| `onBeforeMount` | 挂载�?| 很少�?|
| `onMounted` | **挂载�?* | **发请求、操作DOM、启动定时器** |
| `onUpdated` | 数据更新�?| 慎用，容易死循环 |
| `onUnmounted` | **销毁前** | **清理定时器、解绑全局事件** |

### 4.7 总结：响应式三板�?
```
ref/reactive  �? 存数�?computed      �? 算数据（派生值）
watch         �? 反应数据变化（执行副作用�?```

加上生命周期 `onMounted` 处理初始化，日常开�?90% 的逻辑就这四样�?
---

## 5. 组件化核心：props / emits / v-model / slot

> ★★�?**这是最重要的一�?*，组件化�?Vue 的灵魂�?> 对照文件：`HotelCard.vue`、`SearchBar.vue`、`FilterBar.vue`、`HomeView.vue`、`MultiEmitDemo.vue`

### 5.0 组件化的核心思想

把页面拆成一个个**可复用的小积�?*�?
```
首页(HomeView)
├─ 顶部导航(AppHeader)          �?组件A
├─ 搜索�?SearchBar)            �?组件B
├─ 筛选栏(FilterBar)            �?组件C
├─ 排序�?SortBar)              �?组件D
├─ 酒店卡片(HotelCard) × N      �?组件E（循环渲染多个）
└─ 推荐�?RecommendSidebar)     �?组件F
```

**好处**�?- 复用：HotelCard 写一次，列表里循环用 N �?- 好维护：每个组件管自己的事，改一处不影响别的
- 清晰：页面结构一眼看�?
### 5.1 怎么使用一个组件？

**三步**�?
```vue
<!-- 1. 引入 -->
<script setup lang="ts">
import HotelCard from '@/components/HotelCard.vue'
</script>

<!-- 2. �?HTML 标签�?-->
<template>
  <HotelCard />
</template>
```

组件名规则：
- **PascalCase**（大驼峰）：`<HotelCard />` —�?推荐，编辑器好识�?- **kebab-case**（短横线）：`<hotel-card />` —�?HTML 原生标签都是小写，这样区�?
**自动导入说明**：本项目用的�?*手动 import**（最基础、最透明的方式）。实际生产项目会�?`unplugin-vue-components` 实现自动导入，但初学先理解手动方式�?
### 5.2 props —�?父传子数�?
> **对照文件**：`HotelCard.vue`（接收）、`HomeView.vue`（传递）

**【父 �?子】用 props 往下传数据**�?
#### 子组件：定义接收什么参�?
```vue
<script setup lang="ts">
import type { Hotel } from '@/types'

// 【TS 写法】用泛型定义 props 类型
const props = defineProps<{
  hotel: Hotel           // 必传
  showFavorite?: boolean // 可选（? 表示可不传）
}>()

// 使用：props.hotel.name
</script>
```

**带默认�?*（用 `withDefaults`）：
```ts
const props = withDefaults(
  defineProps<{
    title?: string
    max?: number
  }>(),
  {
    title: '默认标题',    // 不传时用这个
    max: 10,
  },
)
```

#### 父组件：传数据进�?
```html
<!-- 静态字符串 -->
<HotelCard title="酒店列表" />

<!-- 动态变量（必须�?:�?-->
<HotelCard :hotel="myHotel" />

<!-- 传多�?-->
<HotelCard :hotel="myHotel" :showFavorite="true" />
```

#### ⚠️ props 是只读的�?
```ts
const props = defineProps<{ hotel: Hotel }>()

props.hotel.name = '新名�?  // �?错！props 不能�?```

子组件要"�?父组件的数据？用 emit 通知父组件改（见 5.3）�?
#### props 命名：camelCase vs kebab-case

```ts
// 声明时用 camelCase
defineProps<{ userName: string }>()
```
```html
<!-- 模板传递时�?kebab-case（HTML 不区分大小写�?-->
<MyComp user-name="张三" />
```

### 5.3 emits —�?子向父发事件

> **对照文件**：`SearchBar.vue`、`MultiEmitDemo.vue`（发送）、`HomeView.vue`（接收）

**【子 �?父】用 emit 向上发通知**。这是组件通信**最重要的机�?*�?
#### 为什么要 emit�?
Vue 数据流是**单向**的：�?�?子。子组件不能直接改父的数据�?正确做法：子组件"喊一�?（emit 事件），父组�?听到"后自己改�?
#### 子组件：声明并发送事�?
```vue
<script setup lang="ts">
// 【TS 写法】用泛型声明所有事�?const emit = defineEmits<{
  (e: 'search', keyword: string): void      // search 事件，带一�?string 参数
  (e: 'reset'): void                        // reset 事件，不带参�?}>()

function onSearch() {
  // 触发事件：emit('事件�?, 数据)
  emit('search', keyword.value)
}
</script>

<template>
  <button @click="onSearch">搜索</button>
</template>
```

#### 父组件：监听事件

```html
<!-- @事件�?"处理函数"，函数会自动收到参数 -->
<SearchBar @search="handleSearch" @reset="handleReset" />
```
```ts
// 参数和子组件 emit 时的参数对应
function handleSearch(keyword: string) {
  console.log('收到关键词：', keyword)
}
```

#### �?多参�?emit 的两种写�?
> **对照文件**：`MultiEmitDemo.vue`（首页有可交互演示）

**写法一：多个独立参�?*（参数少时用�?
```ts
const emit = defineEmits<{
  // 一个事件名后面跟多个参数类�?  (e: 'add', name: string, reason: string, priority: number): void
}>()

// 触发时依次传入，逗号分隔
emit('add', name.value, reason.value, priority.value)
```

父组件接收（参数顺序要对应）�?```ts
function handleAdd(name: string, reason: string, priority: number) {
  // 三个参数按顺序拿�?}
```

**写法二：打包成对�?*（参数多时用，推荐）

```ts
const emit = defineEmits<{
  (e: 'select', payload: { name: string; reason: string; priority: number }): void
}>()

emit('select', {
  name: name.value,
  reason: reason.value,
  priority: priority.value,
})
```

父组件接收（一个对象参数）�?```ts
function handleSelect(payload: { name: string; reason: string; priority: number }) {
  const { name, reason, priority } = payload   // 解构
}
```

**怎么选？**
- 2~3 个参数：写法一直接传，更简�?- 4 个以�?/ 可能扩展：写法二打包对象，不用记顺序、加字段不破坏老代�?
### 5.4 v-model —�?组件双向绑定

> **对照文件**：`FilterBar.vue`、`HomeView.vue`

**v-model �?props + emit 的语法糖**，专门用�?父子共享一个数�?�?
#### v-model 的本�?
这两段代�?*完全等价**�?
```html
<!-- 简�?-->
<MyInput v-model="text" />
```
```html
<!-- 等价�?-->
<MyInput :modelValue="text" @update:modelValue="text = $event" />
```

**约定**�?- props 属性名固定�?`modelValue`
- emit 事件名固定为 `update:modelValue`

#### 子组件实�?v-model

```vue
<script setup lang="ts">
import type { FilterOptions } from '@/types'

const props = defineProps<{
  modelValue: FilterOptions   // �?接收 modelValue
}>()

const emit = defineEmits<{
  (e: 'update:modelValue', value: FilterOptions): void  // �?声明更新事件
}>()

// �?修改时不能直接改 props，要 emit 通知父组�?function changeBrand(brand: string) {
  emit('update:modelValue', { ...props.modelValue, brand })
}
</script>
```

#### 父组件使�?
```html
<FilterBar v-model="filter" />
```

父组件的 `filter` 变了 �?通过 `modelValue` 传给子组件；
子组件内部点筛�?�?通过 `update:modelValue` 通知父组件更�?`filter`�?
#### 多个 v-model（Vue3 新特性）

一个组件可以有**多个 v-model**，用参数区分�?
```html
<UserForm v-model:name="name" v-model:age="age" />
```

子组件：
```ts
const props = defineProps<{ name: string; age: number }>()
const emit = defineEmits<{
  (e: 'update:name', value: string): void
  (e: 'update:age', value: number): void
}>()
```

### 5.5 slot —�?插槽（内容分发）★★�?
> **对照文件**：`SlotDemo.vue`（专门演示三种插槽）、`HomeView.vue`（使用插槽）、`HotelCard.vue`

#### 5.5.1 插槽是什么？

**一句话**：让父组件往子组件里"塞一段内�?。组件像相框，slot 是相框中间留的空位�?
#### 5.5.2 为什么用插槽而不�?props�?
| | props | slot |
|---|---|---|
| 传什�?| **数据**（字符串/数字/对象�?| **内容/HTML结构** |
| 例子 | `:title="标题"` | `<p>一段说明文�?/p>` |
| 适合 | 简单�?| 复杂结构、可定制布局 |

要传"一�?HTML"时，�?props 很别扭（得传字符串或 render 函数），插槽天生就是为传递内容设计的�?
#### 5.5.3 默认插槽（最简单）

> **对照文件**：`SlotDemo.vue` �?`slot-demo__body`

```vue
<!-- 子组�?Card.vue -->
<template>
  <div class="card">
    <slot />   <!-- �?这里�?空位"，父组件塞的内容会显示在�?-->
  </div>
</template>
```
```html
<!-- 父组�?-->
<Card>
  <p>这段内容会塞�?Card �?<slot /> 位置</p>
</Card>
```

#### 5.5.4 默认内容（fallback�?
`<slot>` 标签里写的内容，�?*父组件没塞东西时**的兜底显示：

```vue
<!-- 子组�?-->
<template>
  <button>
    <slot>确定</slot>   <!-- 父组件不传内容时，默认显�?确定" -->
  </button>
</template>
```
```html
<!-- 父组�?-->
<MyButton />              <!-- 显示 "确定" -->
<MyButton>取消</MyButton>  <!-- 显示 "取消" -->
```

本项�?`SlotDemo.vue` �?header/footer 都用了默认内容：
```html
<slot name="header">
  <h3>📋 酒店信息卡片（默认标题）</h3>   <!-- 父组件没传时显示 -->
</slot>
```

#### 5.5.5 具名插槽（多个空位）

一个组件可能要�?*多个**空位（如 header / body / footer），�?`name` 区分�?
```vue
<!-- 子组�?Layout.vue -->
<template>
  <div>
    <header><slot name="header" /></header>
    <main><slot /></main>              <!-- 没指�?name 的就是默认插�?-->
    <footer><slot name="footer" /></footer>
  </div>
</template>
```
```html
<!-- 父组件：�?#xxx 简写（v-slot:xxx 的简写） -->
<Layout>
  <template #header>
    <h1>标题</h1>
  </template>

  <p>主内容（塞进默认插槽�?/p>

  <template #footer>
    <span>底部</span>
  </template>
</Layout>
```

**`#xxx` �?`v-slot:xxx` 的简�?*，两种等价：
```html
<!-- 简写（推荐�?-->
<template #header>...</template>

<!-- 完整写法 -->
<template v-slot:header>...</template>
```

本项目两个地方用了具名插槽：

�?`HomeView.vue` 给卡片塞底部提示（`#extra`）：
```html
<HotelCard :hotel="hotel">
  <template #extra>
    <span>�?已加入收�?/span>
  </template>
</HotelCard>
```

�?`HomeView.vue` �?SlotDemo 时塞了多个具名插槽（`#header` / `#footer`）：
```html
<SlotDemo :hotels="filteredHotels">
  <template #header><h3>自定义标�?/h3></template>
  <template #footer><span>自定义页�?/span></template>
</SlotDemo>
```

#### 5.5.6 作用域插槽（子组件向父组件传数据）★�?
**最难但最有用**。子组件把数�?�?给父组件，让父组件决�?*怎么渲染每一�?*�?
> **对照文件**：`SlotDemo.vue` �?`slot-demo__list`、`HomeView.vue` �?`#item`

**子组�?*：用 `<slot :xxx="数据" />` 把数据暴露出�?```vue
<template>
  <ul>
    <li v-for="h in hotels" :key="h.id">
      <!-- �?hotel 数据暴露给使用插槽的父组�?-->
      <slot name="item" :hotel="h" :index="h.id" />
    </li>
  </ul>
</template>
```

**父组�?*：用 `#名字="{ 解构 }"` 接收子组件暴露的数据
```html
<SlotDemo :hotels="filteredHotels">
  <template #item="{ hotel }">
    <!-- 这里能用到子组件传来�?hotel 数据 -->
    <strong>{{ hotel.name }}</strong>
    <span>¥{{ hotel.price }}</span>
  </template>
</SlotDemo>
```

**本质**：数据是子组件的，但**渲染方式**由父组件决定。子组件负责"有什么数�?，父组件负责"怎么显示"�?
**典型应用场景**�?- 列表组件（如 `<DataTable>`）：子组件提供数据，父组件决定每行长啥样
- 通用弹窗：子组件提供开关逻辑，父组件决定弹窗内容

#### 5.5.7 三种插槽速查�?
| 类型 | 子组件写�?| 父组件写�?| 用�?|
|---|---|---|---|
| 默认插槽 | `<slot />` | `<Card>内容</Card>` | 塞一段内�?|
| 默认内容 | `<slot>默认�?/slot>` | 不传时显示默认�?| 兜底 |
| 具名插槽 | `<slot name="x" />` | `<template #x>...</template>` | 多个空位 |
| 作用域插�?| `<slot :data="x" />` | `<template #x="{ data }">` | 子传父数�?|

#### 5.5.8 完整对照练习

打开 `SlotDemo.vue` �?*子组件怎么定义**三种插槽，再打开 `HomeView.vue` �?`SlotDemo` �?*父组件怎么�?*，对照下表：

| 子组件（SlotDemo.vue�?| 父组件（HomeView.vue�?|
|---|---|
| `<slot name="header">默认</slot>` | `<template #header>...</template>` |
| `<slot>默认</slot>` | 直接写在标签里的内容 |
| `<slot name="item" :hotel="h" />` | `<template #item="{ hotel }">...</template>` |
| `<slot name="footer">默认</slot>` | `<template #footer>...</template>` |

### 5.6 组件通信方式总结

| 方向 | 方式 | 例子 |
|---|---|---|
| �?�?�?| **props** | `<HotelCard :hotel="h" />` |
| �?�?�?| **emit** | `<SearchBar @search="fn" />` |
| �?�?�?| **v-model** | `<FilterBar v-model="filter" />` |
| �?�?子（内容�?| **slot** | `<Card><p>内容</p></Card>` |
| 跨组�?全局 | **composable**（见�?章） | `useFavorites()` |
| 跨组�?全局 | provide / inject | 祖先 provide，后�?inject |

**3 句口诀**�?1. 父传�?�?`props`
2. 子传�?�?`emit`
3. 跨组件共�?�?`composable`

### 5.7 provide / inject（补充）

适合"祖先组件 �?深层后代组件"传值，不用层层 props�?
```ts
// 祖先组件
import { provide, ref } from 'vue'
const theme = ref('dark')
provide('theme', theme)        // 提供数据

// 后代组件（不管嵌套多深）
import { inject } from 'vue'
const theme = inject('theme', 'light')   // 取数据，第二个参数是默认�?```

> ⚠️ 大型项目状态管理建议用 **Pinia**（官方推荐的状态库），provide/inject 适合简单场景�?
---

## 6. 路由 vue-router

> **对照文件**：`router/index.ts`、`App.vue`、`AppHeader.vue`、`HomeView.vue`、`HotelDetailView.vue`

### 6.1 什么是路由�?
**传统网站**：点链接 �?浏览器整页刷�?�?服务器返回新 HTML�?**Vue 单页应用(SPA)**：点链接 �?JS 拦截 �?**只换页面里的一块内�?*，浏览器地址栏变了但不刷新，体验更流畅�?
vue-router 管理"**地址(URL) �?页面组件**"的对应关系�?
### 6.2 安装与注�?
```bash
npm install vue-router
```

�?`main.ts` 注册�?```ts
import { createApp } from 'vue'
import App from './App.vue'
import router from './router'

const app = createApp(App)
app.use(router)        // �?关键：注册路由插�?app.mount('#app')
```

注册后，整个应用就能�?`<router-view>` �?`<router-link>` 了�?
### 6.3 配置路由�?
> **对照文件**：`router/index.ts`

```ts
import { createRouter, createWebHistory } from 'vue-router'

export const router = createRouter({
  // history 模式：URL 长这�?/detail/3（不�?#�?  // 另一�?hash 模式：URL 长这�?/#/detail/3（兼容性好但难看）
  history: createWebHistory(),

  routes: [
    {
      path: '/',                    // 浏览器地址
      name: 'home',                 // 路由名字
      component: () => import('@/views/HomeView.vue'),  // 懒加�?    },
    {
      // 【动态路由�?id 是占位符，匹�?/detail/1�?detail/2...
      path: '/detail/:id',
      name: 'detail',
      component: () => import('@/views/HotelDetailView.vue'),
    },
  ],
})
```

**路由对象字段说明**�?
| 字段 | 作用 | 例子 |
|---|---|---|
| `path` | URL 路径 | `/`、`/detail/:id` |
| `name` | 路由名字（可选但推荐�?| `'home'` |
| `component` | 对应的页面组�?| `HomeView` |
| `redirect` | 重定�?| `redirect: '/'` |
| `children` | 嵌套路由 | 子路由数�?|

#### 懒加载为什么重要？

```ts
// �?懒加载：第一次访问该页面时才下载代码
component: () => import('@/views/HotelDetailView.vue')

// �?立即加载：不管访不访问，都打包进首页
import HotelDetailView from '@/views/HotelDetailView.vue'
component: HotelDetailView
```

好处：首页打开更快（不用一次性下载所有页面）。大项目必用�?
### 6.4 `<router-view>` —�?路由出口

> **对照文件**：`App.vue`

```html
<template>
  <AppHeader />
  <!-- 路由匹配到的页面会渲染到这里 -->
  <router-view />
  <footer>...</footer>
</template>
```

可以理解为：`<router-view />` 是个"占位�?，访�?`/` 时它变成首页，访�?`/detail/1` 时它变成详情页�?
### 6.5 `<router-link>` —�?声明式导�?
> **对照文件**：`AppHeader.vue`、`RecommendSidebar.vue`

```html
<!-- 基本用法 -->
<router-link to="/">首页</router-link>
<router-link to="/favorites">收藏</router-link>

<!-- 对象写法（推荐，更灵活） -->
<router-link :to="{ name: 'detail', params: { id: 1 } }">
  详情
</router-link>

<!-- 带查询参�?-->
<router-link :to="{ path: '/list', query: { city: '深圳' } }">
  <!-- URL 变成 /list?city=深圳 -->
</router-link>
```

渲染后就是个 `<a>` 标签，但点击**不会整页刷新**�?
**激�?class**：当前正在的页面，对应的 router-link 会自动加�?class�?- `router-link-active`：匹配当前路由（包含子路径）
- `router-link-exact-active`：精确匹配当前路�?
利用这个做导航高亮：
```css
.router-link-exact-active {
  color: var(--color-primary);
  font-weight: 600;
}
```

### 6.6 编程式导航（JS 里跳转）

> **对照文件**：`HomeView.vue` �?`handleDetail`、`HotelDetailView.vue` �?`goBack`

```ts
import { useRouter } from 'vue-router'
const router = useRouter()

// push：跳转（会在浏览器历史里留下记录，能后退�?router.push('/favorites')
router.push({ name: 'detail', params: { id: 1 } })
router.push({ path: '/list', query: { city: '深圳' } })

// replace：替换（不留记录，不能后退到当前页�?router.replace('/login')

// 前进/后退
router.back()       // 后退
router.forward()    // 前进
router.go(-1)       // 后退一步（等价 back�?router.go(2)        // 前进两步
```

**push vs replace**�?- `push`：A→B，按后退能回�?A（常用）
- `replace`：A→B，按后退回不�?A（登录跳转后常用，避免后退回登录页�?
### 6.7 读取路由参数

> **对照文件**：`HotelDetailView.vue`

```ts
import { useRoute } from 'vue-router'
const route = useRoute()

// 当前地址�?/detail/42?from=home

route.path        // '/detail/42'         完整路径
route.params.id   // '42'                 动态路由参数（:id�?route.query.from  // 'home'               查询参数�?xxx�?route.name        // 'detail'             路由名字
route.fullPath    // '/detail/42?from=home'
```

**注意区分**�?- `useRouter()` �?拿到路由**实例**，用�?*跳转**（push/back�?- `useRoute()` �?拿到当前路由**信息**，用�?*读取**当前地址

> ⚠️ `route.params.id` 永远�?string 类型！用时记�?`Number(route.params.id)` 转换�?
### 6.8 动态路由参数监�?
```ts
import { watch } from 'vue'
import { useRoute } from 'vue-router'

const route = useRoute()

// 在同一个页面组件里，从 /detail/1 跳到 /detail/2，组件不会重�?// 如果需要响�?id 变化，要 watch
watch(
  () => route.params.id,
  (newId) => {
    console.log('id 变了�?, newId)
    // 重新请求数据...
  },
)
```

### 6.9 完整实战：路由教学详情页 ★★�?
> **对照文件**：`RouteInfoView.vue`（详情页）、`router/index.ts`（路由配置）、`HomeView.vue`（跳转入口）

前面几节是零散的知识点，这一节把它们串起来，做一�?*完整闭环**�?**点击列表里的酒店 �?跳到详情�?�?显示该酒店信�?�?点返回回到列�?*�?
#### 6.9.1 第一步：配置路由（带动态参数）

`router/index.ts`�?```ts
{
  // :id 是动态参数占位符
  path: '/route-info/:id',
  name: 'route-info',
  component: () => import('@/views/RouteInfoView.vue'),
}
```

#### 6.9.2 第二步：列表页发起跳转（传参�?
`HomeView.vue` —�?�?`router.push` 跳转，把酒店 id 作为参数传过去：
```ts
function goToRouteInfo(id: number) {
  router.push({ name: 'route-info', params: { id } })
  // 跳转后地址栏变�?/route-info/3
}
```

模板里绑定到按钮�?```html
<button @click="goToRouteInfo(hotel.id)">🚀 路由教学详情�?/button>
```

#### 6.9.3 第三步：详情页接收参�?+ 显示数据

`RouteInfoView.vue` —�?�?`useRoute()` 读取传过来的 id�?```ts
import { useRoute, useRouter } from 'vue-router'
import { hotelList } from '@/data/mockData'

const route = useRoute()

// ⚠️ route.params.id 永远是字符串！用 Number() 转换
const hotelId = Number(route.params.id)

// 根据 id 查酒�?const hotel = computed(() => hotelList.find((h) => h.id === hotelId))
```

```html
<div v-if="hotel">
  <h1>{{ hotel.name }}</h1>
  <p>¥{{ hotel.price }} /�?/p>
</div>
<div v-else>
  找不�?id = {{ hotelId }} 的酒�?</div>
```

#### 6.9.4 第四步：返回上一�?
`RouteInfoView.vue`�?```ts
const router = useRouter()

// 方式一：浏览器后退（最常用�?function goBack() {
  router.back()
}

// 方式二：跳回首页（没有历史记录时也能用，更稳妥）
function goHome() {
  router.push({ name: 'home' })
}
```

#### 6.9.5 ⚠️ 新手最容易踩的�?
**�?1：`route` �?`router` 写混**

```ts
import { useRoute, useRouter } from 'vue-router'

const route = useRoute()    // 读信息（名词）—�?route.params.id
const router = useRouter()  // 做动作（动词）—�?router.push / router.back
```
记忆�?*route 是名�?那条路由"，router 是动�?去路�?**�?
**�?2：`route.params.id` 是字符串**

```ts
const id = route.params.id   // "3"（字符串！）
const hotel = list.find(h => h.id === Number(id))   // �?要转 number
```
即使你在 `router.push({ params: { id: 3 } })` 传的是数字，拿出来还是字符串�?
**�?3：`router.back()` 可能没反�?*

如果用户�?*直接打开** `/route-info/3`（比如复制链接到新标签页），就没有历史记录，`back()` 不会跳。所以重要入口建议用 `router.push({ name: 'home' })` �?`<router-link to="/">`�?
**�?4：同组件�?id 变化不触发重�?*

�?`/route-info/1` 跳到 `/route-info/2`�?*组件不会重建**（同一个页面复用）。如果需要在 id 变化时重新发请求，要 watch�?```ts
watch(() => route.params.id, (newId) => {
  // id 变了，重新加载数�?})
```

#### 6.9.6 整个流程的时�?
```
用户点首�?🚀 路由教学详情�?按钮
    �?    �?goToRouteInfo(3) 执行
    �?    �?router.push({ name: 'route-info', params: { id: 3 } })
    �?    �?地址栏变�?/route-info/3
    �?    �?<router-view> �?RouteInfoView 渲染出来
    �?    �?RouteInfoView �?route.params.id === "3"
    �?    �?hotelList.find(h => h.id === 3) 查到酒店
    �?    �?页面显示该酒店信�?    �?    �?用户�?�?返回上一�?
    �?    �?router.back() �?回到首页列表
```

### 6.10 跳转方式：path vs name

> **对照文件**：`HomeView.vue` 的「路由跳�?& 传参演示」区（按�?�?②）

跳转有两种定位目标的方式�?
#### �?path 跳转（直接写地址�?
```ts
// 字符串形�?router.push('/route-param-demo')

// 对象形式 + path
router.push({ path: '/route-param-demo' })
```

#### �?name 跳转（推荐）

```ts
router.push({ name: 'route-param-demo' })
```

#### path vs name 怎么选？

| | path | name |
|---|---|---|
| 写法 | `'/route-param-demo'` | `{ name: 'xxx' }` |
| 依赖 | 地址字符�?| 路由配置里的 `name` 字段 |
| 改地址�?| 所有写 path 的地方都要改 | **不受影响**（name 没变�?|
| 拼错�?| 静默失败（跳到空页面�?| **运行时报�?*（容易发现） |
| 能否�?params | �?不能 | �?能（�?6.11�?|
| 推荐 | 简单页�?| **推荐**（安全、解耦） |

> 💡 **经验**：需要传 params �?*必须**�?name；其他场景也建议优先 name，改地址不影响跳转逻辑�?
### 6.11 三种传参方式：query / params / state ★★�?
> **对照文件**：`HomeView.vue` 的按�?③④�?�?`RouteParamDemoView.vue`（接收页�?
这是本章重点。三种方式各有适用场景，区别如下：

#### �?query —�?地址�?`?` 后面

```ts
router.push({
  path: '/route-param-demo',     // query 可以配合 path �?name
  query: { city: '深圳', star: 5 },
})
// 跳转后地址�?route-param-demo?city=深圳&star=5
```

**接收�?*�?```ts
route.query.city   // '深圳'（string | string[] | null�?route.query.star   // '5'（注意是字符串）
```

#### �?params —�?路径里的动态段 `:id`

```ts
router.push({
  name: 'route-info',     // ⚠️ params 必须配合 name，不能用 path�?  params: { id: 3 },
})
// 跳转后地址�?route-info/3
```

**接收�?*�?```ts
route.params.id   // '3'（字符串�?```

**前提**：路由配置里必须先定义动态段�?```ts
{ path: '/route-info/:id', name: 'route-info', component: ... }
```

#### �?state —�?不在地址栏（隐藏�?
```ts
router.push({
  path: '/route-param-demo',
  state: { from: 'home', note: '这是不显示在 URL 的数�? },
})
// 跳转后地址�?route-param-demo（看不到 state�?```

**接收�?*（用浏览器原�?API）：
```ts
history.state.state   // { from: 'home', note: '...' }
```

#### �?三种方式对比�?
| | query | params | state |
|---|---|---|---|
| **位置** | 地址�?`?` 后面 | 路径�?`:xxx` | 不在地址�?|
| **地址栏可�?* | �?可见 | �?可见 | �?不可�?|
| **刷新�?* | �?保留 | �?保留 | �?**丢失** |
| **可分�?收藏** | ✅（URL 含参数） | ✅（URL 含参数） | ❌（别人拿不到） |
| **�?path 还是 name** | 都行 | **必须 name** | 都行 |
| **需要路由预定义** | 不用 | **�?*（定�?`:xxx`�?| 不用 |
| **适合场景** | 筛选、搜索词、页�?| 详情�?id | 临时提示、隐藏数�?|

> 💡 **选型口诀**�?> - 想让别人能通过 URL 访问�?�?**query �?params**
> - 数据�?这条路由的身�?（如 id�?�?**params**
> - 数据�?筛选条�? �?**query**
> - 数据不想暴露、且刷新丢也没关�?�?**state**

### 6.12 replace —�?不留历史记录的跳�?
```ts
// push：会进历史栈，能�?后退"回到当前�?router.push('/page-b')

// replace：替换当前历史记录，不能后退回来
router.replace('/page-b')
```

**什么时候用 replace�?*
- 登录后跳首页（避免后退回登录页�?- 表单提交后跳结果页（避免后退重复提交�?
### 6.13 路由额外信息：meta（元数据�?
> **对照文件**：`router/index.ts` �?`meta` 字段 + `beforeEach` 守卫

每条路由可以挂任意自定义信息，放�?`meta` 里：

```ts
{
  path: '/favorites',
  name: 'favorites',
  component: () => import('@/views/FavoritesView.vue'),
  meta: {
    title: '我的收藏',        // 页面标题
    requiresAuth: true,       // 是否需要登�?    // 可以加任何字段：icon、menuVisible、permission...
  },
}
```

#### 读取 meta

```ts
import { useRoute } from 'vue-router'
const route = useRoute()

route.meta.title         // '我的收藏'
route.meta.requiresAuth  // true
```

#### 典型用途：全局前置守卫

> **对照文件**：`router/index.ts` 末尾�?`router.beforeEach`

```ts
router.beforeEach((to, _from) => {
  // �?自动设置页面标题
  if (to.meta.title) {
    document.title = `${to.meta.title} · 差旅通`
  }

  // �?登录拦截：需要登录但没登录就重定�?  const isLoggedIn = false   // 真实项目�?store �?  if (to.meta.requiresAuth && !isLoggedIn) {
    return { name: 'home' }   // 重定向到首页（或登录页）
  }
})
```

`beforeEach` �?*每次跳转�?*执行，返�?false 或一个路由地址可以**拦截/重定�?*。这是做权限控制的标准方式�?
### 6.14 路由总结�?
| 需�?| 写法 |
|---|---|
| 配置地址↔页�?| `routes: [{ path, component }]` |
| 页面放哪 | `<router-view />` |
| 链接跳转 | `<router-link to="...">` |
| JS 跳转（path�?| `router.push('/xxx')` |
| JS 跳转（name�?| `router.push({ name: 'xxx' })` |
| �?query | `push({ query: { k: v } })` �?�?`route.query.k` |
| �?params | `push({ name, params: { id } })` �?�?`route.params.id` |
| �?state | `push({ path, state: {...} })` �?�?`history.state.state` |
| 不留历史 | `router.replace(...)` |
| 路由额外信息 | `meta: { title, requiresAuth }` �?�?`route.meta.xxx` |
| 权限拦截 | `router.beforeEach` |
| 完整实战 | `HomeView` 的「路由跳转演示」→ `RouteParamDemoView.vue` |

---

## 7. 逻辑复用：Composables（组合式函数�?
> **对照文件**：`composables/useFavorites.ts`

### 7.1 什么是 Composable�?
一�?*�?`use` 开头的函数**，里面封装了「响应式数据 + 操作方法」，可以在任意组件里复用�?
这是 Vue3 官方推荐�?*逻辑复用方式**�?
### 7.2 为什么要它？

考虑"收藏功能"�?- 首页有收藏按�?- 详情页要显示收藏状�?- 收藏页要列出所有收�?
如果每个组件各自维护一份收藏数据，�?**各管各的、不同步**"。所以要把数据抽出来，让所有组�?*共享同一�?*�?
### 7.3 怎么写一�?Composable�?
> **对照文件**：`useFavorites.ts`

```ts
import { ref, computed } from 'vue'
import type { Hotel } from '@/types'

// �?关键：把共享数据定义在函数【外面】（模块级单例）
const favoriteList = ref<Hotel[]>([])

// use 开头的函数
export function useFavorites() {
  // computed：派生数�?  const favoriteCount = computed(() => favoriteList.value.length)

  // 方法
  const isFavorite = (id: number) =>
    favoriteList.value.some((h) => h.id === id)

  function toggleFavorite(hotel: Hotel) {
    if (isFavorite(hotel.id)) {
      favoriteList.value = favoriteList.value.filter((h) => h.id !== hotel.id)
    } else {
      favoriteList.value = [...favoriteList.value, hotel]
    }
  }

  // 把要暴露的东�?return 出去
  return {
    favoriteList,
    favoriteCount,
    isFavorite,
    toggleFavorite,
  }
}
```

### 7.4 怎么用？

```ts
// 在任意组件里
import { useFavorites } from '@/composables/useFavorites'

const { favoriteList, favoriteCount, toggleFavorite } = useFavorites()

// 当作普通变�?函数�?console.log(favoriteCount.value)     // 收藏数量
toggleFavorite(hotel)                // 切换收藏
```

**所有调用了 `useFavorites()` 的组件，共享同一�?`favoriteList`**（因为是模块级的）�?
### 7.5 为什么数据要定义在函数外面？

```ts
// �?数据在函数里面：每次调用都创建新数据，组件间不共�?export function useFavorites() {
  const favoriteList = ref([])   // �?每次调用都是新的�?  return { favoriteList }
}

// �?数据在函数外面：模块级单例，所有组件共�?const favoriteList = ref([])     // �?模块加载时创建一�?export function useFavorites() {
  return { favoriteList }
}
```

> 💡 如果你不想要共享（每次都独立的数据），就放函数里面。看需求�?
### 7.6 Composable vs Pinia

| | Composable | Pinia |
|---|---|---|
| 复杂�?| 简单，就是普通函�?| 独立的状态库 |
| 适合 | 中小项目、局部共�?| 大型项目、全局状�?|
| 学习成本 | �?| �?|
| 调试工具 | �?| �?Vue Devtools 集成 |

> 💡 本项�?*两种方案都用�?*�?> - AppHeader / 收藏页等�?composable（`composables/useFavorites.ts`�?> - PiniaDemo 演示组件�?Pinia（`stores/favoriteStore.ts`�?>
> 对照看，理解差异 �?详见下一�?**[�?8 �?Pinia](#8-状态管理pinia)**�?
---

## 8. 状态管理：Pinia ★★�?
> **对照文件**：`stores/favoriteStore.ts`（store 定义）、`components/PiniaDemo.vue`（使用）、`main.ts`（注册）
> 这一章和�?7 章是**姊妹�?*——同一�?收藏"功能，第 7 章用 composable 实现，本章用 Pinia 实现，对照看更易理解�?
### 8.1 为什么需要状态管理库�?
�?7 章我们用 **composable** 实现了跨组件状态共享：把数据定义在函数外面（模块级单例）�?
这在**小项�?*里很好用，但项目变大后会暴露问题�?
| 问题 | 说明 |
|---|---|
| 没有结构化组�?| 功能多了，一�?`useXxx` 散落各处，难�?|
| 调试困难 | 改了数据没法回放、没�?时光旅行" |
| 无统一 API | 每个 composable 写法可能不一�?|
| 难扩�?| 数据持久化、SSR、模块化都要自己造轮�?|

**Pinia** �?Vue3 官方推荐的状态管理库，专门解决这些问题。它�?Vuex 的继任者（Vuex 已停止维护）�?
### 8.2 Pinia 是什么？核心概念

| 概念 | 类比组件里的 | 说明 |
|---|---|---|
| **Store** | —�?| 一个全局"仓库"，存放某类共享数�?|
| **State** | `data` / `ref` | 仓库里的数据 |
| **Getters** | `computed` | �?state 派生出的数据（只读） |
| **Actions** | `methods` | 修改 state 的方�?|

一句话�?*Store = 全局共享的组�?*（只是没�?template �?style）�?
### 8.3 安装与注�?
```bash
npm install pinia
```

�?`main.ts` 注册（必须在 `app.mount()` 之前）：
```ts
import { createApp } from 'vue'
import { createPinia } from 'pinia'
import App from './App.vue'

const app = createApp(App)
app.use(createPinia())   // �?注册 Pinia
app.mount('#app')
```

注册后，整个应用里的组件就能�?`useXxxStore()` 拿到 store 了�?
### 8.4 定义 Store —�?两种写法

> **对照文件**：`stores/favoriteStore.ts`

#### 写法一：Setup Store（组合式，★ 推荐�?
�?`<script setup>` 写法几乎一样：

```ts
import { defineStore } from 'pinia'
import { ref, computed } from 'vue'
import type { Hotel } from '@/types'

// defineStore('唯一名字', 定义函数)
export const useFavoriteStore = defineStore('favorite', () => {
  // ===== state：用 ref 定义 =====
  const list = ref<Hotel[]>([])

  // ===== getters：用 computed 定义 =====
  const count = computed(() => list.value.length)

  // ===== actions：用普通函数定�?=====
  function isFavorite(id: number): boolean {
    return list.value.some((h) => h.id === id)
  }
  function toggle(hotel: Hotel) {
    if (isFavorite(hotel.id)) {
      list.value = list.value.filter((h) => h.id !== hotel.id)
    } else {
      list.value = [...list.value, hotel]
    }
  }
  function clear() {
    list.value = []
  }

  // �?关键：return 出去的才是对外暴露的
  return { list, count, isFavorite, toggle, clear }
})
```

#### 写法二：Options Store（选项式，了解�?
结构�?`state` / `getters` / `actions` 三个固定字段�?
```ts
export const useFavoriteStore = defineStore('favorite', {
  state: () => ({
    list: [] as Hotel[],
  }),
  getters: {
    count: (state) => state.list.length,
  },
  actions: {
    isFavorite(id: number): boolean {
      return this.list.some((h) => h.id === id)
    },
    toggle(hotel: Hotel) {
      if (this.isFavorite(hotel.id)) {
        this.list = this.list.filter((h) => h.id !== hotel.id)
      } else {
        this.list.push(hotel)    // Options 写法可以�?this.list.push
      }
    },
    clear() {
      this.list = []
    },
  },
})
```

#### 两种写法怎么选？

| | Setup Store | Options Store |
|---|---|---|
| 风格 | �?`<script setup>` 一�?| �?Vue2 �?data/methods |
| 私有成员 | �?return 就是私有 | 都得写在固定字段�?|
| TS 支持 | �?| 一�?|
| 推荐 | �?**推荐** | 了解即可 |

> 💡 本项�?`stores/favoriteStore.ts` 默认用的�?Setup Store（Options 版写成了注释保留）�?
### 8.5 在组件里使用 Store

> **对照文件**：`components/PiniaDemo.vue`

```ts
import { useFavoriteStore } from '@/stores/favoriteStore'

// 调用 useFavoriteStore() 拿到 store 实例
const favoriteStore = useFavoriteStore()

// 用法 A：直接通过 store.xxx 访问（最简单）
favoriteStore.count              // �?state/getter
favoriteStore.toggle(hotel)      // �?action
favoriteStore.isFavorite(id)     // �?action
```

#### ⚠️ 解构 store 的坑：要�?`storeToRefs`

```ts
import { storeToRefs } from 'pinia'

// �?直接解构 state/getter：会丢失响应式！
const { count, list } = favoriteStore

// �?正确：用 storeToRefs 解构 state �?getter
const { count, list } = storeToRefs(favoriteStore)

// �?action（方法）可以直接解构，没有响应式问题
const { toggle, clear } = favoriteStore
```

**为什么？** Pinia store 内部�?reactive 实现，解构出来的原始值会脱离响应式。`storeToRefs` 会把 state/getter 包成 ref，保持响应式�?
### 8.6 Pinia 的特�?API

> **对照文件**：`PiniaDemo.vue` 里的演示按钮

#### `$patch` —�?批量修改 state

```ts
// 对象写法
favoriteStore.$patch({ count: 5, name: '张三' })

// 函数写法（推荐，能改嵌套�?favoriteStore.$patch((state) => {
  state.list = [hotel1, hotel2]
  state.lastUpdate = Date.now()
})
```

好处：一次修改多�?state�?*只触发一次更�?*，比连续调多�?action 性能好�?
#### `$reset` —�?重置为初始状�?
```ts
favoriteStore.$reset()   // state 回到定义时的初始�?```

> ⚠️ 这个方法只有 **Options Store** �?Setup Store 都支持，�?Setup Store 需�?Pinia 2.2+�?
#### `$subscribe` —�?订阅 state 变化（类�?watch�?
```ts
// state 变化时触发，返回一个取消订阅的函数
const unsubscribe = favoriteStore.$subscribe((mutation, state) => {
  console.log('state 变了，当前收藏数�?, state.list.length)
})

// 不再需要时取消订阅（防止内存泄漏）
unsubscribe()
```

#### `$onAction` —�?订阅 action 调用

```ts
const unsubscribe = favoriteStore.$onAction(({ name, args, after, onError }) => {
  console.log(`调用�?${name} 方法，参数：`, args)
  after((result) => console.log(`${name} 执行完毕，返回：`, result))
  onError((error) => console.error(`${name} 出错了：`, error))
})
```

### 8.7 Pinia vs Composable 对比（本项目两种方案都在用）

本项�?*故意同时保留两套方案**，方便学员对照：

| | Composable（`useFavorites.ts`�?| Pinia（`favoriteStore.ts`�?|
|---|---|---|
| 用在�?| AppHeader / HomeView / 各页 | PiniaDemo.vue（教学对比） |
| 实现单例 | 手写：数据定义在函数�?| 自动：defineStore 内部处理 |
| 代码�?| �?| 稍多（要 return 全部�?|
| Devtools | �?�?| �?有（Vue Devtools 可看 state�?|
| $reset | �?要自己写 | �?自带 |
| $patch | �?要自己写 | �?自带 |
| $subscribe | �?要用 watch | �?自带 |
| 适合 | 小项目、局部共�?| 中大型项目、全局状�?|

**组件里用法对�?*�?
```ts
// ===== Composable 方案 =====
import { useFavorites } from '@/composables/useFavorites'
const { favoriteCount, toggleFavorite } = useFavorites()
toggleFavorite(hotel)
favoriteCount.value          // ref，要 .value

// ===== Pinia 方案 =====
import { useFavoriteStore } from '@/stores/favoriteStore'
const favoriteStore = useFavoriteStore()
favoriteStore.toggle(hotel)
favoriteStore.count          // 自动解包，不�?.value
```

### 8.8 什么时候该�?Pinia�?
| 场景 | 推荐 |
|---|---|
| 只在 2~3 个相邻组件间共享简单数�?| **composable** �?props |
| 登录状态、用户信息、权�?| **Pinia** |
| 购物车、全局主题、多标签�?| **Pinia** |
| 需要数据持久化（localStorage�?| **Pinia** + 插件 |
| 需�?SSR（服务端渲染�?| **Pinia** |

> 💡 **经验法则**：如果一个状态会�?*多个不相关的组件**用到，或者需�?*调试/持久�?*，就�?Pinia�?
### 8.9 安装 Vue Devtools 调试 Pinia

1. 装浏览器插件 [Vue.js devtools](https://devtools.vuejs.org/)
2. 打开开发者工具，切到 "Pinia" 标签�?3. 能看到所�?store �?state/getter，还�?*实时编辑**�?*时间旅行**

这是 composable 做不到的，也�?Pinia 在大型项目里的核心优势�?
---

---

## 9. 接口请求：axios（封�?+ 拦截器）

> **对照文件**：`api/request.ts`（封装实例）、`api/hotel.ts`（业务接口）、`vite.config.ts`（代理）
> 项目里的页面目前用的�?`mockData.ts` 假数据，这一章演示「真实项目」里怎么请求后端�?
### 11.1 axios 是什么？为什么用它？

**axios** 是最流行�?HTTP 请求库，用来在前端调后端接口�?
浏览器原生有 `fetch`，为什么还要用 axios�?
| 能力 | fetch（原生） | axios |
|---|---|---|
| 请求/响应拦截�?| �?要自己�?| �?内置 |
| 自动 JSON 转换 | 要手�?`.json()` | �?自动 |
| 请求超时控制 | 要用 AbortController | �?`timeout: 10000` |
| 取消请求 | 复杂 | �?内置 CancelToken |
| 错误处理 | HTTP 4xx/5xx �?reject | �?自动 reject |
| 并发请求 | �?| �?`axios.all` |

> 💡 简单场�?fetch 够用；真实项目推�?axios（尤其需要拦截器、统一错误处理时）�?
### 11.2 安装

```bash
npm install axios
```

### 11.3 不封装直接用（了解，不推荐）

```ts
import axios from 'axios'

const res = await axios.get('http://localhost:8080/hotels')
const list = res.data   // 还要手动�?.data
```

**缺点**：每个请求都要写完整地址、手动取 `.data`、没有统一错误处理�?
### 11.4 封装请求实例（★ 推荐做法�?
> **对照文件**：`api/request.ts`

真实项目都会封装一个统一的请求实例，处理这些公共逻辑�?
```ts
// api/request.ts
import axios, { type AxiosInstance, type AxiosResponse } from 'axios'

// 后端统一返回结构（按你们后端实际结构调整�?export interface ApiResult<T = unknown> {
  code: number
  data: T
  message: string
}

// �?创建实例
const service: AxiosInstance = axios.create({
  baseURL: '/api',           // 公共前缀，配�?vite 代理
  timeout: 10000,            // 10 秒超�?  headers: { 'Content-Type': 'application/json' },
})

// �?请求拦截器：发请求前自动�?token
service.interceptors.request.use((config) => {
  const token = localStorage.getItem('token')
  if (token) config.headers.Authorization = `Bearer ${token}`
  return config
})

// �?响应拦截器：统一解包数据 + 错误处理
service.interceptors.response.use((response: AxiosResponse<ApiResult>) => {
  const res = response.data
  if (res.code !== 200) {
    console.error(`[接口错误] ${res.message}`)
    if (res.code === 401) {
      // token 过期，清掉并跳登�?      localStorage.removeItem('token')
    }
    return Promise.reject(new Error(res.message))
  }
  // �?成功：只返回 data 字段（解包）
  return res.data as unknown as AxiosResponse
})

// �?导出统一方法
export const request = {
  get:  <T>(url: string, config?) => service.get(url, config),
  post: <T>(url: string, data?)   => service.post(url, data),
  put:  <T>(url: string, data?)   => service.put(url, data),
  delete: <T>(url: string)        => service.delete(url),
}
```

### 11.5 拦截器详解（最重要�?
拦截器是 axios 封装的核心，理解它就理解了为什么要封装�?
```
组件�?request.get('/hotels')
        �?        �?【请求拦截器】发出去之前：加 token、加 loading
        �?        �?   发到后端 ────────�?后端返回 { code:200, data:[...], message:'ok' }
        �?        �?【响应拦截器】回来之后：
   - code===200  �?取出 data 返回给组�?   - code!==200  �?报错提示
   - code===401  �?�?token 跳登�?        �?        �?   组件拿到干净�?Hotel[] 数据
```

| 拦截�?| 时机 | 典型用�?|
|---|---|---|
| `request.use` | 请求**发出�?* | �?token、显�?loading、改参数 |
| `response.use` | 响应**回来�?* | 解包数据、统一报错�?01 跳登�?|

> 💡 没有拦截器的话，上面这些逻辑每个接口都要重写一遍；有了拦截器，**写一次全局生效**�?
### 9.6 写业务接�?
> **对照文件**：`api/hotel.ts`

封装好后，写业务接口非常清爽�?
```ts
// api/hotel.ts
import { request } from './request'
import type { Hotel } from '@/types'

// GET 列表（泛�?<Hotel[]> 让返回值有类型提示�?export function fetchHotelList(): Promise<Hotel[]> {
  return request.get<Hotel[]>('/hotels')
}

// GET 详情（路径参数用模板字符串拼�?export function fetchHotelDetail(id: number): Promise<Hotel> {
  return request.get<Hotel>(`/hotels/${id}`)
}

// GET 搜索（query 参数�?params，自动拼�??city=深圳&star=5�?export function searchHotels(params: { city?: string; star?: number }) {
  return request.get<Hotel[]>('/hotels', { params })
}

// POST 新增（第二个参数是请求体�?export function addFavorite(hotelId: number) {
  return request.post('/favorites', { hotelId })
}

// DELETE 删除
export function removeFavorite(hotelId: number) {
  return request.delete(`/favorites/${hotelId}`)
}

// PUT 更新
export function updateHotel(id: number, data: Partial<Hotel>) {
  return request.put<Hotel>(`/hotels/${id}`, data)
}
```

### 9.7 四种请求方法对照

| 方法 | 用�?| 例子 | 参数位置 |
|---|---|---|---|
| **GET** | 获取数据 | 查列表、查详情 | query（`params`）或路径 |
| **POST** | 新增数据 | 收藏、提交表�?| body（第二个参数�?|
| **PUT** | 更新数据 | 改酒店信�?| body + 路径 id |
| **DELETE** | 删除数据 | 取消收藏 | 路径 id |

**GET 传参的两种方�?*�?
```ts
// 方式一：query 参数（params 字段，自动拼 ?xxx=yyy�?request.get('/hotels', { params: { city: '深圳', star: 5 } })
// 实际请求�?hotels?city=深圳&star=5

// 方式二：路径参数（模板字符串拼）
request.get(`/hotels/${id}`)
// 实际请求�?hotels/3
```

### 9.8 在组件里调用

```ts
import { onMounted, ref } from 'vue'
import { fetchHotelList, addFavorite } from '@/api/hotel'
import type { Hotel } from '@/types'

const list = ref<Hotel[]>([])
const loading = ref(false)

// 页面加载时请求数�?onMounted(async () => {
  loading.value = true
  try {
    list.value = await fetchHotelList()   // 直接拿到 Hotel[]
  } catch (e) {
    // 错误已在 request.ts 拦截器里统一提示了，这里只需处理业务（如显示空状态）
    console.error(e)
  } finally {
    loading.value = false
  }
})

// 点击收藏
async function onFav(id: number) {
  try {
    await addFavorite(id)
    alert('收藏成功')
  } catch {
    // 失败提示已在拦截器处�?  }
}
```

### 9.9 axios 完整流程总结

```
1. 组件�?fetchHotelList()
   �?2. request.get('/hotels')  （api/hotel.ts�?   �?3. axios 实例发出请求，baseURL 拼成 /api/hotels  （api/request.ts�?   �?4. 【请求拦截器】自动加 token
   �?5. �?vite 代理转发到后�?http://localhost:8080/hotels  （vite.config.ts�?   �?6. 后端返回 { code:200, data:[...], message:'ok' }
   �?7. 【响应拦截器】判�?code，取�?data 字段
   �?8. 组件拿到干净�?Hotel[] 数据
```

> 💡 每一层各司其职：vite.config.ts 管跨域、request.ts 管公共逻辑、hotel.ts 管业务接口、组件管显示�?
---

## 10. TypeScript �?Vue 里的用法

> **对照文件**：`types.ts`、所�?`.vue` 文件�?`<script setup lang="ts">`

### 10.1 为什么要�?TypeScript�?
JavaScript �?*动态类�?*，变量可以随时变类型，容易出 bug�?```js
// JS：不报错，但运行时炸
const price = '100'
console.log(price * 2)   // NaN！字符串乘法
```

TypeScript �?JS 上加�?*类型检�?*�?*写代码时**就能发现错误�?```ts
// TS：写的时候就报错
const price: string = '100'
console.log(price * 2)   // �?编辑器红线：string 不能�?```

好处�?1. **提前发现 bug**（不用等运行时）
2. **代码提示更智�?*（输�?`hotel.` 会列出所有字段）
3. **重构更安�?*（改个字段名，所有用到的地方都报错提醒）

### 10.2 基础类型

```ts
// 基础类型
let name: string = '张三'
let age: number = 18
let isOK: boolean = true

// 数组
let list: number[] = [1, 2, 3]
let list2: Array<string> = ['a', 'b']

// 联合类型（可以是多种类型之一�?let id: string | number = 123
id = 'abc'   // 也行

// 字面量类型（只能是固定值）
type Status = 'active' | 'inactive' | 'banned'
let s: Status = 'active'   // 只能是这三个值之一
```

### 10.3 interface �?type —�?描述对象形状

> **对照文件**：`types.ts`

**interface**（接口）：描述对象有哪些字段、什么类�?```ts
export interface Hotel {
  id: number
  name: string
  price: number
  facilities: string[]     // 字符串数�?  address?: string         // ? 表示可�?}
```

**type**（类型别名）：给类型起个名字
```ts
export type SortKey = 'recommend' | 'price-asc' | 'price-desc' | 'score-desc'

// 也能描述对象
type User = {
  name: string
  age: number
}
```

**interface vs type 怎么选？**
- 描述对象形状 �?�?`interface`（更直观，支持扩展）
- 联合类型、字面量类型 �?�?`type`
- 实际上两者大部分场景能互换，团队统一就行

### 8.4 泛型 —�?类型�?参数"

泛型就是"类型的变�?，让一个函�?类型能适应多种类型�?
```ts
// ref<T> 里的 T 就是泛型
const count = ref<number>(0)         // 指定存数�?const name = ref<string>('张三')      // 指定存字符串
const list = ref<Hotel[]>([])        // 指定�?Hotel 数组
```

不用泛型的话，TS 只能自己推导，有时推导不准。显式写 `<T>` 更保险�?
### 8.5 �?.vue 文件里用 TS

```vue
<script setup lang="ts">
//         �?lang="ts" 告诉编译器用 TS

import { ref } from 'vue'
import type { Hotel } from '@/types'   // type 只导入类型，不打包进产物

// 1. 响应式变量带类型
const hotel = ref<Hotel | null>(null)   // 可能�?Hotel �?null

// 2. props 带类型（见第5章）
const props = defineProps<{
  hotel: Hotel
  showFavorite?: boolean
}>()

// 3. emits 带类型（见第5章）
const emit = defineEmits<{
  (e: 'search', keyword: string): void
}>()

// 4. 函数参数和返回值带类型
function formatPrice(price: number): string {
  return '¥' + price.toFixed(2)
}
</script>
```

**`import type` 是什么？**
```ts
import type { Hotel } from '@/types'   // �?只导入类型，编译后会被删�?import { Hotel } from '@/types'        // 普�?import，编译后保留（但 Hotel 是类型会报错�?```

只用来做类型注解的东西，�?`import type` 导入，能让打包体积更小�?
### 8.6 TS 实用技�?
**类型断言 `as`**：手动告�?TS"我知道这是什么类�?
```ts
const el = document.querySelector('#app') as HTMLDivElement
```

**非空断言 `!`**：告�?TS"这个值一定不�?null"
```ts
const hotel = list.find(h => h.id === id)!
// �?告诉 TS：别�?find 可能返回 undefined，我确定能找�?```

**可选链 `?.`**：前面是 null/undefined 就不报错，返�?undefined
```ts
const name = user?.profile?.name   // user �?profile �?null 就返�?undefined，不报错
```

**空值合�?`??`**：左边是 null/undefined 就用右边�?```ts
const name = inputName ?? '匿名'   // inputName �?null/undefined 时用 '匿名'
```

### 10.7 env.d.ts 的作�?
> **对照文件**：`src/env.d.ts`

```ts
declare module '*.vue' {
  import type { DefineComponent } from 'vue'
  const component: DefineComponent<{}, {}, any>
  export default component
}
```

`.vue` 不是 TS 原生支持的扩展名，TS 会报�?找不到模�?。这个声明文件告�?TS�?"遇到 `import xxx from 'xxx.vue'` 时，把它当成 Vue 组件类型"�?
---

## 11. 样式�?scoped

> **对照文件**：`styles/global.css`、各组件�?`<style scoped>`

### 11.1 `<style scoped>` —�?样式隔离

```vue
<template><div class="card">...</div></template>

<style scoped>
/* scoped：这里的样式只作用于当前组件，不会污染别的组�?*/
.card {
  background: white;
}
</style>
```

**原理**：Vue 编译时给当前组件的每个元素加一�?`data-v-xxx` 属性，CSS 选择器自动变�?`.card[data-v-xxx]`，所以只匹配当前组件�?
**好处**：组�?A 写了 `.card`，组�?B 也写�?`.card`，互不影响�?
### 11.2 什么时候不�?scoped�?
需要影�?*子组件内�?*�?*全局**时：

```vue
<!-- 全局样式（不�?scoped�?-->
<style>
body { margin: 0; }
</style>

<!-- 穿�?scoped 影响子组件（深度选择器） -->
<style scoped>
:deep(.child-class) {
  /* 能影响子组件内部�?.child-class */
}
</style>
```

### 11.3 CSS 变量 —�?统一管理主题�?
> **对照文件**：`global.css`

```css
:root {
  --color-primary: #287dfa;
  --color-text: #222;
}

/* 用的时�?*/
.btn {
  background: var(--color-primary);
  color: var(--color-text);
}
```

**好处**�?- 一处定义，全项目复�?- 改主题只�?`:root`，所有用到的地方都更�?- �?SCSS 变量更轻量（不用编译，浏览器原生支持�?
### 11.4 BEM 命名法（本项目用的）

本项�?CSS 类名遵循 **BEM**（Block Element Modifier）规范：

```
.card                �?Block（块）：独立的组�?.card__cover         �?Element（元素）：块的一部分，双下划�?.card__cover--active �?Modifier（修饰）：状态变体，双短横线
```

例子（来�?HotelCard.vue）：
```css
.card { }              /* 卡片本体 */
.card__cover { }       /* 卡片的封�?*/
.card__body { }        /* 卡片的内容区 */
.card__tag { }         /* 标签 */
```

好处：看类名就知道它属于哪个组件、是哪一部分，避免冲突�?
### 11.5 �?JS 里用 CSS 变量

```ts
// 读取
const color = getComputedStyle(document.documentElement)
  .getPropertyValue('--color-primary')

// 设置（动态改主题�?document.documentElement.style.setProperty('--color-primary', '#ff0000')
```

---

## 12. 工程化配置：代理 / 路径别名 / 环境变量

> **对照文件**：`vite.config.ts`、`src/api/hotel.ts`
> 这一章讲项目级配置，都是真实开发必懂的�?
### 10.1 为什么需要开发服务器代理�?
#### 跨域问题怎么来的

浏览器有**同源策略**：协议、域名、端口任一不同，就属于"跨域"，默认不让请求�?
```
前端�?  http://localhost:5173   （Vite 开发服务器�?后端�?  http://localhost:8080   （Spring Boot / Node 等）
            �?端口不同 �?跨域！浏览器会拦截响�?```

#### 代理的原�?
前端**不直接请求后�?*，而是请求**自己的开发服务器**�?173），由开发服务器（运行在 Node 环境�?*不受浏览器同源策略限�?*）转发给后端�?
```
浏览�?5173) ──请求 /api/hotels──> Vite开发服务器 ──转发──> 后端(8080)
     �?                             (Node环境)                    �?     �?<──────────────── 返回数据 <────────────── 返回数据 <──────�?     �?     �?对浏览器来说，全程都在和 5173 通信，没有跨�?```

### 10.2 配置代理（vite.config.ts�?
```ts
export default defineConfig({
  server: {
    port: 5173,
    proxy: {
      // 规则一：以 /api 开头的请求，转发到本地后端
      '/api': {
        target: 'http://localhost:8080',   // 后端真实地址
        changeOrigin: true,                 // 改写 Host 头（�?10.3�?        rewrite: (p) => p.replace(/^\/api/, ''),  // 去掉 /api 前缀（见 10.4�?      },

      // 可以配多个规则（不同后端/不同服务�?      '/mock': {
        target: 'https://mock.example.com',
        changeOrigin: true,
        rewrite: (p) => p.replace(/^\/mock/, ''),
      },
    },
  },
})
```

**匹配规则**：浏览器请求�?URL **以什么开�?*，就走哪条代理�?- `fetch('/api/hotels')` �?�?`/api` 开�?�?走第一条规�?- `fetch('/api/user/1')` �?�?`/api` 开�?�?走第一条规�?- `fetch('https://other.com/x')` �?不以 `/api` �?`/mock` 开�?�?**不走代理，原样发出去**

### 12.3 `changeOrigin: true` 是干嘛的�?
控制是否把请求头里的 **Host** 字段改成 target 的地址�?
```ts
'/api': {
  target: 'http://localhost:8080',
  changeOrigin: true,   // �?Host 头会变成 localhost:8080
}
```

| | 不设 / false | true |
|---|---|---|
| 后端收到�?Host | `localhost:5173`（前端地址�?| `localhost:8080`（后端地址�?|
| 后端反应 | 有的后端会拒绝（以为是伪造请求） | 正常 |

**经验法则**�?*默认�?`changeOrigin: true`**，几乎不会错�?
### 12.4 `rewrite` 是干嘛的�?
**改写转发给后端的路径**，常用来"去掉前缀"�?
```ts
'/api': {
  target: 'http://localhost:8080',
  rewrite: (p) => p.replace(/^\/api/, ''),
}
```

| | 前端请求 | 实际转发�?|
|---|---|---|
| `rewrite` 去掉 `/api` | `/api/hotels` | `http://localhost:8080/hotels` |
| 不写 `rewrite` | `/api/hotels` | `http://localhost:8080/api/hotels` |

**怎么判断要不要写�?*
- 看后端接口本身有没有 `/api` 前缀�?  - 后端接口�?`http://localhost:8080/hotels` �?要去�?`/api` �?**�?rewrite**
  - 后端接口�?`http://localhost:8080/api/hotels` �?保留 �?**不写 rewrite**

### 10.5 配好代理后，前端代码怎么调接口？

> **对照文件**：`src/api/hotel.ts`

**关键**：前端请求地址�?*相对路径** `/api/xxx`�?*不要写完整域�?*�?
```ts
// �?正确：写相对路径，走代理
const res = await fetch('/api/hotels')

// �?错误：写完整域名，绕过代理，会跨�?const res = await fetch('http://localhost:8080/hotels')
```

完整示例（`src/api/hotel.ts`）：
```ts
import type { Hotel } from '@/types'

export async function fetchHotelList(): Promise<Hotel[]> {
  // 走代理：/api/hotels -> 转发�?http://localhost:8080/hotels
  const res = await fetch('/api/hotels')
  if (!res.ok) {
    throw new Error(`获取酒店列表失败�?{res.status}`)
  }
  return res.json() as Promise<Hotel[]>
}

// POST 请求示例
export async function syncFavorite(hotelId: number, favorite: boolean) {
  await fetch('/api/favorites', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ hotelId, favorite }),
  })
}
```

组件里调用：
```ts
import { onMounted, ref } from 'vue'
import { fetchHotelList } from '@/api/hotel'

const list = ref<Hotel[]>([])
const loading = ref(false)
const error = ref('')

onMounted(async () => {
  loading.value = true
  try {
    list.value = await fetchHotelList()
  } catch (e) {
    error.value = (e as Error).message
  } finally {
    loading.value = false
  }
})
```

### 10.6 路径别名 `@`

```ts
resolve: {
  alias: {
    '@': path.resolve(__dirname, 'src'),   // @ 指向 src 目录
  },
}
```

```ts
// 两种写法等价
import HotelCard from '@/components/HotelCard.vue'
import HotelCard from '../../components/HotelCard.vue'   // 相对路径，层次深时难�?```

**好处**�?- 不用�?`../../` 数到眼花
- 移动文件时，`@/` 开头的导入不会断（只要被引文件不动�?
### 10.7 环境变量（补充）

真实项目常需�?开发环境用这个地址，生产环境用另一�?。Vite 支持 `.env` 文件�?
```
项目根目�?
├─ .env                # 所有环境都加载
├─ .env.development     # npm run dev 时加�?└─ .env.production      # npm run build 时加�?```

`.env.development` 内容（变量名必须�?`VITE_` 开头）�?```
VITE_API_BASE=/api
```

代码里读取：
```ts
const baseURL = import.meta.env.VITE_API_BASE   // '/api'
```

> 💡 代理只在**开发环�?*有效。生产环境一般用 Nginx 做反向代理，或后端配 CORS�?
### 10.8 调试代理：怎么看请求有没有走对�?
1. 打开浏览�?**F12 �?Network（网络）** 面板
2. 触发一次接口请�?3. 点开那条请求看：
   - **请求 URL** 应该�?`http://localhost:5173/api/hotels`（自己的地址�?   - **Response（响应）** 有数据说明代理通了
4. 如果请求 URL 是后端真实地址（如 `localhost:8080`），说明**没走代理**（检查路径前缀�?
**常见报错**�?| 现象 | 原因 |
|---|---|
| 请求 404 | 后端没这个接口，�?rewrite 写错 |
| 请求一�?pending | target 地址不对/后端没启�?|
| CORS 报错 | 没走代理（检�?URL 是不是后端的真实地址�?|
| 502 Bad Gateway | 后端服务没起�?|

---

## 13. 常见疑问 FAQ

### Q1: `<script setup>` 和普�?`<script>` 有什么区别？

| | `<script setup>` | `<script>` |
|---|---|---|
| 写法 | 顶层声明变量/函数即可 | �?`export default { data, methods }` |
| 暴露给模�?| 自动暴露 | 需�?return |
| 组件导入 | 直接用，不用注册 | 要写 `components: { xxx }` |
| 推荐 | �?Vue3 官方推荐 | 旧代码、特殊场�?|

### Q2: ref 的值什么时候写 `.value`�?
| 场景 | 写法 |
|---|---|
| `<script>` 里读/�?| `count.value`�?*必须**加） |
| `<template>` �?| `count`（自动解包，**不要**加） |
| 解构 props/composable 返回�?| 拿到的是 ref 本身，访问也�?`.value` |

### Q3: `@/xxx` 是什么？

`@` 是在 `vite.config.ts` 配的路径别名，指�?`src` 目录�?```ts
resolve: { alias: { '@': path.resolve(__dirname, 'src') } }
```
- `@/components/HotelCard.vue` = `src/components/HotelCard.vue`
- 好处：写起来短、移动文件时相对路径不容易坏

### Q4: v-if �?v-for 能一起用吗？

**不能**（且 Vue 风格检查会警告）�?
```html
<!-- �?错误：v-if �?v-for 在同一个元�?-->
<li v-for="user in users" v-if="user.active" :key="user.id">

<!-- �?正确：用 computed 先过�?-->
<li v-for="user in activeUsers" :key="user.id">
```
```ts
const activeUsers = computed(() => users.value.filter(u => u.active))
```

### Q5: 组件怎么命名�?
- **文件�?*：PascalCase，如 `HotelCard.vue`
- **组件�?*：和文件名一致，`HotelCard`
- **使用�?*：`<HotelCard />`（推荐）�?`<hotel-card />`

**避免**�?HTML 原生标签名做组件名（�?`Header`、`Button`），会和原生冲突，加前缀�?`AppHeader`�?
### Q6: 为什�?`import type`�?
```ts
import type { Hotel } from '@/types'   // �?只导入类型，编译后被删除
import { Hotel } from '@/types'        // Hotel �?interface，运行时不存在，普�?import 会出�?```

凡是用在类型注解位置（`ref<Hotel>`、`: Hotel`、`defineProps<{...}>`）的，都�?`import type`�?
### Q7: 数据从哪来？怎么接后端接口？

本项目用的是 `src/data/mockData.ts` 里的假数据。真实项目用 `fetch` �?`axios`�?
```ts
import { ref, onMounted } from 'vue'
import type { Hotel } from '@/types'

const hotelList = ref<Hotel[]>([])

onMounted(async () => {
  // 真实接口请求（本项目没连后端，这里只是演示）
  const res = await fetch('/api/hotels')
  hotelList.value = await res.json()
})
```

### Q8: 报错 "Cannot find module './xxx.vue'"�?
检�?`src/env.d.ts` 是否存在，内容是否有 `declare module '*.vue'`（见 10.7）�?
### Q9: 如何调试 Vue�?
1. **浏览�?Vue Devtools 插件**：查看组件树、状态、路由（强烈推荐�?2. **`console.log`**：简单粗�?3. **VS Code + Volar 插件**：代码提示、类型检�?
### Q10: 接下来该学什么？

学完本项目后，建议按顺序学：
1. **axios** —�?HTTP 请求库（本项�?`api/hotel.ts` 用的是原�?fetch，axios 功能更全�?2. **Element Plus / Ant Design Vue** —�?UI 组件�?3. **Vitest** —�?单元测试
4. **SSR / Nuxt** —�?服务端渲�?5. **Pinia 进阶** —�?持久化插件（pinia-plugin-persistedstate）、模块化拆分

---

## 🎯 知识�?�?文件 对照速查�?
| 想看什�?| 打开哪个文件 |
|---|---|
| 最小可运行的组�?| `components/CounterDemo.vue` |
| props（父传子�?| `HotelCard.vue` �?`defineProps` + `HomeView.vue` �?`:hotel` |
| emit（子传父�?| `SearchBar.vue` �?`defineEmits` + `HomeView.vue` �?`@search` |
| emit 多参�?| `MultiEmitDemo.vue`（首页有交互演示�?|
| v-model 组件 | `FilterBar.vue` + `HomeView.vue` �?`v-model="filter"` |
| slot 插槽（三种全�?| `SlotDemo.vue` + `HomeView.vue` �?`#header`/`#item`/`#footer` |
| computed 计算属�?| `HomeView.vue` �?`filteredHotels` |
| watch 侦听�?| `HomeView.vue` 末尾 |
| ref 响应�?| `CounterDemo.vue` |
| v-for 循环 | `HomeView.vue` 的酒店列�?|
| v-if 条件渲染 | 各组件的空状态判�?|
| 路由配置 | `router/index.ts` |
| 路由 meta 额外信息 | `router/index.ts` �?`meta` 字段 + `beforeEach` 守卫 |
| `<router-link>` | `AppHeader.vue` |
| 编程式跳�?| `HomeView.vue` �?`router.push` |
| 路由跳转+传参实战 | `HomeView.vue` �?`goToRouteInfo` �?`RouteInfoView.vue`（含返回�?|
| �?query/params/state 三种传参 | `HomeView.vue` 演示�?�?`RouteParamDemoView.vue` |
| 读路由参�?| `RouteInfoView.vue` / `HotelDetailView.vue` �?`route.params.id` |
| composable 复用 | `composables/useFavorites.ts` |
| �?Pinia 状态管�?| `stores/favoriteStore.ts` + `components/PiniaDemo.vue`（首页有交互演示�?|
| TypeScript 类型 | `types.ts` |
| 全局样式/CSS变量 | `styles/global.css` |
| 接口请求封装（axios） | `api/request.ts`（实例+拦截器）+ `api/hotel.ts`（业务接口） |
| 代理配置 / 跨域解决 | `vite.config.ts` 的 `server.proxy` |
| 路径别名 `@` | `vite.config.ts` �?`resolve.alias` |

---

## 📖 建议学习路线

```
�?天：读懂项目结构
  index.html �?main.ts �?App.vue �?理解"页面怎么跑起�?

�?天：模板 + 响应�?  CounterDemo.vue（最小组件）
  �?HomeView.vue（看 v-for/v-if/computed/watch�?
�?天：组件通信 �?  HotelCard.vue（props + emit + slot 三件套）
  �?SearchBar.vue（emit 单参数）
  �?MultiEmitDemo.vue（emit 多参数）
  �?FilterBar.vue（v-model�?  �?SlotDemo.vue（三种插槽：默认/具名/作用域）

�?天：路由
  router/index.ts �?AppHeader.vue（router-link�?  �?RouteInfoView.vue（跳�?传参+返回，极简教学版）
  �?HotelDetailView.vue（动态路由参数，完整业务版）

�?天：进阶
  useFavorites.ts（composable 复用�?  �?favoriteStore.ts + PiniaDemo.vue（Pinia 状态管理，�?composable 对比�?  �?types.ts（TypeScript 类型�?  �?自己加一个新功能试试（比�?最近浏�?列表�?```

**最重要的一条建�?*�?*边读边改**。看懂一个知识点后，立刻在代码里改一改、加一加，看页面变化，比纯看十遍都强�?
---

> 🎉 祝学习顺利！遇到问题先看�?FAQ，再看控制台报错，大部分问题都能自己解决�?



