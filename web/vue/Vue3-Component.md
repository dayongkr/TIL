# Vue3 Component

> ref. [Component Basics](https://v3.vuejs.org/guide/component-basics.html) + Props, Component Events, Lifecycle Hooks

## Components Basics

natvie Web Component와 같이 Vue도 컴포넌트 기반으로 UI를 구성한다. Vue와 native간 차이는 [링크](https://vuejs.org/guide/extras/web-components.html)를 참고하자!

### Component 사용하기

```html
<script setup>
  imponrt HelloWorld from './components/HelloWorld.vue'
</script>
```

위와 같이 script 태그 안에서 원하는 child component를 불러오고 template 태그에 child component를 사용하면 된다.

> import는 해당 파일의 default export를 가져오고 script 옆에 setup을 추가하면 template에서 해당 component를 사용할 수 있다.

해당 방법은 local component를 사용하는 방법이고 global registartion을 통해 모든 component에서 사용할 수 있도록 할 수도 있다.

Component는 각자만의 data, methods등을 가지기 때문에 같은 Component를 여러 번 사용해도 각자의 상태를 가지고 있다.

### Props

Composition API에서는 defineProps이라는 함수를 통해 props를 정의할 수 있다. defineProps는 compile-time macro로 script setup에서만 사용할 수 있다.

```html
<script setup>
  defineProps(["title", "likes"]);
</script>

<template>
  <h1>{{ title }}</h1>
  <p>{{ likes }}</p>
</template>
```

해당 함수는 component로 전달된 props를 반환하기 때문에 바로 template에서 사용할 수 있다. 과제에서는 이 방법 말고 option API에서 사용하는 방법을 사용했다.

더 자세한 내용은 Props 섹션에서 추가로 다룬다.

### Emitting Events

Composition API에서는 defineEmits라는 함수를 통해 event를 정의할 수 있다. defineProps와 마찬가지로 compile-time macro로 script setup에서만 사용할 수 있다.

```html
<script setup>
  defineEmits(["update:likes"]);
</script>

<template>
  <button @click="$emit('update:likes', likes + 1)">Like</button>
</template>
```

위 코드는 button을 클릭하면 update:likes라는 event를 emit하는 코드이다. 이 event를 parent component에서 받아서 likes를 업데이트 할 수 있다.

```html
<template>
  <HelloWorld :title="title" :likes="likes" @update:likes="likes = $event" />
</template>
```

### Dynamic Components

:is directive를 사용하면 동적으로 component를 바꿀 수 있다.

```html
<template>
  <component :is="tabs[currentTabComponent]"></component>
</template>

<script setup>
  const currentTabComponent = ref("tab-home");
  const tabs = {
    "tab-home": {
      template: "<div>Home component</div>",
    },
    "tab-posts": {
      template: "<div>Posts component</div>",
    },
    "tab-archive": {
      template: "<div>Archive component</div>",
    },
  };
</script>
```

위 코드는 currentTabComponent의 값에 따라 동적으로 component를 바꾸는 코드이다.

### Element Placement Restrictions

ul, ol, table등과 같은 html elements는 안에 어떤 것이 있을 수 있는지 제한이 있다. 따라서 이런 element들 안에 component를 넣을 때는 is directive를 사용해야 한다.

```html
<ul>
  <li is="my-component"></li>
</ul>
```
