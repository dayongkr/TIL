# Vue 3 Composition API

> Vue3 완벽 마스터: 기초부터 실전까지 - "기본편" 중 섹션 3의 내용과 Vue 3 공식 문서를 참고하여 작성했다.

## Composition API

- 반응형 API (Reactivity API)
  - ref, reactive 등
  - 반응하는 데이터와 관련된 API 세트
- 라이프 사이클 훅 (Lifecycle Hooks)
  - onMounted, onUpdated 등
- 종속성 주입 (Dependency Injection)
  - provide, inject

### 반응형 API (Reactivity API)

일반 변수로 선언된 데이터는 반응성이 없어서 데이터가 변경되어도 화면이 갱신되지 않는다. 화면에 갱신하기 위해서는 Reactivity API를 사용해야 한다. 예를들어 ref 함수를 사용하면 반응성이 있는 데이터를 만들 수 있다.

```js
const count = ref(0);
```

이외에도 이러한 반응형 데이터를 다루기 위한 다양한 API가 존재한다.

#### reactive & ref

- reactive
  - 반응성이 있는 객체를 만든다.
  - e.g. const state = reactive({ count: 0 })
  - es6 문법인 destructuring을 사용하면 반응형을 잃게 된다.
- ref
  - ref는 reactive의 `primitive type` 버전이다.
  - ref는 mutable object를 반환한다.
  - 따라서 setup 함수 내에서 ref를 사용할 때는 `.value`를 사용해야 한다.
  - 다만 몇 가지 경우에는 `.value`를 사용하지 않아도 된다.
    - template에서 ref를 사용할 때
    - ref -> reactive Object 안에 넣었을 때
- toRefs & toRef
  - 이를 사용하면 reactive object를 ref로 변환할 수 있다.
  - 따라서 destructuring을 사용해도 반응성을 유지할 수 있다.
  - toRef는 reactive object의 특정 property를 ref로 변환한다.
  - e.g. const { count } = toRefs(state), const count = toRef(state, 'count')
- readonly
  - 반응형 객체를 읽기 전용으로 만든다.

> 영상에 나왔던 Reactivity Transform은 Deprecated 되었다. [참조](https://github.com/vuejs/rfcs/discussions/369#discussioncomment-5059028)

#### Computed

중괄호(mustache) 안에는 js 표현식이 사용 가능하다고 했는데 이는 한 줄로 표현할 수 있는 간단한 표현식만 사용할 수 있다. 따라서 복잡한 로직을 사용하고 싶으면 computed를 사용해야 한다.

```js
const count = ref(1);
const double = computed(() => count.value * 2);
...
<p>{{count}}</p> // 1
<p>{{double}}</p> // 2
```

#### Watch

반응형 데이터의 변화를 감지하기 위해 watch를 사용할 수 있다.

```js
const count = ref(1);
watch(count, (newVal, oldVal) => {
  console.log(newVal, oldVal);
});
```

사용 방법은 인자에 반응형 데이터와 콜백 함수를 넣어주면 된다. 콜백 함수의 첫 번째 인자는 새로운 값이고 두 번째 인자는 이전 값이다. immediate 옵션을 주면 콜백 함수를 최초에 한 번 실행할 수 있다.

> 반응형 데이터에는 ref, reactive, computed, getter, array 타입이 될 수 있다.

##### 객체를 watch하는 경우

객체를 watch하면 객체의 모든 프로퍼티를 감시한다. 또한 new value와 old value는 객체의 참조이기 때문에 객체의 프로퍼티가 변경되어도 new value와 old value는 같다.

만약에 reactive 안에 있는 객체를 감시하면 해당 객체의 프로퍼티가 변경되었을 땐 콜백 함수가 실행되지 않고 해당 객체가 아예 다른 객체로 변경되었을 때 콜백 함수가 실행된다.

#### watchEffect

watchEffect는 콜백 함수 내에서 사용된 모든 반응형 데이터를 감시한다. 따라서 콜백 함수 내에서 사용된 반응형 데이터가 변경되면 콜백 함수가 실행된다. 또한 기본적으로 콜백 함수를 최초에 한 번 실행한다.

#### computed vs watch

- computed
  - 종속 관계로 인해 다시 계산되어야 하는 값에 사용한다.
- watch
  - 변경 시점에 특정 액션을 수행해야 하는 경우에 사용한다.

### 라이프 사이클 훅 (Lifecycle Hooks)

컴퍼넌트가 생성될 때 또는 갱신될 때 특정 로직을 실행할 수 있다. 이러한 로직을 라이프 사이클 훅이라고 한다. Vue 3에서는 라이프 사이클 훅을 사용하기 위해 `on` 접두사를 사용한다.

![라이프 사이클](./imgs/2023-04-25-20-35-41.png)

> 출처: [Vue 공식 문서](https://vuejs.org/guide/essentials/lifecycle.html#lifecycle-diagram)

예를 들어 component가 mount 되기 전 특정 로직을 실행하고 싶다면 `onMounted` 함수를 사용하면 된다.

```js
onMounted(() => {
  console.log("mounted");
});
```

computed는 마지막 반환값을 캐싱하고 있다가 함수 안에 있는 reactive dependecy를 추적해 변경 사항이 있을 때마다 다시 계산한다.

get과 set 함수를 통해 writable한 computed 함수를 만들 수 있다.

```js
const count = ref(1);
const double = computed({
  get: () => count.value * 2,
  set: (val) => {
    count.value = val / 2;
  },
});
double.value = 4;
...
<p>{{count}}</p> // 2
<p>{{double}}</p> // 4
```

### 종속성 주입 (Dependency Injection)

일단 강의에서는 스킵함

### Setup 함수

Composition API를 사용하기 위해서는 `setup` 함수를 사용해야 한다. `setup` 함수는 컴포넌트가 생성되기 전에 실행되는 함수이다.

해당 함수 내에서 반응형 데이터를 생성하거나 함수를 정의하기만 하는 게 아니라 이를 반환해줘야 template에서 사용할 수 있다.

해당 함수의 첫 번째 매개변수는 props이고 두 번째 매개변수는 context이다. 이 두가지는 나중에 알아본다고 한다.

## 디렉티브, 바인딩

### 디렉티브

directive는 v-로 시작하는 특수한 속성이다.

- v-text: textContent를 바인딩한다.
- v-html: innerHTML을 바인딩한다.
- v-show: display: none을 사용해서 렌더링을 하거나 하지 않는다.
- v-if: 조건부 렌더링을 한다.
- v-for: 배열이나 객체를 렌더링한다.
- v-on: 이벤트를 바인딩한다. (@로 축약해서 사용할 수 있다.)
- v-bind: 속성을 바인딩한다. (:로 축약해서 사용할 수 있다.)
- v-slot: slot을 바인딩한다. (#로 축약해서 사용할 수 있다.)
- v-model: 양방향 바인딩을 한다.
- v-pre: 컴파일을 하지 않는다.
- v-once: 한 번만 렌더링한다.
- v-cloak: 컴파일이 완료되기 전까지 표시되지 않는다.
  - 이를 사용해서 로딩이 끝난 후에 화면을 보여줄 수 있다.
- v-memo: 컴포넌트를 메모이징한다.
  - 배열 안에 있는 요소가 변경되면 새로 렌더링한다.

![디렉티브 문법](./imgs/2023-04-25-22-14-51.png)

> 출처: [Vue 공식 문서](https://vuejs.org/guide/essentials/template-syntax.html#directives)

디렉티브는 디렉티브의 이름, 인자, 수식어, 값으로 구성되어 있다.

### 조건부 렌더링 v-if

```js
<div v-if="isShow">True</div>
<div v-else>False</div>
...
setup() {
  const isShow = ref(true);
  return { isShow };
}
```

isShow가 true이면 첫 번째 div가 렌더링되고 false이면 두 번째 div가 렌더링된다. 이와 같이 v-if와 v-else(v-else-if)를 사용해서 조건부 렌더링을 할 수 있다.

여러개 태그를 조건부 렌더링하고 싶으면 template 태그를 사용하면 된다.

#### v-if vs v-show

show 디렉티브를 사용하면 조건부 렌더링을 할 수 있다. v-show는 display: none을 사용해서 렌더링을 하거나 하지 않는다.

v-if는 실제로 component를 생성하고 제거하는 반면 v-show는 display: none을 사용해서 렌더링을 하거나 하지 않는다. 따라서 v-if는 toggle cost가 높으므로 자주 변경이 있으면 v-show를 사용하는 것이 좋다.

#### v-if와 v-for

v-for와 같이 사용하는 것을 조심해야한다. v-if가 우선순위가 높아서 먼저 계산되기 때문에 원치 않은 결과가 나올 수 있다. 따라서 필터링된 배열을 사용하거나 template 태그에 v-for을 그 안에 있는 태그에는 v-if를 사용하면 된다.

### 목록 렌더링 v-for

#### 배열

```js
<ul>
  <li v-for="item in list" :key="item.id">{{item.name}}</li>
</ul>
...
setup() {
  const list = ref([
    { id: 1, name: "apple" },
    { id: 2, name: "banana" },
    { id: 3, name: "orange" },
  ]);
  return { list };
}
```

v-for을 사용해서 list에 있는 요소들을 렌더링할 수 있다. key를 사용해서 고유한 값을 지정해줘야한다. key가 없으면 node의 identity를 track 할 수 없어서 reuse를 할 수 없어 성능상 좋지 않기 때문에 사용이 강제된다.

#### 객체

```js
<ul>
  <li v-for="(value,key,index) in list" :key="index">{{index}} {{key}} {{value}}</li>
</ul>
...
setup() {
  const list = ref([
    { id: 1, name: "apple" },
    { id: 2, name: "banana" },
    { id: 3, name: "orange" },
  ]);
  return { list };
}
```

객체를 렌더링하고 싶으면 위와 같이 value, key, index를 사용해서 렌더링할 수 있다. 배열도(item, index)와 같이 사용할 수 있다.

### 이벤트 처리 v-on

```js
<button @click="handleClick">Click</button>
...
setup() {
  const handleClick = () => {
    console.log("click");
  };
  return { handleClick };
}
```

v-on은 @으로 단축해서 사용할 수 있다.

이벤트 객체 접근은 인라인에서 $event를 사용해서 접근할 수 있다. 기본적으로 이벤트 객체는 첫번째 인자로 넘겨 받는다.

```js
<button @click="handleClick($event)">Click</button>
...
setup() {
  const handleClick = (e) => {
    console.log(e);
  };
  return { handleClick };
}
```

#### 이벤트 수식어(modifier)

event.preventDefault()와 같은 기능을 하는 수식어를 사용할 수 있다.

- .stop: event.stopPropagation()과 같다.
  - event 전파를 막는다.
- .prevent: event.preventDefault()와 같다.
  - 기본 동작을 막는다.
- .capture: 이벤트 캡쳐링을 사용한다.
- .self: event.target이 자기 자신일 때만 이벤트가 발생한다.
- .once: 이벤트가 한 번만 발생한다.
- .passive: event.preventDefault()를 호출하지 않는다.
  - 스크롤 성능을 향상시키기 위해 사용한다.
  - [참조](https://developer.mozilla.org/en-US/docs/Web/API/EventTarget/addEventListener#improving_scrolling_performance_with_passive_listeners)

> 버블링: 자식 요소에서 이벤트가 발생하면 부모 요소로 이벤트가 전파되는 것, 캡쳐링: 부모 요소에서 자식 요소로 이벤트가 전파되는 것 [참조](https://javascript.info/bubbling-and-capturing)

#### 키 수식어

특정 키를 눌렀을 때 이벤트를 발생시킬 수 있다.

- .enter
- .tab
- .delete
  - delete, backspace 키 모두 수신
- .esc
- .space
- .up
- .down
- .left
- .right
- .ctrl
- .alt
- .shift
- .meta
  - mac에서 command 키를 의미한다.
  - window에서 window 키를 의미한다.

```js
<input @keyup.enter="handleEnter" />
```

.exact를 사용하면 해당 키만 눌러졌을 때 이벤트가 발생한다.

> 마우스 버튼도 수식어가 있다. (.left, .right, .middle)

### Template 문법 및 바인딩

{{}} 와 같이 중괄호으로 사용해 데이터를 바인딩하는 것을 기본으로 한다. 만약에 일회성으로 데이터를 바인딩하고 싶다면 `v-once` 디렉티브를 사용하면 된다. 해당 중괄호 안에는 javascript 표현식을 사용할 수 있다.

만약에 속성에 데이터를 바인딩하고 싶다면 `v-bind` 디렉티브를 사용하면 된다. `v-bind` 디렉티브는 `:`로 축약해서 사용할 수 있다. 또한 반응형 데이터(객체)에 속성을 설정하고 v-bind에 대입하면 해당 속성이 바인딩된다.

```html
<template>
  <input v-bind:value="message" />
  <input :value="message" />
  <input v-bind="option" />
</template>

<script>
  setup() {
    const message = ref("hello");
    const option = ref({ value: "hello" });
    return { message, option };
  }
</script>
```

style은 객체를 사용해서 바인딩할 수 있다. 또한 배열을 사용해서 여러 개의 style을 적용할 수 있다. :style을 사용해서 바인딩을 하면된다.

### Class & Style 바인딩

class는 다른 속성과 다르게 바인딩한 부분과 바인딩하지 않은 부분이 합쳐져서 적용된다.

```js
<div class="wrapper" :class="{active: isActive}"></div>
<button @click="isActive = !isActive">Toggle</button>
...
setup() {
  const isActive = ref(true);
  return { isActive };
}
```

### 양방향 바인딩 v-model

```js
<input v-model="message" />
```

v-model을 사용해서 양방향 바인딩을 할 수 있다. v-model은 v-bind와 v-on을 합친 디렉티브이다.

따라서 html 요소에 따라 다른 속성과 이벤트를 사용한다.

- input(type="text"), textareat: value 속성과 input 이벤트
- checkbox, radio: checked 속성과 change 이벤트
- select(multiple): value 속성과 change 이벤트

#### v-model 수식어

- .lazy: focus를 잃었을 때 변경된 값을 바인딩한다.
  - change 이벤트가 발생할 때까지 기다린다.
- .number: 숫자 타입으로 바인딩한다.
  - parseFloat를 사용해서 변환이 가능하면 변환한다.
  - 따라서 가능하지 않으면 original value를 사용한다.
  - type="number"로 자동으로 변환된다.
- .trim: 입력값의 앞뒤 공백을 제거한다.
